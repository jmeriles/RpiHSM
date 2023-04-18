import numpy as np
from Model import Model
from PlotModel import PlotModel

def CreatePlot(Model,el):
    print("attempt")
    print(el[0].node)
    print(el[0].BOUN)
    print(el[0].CON)
    print(el[0].id_v)
    print(el[0].controlDOF);
    plot=PlotModel()
    plot.Struct(Model,el)
    return 1