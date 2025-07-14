"""
Capture Image, Store
"""

import cv2

CAMERA_ADDRESS = 'USB\VID_090C&PID_037C\5&3478949&0&2'

CAMERA_ADDRESS = 0
cap = cv2.VideoCapture(CAMERA_ADDRESS)  # Opens the first camera
if not cap.isOpened():
    raise IOError("Cannot open webcam")

# Try to open the camera with index 1 (adjust as needed)
cap = cv2.VideoCapture(0) 

# Check if the camera opened successfully
if not cap.isOpened():
    print("Error: Could not open camera.")
    exit()

# Capture and display frames (example)
while True:
    ret, frame = cap.read()
    if not ret:
        print("Can't receive frame (stream end?). Exiting ...")
        break
    cv2.imshow('frame', frame)
    if cv2.waitKey(1) == ord('q'):
        break

# Release the capture and close windows
cap.release()
cv2.destroyAllWindows()
print(cap)