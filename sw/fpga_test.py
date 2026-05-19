import serial
import time
import sys

def slow_print(msg):
    """Helper to print without newlines immediately."""
    sys.stdout.write(msg)
    sys.stdout.flush()

def run_visual_test(port='/dev/ttyUSB1', baud=576000):
    try:
        ser = serial.Serial(port, baud, timeout=2)
        time.sleep(2) # Wait for Basys 3 reset
        ser.reset_input_buffer()

        # Test Vectors
        key_hex = "80000000000000000000000000000000"
        pt_hex  = "00000000000000000000000000000000"
        
        key_bytes = bytes.fromhex(key_hex)
        pt_bytes  = bytes.fromhex(pt_hex)

        print(f"------- Starting AES Test on {port} -------")

        # 1. SEND KEY
        print("\n[STEP 1] Sending KEY (Command 0x01 + 16 Bytes):")
        ser.write(b'\x01')
        slow_print("CMD(01) -> ")
        for b in key_bytes:
            ser.write(bytes([b]))
            slow_print(f"{b:02x} ")
            time.sleep(0.05)
        print(" | DONE")

        time.sleep(0.2) # Small gap between commands

        # 2. SEND PLAINTEXT
        print("\n[STEP 2] Sending PLAINTEXT (Command 0x02 + 16 Bytes):")
        ser.write(b'\x02')
        slow_print("CMD(02) -> ")
        for b in pt_bytes:
            ser.write(bytes([b]))
            slow_print(f"{b:02x} ")
            time.sleep(0.05)
        print(" | DONE")

        # 3. RECEIVE CIPHERTEXT
        print("\n[STEP 3] Waiting for CIPHERTEXT from FPGA...")
        slow_print("RECEIVE <- ")
        
        captured_hex = ""
        for i in range(16):
            # Read exactly one byte at a time
            byte_in = ser.read(1)
            if byte_in:
                hex_val = byte_in.hex()
                captured_hex += hex_val
                slow_print(f"{hex_val} ")
                time.sleep(0.1)
            else:
                print("\n[!] Timeout: FPGA stopped responding.")
                break
        
        # 4. VERIFICATION
        expected = "0edd33d3c621e546455bd8ba1418bec8"
        print(f"\n\n--- Final Result ---")
        print(f"Expected: {expected}")
        print(f"Got:      {captured_hex}")
        
        if captured_hex.lower() == expected.lower():
            print("\nRESULT: SUCCESS (NIST Validated)")
        else:
            print("\nRESULT: FAILURE (Data Mismatch)")

        ser.close()

    except Exception as e:
        print(f"\nError: {e}")

if __name__ == "__main__":
    run_visual_test()
