import os
import sys
sys.path.insert(0, os.path.join(os.path.dirname(__file__), "dll"))

import ac
import acsys
import serial
import time

#ser = serial.Serial(3, 9600)
ser = serial.Serial(port = 'COM4', baudrate = 9600, timeout = 0)
count = 0

def acMain(acVersion):
    # do something with serial library
    global ser
    ac.log("called acMain()")
    time.sleep(3)
    #ser.write("1:0;".encode())
    ser.write("3:17000;".encode())
    return "Arduino Serial"
def acUpdate(deltaT):
    global ser,ac,acsys,count

    if count == 15:
        value=ac.getCarState(0,acsys.CS.RPM)
        value = str(round(value))
        toSend="1:" + value + ";"
        ser.write(toSend.encode())
        gear=ac.getCarState(0,acsys.CS.Gear)
        gear = int(gear)
        gear = gear - 1
        if gear == 0:
            gear = "n"
        elif gear == -1:
            gear = "r"
        else:
            gear = str(gear)
        toSendGear = "2:" + gear + ";"
        ser.write(toSendGear.encode())
        count = 0
    else:
        count = count + 1
def acShutdown():
    global ser
    ac.log("called acShutdown()")
    ser.close()