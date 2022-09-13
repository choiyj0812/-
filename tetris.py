import msvcrt
import time
import os
import ctypes
import numpy as np

def cls():
    os.system('cls')

def makeBlock():
    for i in range(4):
        for j in range(4):
            if block_L[i][j] == 0:
                print("-", end=' ')
            else:
                print("*", end=' ')
        print()

#-------------------------------------

block_L = np.array([
    [0,0,0,0],
    [0,1,0,0],
    [0,1,1,1],
    [0,0,0,0]
])

blynk = int(0)

#-------------------------------------

while(1):
    for i in range(gap):
        print()
    blynk += 1
    
    makeBlock()
    time.sleep(1)
    cls()