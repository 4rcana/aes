import sys
import os
import re

def hex_to_chunks(hex_str, limit):
    """Splits hex string into 32-bit words with proper C++ formatting."""
    hex_str = "".join(c for c in hex_str if c in "0123456789abcdefABCDEF")
    chunks = [f"0x{hex_str[i:i+8]}u" for i in range(0, len(hex_str), 8)]
    
    # Pad to limit
    if len(chunks) < limit:
        chunks += ["0x00000000u"] * (limit - len(chunks))
    else:
        chunks = chunks[:limit]
    
    if limit > 4:
        return "{" + ", ".join(chunks[:4]) + ",\n        " + ", ".join(chunks[4:]) + "}"
    return "{" + ", ".join(chunks) + "}"

def parse_files(file_list):
    TYPE_MAP = {
        "VARTXT": "VarTxt", "VARKEY": "VarKey", 
        "GFSBOX": "GFSbox", "KEYSBOX": "KeySbox", 
        "MCT": "MCT", "MMT": "MMT"
    }
    
    print("#ifndef AES_VECTORS_H\n#define AES_VECTORS_H\n#include <stdint.h>\n")
    print("struct TestVector {")
    print("    uint32_t key[8];")
    print("    uint32_t iv[4];")
    print("    uint32_t pt[4];")
    print("    uint32_t ct[4];")
    print("    const char* name;")
    print("};\n")
    print("static const TestVector vectors[] = {")

    total_vectors = 0
    for file_path in file_list:
        if not os.path.exists(file_path):
            continue

        filename = os.path.basename(file_path)
        mode, test_type, direction = "AES", "KAT", "Enc"
        
        # --- Pass 1: Scan for Metadata (Mode and Test Type) ---
        with open(file_path, 'r') as f:
            for line in f:
                u = line.strip().upper()
                if not u: continue
                if "ECB" in u: mode = "ECB"
                if "CBC" in u: mode = "CBC"
                t = re.search(r"\b(VARTXT|VARKEY|GFSBOX|KEYSBOX|MCT|MMT)\b", u)
                if t: test_type = TYPE_MAP.get(t.group(1), t.group(1))
                # Stop if we hit data
                if u.startswith('[ENCRYPT]') or u.startswith('COUNT'): break

        # --- Pass 2: Extract Data ---
        with open(file_path, 'r') as f:
            current_vec = {"IV": "0"*32}
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
                        k_v, p_v, c_v, iv_v = current_vec["KEY"], current_vec["PLAINTEXT"], current_vec["CIPHERTEXT"], current_vec["IV"]
                        
                        # CALCULATION FIX: Determine bit length from the actual key string
                        # 32 hex chars = 128 bits, 48 = 192 bits, 64 = 256 bits
                        actual_bits = len(k_v) * 4
                        
                        num_blocks = 1 if test_type == "MCT" else (len(p_v) // 32)
                        
                        for b in range(num_blocks):
                            sub_p = p_v[b*32:(b+1)*32]
                            sub_c = c_v[b*32:(b+1)*32]
                            actual_iv = iv_v if b == 0 else "0"*32 
                            
                            # Use actual_bits in the label
                            label = f"[{test_type}] {mode}{actual_bits} {direction} C{current_vec.get('COUNT','0')} B{b}"
                            
                            print(f"    {{ {hex_to_chunks(k_v, 8)},")
                            print(f"      {hex_to_chunks(actual_iv, 4)},")
                            print(f"      {hex_to_chunks(sub_p, 4)},")
                            print(f"      {hex_to_chunks(sub_c, 4)},")
                            print(f"      \"{label}\" }},")
                            total_vectors += 1
                        
                        del current_vec["PLAINTEXT"]
                        del current_vec["CIPHERTEXT"]

    print("};")
    print(f"\nstatic const int NUM_VECTORS = {total_vectors};")
    print("#endif")
    print(f"DEBUG: Processed {total_vectors} vectors.", file=sys.stderr)

if __name__ == "__main__":
    parse_files(sys.argv[1:])
