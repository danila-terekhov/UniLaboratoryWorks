#!/usr/bin/env python3
# -*- coding: utf-8 -*-
import numdifftools as nd

def f(x):
    return 2*x[0]*x[0]+x[1]*x[1]
x=[0.5,1]
fx = f(x)

# step0
e = 10**-2
a = 1
k = 0
Nmax = 100000000

while k < Nmax:
    # STEP 2
    grad = nd.Gradient(f)(x)
    #print(f"grad={grad}")
    if sum([z*z for z in grad])**(1/2) < e:
        break
    # STEP 3
    x_new = [ x[i]-a*grad[i] for i in range(len(grad))]
    #print(f"f(x0)={f(x)}")
    #print(f"f(x1)={f(x_new)}")

    while f(x_new) > fx:
        a = a/2
        x_new = [ x[i]-a*grad[i] for i in range(len(grad))]
        #print(f"a={a}")
        #print(f"x_new={x_new}")
        #print(f"f(x0)={f(x)}")
        #print(f"f(x1)={f(x_new)}")
    x = x_new
    fx = f(x_new)
    k+=1

print("x =", end=" ")
for i in range(len(x)):
    print("%.3g" % round(x[i], 3), end=" ")

print()
print("f(x) = %.3g" % round(f(x),3))
print("k = %g" % k)
