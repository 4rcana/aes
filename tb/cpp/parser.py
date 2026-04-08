# Parser usage example:
# python parse.py KAT_AES/ECB*128.rsp > vectors.h

import sys
import os
import re

def hex_to_chunks(hex_str):
    """Splits hex string into 32-bit words with proper formatting."""
    # Remove any non-hex characters
    hex_str = "".join(c for c in hex_str if c in "0123456789abcdefABCDEF")
    
    # Generate 32-bit chunks
    chunks = [f"0x{hex_str[i:i+8]}u" for i in range(0, len(hex_str), 8)]
    
    # Format with newlines if the key is long (AES-192 or 256)
    if len(chunks) > 4:
        first_half = ", ".join(chunks[:4])
        second_half = ", ".join(chunks[4:])
        return "{" + first_half + ",\n        " + second_half + "}"
    
    return "{" + ", ".join(chunks) + "}"

def parse_files(file_list):
    # Mapping for exact requested casing
    TYPE_MAP = {
        "VARTXT": "VarTxt",
        "VARKEY": "VarKey",
        "GFSBOX": "GFSbox",
        "KEYSBOX": "KeySbox",
        "MCT": "MCT"
    }

    # Print C++ Header and Struct Definition
    print("#ifndef AES_VECTORS_H")
    print("#define AES_VECTORS_H")
    print("#include <stdint.h>")
    print("")
    print("struct TestVector {")
    print("    uint32_t key[8]; // Supports up to AES-256")
    print("    uint32_t pt[4];  // Plaintext")
    print("    uint32_t ct[4];  // Ciphertext")
    print("    const char* name;")
    print("};")
    print("")
    print("static const TestVector vectors[] = {")

    total_vectors = 0

    for file_path in file_list:
        if not os.path.exists(file_path):
            continue

        filename = os.path.basename(file_path)
        mode = "AES"
        test_type = "KAT"
        key_len = ""
        direction = "Enc"
        file_vectors = 0

        # --- Pass 1: Scan for Metadata (STRICTLY in comments) ---
        mode_found = False
        type_found = False
        len_found = False

        with open(file_path, 'r') as f:
            for line in f:
                stripped = line.strip()
                if not stripped: continue
                
                # If we hit a line that isn't a comment, stop scanning metadata.
                # This prevents matching hex keys (which follow metadata) as modes.
                if not stripped.startswith('#'):
                    if '[' in stripped or '=' in stripped:
                        break
                    continue

                u_line = stripped.upper()
                
                # Detect Mode (First whole-word match wins)
                if not mode_found:
                    m_match = re.search(r"\b(ECB|CBC|CFB128|OFB|GCM|CTR)\b", u_line)
                    if m_match: 
                        mode = m_match.group(1)
                        mode_found = True
                
                # Detect Test Type
                if not type_found:
                    t_match = re.search(r"\b(VARTXT|VARKEY|GFSBOX|KEYSBOX|MCT)\b", u_line)
                    if t_match: 
                        test_type = TYPE_MAP.get(t_match.group(1), t_match.group(1))
                        type_found = True

                # Detect Key Length
                if not len_found:
                    k_match = re.search(r"(?:KEY LENGTH|L\s*[:=])\s*(\d+)", u_line)
                    if k_match: 
                        key_len = k_match.group(1)
                        len_found = True

        # Filename fallback if key length not found in headers
        if not key_len:
            fn_match = re.search(r"(128|192|256)", filename)
            if fn_match: key_len = fn_match.group(1)

        # --- Pass 2: Extract Data ---
        with open(file_path, 'r') as f:
            current_vec = {}
            for line in f:
                line = line.strip()
                if not line or line.startswith('#'): continue
                
                u_line = line.upper()
                if "[ENCRYPT]" in u_line: direction = "Enc"
                elif "[DECRYPT]" in u_line: direction = "Dec"
                
                # Section headers like [L=192] can change key length mid-file
                klen_sect = re.search(r"\[L\s*=\s*(\d+)\]", u_line)
                if klen_sect: key_len = klen_sect.group(1)

                if '=' in line:
                    parts = line.split('=', 1)
                    key = parts[0].strip().upper()
                    val = parts[1].strip()
                    current_vec[key] = val
                    
                    if all(k in current_vec for k in ["KEY", "PLAINTEXT", "CIPHERTEXT"]):
                        # Final bit-length check based on actual key data
                        this_key_len = key_len
                        if not this_key_len:
                            this_key_len = str(len(current_vec['KEY']) * 4)

                        count = current_vec.get("COUNT", file_vectors)
                        label = f"{mode}{test_type}{this_key_len}"
                        
                        print(f"    // From {filename}")
                        print(f"    {{ {hex_to_chunks(current_vec['KEY'])},")
                        print(f"      {hex_to_chunks(current_vec['PLAINTEXT'])},")
                        print(f"      {hex_to_chunks(current_vec['CIPHERTEXT'])},")
                        print(f"      \"{label} {direction} COUNT={count}\" }},")
                        
                        file_vectors += 1
                        total_vectors += 1
                        del current_vec["PLAINTEXT"]
                        del current_vec["CIPHERTEXT"]

    print("};")
    print(f"\nstatic const int NUM_VECTORS = {total_vectors};")
    print("")
    print("#endif // AES_VECTORS_H")
    print(f"DEBUG: Total vectors found: {total_vectors}", file=sys.stderr)

if __name__ == "__main__":
    files = sys.argv[1:]
    if not files:
        print("Usage: python3 parse_aes.py *.rsp > vectors.h")
    else:
        parse_files(files)
