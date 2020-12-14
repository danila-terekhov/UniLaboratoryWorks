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


    def jacobian_rotation(self, i,j,c,s, diagonal):

        for m in range(self.n): # TODO
            self.A[i][m] = c*self.A[i][m] + s*self.A[j][m]
            self.A[j][m] = -s*self.A[i][m] + c*self.A[j][m]

        for l in range(self.n): # TODO
            self.A[l][i] = c*self.A[l][i] + s*self.A[l][j]
            self.A[l][j] = -s*self.A[l][i] + c*self.A[l][j]

        diagonal[i] = self.A[i][i]
        diagonal[j] = self.A[j][j]



    def calculation(self, M, eps):
        n = self.n
        K = 0
        diagonal = np.diag(self.A).tolist() # take diagonal of matrix
        self.A = self.A.tolist()
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

            self.jacobian_rotation(i,j,c,s,diagonal)
            K+=1

        q = 0.001
        delta = [0] * n
        for i in range(n):
            if abs(diagonal[i]-self.A[i][i]) > q:
                delta[i] = abs((diagonal[i]-self.A[i][i])/self.A[i][i])
            else:
                delta[i] = abs(diagonal[i]-self.A[i][i])
        return max(delta), K
#        q = 0.001
#        for i in range(n):
#            if abs(x[i]-self.x[i]) > q:
#                delta[i] = abs((x[i]-self.x[i])/self.x[i])
#            else:# abs(x[i]-xz[i]) <= q:
#                delta[i] = abs(x[i]-self.x[i])
#
#        return max(delta)



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
    size = 30
    ranges = 10
    lamb = 50
    eps = 10**(-9)

    count_succes = 0
    acc = []; count = []
    while count_succes<10:
        m = Matrix(size,ranges)
        a,k = m.calculation(1000000000, eps)
        acc.append(a)
        count.append(k)
        count_succes += 1

    a = sum(acc)/len(acc)
    c = sum(count)/len(count)
    print("size=%d,ranges=%d,lamb=%d,eps\n"% (size,ranges, lamb))
    print("Error: %.3g" % a)
