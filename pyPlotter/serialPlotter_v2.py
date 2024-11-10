import numpy as np
import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation
import serial

#initialize serial port
ser = serial.Serial()
ser.port = 'COM4' #Arduino serial port
ser.baudrate = 115200
ser.timeout = 100 #specify timeout when using readline()
ser.open()
if ser.is_open==True:
	print("\nAll right, serial port now open. Configuration:\n")
	print(ser, "\n") #print serial parameters

#fig, ax = plt.subplots()
fig = plt.figure()
ax = plt.axes()
ax.set_ylim(-1,1)
#ax.set_xlim(0,100)
xlim_interval = 100
xdata, ydata1, ydata2, ydata3 = [], [], [], []
#ln, = ax.plot([], [], 'ro')
ln1, = ax.plot([], [], lw=1,color="blue")
ln2, = ax.plot([],[],lw=1, color="green")
ln3, = ax.plot([],[], lw=1, color="red")

def init():
    ln1.set_data(xdata, ydata1)
    ln2.set_data(xdata, ydata2)
    ln2.set_data(xdata, ydata3)
    return ln1, ln2, ln3

def update(frame):
    global xdata, ydata1, ydata2, ydata3
    global xlim_interval

    #Aquire and parse data from serial port
    line=ser.readline().strip()      #ascii
    try:
        line_as_list = line.split(b',')
        #print(line_as_list)
        t = int(line_as_list[0])
        angle_raw = float(line_as_list[1])
        angle_gyro = float(line_as_list[2])
        angel_filt = float(line_as_list[3])
        # add additional data here
        

    except:
        t = float("NaN")
        angle_raw = float("nan")
        angle_gyro = float("nan")
        angel_filt = float("nan")

    
    #maipluate x and y
    t = t/1000 # milisec to sec
    print(t, angle_raw, angle_gyro)

    xdata.append(t)
    ydata1.append(angle_raw)
    ydata2.append(angle_gyro)
    ydata3.append(angel_filt)

    ln1.set_data(xdata, ydata1)
    ln2.set_data(xdata, ydata2)
    ln3.set_data(xdata, ydata3)

    # Dynamically update x-axis range
    ax.relim()
    ax.autoscale_view(scalex=True, scaley=True)
    if t>xlim_interval:
        xlim_interval += xlim_interval
        ax.set_xlim(0,xlim_interval)
    
    return ln1, ln2, ln3

ani = FuncAnimation(fig, update, frames=20000,
                    init_func=init, blit=True,
                    interval=1
                    )
plt.show()