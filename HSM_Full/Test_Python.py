import numpy as np
def Test_Python(self):
    A = np.array([[1,4,5],[2,4,6],[8,9,1]])
    b = np.array([[1],[3],[9]])
    for i in range(100000):
        x = np.linalg.inv(A) @ b

    return x[0]
    
