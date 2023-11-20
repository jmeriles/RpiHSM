#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Mon Jul 31 19:56:40 2023

@author: juanmeriles
"""

import numpy as np
import matplotlib.pyplot as plt
from Model import Model
from PlotModel import PlotModel
from Analyze import Analyze
from GMread import GMread
from Time_Integrator import InitializeAlphaOS,AlphaOS
import scipy.interpolate as sp
#from PlotHybridResults import PlotHybridResults


NODE = np.array([[0,236.16,-1302.96,0],
                 [0,236.16,-900,0],
                 [0,236.16,-500,0],
                 [0,236.16,0,0],
                 [0,236.16,500,0],
                 [0,236.16,900,0],
                 [0,236.16,1341.84,0],
                 [0,0,0,0]])

CON = np.array([[8,4],
                [1,2],
                [2,3],
                [3,4],
                [4,5],
                [5,6],
                [6,7]])

BC = np.array([[1,1,1,0,0,0],
               [0,0,0,0,0,0],
               [0,0,0,0,0,0],
               [0,0,0,0,0,1],
               [0,0,0,0,0,0],
               [0,0,0,0,0,0],
               [1,1,1,0,0,0],
               [1,1,1,1,1,1]])

        
E = 4030.5
A = 14046.62
Iy = 78753254.4
Iz = 3739281.41
v = 0.1
J = 7080141.3

#Need confimation of this...
concreteDens = (0.0868056 / 386.22) / 1000

el_prop = np.array([[E,A,J,v,Iy,Iz,0,1,0.0,0,0],
                    [E,A,J,v,Iy,Iz,concreteDens,0,0],
                    [E,A,J,v,Iy,Iz,concreteDens,0,0],
                    [E,A,J,v,Iy,Iz,concreteDens,0,0],
                    [E,A,J,v,Iy,Iz,concreteDens,0,0],
                    [E,A,J,v,Iy,Iz,concreteDens,0,0],
                    [E,A,J,v,Iy,Iz,concreteDens,0,0],
                    [E,A,J,v,Iy,Iz,concreteDens,0,0]])


el_rel = -1*np.ones((7,12))

customProps = -1
el_load = np.zeros((7,6))

node_load = np.zeros((8,6))


modelProp = np.array([1,0])

dynOpt = np.array([1,0,0,.7 * 386.22,.01,.01,0,0.0407,0,5])

hybridProps = np.array([[[ 0,0,0,0,0,0,0,0,0,0,0,0],
                         [ 0,0,0,0,0,0,0,0,0,0,0,0],
                         [ 0,0,0,0,0,0,0,0,0,0,0,0],
                         [ 0,0,0,0,0,0,0,0,0,0,0,0],
                         [ 0,0,0,0,0,0,0,0,0,0,0,0],
                         [ 0,0,0,0,0,0,0,0,0,0,0,0],
                         [ 0,0,0,0,0,0,0,0,0,0,0,0],
                         [ 0,0,0,0,0,0,0,300,0,0,0,0],
                         [ 0,0,0,0,0,0,0,0,0,0,0,0],
                         [ 0,0,0,0,0,0,0,0,0,0,0,0],
                         [ 0,0,0,0,0,0,0,0,0,0,0,0],
                         [ 0,0,0,0,0,0,0,0,0,0,0,0]]])
'''
hybridProps = np.array([[[239731, 0, 0, 0, 0, 0, -239731, 0, 0, 0, 0, 0],
                        [0, 13731.2, 0, 0, 0, 1.62138e+06, 0, 0, 0, 0, 0, 1.62138e+06],
                        [0, 0, 289194, 0, -3.41481e+07, 0, 0, 0, -289194, 0, -3.41481e+07, 0],
                        [0, 0, 0, 13627.4, 0, 0, 0, 0, 0, -13627.4, 0, 0],
                        [0, 0, -3.41481e+07, 0,5.37627e+09, 0, 0, 0, 3.41481e+07, 0, 2.68814e+09, 0],
                        [0, 1.62138e+06, 0, 0, 0, 2.55271e+08, 0, 0, 0, 0, 0, 1.27635e+08],
                        [-239731, 0, 0, 0, 0, 0, 239731, 0, 0, 0, 0, 0],
                        [0, 0, 0, 0, 0, 0,  0, 300, 0, 0, 0, 0],
                        [0, 0, -289194, 0, 3.41481e+07, 0, 0, 0, 289194, 0, 3.41481e+07, 0],
                        [0, 0, 0, -13627.4, 0, 0, 0, 0, 0, 13627.4, 0, 0],
                        [0, 0, -3.41481e+07, 0, 2.68814e+09, 0, 0, 0, 3.41481e+07, 0, 5.37627e+09, 0],
                        [0, 1.62138e+06, 0, 0, 0, 1.27635e+08, 0, 0, 0, 0, 0, 2.55271e+08]]])

'''
controlProps = np.array([[0,0,0,0,0,0,0,1,0,0,0,0]])

if modelProp[0] == 0:
    dim = 'Planar'
elif modelProp[0] == 1:
    dim = '3D'
else:
    print("ERROR, dimension is neither 2D nor 3D")


ModelSet=[dim,'line']

Node_Mass = NODE[:,-1].tolist()
NODE = NODE[:,0:-1].tolist()
CON = CON.tolist()

selfweight = modelProp[1]


myModel=Model(NODE,CON,Node_Mass,selfweight,ModelSet)
myModel.BOUN = BC.tolist()
myModel.LOAD = node_load.tolist()

el=myModel.init_el()
print("el setup")
numhybrid = 0
numcustom = 0
for i in range(len(el_rel)):
    for j in range(len(el_rel[0])):
        if el_rel[i][j] == -1:
            el_rel[i][j] = np.inf
print(el_rel)
                   
    
for i in range (myModel.numel):
    if dim == '3D':
        el[i].Iy=el_prop[i][4]
        el[i].Iz=el_prop[i][5]
        el[i].A=el_prop[i][1]
        el[i].E=el_prop[i][0]
        el[i].G=1/(2*(1+el_prop[i][3]))
        el[i].J=el_prop[i][2]
        el[i].rho=el_prop[i][6]
        el[i].hybrid = el_prop[i][7]
        el[i].custom = el_prop[i][8]
        el[i].w_x = el_load[i][0]
        el[i].w_y = el_load[i][1]
        el[i].w_z = el_load[i][2]
        el[i].m_x = el_load[i][3]
        el[i].m_y = el_load[i][4]
        el[i].m_z = el_load[i][5]
        el[i].REL = el_rel[i].tolist()
    elif dim == "Planar":
        el[i].Iz=el_prop[i][2]
        el[i].A=el_prop[i][1]
        el[i].E=el_prop[i][0]
        el[i].rho=el_prop[i][3]
        el[i].hybrid = el_prop[i][4]
        el[i].custom = el_prop[i][5]
        el[i].w_x = el_load[i][0]
        el[i].w_y = el_load[i][1]
        el[i].m_z = el_load[i][2]
        el[i].REL = el_rel[i].tolist()
    if el[i].hybrid == 1:
        el[i].ke = hybridProps[numhybrid]
        el[i].controlDOF = controlProps[numhybrid]
        numhybrid+=1
    if el[i].custom == 1:
        el[i].ke = customProps[numcustom]
        numcustom+=1

myModel.DynOp = [dynOpt[6],dynOpt[5],[dynOpt[0],dynOpt[1],dynOpt[2],0,0,0]]
print("Does it not like DynOp?")
el=myModel.elMat(el)
myModel.Create_B(el)
myModel.Create_K()

myModel.Create_M()
myModel.Create_Loading(el)
myModel.CheckHybridEl(el)
myModel.Eig()
myModel.Create_C("Rayleigh",[dynOpt[7],int(dynOpt[8]),int(dynOpt[9])])



Ground_Motion='Kobe(EQ9)_reinterp.txt'

import os
import numpy as np
THIS_FOLDER = os.path.dirname(os.path.abspath(__file__))
GM1 = os.path.join(THIS_FOLDER, Ground_Motion)

GM=[]

f=open(GM1)

for line in f.readlines():
    GM.append(float(line))
GM = np.array(GM)*dynOpt[3]
f.close

dtold = .01
told = np.arange(0,dtold*len(GM),dtold)


#interpolate eq
GM_new=sp.interp1d(told,GM)

dt = myModel.DynOp[1]
time = np.arange(0,dtold*(len(GM)-1),dt)
GM = GM_new(time)
#Eq_a = Eq_a/40
GM = np.hstack((GM))
time = np.arange(0,dt*(len(GM)),dt)

#Doing this confirmed that the time integrator is not the problem. The slight diff
#in the mass matrix causes any discrepencies with opensees. But mass matrix is SO close
#DynOp=[.25,.5,.01,[1 / 386.4,0,0]]
#An=Analyze()
#[U,dUdt,ddUddt, Pbar]=An.Dyn_Newmark(myModel,DynOp,[],GM)


(myModel,uddot0) = InitializeAlphaOS(myModel,el,GM)
#print("MDOFS              ___________")
#print(myModel.mDOF[0])
#print(myModel.mDOF[1])
uhist = [0]
udothist = [0]
uddothist = [uddot0]
measfvec = []
u_next = [0,0]
for i in range(1,len(GM)-1):
    meas_f = 10 * [30*u_next[0]]
    #meas_f = []
    
    measfvec.append(meas_f)
    (myModel,u_next,udot,uddot) = AlphaOS(myModel,el,meas_f,GM,i)
    uhist.append(u_next)
    udothist.append(udot)
    uddothist.append(uddot)
 
#plt.plot(uhist)
#A=PlotHybridResults(myModel)

plt.figure(4)
plt.plot(myModel.u[0])
plotter=PlotModel()
plotter.Struct(myModel,el)
