import ffmpeg
import os

def capture_image(output_filename="capture.jpg", device="USB\VID_090C&PID_037C\5&3478949&0&2", resolution="640x480"):
    try:
        (
            ffmpeg
            .input(device, format='v4l2', video_size=resolution)
            .output(output_filename, vframes=1)
            .run(capture_stdout=True, capture_stderr=True)
        )
        print(f"Image captured successfully: {output_filename}")
    except ffmpeg.Error as e:
        print(f"Error capturing image: {e.stderr.decode()}")

if __name__ == "__main__":
    capture_image()