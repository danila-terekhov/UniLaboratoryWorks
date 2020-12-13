#!/usr/bin/env python3
# -*- coding: utf-8 -*-
from random import *
import numpy as np

def non_zero_randfloat(rang):
    while True:
        x = round(uniform(-rang,rang), 2)
        if x:
            return x

def randlist_wo_zero(size, rang):
    a = [non_zero_randfloat(rang) for _ in range(size)]
    return a


class Matrix:

    def __init__(self, size=10, rang=10, lambda_rang=10):
        self.n = size
        self.l = randlist_wo_zero(self.n, lambda_rang)

        tmp = [[0]*size for _ in range(size)]
        for i in range(size):
            tmp[i][i] = self.l[i]

        self.l = tmp

        w = randlist_wo_zero(self.n, rang)
        w = np.array(w)

    def show(self):
        print("Matrix:")
        for row in self.A:
            print(row)
        print()

    def calculation(self):

        n = self.n















#
#
#
#        x[n-1] = self.f[n-1] / self.A[n-1][n-1]
#
#        for i in range(n-2, -1, -1):
#            summ = self.f[i]
#            for k in range(i+1, n):
#                summ -= x[k] * self.A[i][k]
#            x[i] = summ / self.A[i][i]
#
#        delta = [0.0 for _ in range(n)]
#        q = 0.001
#        for i in range(n):
#            if abs(x[i]-self.x[i]) > q:
#                delta[i] = abs((x[i]-self.x[i])/self.x[i])
#            else:# abs(x[i]-xz[i]) <= q:
#                delta[i] = abs(x[i]-self.x[i])
#
#        return max(delta)
        return 0

if __name__ == "__main__":
    print("\n\
Численные методы\n\
Лабораторная N2 \n\
Вариант: 13\n\
Ученик: Терехов Данила Евгеньевич\n\
Преподаватель: Шабунина Зоя Александровна\n\
Курс: 3\n\
Группа: 8\n")
    size,ranges = [int(a) for a in input("Enter size and range: (10,100,1000) : ").split()]
    print()

    count_succes = 0
    acc = [] ; err = []
    while count_succes<10:
        m = Matrix(size,ranges)
        e = m.calculation()
        err.append(e)
        count_succes += 1

    e = sum(err)/len(err)
    print("Input ", size,ranges)
    print("Error: %.3g" % e)
