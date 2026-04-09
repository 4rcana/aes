import sys
import os
import re

def hex_to_chunks(hex_str, limit):
    """
    Splits hex string into 32-bit words.
    Pads with 0x00000000u up to the 'limit' (4 for data, 8 for keys).
    """
    # Remove any non-hex characters
    hex_str = "".join(c for c in hex_str if c in "0123456789abcdefABCDEF")
    
    # Generate 32-bit chunks
    chunks = [f"0x{hex_str[i:i+8]}u" for i in range(0, len(hex_str), 8)]
    
    # Pad or truncate to the specified limit
    if len(chunks) < limit:
        chunks += ["0x00000000u"] * (limit - len(chunks))
    else:
        chunks = chunks[:limit]
    
    # Formatting: Put a newline after 4 words for readability if it's a long array (key[8])
    if limit > 4:
        first_half = ", ".join(chunks[:4])
        second_half = ", ".join(chunks[4:])
        return "{" + first_half + ",\n        " + second_half + "}"
    
    return "{" + ", ".join(chunks) + "}"

def parse_files(file_list):
    TYPE_MAP = {
        "VARTXT": "VarTxt", "VARKEY": "VarKey", 
        "GFSBOX": "GFSbox", "KEYSBOX": "KeySbox", 
        "MCT": "MCT", "MMT": "MMT"
    }

    # Print C++ Header and Struct Definition
    print("#ifndef AES_VECTORS_H")
    print("#define AES_VECTORS_H")
    print("#include <stdint.h>")
    print("")
    print("struct TestVector {")
    print("    uint32_t key[8]; // Max size for AES-256")
    print("    uint32_t pt[4];  // Always 128-bit")
    print("    uint32_t ct[4];  // Always 128-bit")
    print("    const char* name;")
    print("};")
    print("")
    print("static const TestVector vectors[] = {")

    total_vectors = 0

    for file_path in file_list:
        if not os.path.exists(file_path):
            continue

        filename = os.path.basename(file_path)
        mode, test_type, key_len, direction = "AES", "KAT", "", "Enc"

        # --- Pass 1: Metadata strictly from comments ---
        with open(file_path, 'r') as f:
            for i, line in enumerate(f):
                line = line.strip()
                if not line.startswith('#'):
                    if line and ('[' in line or '=' in line): break
                    continue
                u = line.upper()
                m = re.search(r"\b(ECB|CBC|OFB|CFB128|CTR)\b", u)
                if m: mode = m.group(1)
                t = re.search(r"\b(VARTXT|VARKEY|GFSBOX|KEYSBOX|MCT|MMT)\b", u)
                if t: test_type = TYPE_MAP.get(t.group(1), t.group(1))
                k = re.search(r"(?:L\s*=\s*|LENGTH\s*)(\d+)", u)
                if k: key_len = k.group(1)

        # --- Pass 2: Extract Data ---
        with open(file_path, 'r') as f:
            current_vec = {}
            for line in f:
                line = line.strip()
                if not line or line.startswith('#'): continue
                
                u_line = line.upper()
                if "[ENCRYPT]" in u_line: direction = "Enc"
                elif "[DECRYPT]" in u_line: direction = "Dec"
                
                if '=' in line:
                    parts = line.split('=', 1)
                    key = parts[0].strip().upper()
                    val = parts[1].strip()
                    current_vec[key] = val
                    
                    if all(k in current_vec for k in ["KEY", "PLAINTEXT", "CIPHERTEXT"]):
                        k_v, p_v, c_v = current_vec["KEY"], current_vec["PLAINTEXT"], current_vec["CIPHERTEXT"]
                        
                        # MMT logic: split into 128-bit blocks. MCT/KAT: 1 block.
                        num_blocks = 1 if test_type == "MCT" else (len(p_v) // 32)
                        
                        for b in range(num_blocks):
                            sub_p = p_v[b*32:(b+1)*32]
                            sub_c = c_v[b*32:(b+1)*32]
                            label = f"[{test_type}] {mode}{key_len} {direction} C{current_vec.get('COUNT','0')} B{b}"
                            
                            print(f"    {{ {hex_to_chunks(k_v, 8)},") # Key limited to 8
                            print(f"      {hex_to_chunks(sub_p, 4)},") # PT limited to 4
                            print(f"      {hex_to_chunks(sub_c, 4)},") # CT limited to 4
                            print(f"      \"{label}\" }},")
                            total_vectors += 1
                        
                        # Keep key/count for files that reuse them
                        current_vec = {"KEY": k_v, "COUNT": current_vec.get("COUNT", "0")}

    print("};")
    print(f"\nstatic const int NUM_VECTORS = {total_vectors};")
    print("")
    print("#endif // AES_VECTORS_H")
    print(f"DEBUG: Processed {total_vectors} vectors.", file=sys.stderr)

if __name__ == "__main__":
    if len(sys.argv) < 2:
        print("Usage: python3 parser.py *.rsp > vectors.h")
    else:
        parse_files(sys.argv[1:])
