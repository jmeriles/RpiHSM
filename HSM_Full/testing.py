import numpy as np
import matplotlib.pyplot as plt
from Model import Model
from PlotModel import PlotModel
from Analyze import Analyze
from GMread import GMread


ModelSet=['3D','line']

Node_Mass = [0,0,0]
NODE = [[0,0,0],[0,0,0],[0,0,0]]

selfweight = 0

CON = [[1,2],[2,3]]
print(NODE)
print(CON)
print(Node_Mass)
print(selfweight)
print(ModelSet)
myModel=Model(NODE,CON,Node_Mass,selfweight,ModelSet)

myModel.BOUN = [[0,0,0,0,0,0],[0,0,0,0,0,0],[0,0,0,0,0,0]]
#myModel.LOAD = node_load

el=myModel.init_el()
