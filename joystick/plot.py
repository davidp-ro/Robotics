import serial
import matplotlib.pyplot as plt
import matplotlib.style as style
import numpy as np
import sys

sr = serial.Serial('COM4', 9600)
plt.close('all')
plt.figure()
plt.ion()
style.use('seaborn-darkgrid')
plt.show()

data_lx = np.array([])
data_ly = np.array([])
data_rx = np.array([])
data_ry = np.array([])

while True:
    try:
        read = str(sr.readline())[2:-3]
        
        left, right = read.split('.')
        lx, ly = left.split(',')
        rx, ry = right.split(',')
        
        data_lx = np.append(data_lx, float(lx))
        data_ly = np.append(data_ly, float(ly))
        data_rx = np.append(data_rx, float(rx))
        data_ry = np.append(data_ry, float(ry))
        
        plt.cla()
        plt.plot(data_lx)
        plt.plot(data_ly)
        plt.plot(data_rx)
        plt.plot(data_ry)
        plt.pause(0.05)

    except KeyboardInterrupt:
        print('\n')
        sys.exit()
