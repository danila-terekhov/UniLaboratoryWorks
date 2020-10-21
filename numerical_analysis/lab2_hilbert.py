#!/usr/bin/env python3
# -*- coding: utf-8 -*-
from random import *

def non_zero_randfloat(rang):
    while True:
        x = round(uniform(-rang,rang), 2)
        if x:
            return x

def randlist_wo_zero(size, rang):
    a = [non_zero_randfloat(rang) for _ in range(size)]
    return a

def kron(i,j):
    return i==j

kron = lambda x,y: (0,1)[x == y]
sign = lambda x: (1,-1)[x < 0]
sqrt = lambda x: x**(0.5)
my = lambda b,x: 1/sqrt(2*b*b - 2*b*x)

class Matrix:

    def __init__(self, size=10, rang=10):
        self.n = size
        #self.A = [randlist_wo_zero(self.n, rang) for _ in range(size)]
        self.A = [[0.0 for _ in range(self.n)] for _ in range(self.n)]
        #self.x = randlist_wo_zero(self.n, rang)
        self.x = [1] * self.n
        self.f = [None] * self.n


    def show(self):
        print("Matrix:")
        for row in self.A:
            print(row)
        print()

    def beta(self,i):
        summ = 0
        for k in range(i, self.n):
            summ += self.A[k][i]*self.A[k][i]
        summ = sqrt(summ)
        return sign(-self.A[i][i]) * summ

    def multiply(self, w):

        n = self.n
        for j in range(n):
            summ = 0
            for k in range(n):
                summ += w[k] * self.A[k][j]
            summ *= 2

            for i in range(n):
                self.A[i][j] -= w[i] * summ
                #self.A[i][j] = round(self.A[i][j],13)



    def calculation(self):

        n = self.n
        for i in range(n):
            for j in range(n):
                self.A[i][j] = 1/(i+j+1)
        self.f = [sum(self.A[i]) for i in range(n)]
        for i in range(n):
            print(self.A[i],self.f[i])
        #self.f = [sum([self.A[i][j]*self.x[j] for j in range(n)]) for i in range(n)]

        for i in range(n-1):

            b = self.beta(i)

            if self.A[i][i] == b:
                continue

            m = my(b, self.A[i][i])

            w = [0]* i
            w.append(m*(self.A[i][i] - b))
            for k in range(i+1,n):
                w.append(m*self.A[k][i])

            self.multiply(w)

        x = [None] * n
        x[n-1] = self.f[n-1] / self.A[n-1][n-1]

        for i in range(n-2, -1, -1):
            summ = self.f[i]
            for k in range(i+1, n):
                summ -= x[k] * self.A[i][k]
            x[i] = summ / self.A[i][i]

        delta = [0.0 for _ in range(n)]
        q = 0.01
        for i in range(n):
            if abs(x[i]-self.x[i]) > q:
                delta[i] = abs((x[i]-self.x[i])/self.x[i])
            else:# abs(x[i]-xz[i]) <= q:
                delta[i] = abs(x[i]-self.x[i])

        return max([abs(x[i]-1) for i in range(n)])

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
#   print("Size of matrix: %d x %d"  % (m.n, m.n))
    print("Input ", size,ranges)
    print("Error: %.3g" % e)
    #m.show()
