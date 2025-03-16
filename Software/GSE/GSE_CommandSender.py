"""
Commandline utility for interfacing with payload from ground support equipment (GSE
Malachi Mooney-Rivkin
06.02.2025
"""

#Dependencies
#import pyserial as ps

#Commands
task1 = 0x00
task2 = 0x01
task3 = 0x02

#run


while True:
    print("---Command Set---")
    print("[1] task1 \n [2] task2 \n [3] task3")
    print("---End Command Set---")
    command = input("Select Command [#]")
    command = int(command)

    match command:
        case 1:
            print("task 1 executed")
        case 2:
            print("Task 2 executed")
        case 3:
            print("task 3 executed")
        case _:
            print("Command not identified")
            break

print("DONE \n")