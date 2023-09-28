#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Mon Jul  6 19:37:16 2020

@author: jim53
"""

from IPython import get_ipython
import numpy as np
from Model import Model
from PlotModel import PlotModel
#get_ipython().magic('reset -sf')
from Analyze import Analyze
from GMread import GMread
import scipy.interpolate as sp
import matplotlib.pyplot as plt

ModelSet=['Planar','line']
#Number and define NODE locations
NODE=[]
NODE.insert(0,[0,0])
NODE.insert(1,[0,5])
NODE.insert(2,[10,5])
NODE.insert(3,[10,0])

CON=[[1,2],[2,3],[3,4]]

#Turn selfweight on and off
selfweight=0

#Add nodal masses
Node_Mass=[10000,10000,10000,10000]

# DO NOT EDIT THIS
Model=Model(NODE,CON,Node_Mass,selfweight,ModelSet)

#Set the Boundary conditions at the nodes where there are boundaries.
#Others will have no BC

Model.BOUN[0]=[1,1,1];
Model.BOUN[3] = [1,1,0];


#USER Define loading
#Model.LOAD[2]=[5,0,0,0,0,0]

#DO NOT EDIT THIS
# Given Node Locations, connectivity, Element Type, BC, and Loading, initiates elements
el=Model.init_el()

# USER Define E A and I, releases, q0 and w here

#w is defined as positive outwards and negative into the beam
#Order of basic forces is [axial, torsion, Myi,Myj,Mzi,Mzj]

for i in range (Model.numel):
    el[i].Iz=10000
    el[i].A=10000000000000
    el[i].E=1
    el[i].rho=0

#el[1].Iz = 1000000000000000
el[1].REL=[np.inf,np.inf,0,np.inf,np.inf,np.inf];

#el[0].w_y=10
el[0].hybrid = 1
#el[1].hybrid = 1
el[0].controlDOF = [0,0,0,0,1,0]



el[0].ke = np.array([[ 0,0,0,0,0,0],
                    [ 0,0,0,0,0,0],
                    [ 0,0,0,0,0,0],
                    [0,0,0,2.0e+12,0,0],
                    [ 0,0,0,0, 240, 0],
                    [ 0,0,0,0,0,0]])

# el[0].ke = np.array([[0,0,0,0,0,0],
#                       [0,0,0,0,0,0],
#                       [0,0,0,0,0,0],
#                       [0,0,0,0,0,0],
#                       [0,0,0,0,0,0],
#                       [0,0,0,0,0,0]])



Ground_Motion='El_Centro.txt'
DynOp=[.25,.5,.001,[1,0,0]]
#DO NOT EDIT
el=Model.elMat(el)
Model.Create_B(el)
Model.Create_K()
Model.Create_M()
Model.Create_Loading(el)
Model.CheckHybridEl(el)


plot=PlotModel()
plot.Struct(Model,el)


An=Analyze()

#Static Analysis
# An.Displ(Model,el)
# plot = PlotModel()
# plot.Struct(Model,el)
# plot.DefShape(Model,el)




K=np.array(Model.K)
M=np.array(Model.M)




# masslessDOF = []
# massDOF = []
# for i in range(len(M)):
#     if M[i,i] < 10**-5:
#         masslessDOF.append(i)
#     else:
#         massDOF.append(i)
        
# NewOrder = np.hstack([massDOF,masslessDOF])
# K_cond = np.array([[K[i,j] for i in NewOrder] for j in NewOrder])
# K_mass = K_cond[0:len(massDOF),0:len(massDOF)]
# K_mass_nmass = K_cond[len(massDOF):,0:len(massDOF)]
# K_nmass = K_cond[len(massDOF):,len(massDOF):]
# K_cond = K_mass-K_mass_nmass.T @ np.linalg.inv(K_nmass) @ K_mass_nmass
# Kh_cond = np.array([[Model.Kh[i,j] for i in NewOrder] for j in NewOrder])
# Kh_mass = Kh_cond[0:len(massDOF),0:len(massDOF)]
# Kh_mass_nmass = Kh_cond[len(massDOF):,0:len(massDOF)]
# Kh_nmass = Kh_cond[len(massDOF):,len(massDOF):]
# Kh_cond = Kh_mass-Kh_mass_nmass.T @ np.linalg.inv(Kh_nmass) @ Kh_mass_nmass
# M_cond = np.array([[M[i,j] for i in NewOrder] for j in NewOrder])
# M_cond = M_cond[0:len(massDOF),0:len(massDOF)]
# Model.FDOF = [Model.FDOF[i] for i in massDOF]

# Model.K = K_cond
# Model.Kh = Kh_cond
# Model.M = M_cond

Model.Eig()
Model.Create_C("Rayleigh",[1,0,0])
C=np.array(Model.C)
K=np.array(Model.K)
M=np.array(Model.M)

GM=GMread(Ground_Motion)
dtold = .02
told = np.arange(0,dtold*len(GM),dtold)


#interpolate eq
GM_new=sp.interp1d(told,GM)

dt=.01
time = np.arange(0,dtold*(len(GM)-1),dt)
GM = GM_new(time)
#Eq_a = Eq_a/40
GM = np.hstack((GM))
time = np.arange(0,dt*(len(GM)),dt)

flag = 0
P = []
if len(P) == 0:
    P=np.zeros((len(Model.FDOF),GM.shape[0]))
    g=386.4 #in/s^2, this is the standard but I should probably let people change it
    GM=386.4*GM
    LoadingLen = GM.shape[0]
    flag = 1
if len(GM) == 0:
    GM=np.zeros((1,P.shape[1]))
    LoadingLen = P.shape[1]
    Res = np.zeros((1,P.shape[0]))        
influence=[]


if Model.ModelSet[0]=='Planar':
    for i in range(len(Model.FDOF)):
        if (Model.FDOF[i]+3) % 3 == 0 and DynOp[3][0]==1:
            influence.append(1)
        elif (Model.FDOF[i]+3-1) % 3==0 and DynOp[3][1]==1:
            influence.append(1)
        else:
            influence.append(0)
            
else:
    for i in range(len(Model.FDOF)):
        if (Model.FDOF[i]+6) % 6 == 0 and DynOp[3][0]==1:
            influence.append(1)
        elif (Model.FDOF[i]+6-1) % 6==0 and DynOp[3][1]==1:
            influence.append(1)
        elif (Model.FDOF[i]+6-2) % 6==0 and DynOp[3][2]==1:
            influence.append(1)
        else:
            influence.append(0)

influence = np.array([influence])
#Set of influence vectors for each fixed dof


u = np.zeros(len(Model.FDOF))
udot = np.zeros(len(Model.FDOF))
uddot = np.zeros(len(Model.FDOF))
u_pred = np.zeros(len(Model.FDOF))

alpha = 0
Beta = ((1-alpha)**2)/4
gamma = (1-2*alpha)/2


P0 = P[:,0]
P_next=P[:,0]-np.transpose(np.matmul(M,GM[0]*np.transpose(influence)))
#P_next=P[:,1]-np.transpose(np.matmul(M,GM[1]*np.transpose(influence)))
m_eff = Model.M + (1+alpha)*dt*gamma*Model.C + dt**2*Beta*(1+alpha)*Model.K
u_pred = u+dt*udot+(dt**2)*(1-2*Beta)*uddot/2


U_hist = []
U_hist.append(u)
#U_hist.append(u_pred)

P_resisting = Model.Kh@u_pred

P_old = P[:,0]
P_m = np.array([240*u_pred[0],0,0,0,0,0])
P_tot = P_m+P_resisting


P_eff = (1-alpha)*P_next+alpha*P0-(1-alpha)*P_tot-alpha*P_old- ((1-alpha)*C*dt*(1-gamma)+alpha*(dt**2)*Beta*K)@uddot.T-C@udot.T
uddot_old = uddot
uddot = np.linalg.solve(m_eff,P_eff[0])

#Initializing uddot here, everything else initialized as 0, not 100% sure this is right
#u = u_pred+(dt**2)*Beta*uddot
#udot = udot + dt*((1-gamma)*uddot_old+gamma*uddot)
#u_pred = u+dt*udot+(dt**2)*(1-2*Beta)*uddot/2

#U_hist.append(u)
T=dt*GM.shape[0]
t=np.linspace(0,T,GM.shape[0]-1)


P_hist = []

for i in range(0,GM.shape[0]-1):

    Pi=P_next
    #print(M)

    P_hist.append(Pi)
    P_next=P[:,i+1]-np.transpose(np.matmul(M,GM[i+1]*np.transpose(influence)))
    P_m = np.array([240*u_pred[0],0,0,0,0,0])
    P_old = P_tot
    P_resisting = Model.Kh@u_pred
    P_tot = P_m+P_resisting
    
    
    P_eff = (1-alpha)*P_next+alpha*Pi-(1-alpha)*P_tot-alpha*P_old- ((1-alpha)*C*dt*(1-gamma)+alpha*(dt**2)*Beta*K)@uddot.T-C@udot.T
    uddot_old = uddot
    uddot = np.linalg.solve(m_eff,P_eff[0])
    u = u_pred+(dt**2)*Beta*uddot
    udot = udot + dt*((1-gamma)*uddot_old+gamma*uddot)
    u_pred = u+dt*udot+(dt**2)*(1-2*Beta)*uddot/2
    U_hist.append(u)
    
U_hist = np.vstack(U_hist)  
P_hist = np.vstack(P_hist)   
#plt.plot(U_hist[:,0]) 
plt.figure(21)
T = len(U_hist[:,0])*dt
time = np.arange(0,T,dt)
plt.plot(time,U_hist[:,0]) 


#Dynamic analysis
#Model.Eig()
#Model.Create_C("Rayleigh",[1,1,1])
#An=Analyze()
#GM=GMread(Ground_Motion)
#[Model.Udy,Model.U_dotdy,Model.U_ddotdy]=An.Dyn_Newmark(Model,DynOp,[],GM)

#Static Analysis
#An.Displ(Model,el)


#plot=PlotModel()
#plot.Struct(Model,el)
#plot.DefShape(Model,el)
#animation = plot.AnimateDefShape(Model,el,100)
