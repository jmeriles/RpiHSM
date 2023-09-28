import numpy as np
import matplotlib.pyplot as plt
from Model import Model
from Element import Element
def AlphaOS(myModel,meas_f,GM,i):
    print("Hello")
    #print(meas_f)
    i = i-1
    #print(i)
    #print(np.array(GM))

    A = GM[i]

    dt = myModel.DynOp[1]

    C=np.array(myModel.C)

    K=np.array(myModel.K)

    M=np.array(myModel.M)

    Pi = myModel.P_next
    print(GM)
    print("PyCheck 2")
    
    print(myModel.P[:,0])
    print("ELcheck1")
    print(M)
    print("ElCheck2")
    print(myModel.influence)
    print("ElCheck3")
    myModel.P_next = myModel.P[:,i+1]-np.transpose(np.matmul(M,GM[i+1]*np.transpose(myModel.influence)))
    print("PyCheck 7")
    P_m = np.zeros(len(myModel.FDOF))
    print("PyCheck 8")
    P_m[myModel.mDOF[0][0]] = meas_f
    #P_m[myModel.mDOF[0][1]] = meas_f[1]
    print("PyCheck 9")
    P_old = np.copy(myModel.P_tot[:,i])
    print("PyCheck 10")
    P_resisting = myModel.Kh@myModel.u_pred[:,i]
    print("PyCheck 11")
    myModel.P_tot[:,i] = P_m+P_resisting
    print("PyCheck 12")
    P_eff = (1-myModel.alpha)*myModel.P_next+myModel.alpha*Pi-(1-myModel.alpha)*myModel.P_tot[:,i]-myModel.alpha*P_old- ((1-myModel.alpha)*C*dt*(1-myModel.gamma)+myModel.alpha*(dt**2)*myModel.Beta*K)@myModel.uddot[:,i].T-C@myModel.udot[:,i].T
    print("PyCheck 13")
    P_eff = np.array(P_eff)
    print("PyCheck 3")
    print(np.shape(P_eff[0]))
    myModel.uddot[:,i+1] = np.linalg.solve(myModel.m_eff,P_eff[0].T)
    print("PyCheck 14")
    

    myModel.u[:,i] = myModel.u_pred[:,i]+(dt**2)*myModel.Beta*myModel.uddot[:,i+1]
    print("PyCheck 15")
    myModel.udot[:,i+1] = myModel.udot[:,i] + dt*((1-myModel.gamma)*myModel.uddot[:,i]+myModel.gamma*myModel.uddot[:,i+1])
    print("PyCheck 16")
    myModel.u_pred[:,i+1] = myModel.u[:,i]+dt*myModel.udot[:,i+1]+(dt**2)*(1-2*myModel.Beta)*myModel.uddot[:,i+1]/2
    print("PyCheck 17")
    #print(Model.u_pred[:,i+1])

    
    return (myModel,myModel.u_pred[myModel.mDOF[0],i+1])