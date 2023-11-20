import numpy as np
import matplotlib.pyplot as plt
from Model import Model
from PlotModel import PlotModel
from Analyze import Analyze
from GMread import GMread
import pickle as pkl


def Model_Setup(NODE,CON,BC,el_prop,el_rel,customProps,el_load,node_load,modelProp,dynOpt=None,hybridProps=None,controlProps=None):
    print("NODE")
    print(NODE)
    print("CON")
    print(CON)
    print("BC")
    print(BC)
    print("El Prop")
    print(el_prop)
    print("El Rel")
    print(el_rel)
    print("Custom Props")
    print(customProps)
    print("modelProp")
    print(modelProp)
    print("Dynamic Options")
    print(dynOpt)
    print("Hybrid Props")
    print(hybridProps)
    print("control Props")
    print(controlProps)
    
    
    
    
    
    
    
    print("Pycheck1")
    if modelProp[0] == 0:
        dim = 'Planar'
    elif modelProp[0] == 1:
        dim = '3D'
        print('3D')
    else:
        print("ERROR, dimension is neither 2D nor 3D")
    print("Pycheck1")
    if not hasattr(dynOpt,"__len__"):
        dynOpt = np.zeros(10)
        
    ModelSet=[dim,'line']
    print("Pycheck2")
    Node_Mass = NODE[:,-1].tolist()
    NODE = NODE[:,0:-1].tolist()
    CON = CON.tolist()
    print("Pycheck3")
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
                       
    print(el_prop)    
    for i in range (myModel.numel):
        if dim == '3D':
            el[i].Iy=el_prop[i][4]
            print('test1')
            el[i].Iz=el_prop[i][5]
            print('test2')
            el[i].A=el_prop[i][1]
            print('test2')
            el[i].E=el_prop[i][0]
            print('test3')
            el[i].G=el[i].E/(2*(1+el_prop[i][3]))
            print('test4')
            el[i].J=el_prop[i][2]
            print('test5')
            el[i].rho=el_prop[i][6]
            print('test6')
            el[i].hybrid = el_prop[i][7]
            print('test7')
            el[i].custom = el_prop[i][8]
            print('test8')
            el[i].w_x = el_load[i][0]
            print('test9')
            el[i].w_y = el_load[i][1]
            print('test10')
            el[i].w_z = el_load[i][2]
            print('test11')
            el[i].m_x = el_load[i][3]
            print('test12')
            el[i].m_y = el_load[i][4]
            print('test13')
            el[i].m_z = el_load[i][5]
            print('test14')
            el[i].REL = el_rel[i].tolist()
            print('test15')
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
            el[i].controlDOF = np.array(controlProps[numhybrid])
            print("Control Props")
            print(el[0].controlDOF)

            numhybrid+=1
        if el[i].custom == 1:
            el[i].ke = customProps[numcustom]
            numcustom+=1

    myModel.DynOp = [dynOpt[6],dynOpt[5],[dynOpt[0],dynOpt[1],dynOpt[2]]]
    print("Does it not like DynOp?")
    el=myModel.elMat(el)
    myModel.Create_B(el)
    myModel.Create_K()
    myModel.Create_M()
    myModel.Create_Loading(el)
    myModel.CheckHybridEl(el)
    myModel.Eig()
    myModel.Create_C("Rayleigh",[dynOpt[7],int(dynOpt[8]),int(dynOpt[9])])
    
    ModelDictionary = {'Model': myModel,'el': el}
    file = open('ModelFile.dat', 'w+b')
    pkl.dump(ModelDictionary,file)
    file.close()
    
    return (myModel,el)

def modelLoad(PickleFileName):
    print(PickleFileName)
    file = open(PickleFileName,'rb')
    ModelDictionary = pkl.load(file)
    file.close()
    Model = ModelDictionary['Model']
    el = ModelDictionary['el']
    return (Model, el)
    
def saveModel(Model,el):
    ModelDictionary = {'Model': Model,'el': el}
    file = open('ModelFile.dat', 'w+b')
    pkl.dump(ModelDictionary,file)
    file.close()
    return (1)
    

