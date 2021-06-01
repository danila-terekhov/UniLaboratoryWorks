#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import math

data="input2.txt"

"""
y(x) = x+1
y'(x) = 1
y''(x) = 0

p(x) = 1
q(x) = -2
f(x) == 2x+2

(p(x)*y'(x))'-q(x)*y(x)=f(x)
"""

def f(x):
   return 2*x+2


def p(x):
    return 1


def q(x):
    return -2


def u(x, z, y):
    return f(x) + q(x)*y


def v(x, z, y):
    return z


def f11(x, y1, y2):
    return q(x) - (y1 ** 2) / p(x)


def f12(x, y1, y2):
    return f(x) - (y1 * y2) / p(x)


def f21(x, y1, y2):
    return 1 / (p(x)) - q(x) * y1 ** 2


def f22(x, y1, y2):
    return f(x) * y1 - q(x) * y1 * y2



def integrate(x, y1, y2, h, f1, f2):

    k11 = h * f1(x, y1, y2)
    k12 = h * f2(x, y1, y2)

    k21 = h * f1((x + h), (y1 + k11), (y2 + a * k12))
    k22 = h * f2((x + h), (y1 + k11), (y2 + a * k12))

    y1 = y1 + (k11 + k21)/2
    y2 = y2 + (k12 + k22)/2

    return y1, y2


def transfer(a, b):
    pass
        # | ->   from x=b to x=a











if __name__ == "__main__":
    with open(data, 'r') as file:
        line = file.readline().split()
        A1=float(line[0])
        B1=float(line[1])
        G1=float(line[2])
        A2=float(line[3])
        B2=float(line[4])
        G2=float(line[5])
        line = file.readline().split()
        a=float(line[0])
        b=float(line[1])
        n=int(line[2])

        x = list()
        for i in range(2, n+2):
            line = file.readline().split()
            x.append(float(line[0]))

        if (A1*A1 + B1*B1 <= 0) or (A2*A2 + B2*B2 <= 0):
            print(" Error! краевое условие ")
            exit(1)

    if A1 != 
