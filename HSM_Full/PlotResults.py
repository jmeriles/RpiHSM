import os
import numpy as np
import matplotlib.pyplot as plt
THIS_FOLDER = os.path.dirname(os.path.abspath(__file__))
dCommand = os.path.join(THIS_FOLDER+"/build-HSM_Full-Desktop-Debug/", "Command.txt")
    
dispCommand=[]
f=open(dCommand)

dispCommand = []
for line in f.readlines():
    dispCommand.append(float(line))

f.close
dispCommand = dispCommand[0:-2]
plt.figure(1)
plt.plot(dispCommand)

calcDisp = os.path.join(THIS_FOLDER+"/build-HSM_Full-Desktop-Debug/", "IntegratorDisp.txt")
    
analyticDisp=[]
f=open(calcDisp)

analyticDisp = []
for line in f.readlines():
    analyticDisp.append(float(line))

f.close
analyticDisp = analyticDisp[0:-2]
plt.figure(2)
plt.plot(analyticDisp)

intIndex = os.path.join(THIS_FOLDER+"/build-HSM_Full-Desktop-Debug/", "integratorIndex.txt")
    
intIndices=[]
f=open(intIndex)

for line in f.readlines():
    intIndices.append(int(line))

f.close
intIndices = intIndices[0:-1]
print(len(intIndices))
print(len(analyticDisp))
plt.figure(2)
plt.plot(np.array(dispCommand)[intIndices])
#plt.figure(2)
#plt.plot(analyticDisp)
plt.show()




