import msvcrt
import time
import os
import ctypes
import numpy as np

def cls():
    os.system('cls')
    
def gotoxy(x, y):
    ctypes.windll.kernel32.SetConsoleCursorPosition(ctypes.windll.kernel32.GetStdHandle(-11), (((y & 0xFFFF) << 0x10) | (x & 0xFFFF)))

def printBackground():
    for j in range(22):
        for i in range(12):
            if background[j, i] == 1:
                gotoxy(i, j)
                print("*")
            else:
                gotoxy(i, j)
                print("-")
                
def printBackgroundData():
    for j in range(22):
        for i in range(12):
            if background[j, i] == 1:
                gotoxy(i + 15, j)
                print("1")
            else:
                gotoxy(i + 15, j)
                print("0")

def makeBlock():
    for j in range(4):
        for i in range(4):
            gotoxy(x + i, y + j)
            if block_L[rotate, j, i] == 1:
                print("*")
        
def deleteBlock():
    for j in range(4):
        for i in range(4):
            if block_L[rotate, j, i] == 1:
                gotoxy(x + i, y + j)
                print("-")

def overlapCheck(offset_x, offset_y):
    overlap_count = 0
    for j in range(4):
        for i in range(4):
            if block_L[rotate, j, i] == 1 and background[j + y + offset_y, i + x + offset_x] == 1:
                overlap_count += 1
    return overlap_count

def overlapCheckRotate():
    overlap_count = 0
    tmp = rotate
    tmp += 1
    if tmp == 4:
        tmp = 0
    
    for j in range(4):
        for i in range(4):
            if block_L[tmp, j, i] == 1 and background[j + y, i + x] == 1:
                overlap_count += 1
    return overlap_count

def insertBlock():
    for j in range(4):
        for i in range(4):
            gotoxy(x + i, y + j)
            if block_L[rotate, j, i] == 1:
                background[y + j, x + i] = 1
                print("*")
                
def lineCheck(line_num):
    block_count = 0
    for i in range(10):
        if background[line_num, i + 1] == 1:
            block_count += 1
    if block_count == 10:
        for j in range(line_num, 1, -1):
            for i in range(10):
                background[j, i + 1] = background[j - 1, i + 1]
        printBackground()
        printBackgroundData()

#-------------------------------------

background = np.array([
    [1,1,1,1,1,1,1,1,1,1,1,1],
    [1,0,0,0,0,0,0,0,0,0,0,1],
    [1,0,0,0,0,0,0,0,0,0,0,1],
    [1,0,0,0,0,0,0,0,0,0,0,1],
    [1,0,0,0,0,0,0,0,0,0,0,1],
    [1,0,0,0,0,0,0,0,0,0,0,1],
    [1,0,0,0,0,0,0,0,0,0,0,1],
    [1,0,0,0,0,0,0,0,0,0,0,1],
    [1,0,0,0,0,0,0,0,0,0,0,1],
    [1,0,0,0,0,0,0,0,0,0,0,1],
    [1,0,0,0,0,0,0,0,0,0,0,1],
    [1,0,0,0,0,0,0,0,0,0,0,1],
    [1,0,0,0,0,0,0,0,0,0,0,1],
    [1,0,0,0,0,0,0,0,0,0,0,1],
    [1,0,0,0,0,0,0,0,0,0,0,1],
    [1,0,0,0,0,0,0,0,0,0,0,1],
    [1,0,0,0,0,0,0,0,0,0,0,1],
    [1,0,0,0,0,0,0,0,0,0,0,1],
    [1,0,0,0,0,0,0,0,0,0,0,1],
    [1,0,0,0,0,0,0,0,0,0,0,1],
    [1,0,0,0,0,0,0,0,0,0,0,1],
    [1,1,1,1,1,1,1,1,1,1,1,1]
])

# block_L = np.array([
#     [0,0,0,0],
#     [0,1,0,0],
#     [0,1,1,1],
#     [0,0,0,0]
# ])
    
block_L = np.array([
    [[0,0,0,0],
     [0,1,0,0],
     [0,1,1,1],
     [0,0,0,0]],
    
    [[0,0,0,0],
     [0,1,1,0],
     [0,1,0,0],
     [0,1,0,0]],
    
    [[0,0,0,0],
     [1,1,1,0],
     [0,0,1,0],
     [0,0,0,0]],
    
    [[0,0,1,0],
     [0,0,1,0],
     [0,1,1,0],
     [0,0,0,0]]
])

x = 3
y = 3
count = 0
rotate = 0

#-------------------------------------

printBackground()
printBackgroundData()
while(1):
    if msvcrt.kbhit():
        key = msvcrt.getch()
        
        if key == b'a':
            if overlapCheck(-1, 0) == 0:
                deleteBlock()
                x -= 1
                makeBlock()
        elif key == b'd':
            if overlapCheck(1, 0) == 0:
                deleteBlock()
                x += 1
                makeBlock()
        elif key == b's':
            if overlapCheck(0, 1) == 0:
                deleteBlock()
                y += 1
                makeBlock()
        elif key == b'r':
            if overlapCheckRotate() == 0:
                deleteBlock()
                rotate += 1
                if rotate == 4:
                    rotate = 0
                makeBlock()
#-------------------------------------
    
    if count == 100:
        count = 0
        
        if overlapCheck(0, 1) == 0:
            deleteBlock()
            y += 1
            makeBlock()
        else:
            insertBlock()
            printBackgroundData()
            
            for i in range(1, 21):
                lineCheck(i)
            
            x = 3
            y = 3
    
    count += 1
    time.sleep(0.01)
