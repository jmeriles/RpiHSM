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
    

    plt.figure(100)
    for i in range(len(myModel.mDOF)):
        pltlabel = "Hybrid DOF " + str(i+1)
        plt.plot(time,u[myModel.mDOF[i][0],0:-2],label = pltlabel)
    plt.xlabel("Time(s)")
    plt.ylabel("Calculated Displacements(in)")
    plt.title("Hybrid Element Calculated Displacements")
    plt.legend()
    plt.figure(200)
    for i in range(len(myModel.mDOF)):
        lpltlabel = "Hybrid DOF " + str(i+1)
        plt.plot(time,udot[myModel.mDOF[i][0],0:-2],label = pltlabel)
    plt.xlabel("Time(s)")
    plt.ylabel("Calculated Velocity(in/s)")
    plt.title("Hybrid Element Calculated Velocity")
    plt.legend()
    plt.figure(300)
    for i in range(len(myModel.mDOF)):
        pltlabel = "Hybrid DOF " + str(i+1)
        plt.plot(time,uddot[myModel.mDOF[i][0],0:-2],label = pltlabel)
    plt.xlabel("Time(s)")
    plt.ylabel("Calculated Acceleration(in/s^2)")
    plt.title("Hybrid Element Calculated Acceleration")
    plt.legend()
    plt.show()
    return 1