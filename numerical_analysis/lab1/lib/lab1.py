from random import *

def non_zero_randfloat(rang):
    while True:
        x = randint(-rang, rang)
        if x:
            return float(x)

def randlist_wo_zero(size, rang):
    a = [non_zero_randfloat(rang) for _ in range(size)]
    return a

class Matrix:

    def __init__(self, size=10, rang=10):
        self.n = size
        self.a = randlist_wo_zero(size, rang)
        self.b = randlist_wo_zero(size, rang)
        self.c = randlist_wo_zero(size, rang)
        self.p = randlist_wo_zero(size, rang)
        self.q = randlist_wo_zero(size, rang)
        self.f = [1.0 for _ in range(self.n)]
        self.a[0] = self.c[self.n-1] = 0.0
        self.p[0] = self.b[0]
        self.p[1] = self.a[1]
        self.q[self.n-1] = self.b[self.n-1]
        self.q[self.n-2] = self.c[self.n-2]


    def show(self):
        matrix = [[0.0 for _ in range(self.n)] for _ in range(self.n)]
        for i in range(self.n):
            matrix[i][0] = self.p[i]
            matrix[i][self.n-1]= self.q[i]
            matrix[i][i] = self.b[i]
            if i>0:
                matrix[i][i-1] = self.a[i]
            if i<self.n-2:
                matrix[i][i+1] = self.c[i]
            print(matrix[i]," | ", self.f[i])

    def calculation(self):

        n = self.n

        for i in range(1,n-1):
            R = self.b[i]**-1 ; self.b[i] = 1.0
            self.c[i] *= R ; self.p[i] *= R ; self.q[i] *= R ; self.f[i] *= R
            R = self.a[i+1] ;# self.a[i+1] = 0.0
            self.a[i+1] -= R*self.b[i]
            self.b[i+1] -= R*self.c[i]
            self.f[i+1] -= R*self.f[i]
            self.p[i+1] -= R*self.p[i]
            self.q[i+1] -= R*self.q[i]

        self.c[n-1] = self.q[n-1]
        #R = self.b[n-3]**-1 ; self.b[n-3] = 1.0

        print (self.c[n-2], self.q[n-2])
#        self.p[n-1] /= self.q[n-1] ; self.f[n-1] /= self.q[n-1] ; self.q[n-1] = 1

#        for i in range(n//2-1, -1, -1):
#            if self.b[i]:
#                R = self.b[i]**-1 ; self.b[i] = 1.0
#                self.a[i] *= R ; self.p[i] *= R ; self.q[i] *= R ; self.f[i] *= R
#            if self.c[i-1]:
#                R = self.c[i-1] ; self.c[i-1] = 0.0
#                self.b[i-1] -= R*self.a[i]
#                self.f[i-1] -= R*self.f[i]
#                self.p[i-1] -= R*self.p[i]
#                self.q[i-1] -= R*self.q[i]
#
#        for i in range(1,n):
#            if self.p[i] != 0:
#                R = self.p[i] ; self.p[i] = 0.0
#                self.f[i] -= R*self.f[0]
#                self.q[i] -= R*self.q[0]
#
#        R = self.q[n-1]**-1; self.q[n-1] = 1.0
#        self.f[n-1] *= R
#        for i in range(n-2,-1,-1):
#            if self.q[i] != 0:
#                R = self.q[i] ; self.q[i] = 0.0
#                self.f[i] -= R*self.f[n-1]


m = Matrix()
m.calculation()
m.show()



