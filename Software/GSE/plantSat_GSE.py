
#dependencies
import serial
from serial.tools import list_ports
import datetime
import csv


#params
test_code = False

log_mode_on = False #flag to log data

def scan_serial_ports():
    ports = []
    available_ports = serial.tools.list_ports.comports()

    for i in available_ports:
        ports.append(i.name)
    
    return ports

def open_serial_port(COM_PORT, BAUD_RATE, TIMEOUT):
    serPort = 1
    print(COM_PORT)
    print(BAUD_RATE)
    print(TIMEOUT)

    try:
        serPort = serial.Serial(str(COM_PORT), int(BAUD_RATE), timeout=float(TIMEOUT))
    except:
        print("No luck opening serial port")
    return serPort

def close_serial_port(SERIAL_PORT):
    SERIAL_PORT.close()

def monitor_serial_port(SERIAL_PORT):
    input = SERIAL_PORT.readline()
    return input

def log_serial(SERIAL_PORT):
    #fname = datetime.datetime.now()
    #print('fname: ', fname)

    while log_mode_on:
        try:
            incoming_bytes = SERIAL_PORT.readline()
            print(incoming_bytes)

            #with open("test_LOG.csv", 'a') as file:
             #   writer = csv.writer(file, delimiter=',')
              #  writer.writerow([datetime.datetime.now(), incoming_bytes])

        except:
            print("Streaming Complete")
            break


################################################
if(test_code):
    ports = scan_serial_ports()
    print("Available Ports: ", ports)

    port = open_serial_port('COM6', 9600, 10)
    print("Opened Port: ", port)

    #line = monitor_serial_port(port)
    #print(line)

    log_serial(port)


