import numpy as np
import matplotlib.pyplot as plt
from Model import Model
from Element import Element
from pprint import pprint

def InitializeAlphaOS(myModel,el,GM):
    print("Check 1")
    print(myModel.K)
    print(myModel.M)
    print("Check 1")
    influence = []
    print(myModel.K)
    
    if myModel.ModelSet[0]=='Planar':
        for i in range(len(myModel.FDOF)):
            if (myModel.FDOF[i]+3) % 3 == 0 and myModel.DynOp[2][0]!=0:
                influence.append(myModel.DynOp[2][0])
            elif (myModel.FDOF[i]+3-1) % 3==0 and myModel.DynOp[2][1]!=0:
                influence.append(myModel.DynOp[2][1])
            else:
                influence.append(0)
                
    else:
        for i in range(len(myModel.FDOF)):
            if (myModel.FDOF[i]+6) % 6 == 0 and myModel.DynOp[2][0]!=0:
                influence.append(1)
            elif (myModel.FDOF[i]+6-1) % 6==0 and myModel.DynOp[2][1]!=0:
                influence.append(1)
            elif (myModel.FDOF[i]+6-2) % 6==0 and myModel.DynOp[2][2]!=0:
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
    #print("running code")
    i = i - 1
    #print("Meas f is")
    #print(meas_f)
    A = GM[i]
    ##print(A)
    #print("Is Model Empty")
    #print(myModel == None)
    dt = myModel.DynOp[1]
    #print(myModel.C)
    
    C=myModel.C

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
    #print(myModel.mDOF)
    for l in range(len(myModel.mDOF)):
        P_m[myModel.mDOF[l][0]] = meas_f[myModel.mDOF[l][0]]
        

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
    u_next = np.zeros(len(myModel.mDOF))
    udot_next = np.zeros(len(myModel.mDOF))
    uddot_next = np.zeros(len(myModel.mDOF))
    for j in range(len(myModel.mDOF)):
        #u_next[myModel.mDOF[j][0]] = (myModel.u_pred[myModel.mDOF[j][0],i+1])
        #udot_next[myModel.mDOF[j][0]] = (myModel.udot[myModel.mDOF[j][0],i+1])
        #uddot_next[myModel.mDOF[j][0]] = (myModel.uddot[myModel.mDOF[j][0],i+1])
        u_next[j] = (myModel.u_pred[j,i+1])
        udot_next[j] = (myModel.udot[j,i+1])
        uddot_next[j] = (myModel.uddot[j,i+1])
    #print(u_next[0])
    return (myModel,np.array(u_next),np.array(udot_next),np.array(uddot_next))
#Model.u_pred[Model.mDOF[0],i+1]
