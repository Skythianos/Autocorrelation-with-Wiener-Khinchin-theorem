# -*- coding: utf-8 -*-
"""
Created on Fri Aug 18 10:54:50 2017

code is NOT optimized, 
it is for debugging purposes

@author: dv
"""
import numpy as np

def autocorr(x):
    result = np.correlate(x, x, mode='full')
    return result         # [result.size/2:]  for only positiv time lags
    
if __name__ == '__main__':
  data = np.loadtxt('lew.dat')
  data=data-np.mean(data)
  norm=np.sum(data**2)
  auto_corr=autocorr(data)/norm
  np.savetxt('lew_dat2.tmp', auto_corr, fmt='%.12f')
