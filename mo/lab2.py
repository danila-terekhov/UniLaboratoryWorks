#!/usr/bin/env python3
# -*- coding: utf-8 -*-
import numdifftools as nd

def f(x):
    #return 2*x[0]*x[0]+x[1]*x[1]
    return (x[0]-1.2)**4 + (x[1]+1.2)**4

def fpx(x):
    return 4*(x[0]-1.2)**3

def fpy(x):
    return 4*(x[1]+1.2)**3

x=[0.5,1]
fx = f(x)

# step0
e = 10**-7
a = 1
k = 0
Nmax = 100000000

while k < Nmax:
    # STEP 2
    #grad = nd.Gradient(f)(x)
    grad = [fpx(x), fpy(x)]
    if sum([z*z for z in grad])**(1/2) < e:
        break
    # STEP 3
    x_new = [ x[i]-a*grad[i] for i in range(len(grad))]
    while f(x_new) > fx:
        a = a/2
        x_new = [ x[i]-a*grad[i] for i in range(len(grad))]

    x = x_new
    fx = f(x_new)
    k+=1

print("x =", end=" ")
for i in range(len(x)):
    print("%.9g" % round(x[i], 9), end=" ")

print()
print("f(x) = %.7g" % round(f(x),3))
print("k = %g" % k)
