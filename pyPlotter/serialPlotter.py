import matplotlib.pyplot as plt
import matplotlib.animation as animation
from matplotlib import style
import numpy as np
import random
import serial

#initialize serial port
ser = serial.Serial()
ser.port = 'COM4' #Arduino serial port
ser.baudrate = 115200
ser.timeout = 10 #specify timeout when using readline()
ser.open()
if ser.is_open==True:
	print("\nAll right, serial port now open. Configuration:\n")
	print(ser, "\n") #print serial parameters

# Create figure for plotting
fig = plt.figure()
ax = fig.add_subplot(1, 1, 1)

# Format plot
plt.xticks(rotation=45, ha='right')
plt.subplots_adjust(bottom=0.30)
plt.title('accelerometer measurements')
plt.ylabel('radians')
plt.legend()
plt.axis([1, None, 0, 1.1]) #Use for arbitrary number of trials
#plt.axis([1, 100, 0, 1.1]) #Use for 100 trial demo

xs = [] #store trials here (n)
ys = [] #store relative frequency here
rs = [] #for theoretical probability

# This function is called periodically from FuncAnimation
def animate(i, xs, ys):

    #Aquire and parse data from serial port
    line=ser.readline()      #ascii
    try:
        line_as_list = line.split(b',')
        i = int(line_as_list[0])
        relProb = line_as_list[1]
        relProb_as_list = relProb.split(b'\n')
        relProb_float = float(relProb_as_list[0])
    except:
         i = float("NaN")
         relProb_float = float("nan")


    #maipluate x and y
    i = i/1000 # milisec to sec

    print(i, relProb_float)
    
    # Add x and y to lists
    xs.append(i)
    ys.append(relProb_float)
    #rs.append(0.5)

    # Limit x and y lists to 20 items
    #xs = xs[-20:]
    #ys = ys[-20:]

    # Draw x and y lists
    ax.clear()
    ax.plot(xs, ys, label="Experimental Probability")
    #ax.plot(xs, rs, label="Theoretical Probability")



# Set up plot to call animate() function periodically
ani = animation.FuncAnimation(fig, animate, fargs=(xs, ys), interval=1)
plt.show()
