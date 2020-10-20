#!/usr/bin/env python
import numpy as np

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
        self.A = [randlist_wo_zero(self.n, rang) for _ in range(size)]
        self.x = randlist_wo_zero(self.n, rang)
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
        B = self.A
        for j in range(n):

            summ = 0
            for k in range(n):
                summ += w[k] * self.A[k][j]
            summ *= 2

            for i in range(n):
                self.A[i][j] -= w[i] * summ
                self.A[i][j] = round(self.A[i][j],13)



    def calculation(self):

        n = self.n
        self.f = [sum([self.A[i][j]*self.x[j] for j in range(n)]) for i in range(n)]

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
        















m = Matrix(10, 10)
m.calculation()
m.show()
