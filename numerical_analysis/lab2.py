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
        for row in self.A:
            print(row)

#    def beta(self,i):
#        answer = sign(-self.A[i][i]) * sqrt(sum([X*X for X in self.A[i][i:]]))
#        return answer
    def beta(self,i):
        answer = sign(-self.A[i][i])
        summ = 0
        for k in range(i,self.n):
            summ += self.A[k][i]*self.A[k][i]
        return answer * sqrt(summ)



    def multiply(self, w):
        n = self.n
        B = [[0 for _ in range(n)] for _ in range(n)]

        for j in range(n):
            summ = 0
            for k in range(n):
                summ += w[k] * self.A[k][j]
            summ *= 2
            for i in range(n):
                B[i][j] = self.A[i][j] - w[i]*summ


    def my(self,b,x):
        znamenatel = 2*b*b - 2*b*x
        znamenatel = sqrt(znamenatel)
        return 1/znamenatel



    def calculation(self):

        n = self.n
        self.f = [sum([self.A[i][j]*self.x[j] for j in range(n)]) for i in range(n)]

        for i in range(1):

#            self.show()

            b = self.beta(i)
            # check m == 0
            m = self.my(b,self.A[i][i])
            w = [0] * i + self.A[i][i:]
            w[i] -= b
            w = [z*m for z in w]


            print(sqrt(sum([qwe*qwe for qwe in w])))

            H = [[0 for _ in range(n)] for _ in range(n)]
            for I in range(n):
                for J in range(n):
                    H[I][J] = kron(I,J) - 2*w[I]*w[J]
            H1 = np.array(H)
            W = np.array(w)
            print(H1)
            AA = np.array(self.A)
            print(np.dot(H1,AA))




m = Matrix(3,3)
m.calculation()
