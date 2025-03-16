"""
GSE GUI for interfacing to payload HW
Malachi Mooney-Rivkin
03/16/2025

Notes:
Buit on PyQt
tutorial: https://www.pythonguis.com/tutorials/pyqt6-creating-your-first-window/
"""

#dependencies
from PyQt6.QtWidgets import QApplication, QWidget, QPushButton, QMainWindow
from PyQt6.QtCore import QSize, Qt
import sys#might not be needed


#Subclass to contain gui components
class MainWindow(QMainWindow):
    def __init__(self):
        super().__init__()

        self.setWindowTitle("FloraSat GSE Dashboard")
        button = QPushButton("Button!!!")

        self.setMinimumSize(QSize(400,300))

        #set the central widget of the window
        self.setCentralWidget(button)




#we need one (and only one) QApplication instance per application
#pass in sys.argv to allow command line arguments in the app
#if no command line arguments will be used, then QAppliication([]) should work too
#instantiate an application
gui= QApplication(sys.argv)

#create Qt widget, which will be the window

window = MainWindow()
#window = QPushButton("Button!")
window.show()   #windows are hidden by default



#parameters


#GUI class

#run
gui.exec()