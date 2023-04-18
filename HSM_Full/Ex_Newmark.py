import numpy as np
def Ex_Newmark(self,data1,data2):
    A = np.matrix([[23451,1900],
                   [131,112]])
    b = np.matrix([[900],
                   [200]])
    a = np.linalg.inv(A) @ b
    
                
    return a[1,1]
