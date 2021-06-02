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


def transfer(a, b, A3, B3, f1, f2, x):
    h = -0.1
    # | ->   from x=b to x=a

    a3_tmp, b3_tmp = integrate(b, A3, B3, h, f1, f2)

    for i in range(len(x)-2, -1, -1):
        a3_tmp, b3_tmp = integrate(x[i], a3_tmp, b3_tmp, h, f1, f2)
        return a3_tmp, b3_tmp

def solve(a, b, yd, y, x):

    h = 0.1

    yd_tmp, y_tmp = integrate(a, yd, y, h, v, u)
    print(0,"\tx=", a, "\ty=", y_tmp, "\ty'=", yd_tmp)

    for i in range(1, len(x)):

        yd_tmp, y_tmp = integrate(x[i], yd_tmp, y_tmp, h, u, v)
        print(i,"\tx=", x[i], "\ty=", y_tmp, "\ty'=", yd_tmp)

    return yd_tmp, y_tmp



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
            print(" Error! 4")
            exit(4)

    c = b
    if A2 != 0:
        A3 = -(B2 * p(c)) / A2
        B3 = (G2 * p(c)) / A2
        A3, B3 = transfer(a, b, A3, B3, f11, f12, x)
        G3 = B3
        B3 = -A3
        A3 = p(a)
    elif B2 != 0:
        phi = -A2 / (B2 * p(c))
        psi = -G2 / B2
        phi,psi = transfer(a, b, phi, psi, f21, f22, x)
        G3 = psi
        B3 = -1
        A3 = phi * p(a)
    else:
        print(" Error! 2")
        exit(2)

    if A3 == A2 and B3 == B2 and G3 == G2:
        print(" Error! 1")

    D = A3*B1 - A1*B3
    if D == 0:
        print(" Error! 2 полученная система не совместна")
        exit(2)
    else:
        yd = (G3*B1 - G1 * B3) / D
        y = (A3*G1 - A1 * G3) / D
        yd, y = solve(a, b, yd, y, x)

