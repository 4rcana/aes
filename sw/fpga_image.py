import serial
import time
import sys
from PIL import Image

# --- Configuration ---
PORT = '/dev/ttyUSB1'
BAUD = 9600
KEY_HEX = "80000000000000000000000000000000" # Standard NIST Key
INPUT_IMAGE = "input.png"
ENCRYPTED_IMAGE = "encrypted.png"
DECRYPTED_IMAGE = "decrypted.png"

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
        print(f"[*] Setting Key: {key_hex}")
        key_bytes = bytes.fromhex(key_hex)
        self.ser.write(b'\x01' + key_bytes)
        time.sleep(0.1) # Give FPGA time to process key load

    def process_data(self, data_bytes, mode='encrypt'):
        """Sends data in 16-byte blocks and collects results."""
        cmd = b'\x02' if mode == 'encrypt' else b'\x03'
        result = bytearray()
        total_blocks = len(data_bytes) // 16

        print(f"[*] Starting {mode}ion of {len(data_bytes)} bytes ({total_blocks} blocks)...")
        
        start_time = time.time()
        for i in range(0, len(data_bytes), 16):
            block = data_bytes[i:i+16]
            
            # Send Command + 16 bytes
            self.ser.write(cmd + block)
            
            # Read 16 bytes back
            chunk = self.ser.read(16)
            
            if len(chunk) == 16:
                result.extend(chunk)
            else:
                print(f"\n[!] Timeout at block {i//16}. Received only {len(chunk)} bytes.")
                return result # Return partial data for debugging

            # Progress Bar
            if (i // 16) % 10 == 0 or i + 16 >= len(data_bytes):
                progress = (i + 16) / len(data_bytes) * 100
                sys.stdout.write(f"\rProgress: [{int(progress/2)*'=':50}] {progress:.1f}%")
                sys.stdout.flush()

        end_time = time.time()
        print(f"\n[*] Finished in {end_time - start_time:.2f} seconds.")
        return result

def run_image_demo():
    client = AESFPGAClient(PORT, BAUD)
    client.set_key(KEY_HEX)

    # 1. Load Image
    try:
        img = Image.open(INPUT_IMAGE).convert('RGB')
    except Exception as e:
        print(f"[!] Error opening image: {e}")
        return

    width, height = img.size
    original_data = img.tobytes()
    original_len = len(original_data)

    # 2. Pad to 16 bytes
    padding_needed = (16 - (original_len % 16)) % 16
    padded_data = original_data + (b'\x00' * padding_needed)

    # 3. Encrypt
    encrypted_bytes = client.process_data(padded_data, mode='encrypt')
    
    if len(encrypted_bytes) >= original_len:
        # Save Encrypted Image (using original dimensions)
        enc_img = Image.frombytes('RGB', (width, height), bytes(encrypted_bytes[:original_len]))
        enc_img.save(ENCRYPTED_IMAGE)
        print(f"[+] Saved encrypted image: {ENCRYPTED_IMAGE}")
    else:
        print("[!] Encryption failed - incomplete data received.")
        return

    # 4. Decrypt
    decrypted_bytes = client.process_data(encrypted_bytes, mode='decrypt')
    
    if len(decrypted_bytes) >= original_len:
        # Save Decrypted Image
        dec_img = Image.frombytes('RGB', (width, height), bytes(decrypted_bytes[:original_len]))
        dec_img.save(DECRYPTED_IMAGE)
        print(f"[+] Saved decrypted image: {DECRYPTED_IMAGE}")
    else:
        print("[!] Decryption failed - incomplete data received.")

if __name__ == "__main__":
    run_image_demo()
