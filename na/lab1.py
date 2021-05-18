#!/usr/bin/env python3
# -*- coding: utf-8 -*-

data="input1.txt"
rez="output1.txt"
import math
k=8 # константа для проверки на слишком большой шаг

def f(x,y):
    ret = x + y
    #ret = math.exp(x)+y
    return ret

#def solveK(h,x,y):
#    K = list()
#    K.append(h * f(x,y))
#    K.append(h * f(x + h/2, y + K[0]/2))
#    K.append(h * f(x + h, y - K[0] + 2*K[1]))
#    return K
h_min = MAX_ERROR=0.0001

MAX_ERROR_COUNT=0
MIN_ERROR_COUNT=0
COUNT=0
def integrate(x, y, h, pr=True):
    K = list()
    K.append(h * f(x,y))
    K.append(h * f(x + h/2, y + K[0]/2))
    K.append(h * f(x + h, y - K[0] + 2*K[1]))

    sol = y + (K[0] + 4*K[1] + K[2])/6 # 112
    err = y + K[1] # 113
    ret = abs(err - sol)
    global MAX_ERROR_COUNT, MIN_ERROR_COUNT, COUNT
    if (pr):
        print("x =",x," ,y =",sol," ,ret = ",ret)
        COUNT+=1
        if (ret > MAX_ERROR):
            MAX_ERROR_COUNT+=1
        if (h == h_min):
            MIN_ERROR_COUNT+=1


    return sol, ret

def solve(A,B,C,yc,h_min,eps):
    print("A =",A)
    print("B =",B)
    print("C =",C)
    print("y(c) =", yc)
    print("h_min =",h_min)
    print("eps =",eps)

    errorNotReached = 0
    numberOfPoints = 0
    numberOfPointsWithMinStep = 0

    end = B
    h = abs((A-B)/10)
    x = C
    y = yc
    print("x =",x," ,y =",y)


    while(True):
        while(x + h > end):
            h /= 2

        if not (end - (x+h) < h_min):
            while(True):
                if (h < h_min):
                    h = h_min
                    x = x + h
                    y, err = integrate(x, y, h)
                    break
                _, err = integrate(x, y, h, 0)
                if (err > eps):
                    h /= 2
                else:
                    x = x + h
                    y, err = integrate(x, y, h)
                    if (err < eps/k):
                        h *= 2
                    break
        else:
            if (end - x >= 2*h_min):
                #x_old = x
                #x = end - h_min
                #y, err = integrate(x, y, x-x_old)
                y, err = integrate(end-h_min, y, end-h_min-x)

                #x = end
                #y, err = integrate(x, y, h_min)
                y, err = integrate(end, y, h_min)
            elif (end - x <= 1.5*h_min):
                #x = end
                y, err = integrate(end, y, end-x)
            else:
                y, err = integrate(x + (end-x)/2, y, (end-x)/2) #x+(end-x)/2-x)
                y, err = integrate(end, y, (end-x)/2)
            break


if __name__ == "__main__":
    with open(data, 'r') as file:
        line = file.readline().split()
        A=float(line[0])
        B=float(line[1])
        C=float(line[2])
        yc=float(line[3])
        line = file.readline().split()
        h=float(line[0])
        eps=float(line[0])
    solve(A,B,C,yc,h,eps)
    print(MAX_ERROR_COUNT)
    print(COUNT)
    print(MIN_ERROR_COUNT)
