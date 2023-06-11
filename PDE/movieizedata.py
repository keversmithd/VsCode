import numpy as np
import matplotlib
import matplotlib.pyplot as plt
import matplotlib.animation as animation
from matplotlib.animation import PillowWriter
from matplotlib.patches import Rectangle

mindat = 0.0
maxdat = 0.0
f = open("datatemp.txt", "r")
dat = []
sysnodes = 0
for x in f:
  if "nodes" in x:
    sysnodes = int(x.replace("nodes: ",''));
  else:
    entry = float(x.replace('\n',''))
    if(mindat == 0.0):
      mindat = entry
    else:
      if(entry < mindat):
        mindat = entry
    if(maxdat == 0.0):
      maxdat = entry
    else:
      if(entry > maxdat):
        maxdat = entry
    dat.append(entry)


plt.rcParams["figure.figsize"] = [7.00, 3.50]
plt.rcParams["figure.autolayout"] = True
fig, ax = plt.subplots()
l, = plt.plot([],[],'k-')

plt.xlim(0, sysnodes-1)
plt.ylim(mindat,maxdat)

plt.grid()
xlist = np.arange(0,sysnodes)
#print(xlist)

plt.savefig('output.png')

writer = PillowWriter(1)


num_frames = len(dat) // sysnodes



with writer.saving(fig, "output.gif", 100):
  for i in range(num_frames):
    data_start = sysnodes * i
    data_end = data_start+sysnodes
    #print("data_start" + str(data_start) + "data_end" + str(data_end))
    
    sub_data = dat[data_start:data_end]
    
    l.set_data(xlist, sub_data)
    
    writer.grab_frame()
    
  
  

