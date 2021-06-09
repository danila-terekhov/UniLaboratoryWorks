#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import math

data="input1.txt"
k=8 # константа для проверки на слишком большой шаг

def f(x,y):
    #ret = 4*x**3 + 4*y**3
    ret = 5*x**4 + 5*y**4
    #ret = x + y
    #ret = math.exp(x)+y
    #ret = math.cos(y)*x
    return ret

h_min = eps = 0
COUNT = MAX_ERROR_COUNT = MIN_ERROR_COUNT = 0

with open(data, 'r') as file:
    line = file.readline().split()
    A=float(line[0])
    B=float(line[1])
    C=float(line[2])
    yc=float(line[3])
    line = file.readline().split()
    h_min=float(line[0])
    eps=float(line[1])

def integrate(x, y, h, pr=True):
    K = list()
    K.append(h * f(x,y))
    K.append(h * f(x + h/2, y + K[0]/2))
    K.append(h * f(x + h, y - K[0] + 2*K[1]))

    sol = y + (K[0] + 4*K[1] + K[2])/6 # 112
    err = y + K[1] # 113
    ret = abs(err - sol)
    global MAX_ERROR_COUNT, MIN_ERROR_COUNT, COUNT
    global h_min, eps
    if (pr):
        print("x = {:<25} y = {:<25} err = {:<25}".format(x,sol,ret))
        COUNT+=1
        if (ret > eps):
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

    if C == B:
        dir = -1
        end = A
    elif C == A:
        dir = 1
        end = B


    h = abs((A-B)/10)
    x = C
    y = yc
    print("x =",x," ,y =",y)


    while(True):
        while(dir*(x + h*dir) > dir*end):
            h /= 2

        if not (abs(end - (x+h*dir)) < h_min):
            while(True):
                if (h < h_min):
                    h = h_min
                    x = x + h*dir
                    y, err = integrate(x, y, dir*h)
                    break
                _, err = integrate(x, y, dir*h, 0)
                if (err > eps):
                    h /= 2
                else:
                    x = x + h*dir
                    y, err = integrate(x, y, dir*h)
                    if (err < eps/k):
                        h *= 2
                    break
        else:
            if (end - x >= 2*h_min):
                #x_old = x
                #x = end - h_min
                #y, err = integrate(x, y, x-x_old)
                y, err = integrate(end-h_min*dir, y, dir*(end-h_min-x))

                #x = end
                #y, err = integrate(x, y, h_min)
                y, err = integrate(end, y, dir*(h_min))
            elif (end - x <= 1.5*h_min):
                #x = end
                y, err = integrate(end, y, dir*(end-x))
            else:
                y, err = integrate((x + (end-x)/2)*dir, y, dir*(end-x)/2) #x+(end-x)/2-x)
                y, err = integrate(end, y, dir*(end-x)/2)
            break


if __name__ == "__main__":
    solve(A,B,C,yc,h_min,eps)
    print("points =",COUNT)
    print("notReached =",MAX_ERROR_COUNT)
    print("h_min =",MIN_ERROR_COUNT)
