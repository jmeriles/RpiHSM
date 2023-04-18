#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Fri Jul 31 12:36:25 2020

@author: jim53
"""
import os
import numpy as np
import scipy.interpolate as sp

def GMread(GM,DynOp):
    
    dtold = DynOp[4]
    told = np.arange(0,dtold*len(GM),dtold)
    print(GM)
    #interpolate eq
    GM_new=sp.interp1d(told,GM)
    
    dt=DynOp[5]
    time = np.arange(0,dtold*(len(GM)-1),dt)
    GM = GM_new(time)
    GM = GM*DynOp[3]
    GM = np.array(GM)

    return GM
