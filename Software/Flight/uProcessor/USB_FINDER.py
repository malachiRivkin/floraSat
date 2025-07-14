""" List available usb devices
"""

import win32com.client

wmi = win32com.client.GetObject("winmgmts:")
for usb in wmi.InstancesOf("Win32_USBHub"):
    print(usb.DeviceID)

"""
import wmi # Initialize the WMI interface
c = wmi.WMI() # Query for USB devices
for usb in c.Win32_USBControllerDevice():
    print(usb.Dependent)
    """