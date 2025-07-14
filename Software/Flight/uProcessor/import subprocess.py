import subprocess

def list_usb_devices():
    try:
        output = subprocess.check_output(["lsusb"]).decode("utf-8")
        print(output)
    except FileNotFoundError:
        print("lsusb command not found. Please make sure it's installed.")
    except Exception as e:
        print(f"An error occurred: {e}")

if __name__ == "__main__":
    list_usb_devices()