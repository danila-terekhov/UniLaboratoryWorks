#!/usr/bin/enb python3
# -*- coding: utf-8 -*-

f = lambda x: 2*x*x - 12*x
#step 1
a = 0
b = 10
e = 1
k = 0

# step2
x = (a+b)/2
abs_l = b-a
f_x = f(x)

while 1:
    print(f"K={k}")
    # step 3
    y = a + abs_l/4
    z = b - abs_l/4
    f_y = f(y)
    f_z = f(z)
    print(f"step3: y={y},z={z},f(y)={f_y},f(z)={f_z}")
    # step 4
    if (f_y < f_x):
        b = x
        #a = a
        x = y
    # step 5
    elif ( f_z < f_x ):
        a = x
        #b = b
        x = z
    else :
        a = y
        b = z
        #x = x
    print(f"before step6: a={a}, b={b}, x={x}")
    print()
    # step 6
    abs_l = b - a
    if (abs_l <= e):
        break
    else:
        f_x = f(x)
        k = k+1

x_star = (a+b)/2
#N = 1+3*k
#R = lambda N: 1/2**(N/2)
print(f"x*:{x_star}")#, N={N}, R(N)={R(N)}, k={k}")
