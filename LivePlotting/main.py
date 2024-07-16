import serial
import time
import matplotlib.pyplot as plt 
from matplotlib.animation import FuncAnimation
import csv
import shutil
import os

#constants
SERIAL_PORT = 'COM6'
BAUD_RATE = 115200
FILE = 'recorded_data.csv'

#intialise serial connection
ser = serial.Serial(SERIAL_PORT,BAUD_RATE)

#reset esp32
ser.setDTR(False)
time.sleep(1)
ser.flushInput()
ser.setDTR(True)

#intialise empty lists to store data
time_axis=[]
actual_speed=[]
target_speed=[]

#create a function to read and process data 
def read_and_process_data():
    line=ser.readline().decode('utf-8').strip()
    print('Line:\n')
    print(line)
    values=line.split(',')
    try:
        if len(time_axis) > 0:
            time_axis.append(time_axis[-1] + float(values[0]))
        else:
            time_axis.append(float(values[0]))
        actual_speed.append(float(values[1]))
        target_speed.append(float(values[2]))
    except:
        pass

    #print received values
    # print(f'Time: {values[0]},sensor1: {values[1]},sensor2: {values[2]}')

#create the function to update the plot
def update_plot(frame):
    read_and_process_data()
    plt.cla()
    plt.plot(time_axis, actual_speed, label='Actual speed')
    plt.plot(time_axis, target_speed, label='Target speed')
    plt.xlabel('Time')
    plt.ylabel('Speed')
    plt.legend()

#create function to save data to a csv file when the plot window is closed 
def on_close(event):
    try:
        # shutil.rmtree(FILE)
        os.remove(FILE)
    except:
        pass
    with open(FILE, 'w', newline='') as csvfile:
        writer=csv.writer(csvfile)
        writer.writerow(['Time','Actual Speed','Target Speed'])
        for x, s1, s2 in zip(time_axis, actual_speed,target_speed):
            writer.writerow([x,s1,s2])

#register the callback function for when the plot window is closed
fig,ax=plt.subplots()
fig.canvas.mpl_connect('close_event',on_close)

ani=FuncAnimation(fig,update_plot,interval=10)
plt.show()