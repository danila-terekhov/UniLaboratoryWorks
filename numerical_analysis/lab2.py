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
sqrt = lambda x: x**(1/2)
my = lambda b,x: 1/sqrt(2*b**2 - 2*b*x)

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
        answer = sign(-self.A[i][i]) * sqrt(sum([X**2 for X in self.A[i][i:]]))
        return answer

    def calculation(self):

        n = self.n
        self.f = [sum([self.A[i][j]*self.x[j] for j in range(n)]) for i in range(n)]

        b = self.beta(0)
        m = my(b,self.x[0])
        





m = Matrix()
m.calculation()
