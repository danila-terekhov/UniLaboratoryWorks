#!/usr/bin/env python3
# -*- coding: utf-8 -*-
from random import *
from utils import *
import numpy as np
import math
import sys


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
        self.w = np.array([ W/wn for W in w])
        self.H = np.eye(size)-2*(self.w[..., None]*self.w)

        self.A = self.H@self.l@self.H.T

    def show(self):
        print("Matrix:")
        for row in self.A:
            print()
            print(row)
        print()

    def findMaxElem(self):
        max_row = 1
        max_col = 0
        max_elem = self.A[max_row][max_col]
        for i in range(2,self.n):
            for j in range(i):
                if (abs(self.A[i][j]) > max_elem):
                    max_elem = abs(self.A[i][j])
                    max_row = i
                    max_col = j
        return max_row, max_col, max_elem


    def mirror_row(self,i):
        for k in range(i):
            self.A[k][i] = self.A[i][k]
    def mirror_col(self,j):
        for k in range(j):
            self.A[j][k] = self.A[k][j]

    def jacobian_rotation(self, i,j,c,s):
#
#        for m in range(i):
#            self.A[i][m] = c*self.A[m][i] + s*self.A[m][j]
#        for m in range(j):
#            self.A[j][m] = -s*self.A[m][i] + c*self.A[m][j]
#        self.mirror_row(i)
#        self.mirror_row(j)
#
#        diagonal[i] = c:*self.A[i][i] + s*self.A[j][j]
#        diagonal[j] = -s*self.A[i][i] + c*self.A[j][j]
#
#        for l in range(i+1, self.n):
#            self.A[l][i] = c*self.A[i][l] + s*self.A[j][l]
#        for l in range(j+1, self.n):
#            self.A[l][j] = -s*self.A[i][l] + c*self.A[j][l]
#        self.mirror_col(i)
#        self.mirror_col(j)
#        diagonal[i] = c*self.A[i][i] + s*self.A[j][j]
#        diagonal[j] = -s*self.A[i][i] + c*self.A[j][j]

        tmp = self.A
        for m in range(self.n):
            tmp[i][m] = c*self.A[i][m] + s*self.A[j][m]
            tmp[j][m] = -s*self.A[i][m] + c*self.A[j][m]


        tmp = self.A
        for l in range(self.n): # TODO
            tmp[l][i] = c*self.A[l][i]+ s*self.A[l][j]
            tmp[l][j] = -s*self.A[l][i]+ c*self.A[l][j]

        self.A =tmp


    def calculation(self, M, eps):
        n = self.n
        K = 0
        diagonal = (np.diag(self.l)).tolist() # take diagonal of matrix
        self.A = self.A.tolist()
        while K < M:
            i, j, max_elem = self.findMaxElem()

            if max_elem < eps:
                break

            p = 2*self.A[i][j]
            q = self.A[i][i] - self.A[j][j]
#            d = sqrt(p*p + q*q)
#            if (q == 0):
#                c = s = sqrt(2)/2
#            else:
#                r = abs(q)/(2*d)
#                c = sqrt(0.5+r)
#                s = sqrt(0.5-r)*sign(p*q)
            tg_2_phi = p/q
            phi = math.atan(tg_2_phi)/2
            c = math.cos(phi)
            s = math.sin(phi)
            self.jacobian_rotation(i,j,c,s)
            K+=1


        delta = [0] * n
        for i in range(n):
            delta[i] = abs(self.A[i][i]-diagonal[i])
        return maх(delta), K


if __name__ == "__main__":
    print("\n\
Численные методы\n\
Лабораторная N3 \n\
Вариант: 13\n\
Ученик: Терехов Данила Евгеньевич\n\
Преподаватель: Шабунина Зоя Александровна\n\
Курс: 3\n\
Группа: 8\n")
    #size,lamb,eps = [int(a) for a in input("Enter size, range and epsilon grade: ").split()]
    print()
    size = int(sys.argv[1])
    lamb = int(sys.argv[2])
    eps = int(sys.argv[3])
    eps = 10**(-1*eps)
    ranges = 1000

    count_succes = 0
    acc = []; count = []
    while count_succes<10:
        m = Matrix(size,ranges, lamb)
        a,k = m.calculation(1000000, eps)
        acc.append(a)
        count.append(k)
        count_succes += 1

    a = sum(acc)/len(acc)
    c = sum(count)/len(count)
    print("Accuracy: %.3g" % a)
    print("Steps: %d" % c)
