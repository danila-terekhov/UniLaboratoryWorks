#!/usr/bin/env python

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

    def beta(self,i):
        answer = sign(-self.A[i][i]) * sqrt(sum([X*X for X in self.A[i][i:]]))
        return answer


    def multiply(self, w):
        n = self.n
        B = [[0 for _ in range(n)] for _ in range(n)]

        for j in range(n):
            summ = 0
            for k in range(n):
                summ += w[k] * self.A[k][j]
            for i in range(n):
                B[i][j] = self.A[i][j] - 2*w[i]*summ


        for row in B:
            print(row)


    def calculation(self):

        n = self.n
        self.f = [sum([self.A[i][j]*self.x[j] for j in range(n)]) for i in range(n)]

        for i in range(1):

            b = self.beta(0)
            # check m == 0
            m = my(b,self.x[0])
            w = [0.0] * i + self.A[i][i:]
            self.show()
            w[i] -= b
            self.multiply(w)







m = Matrix()
m.calculation()
