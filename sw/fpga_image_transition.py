import serial
import time
import sys
import numpy as np
from PIL import Image
import matplotlib.pyplot as plt

# --- Configuration ---
PORT = '/dev/ttyUSB1'
BAUD = 576000
KEY_HEX = "80000000000000000000000000000000"
INPUT_IMAGE = "input.jpg"
UPDATE_FREQ = 100 # Refresh GUI every 100 blocks (approx 1.6KB)

class AESFPGAClient:
    def __init__(self, port, baud):
        try:
            self.ser = serial.Serial(port, baud, timeout=2)
            print(f"[*] Connected to {port} at {baud} baud.")
            time.sleep(2) # Wait for Basys 3 reboot
            self.ser.reset_input_buffer()
        except Exception as e:
            print(f"[!] Serial Error: {e}")
            sys.exit(1)

    def set_key(self, key_hex):
        print(f"[*] Setting AES Key: {key_hex}")
        self.ser.write(b'\x01' + bytes.fromhex(key_hex))
        time.sleep(0.1)

def run_full_demo():
    client = AESFPGAClient(PORT, BAUD)
    client.set_key(KEY_HEX)

    # 1. Prepare Image Data
    img_org = Image.open(INPUT_IMAGE).convert('RGB')
    width, height = img_org.size
    
    # We use a bytearray as shared memory for the live buffer
    buffer = bytearray(img_org.tobytes())
    original_len = len(buffer)

    # Pad to 16 bytes for AES
    padding_needed = (16 - (original_len % 16)) % 16
    padded_data = buffer + (b'\x00' * padding_needed)
    
    # 2. Setup Matplotlib Window
    plt.ion()
    fig, ax = plt.subplots(figsize=(12, 7))
    # Initialize display with original image
    img_np = np.frombuffer(buffer, dtype=np.uint8).reshape((height, width, 3))
    img_plot = ax.imshow(img_np)
    plt.show()

    # --- PHASE 1: ENCRYPTION ---
    print(f"[*] Phase 1: Live Encryption...")
    ax.set_title("FPGA AES LIVE: ENCRYPTING...")
    
    start_time = time.time()
    for i in range(0, len(padded_data), 16):
        block = padded_data[i:i+16]
        
        # CMD 0x02 = Encrypt
        client.ser.write(b'\x02' + block)
        chunk = client.ser.read(16)
        
        if len(chunk) == 16:
            # Update the buffer (only for visible pixels)
            if i < original_len:
                end_idx = min(i + 16, original_len)
                num_bytes = end_idx - i
                buffer[i:end_idx] = chunk[:num_bytes]
                # Store back in padded_data so Phase 2 starts with ciphertext
                padded_data[i:i+16] = chunk 
        else:
            print(f"\n[!] Timeout during encryption at block {i//16}")
            break

        # Periodic GUI Update
        if (i // 16) % UPDATE_FREQ == 0:
            updated_np = np.frombuffer(buffer, dtype=np.uint8).reshape((height, width, 3))
            img_plot.set_data(updated_np)
            plt.pause(0.001)
            sys.stdout.write(f"\rEncrypting: {(i/len(padded_data))*100:.1f}%")
            sys.stdout.flush()

    print(f"\n[*] Encryption Finished in {time.time() - start_time:.2f}s")
    time.sleep(1) # Pause to let user see the final ciphertext

    # --- PHASE 2: DECRYPTION ---
    print(f"[*] Phase 2: Live Decryption...")
    ax.set_title("FPGA AES LIVE: DECRYPTING...")
    
    start_time = time.time()
    # We iterate through the padded_data which now contains the ciphertext
    for i in range(0, len(padded_data), 16):
        block = padded_data[i:i+16]
        
        # CMD 0x03 = Decrypt
        client.ser.write(b'\x03' + block)
        chunk = client.ser.read(16)
        
        if len(chunk) == 16:
            if i < original_len:
                end_idx = min(i + 16, original_len)
                num_bytes = end_idx - i
                buffer[i:end_idx] = chunk[:num_bytes]
        else:
            print(f"\n[!] Timeout during decryption at block {i//16}")
            break

        # Periodic GUI Update
        if (i // 16) % UPDATE_FREQ == 0:
            updated_np = np.frombuffer(buffer, dtype=np.uint8).reshape((height, width, 3))
            img_plot.set_data(updated_np)
            plt.pause(0.001)
            sys.stdout.write(f"\rDecrypting: {(i/len(padded_data))*100:.1f}%")
            sys.stdout.flush()

    # Final Redraw
    final_np = np.frombuffer(buffer, dtype=np.uint8).reshape((height, width, 3))
    img_plot.set_data(final_np)
    ax.set_title("FPGA AES LIVE: COMPLETE")
    plt.draw()

    print(f"\n[*] Decryption Finished in {time.time() - start_time:.2f}s")
    print("[*] Demonstration Complete.")
    
    plt.ioff()
    plt.show()

if __name__ == "__main__":
    run_full_demo()
