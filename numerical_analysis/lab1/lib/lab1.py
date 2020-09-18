from random import *

def non_zero_randfloat(rang):
    while True:
        x = round(uniform(-rang,rang), 2)
        if x:
            return x

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
        return matrix

    def calculation(self):

        n = self.n

        A = self.show()
        #xv = [1.0 for _ in range(n)]
        fv = []
        for i in range(n):
            fv.append(sum(A[i]))
        print("fv=",fv)

        self.f = fv


        tmp = self.c[0]
        self.c[0] = 0.0

        for i in range(1, n-1):
            R = self.b[i]**-1 ; self.b[i] = 1.0
            self.p[i] *= R
            self.f[i] *= R
            self.q[i] *= R
            if i < n-2:
                self.c[i] *= R # TODO maybe error at last iteration
            else:
                self.c[i] = self.q[i]

            R = self.a[i+1] ; self.a[i+1] = 0.0
            self.p[i+1] -= self.p[i]*R
            self.f[i+1] -= self.f[i]*R
            self.q[i+1] -= self.q[i]*R
            if i+1 < n-1:
                self.b[i+1] -= self.c[i]*R
            else:
                self.b[i+1] = self.q[i+1]
            if i+1 == n-1:
                self.c[i+1] = self.q[i+1]

            self.q[0] -= self.q[i]*R
            self.p[0] -= self.p[i]*R
            self.f[0] -= self.f[i]*R
            #tmp -= self.b[i]*tmp = 0
            if i < n-2:
                tmp = -self.c[i] * tmp

        self.q[0] /= self.p[0] ; self.f[0] /= self.p[0]
        self.p[0] = self.b[0] = 1.0

        for i in range(1,n):
            self.q[i] -= self.q[0]*self.p[i]
            self.f[i] -= self.f[0]*self.p[i]
            self.p[i] = 0.0

        self.a[1] = self.p[1]

        self.f[n-1] /= self.q[n-1]
        self.q[n-1] = self.b[n-1] = 1.0

        for i in range(n-2,-1,-1):
            self.f[i] -= self.f[n-1] * self.q[i]
            self.q[i] = 0.0

        self.c[n-2] = self.q[n-2]

        x = [0.0 for _ in range(0,n)]

        x[0] = self.f[0]
        x[n-2] = self.f[n-2]
        x[n-1] = self.f[n-1]

        for i in range(n-3, 0, -1):
            x[i] = self.f[i] - self.c[i]*x[i+1]

        return x

count_succes=0
while count_succes<1:
    m = Matrix(60,6)
    m.show()
    count_succes+=1
#    try:
#        x = m.calculation()
#    except :
#        continue
#    else:
#        count_succes += 1
#        print(count_succes)

print("x=",Matrix().calculation())


