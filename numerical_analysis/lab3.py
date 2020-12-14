#!/usr/bin/env python3
# -*- coding: utf-8 -*-
from random import *
import numpy as np

sign = lambda x: (1,-1)[x < 0]
sqrt = lambda x: x**(0.5)

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
        self.rang = rang

        self.l = randlist_wo_zero(self.n, lambda_rang)
        self.l = np.diag(self.l)

        w = np.array(randlist_wo_zero(self.n, rang))
        wn = np.linalg.norm(w)
        self.w = [ W/wn for W in w]

        w2 = np.atleast_2d(self.w)
        W = 2*(w2.T*self.w)
        self.H = np.eye(size)-W

        self.A = self.H@self.l@self.H.T
        print(self.A)

    def show(self):
        print("Matrix:")
        for row in self.A:
            print(row)
        print()

    def findMaxElem(self):
        max_row = max_col = 0
        max_elem = self.A[max_row][max_col]
        for i in range(self.n):
            for j in range(i):
                if (abs(self.A[i][j]) > max_elem):
                    max_elem = abs(self.A[i][j])
                    max_row = i
                    max_col = j
        return max_row, max_col, max_elem


    def jacobian_rotation(i,j,c,s):
       pass


    def calculation(self, M, eps):
        n = self.n
        K = 0
        diagonal = np.diag(self.A) # take diagonal of matrix
        while K < M:
            i, j, max_elem = self.findMaxElem()

            if max_elem < eps:
                break

            p = 2*self.A[i][j]
            q = self.A[i][i] - self.A[j][j]
            d = sqrt(p*p + q*q)

            if (q == 0):
                c = s = sqrt(2)/2
            else:
                r = abs(q)/(2*d)
                c = sqrt(0.5+r)
                s = sqrt(0.5-r)*sign(p*q)

            self.jacobian_rotation(i,j,c,s)


            K+=1

#        q = 0.001
#        for i in range(n):
#            if abs(x[i]-self.x[i]) > q:
#                delta[i] = abs((x[i]-self.x[i])/self.x[i])
#            else:# abs(x[i]-xz[i]) <= q:
#                delta[i] = abs(x[i]-self.x[i])
#
#        return max(delta)
        return 0


#MAX_VNEDIAG_ELEM
#NUMBER_OF_STEP













if __name__ == "__main__":
    print("\n\
Численные методы\n\
Лабораторная N3 \n\
Вариант: 13\n\
Ученик: Терехов Данила Евгеньевич\n\
Преподаватель: Шабунина Зоя Александровна\n\
Курс: 3\n\
Группа: 8\n")
#    size,ranges = [int(a) for a in input("Enter size and range: (10,100,1000) : ").split()]
    print()
    size = 4
    ranges = 10

    count_succes = 0
    acc = [] ; err = []
    while count_succes<10:
        m = Matrix(size,ranges)
        e = m.calculation(10,10)
        err.append(e)
        count_succes += 11

#    e = sum(err)/len(err)
#    print("Input ", size,ranges)
#    print("Error: %.3g" % e)
