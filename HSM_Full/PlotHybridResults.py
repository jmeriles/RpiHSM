import numpy as np
from Model import Model
from PlotModel import PlotModel
import matplotlib.pyplot as plt

def PlotHybridResults(myModel):
    dt = myModel.DynOp[1]
    time = np.arange(0,len(myModel.u[myModel.mDOF[0][0],0:-2])*dt,dt)
    u = myModel.u
    udot = myModel.udot
    uddot = myModel.uddot
    plt.figure(1)
    plt.plot(time,u[myModel.mDOF[0][0],0:-2])
    plt.xlabel("Time(s)")
    plt.ylabel("Calculated Displacements(in)")
    plt.title("Hybrid Element Calculated Displacements")
    plt.figure(2)
    plt.plot(time,udot[myModel.mDOF[0][0],0:-2])
    plt.xlabel("Time(s)")
    plt.ylabel("Calculated Velocity(in/s)")
    plt.title("Hybrid Element Calculated Velocity")
    plt.figure(3)
    plt.plot(time,uddot[myModel.mDOF[0][0],0:-2])
    plt.xlabel("Time(s)")
    plt.ylabel("Calculated Acceleration(in/s^2)")
    plt.title("Hybrid Element Calculated Acceleration")
    plt.show()
    return 1