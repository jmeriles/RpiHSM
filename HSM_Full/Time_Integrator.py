import numpy as np
import matplotlib.pyplot as plt
from Model import Model
from Element import Element

def InitializeAlphaOS(myModel,el,GM):
    print("Check 1")
    print(myModel.K)
    print(myModel.M)
    print("Check 1")
    influence = []
    myModel.mDOF = []
    print(myModel.K)
    for i in range(len(el)):
        if el[i].hybrid == 1:
            print("Control DOF vector")
            print(el[i].controlDOF);
            controlDOF = np.nonzero(el[i].controlDOF)
            for j in range(len(controlDOF[0])):
                myModel.mDOF.append(np.nonzero(myModel.Trt[:,i*6+controlDOF[0][j]])[0])
    if myModel.ModelSet[0]=='Planar':
        for i in range(len(myModel.FDOF)):
            if (myModel.FDOF[i]+3) % 3 == 0 and myModel.DynOp[2][0]==1:
                influence.append(1)
            elif (myModel.FDOF[i]+3-1) % 3==0 and myModel.DynOp[2][1]==1:
                influence.append(1)
            else:
                influence.append(0)
                
    else:
        for i in range(len(myModel.FDOF)):
            if (myModel.FDOF[i]+6) % 6 == 0 and myModel.DynOp[2][0]==1:
                influence.append(1)
            elif (myModel.FDOF[i]+6-1) % 6==0 and myModel.DynOp[2][1]==1:
                influence.append(1)
            elif (myModel.FDOF[i]+6-2) % 6==0 and myModel.DynOp[2][2]==1:
                influence.append(1)
            else:
                influence.append(0)

    myModel.influence = np.array([influence])
    #Set of influence vectors for each fixed dof

    print("Check 2")
    dt = myModel.DynOp[1]
    myModel.u = np.zeros((len(myModel.FDOF),GM.shape[0]))
    myModel.udot = np.zeros((len(myModel.FDOF),GM.shape[0]))
    myModel.uddot = np.zeros((len(myModel.FDOF),GM.shape[0]))
    myModel.u_pred = np.zeros((len(myModel.FDOF),GM.shape[0]))
    myModel.P_tot = np.zeros((len(myModel.FDOF),GM.shape[0]))
                           
    myModel.P=np.zeros((len(myModel.FDOF),GM.shape[0]))
    myModel.alpha = myModel.DynOp[0]
    myModel.Beta = ((1-myModel.alpha)**2)/4
    myModel.gamma = (1-2*myModel.alpha)/2

    C=np.array(myModel.C)
    K=np.array(myModel.K)
    M=np.array(myModel.M)

    P0 = myModel.P[:,0]
    myModel.P_next=myModel.P[:,0]-np.transpose(np.matmul(M,GM[0]*np.transpose(myModel.influence)))

    myModel.m_eff = M + (1+myModel.alpha)*dt*myModel.gamma*C + dt**2*myModel.Beta*(1+myModel.alpha)*K
    print(myModel.m_eff)
    myModel.u_pred[:,1] = myModel.u[:,0]+dt*myModel.udot[:,0]+(dt**2)*(1-2*myModel.Beta)*myModel.uddot[:,0]/2


    P_resisting = myModel.Kh@myModel.u_pred[:,1]

    P_old = P0
    P_m = np.zeros(len(myModel.FDOF))
    print(myModel.mDOF[0]);
    P_m[myModel.mDOF[0][0]] = 0
    myModel.P_tot[:,0] = P_m+P_resisting


    P_eff = (1-myModel.alpha)*myModel.P_next+myModel.alpha*P0-(1-myModel.alpha)*myModel.P_tot[:,0]-myModel.alpha*P_old- ((1-myModel.alpha)*C*dt*(1-myModel.gamma)+myModel.alpha*(dt**2)*myModel.Beta*K)@myModel.uddot[:,0].T-C@myModel.udot[:,0].T
    myModel.uddot[:,0] = np.linalg.solve(myModel.m_eff,P_eff[0])
    print(myModel.uddot[:,0])
    
    print("Test")
    print(GM)

    return (myModel, myModel.uddot[myModel.mDOF[0][0],0])

def AlphaOS(myModel,meas_f,GM,i):
    #print("Hello")
    #print(meas_f)
    i = i-1
    #print(i)

    A = GM[i]

    dt = myModel.DynOp[1]

    C=np.array(myModel.C)
    #print(C)

    K=np.array(myModel.K)

    M=np.array(myModel.M)

    Pi = myModel.P_next
    #print(GM)
    #print("PyCheck 2")
    
    #print(myModel.P[:,0])
    #print("ELcheck1")
    #print(M)
    #print("ElCheck2")
    #print(myModel.influence)
    #print("ElCheck3")
    myModel.P_next = myModel.P[:,i+1]-np.transpose(np.matmul(M,GM[i+1]*np.transpose(myModel.influence)))
    #print("PyCheck 7")
    P_m = np.zeros(len(myModel.FDOF))
    #print("PyCheck 8")
    P_m[myModel.mDOF[0][0]] = meas_f
    #print("PyCheck 9")
    P_old = np.copy(myModel.P_tot[:,i])
    #print("PyCheck 10")
    P_resisting = myModel.Kh@myModel.u_pred[:,i]
    #print("PyCheck 11")
    myModel.P_tot[:,i] = P_m+P_resisting
    #print("PyCheck 12")
    P_eff = (1-myModel.alpha)*myModel.P_next+myModel.alpha*Pi-(1-myModel.alpha)*myModel.P_tot[:,i]-myModel.alpha*P_old- ((1-myModel.alpha)*C*dt*(1-myModel.gamma)+myModel.alpha*(dt**2)*myModel.Beta*K)@myModel.uddot[:,i].T-C@myModel.udot[:,i].T
    #print("PyCheck 13")
    P_eff = np.array(P_eff)
    #print("PyCheck 3")
    #print(np.shape(P_eff[0]))
    myModel.uddot[:,i+1] = np.linalg.solve(myModel.m_eff,P_eff[0].T)
    #print("PyCheck 14")
    

    myModel.u[:,i] = myModel.u_pred[:,i]+(dt**2)*myModel.Beta*myModel.uddot[:,i+1]
    #print("PyCheck 15")
    myModel.udot[:,i+1] = myModel.udot[:,i] + dt*((1-myModel.gamma)*myModel.uddot[:,i]+myModel.gamma*myModel.uddot[:,i+1])
    #print("PyCheck 16")
    myModel.u_pred[:,i+1] = myModel.u[:,i]+dt*myModel.udot[:,i+1]+(dt**2)*(1-2*myModel.Beta)*myModel.uddot[:,i+1]/2
    #print("PyCheck 17")
    #print(Model.u_pred[:,i+1])

    
    return (myModel,myModel.u_pred[myModel.mDOF[0][0],i+1],myModel.udot[myModel.mDOF[0][0],i+1],myModel.uddot[myModel.mDOF[0][0],i+1])
#Model.u_pred[Model.mDOF[0],i+1]
