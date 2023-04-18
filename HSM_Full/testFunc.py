import numpy as np
import matplotlib.pyplot as plt
from Model import Model
from Element import Element
def testFunc(GM):
    print("I hate this")
    #print(GM)
    GMnew = []
    for i in range(len(GM)):
        GMnew.append(float(GM[i]))
    GM2 = GMnew.copy()
    GM3 = np.array(GM2)
    #print(GM2)
    print(GM.tolist())
    print(GM)
    #print(np.array(GMnew))
    return 1