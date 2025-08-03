"""
GSE GUI for interfacing to payload HW
Malachi Mooney-Rivkin
03/16/2025

Notes:
Buit on PyQt
tutorial: https://www.pythonguis.com/tutorials/pyqt6-creating-your-first-window/
"""

#dependencies

from PyQt6.QtWidgets import QApplication, QWidget, QPushButton, QMainWindow, QGridLayout, QLabel, QLineEdit
from PyQt6.QtCore import QSize, Qt
import sys#might not be needed

import plantSat_GSE as plant_gse


#Subclass to contain gui components
class Window(QMainWindow):
    def __init__(self):
        super().__init__()

        self.setWindowTitle("FloraSat GSE Dashboard")

        command_widget = QWidget()
        layout = QGridLayout()

        # Create a central widget
        
        #command_widget.setAlignment(Qt.AlignmentFlag.AlignCenter) # Center the text
        self.setCentralWidget(command_widget)

        #button objects
        self.button1 = QPushButton("Scan for Serial Ports")
        self.button1.released.connect(self.gui_scan_ports)
        self.button1Status = QLabel("scan for ports...")

        self.portSelection = QLineEdit(self)
        self.portSelection.setPlaceholderText("e.g. 'COM0'") # Optional placeholder text

        self.baudSetting = QLineEdit(self)
        self.baudSetting.setPlaceholderText("Baud, Plantsat default: 9600") # Optional placeholder text

        self.timeoutSetting = QLineEdit(self)
        self.timeoutSetting.setPlaceholderText("timeout period e.g. 1") # Optional placeholder text

        self.button2 = QPushButton("Connect to Serial Port")
        self.button2.released.connect(self.gui_open_serial_port)
        self.button2Status = QLabel("Serial Port Closed")
        #start serial logging
        self.button3 = QPushButton("Button 3 - Log Serial Data")
        self.button3.setCheckable(True)
        self.button3.toggled.connect(self.gui_log_serial_data_toggled)
        self.button3Status = QLabel("Logging: OFF")
        

        # create button widgets - in descending vertical order
        layout.addWidget(QLabel("GSE Commands"), 0,0)
        layout.addWidget(self.button1, 1,0)
        layout.addWidget(self.button1Status, 2,0)
        layout.addWidget(self.portSelection, 3,0)
        layout.addWidget(self.baudSetting, 4, 0)
        layout.addWidget(self.timeoutSetting, 5,0)
        layout.addWidget(self.button2, 6,0)
        layout.addWidget(self.button2Status, 7,0)
        #layout.addWidget(QPushButton("Button 2 - start serial"), 8,0)
        #layout.addWidget(self.button1Status, 2,0)
        layout.addWidget(self.button3, 8,0)
        layout.addWidget(self.button3Status, 9,0)

        layout.addWidget(QLabel("GSE Commands"), 0,1)
        layout.addWidget(QPushButton("Button 1"), 1,1)
        layout.addWidget(QPushButton("Button 2"), 2,1)
        layout.addWidget(QPushButton("Button 3"), 3,1)
        layout.addWidget(QPushButton("Button 3"), 4,1)
        layout.addWidget(QPushButton("Button 3"), 5,1)
        layout.addWidget(QPushButton("Button 3"), 6,1)
        layout.addWidget(QPushButton("Button 3"), 7,1)

        layout.addWidget(QLabel("Command Modifiers"), 0,2)
        layout.addWidget(QPushButton("Button 1"), 1,2)
        layout.addWidget(QPushButton("Button 2"), 2,2)
        layout.addWidget(QPushButton("Button 3"), 3,2)
        layout.addWidget(QPushButton("Button 3"), 4,2)
        #layout.addWidget(QPushButton("Button Spans two Cols"), 1, 0, 1, 2)

        command_widget.setLayout(layout)
        self.setCentralWidget(command_widget)
        #self.setLayout(layout)

        self.setMinimumSize(QSize(400,300))

    def gui_scan_ports(self):
        ports = plant_gse.scan_serial_ports()
        self.button1Status.setText("Available Ports: " + str(ports))

    def gui_open_serial_port(self):
        #port = plant_gse.open_serial_port(self.portSelection.text(), self.baudSetting.text(), self.timeoutSetting.text())
        port = plant_gse.open_serial_port('COM6', 9600, 3)

        
        if(port.is_open):
            self.button2Status.setText("Serial Port Open")

        self.port = port

    def gui_log_serial_data_toggled(self):

        if(self.button3.isChecked()):
            print("Log on")
            plant_gse.log_mode_on = True
            plant_gse.log_serial(self.port)
            
        else:
            print("log off") 
            plant_gse.log_mode_on = False
            



    
        








#we need one (and only one) QApplication instance per application
#pass in sys.argv to allow command line arguments in the app
#if no command line arguments will be used, then QAppliication([]) should work too
#instantiate an application
gui= QApplication(sys.argv)

#create Qt widget, which will be the window
window = Window()
#window = QPushButton("Button!")
window.show()   #windows are hidden by default



#parameters


#GUI class

#run
gui.exec()