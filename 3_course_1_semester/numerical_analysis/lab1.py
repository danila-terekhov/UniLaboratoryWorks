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

def find_v(A,f):
    A = np.linalg.inv(np.array(A))
    f = np.array(f)
    return A.dot(f).tolist()

class Matrix:

    def __init__(self, size=10, rang=10):
        self.n = randint(size, size*10)
        self.a = randlist_wo_zero(self.n, rang)
        self.b = randlist_wo_zero(self.n, rang)
        self.c = randlist_wo_zero(self.n, rang)
        self.p = randlist_wo_zero(self.n, rang)
        self.q = randlist_wo_zero(self.n, rang)
        self.f = randlist_wo_zero(self.n, rang)
        self.a[0] = self.c[self.n-1] = 0.0
        self.p[0] = self.b[0]
        self.p[1] = self.a[1]
        self.q[self.n-2] = self.c[self.n-2]
        self.q[self.n-1] = self.b[self.n-1]


    def show(self):
        matrix = [[0.0 for _ in range(self.n)] for _ in range(self.n)]
        for i in range(self.n):
            matrix[i][0] = self.p[i]
            matrix[i][self.n-1]= self.q[i]
            matrix[i][i] = self.b[i]
            if i>1:
                matrix[i][i-1] = self.a[i]
            if i<self.n-2:
                matrix[i][i+1] = self.c[i]
            #print(matrix[i]," | ", self.f[i])
        return matrix

    def calculation(self):

        n = self.n
        A = self.show()

        #xv = [1.0 for _ in range(n)]
        fv = [sum(A[i]) for i in range(n)]

        
        xz = randlist_wo_zero(self.n, len(self.b))

        self.f[0] = self.b[0]*xz[0] + self.c[0]*xz[1] + self.q[0]*xz[n-1]
        self.f[1] = self.a[1]*xz[0] + self.b[1]*xz[1] + self.c[1]*xz[2] + self.q[1]*xz[n-1]
        for i in range(2,n-2):
            self.f[i] = self.p[i]*xz[0] + self.a[i]*xz[i-1] + self.b[i]*xz[i] + self.c[i]*xz[i+1] + self.q[i]*xz[n-1]
        self.f[n-2] = self.p[n-2]*xz[0] + self.a[n-2]*xz[n-3] + self.b[n-2]*xz[n-2] + self.c[n-2]*xz[n-1]
        self.f[n-1] = self.p[n-1]*xz[0] + self.a[n-1]*xz[n-2] + self.b[n-1]*xz[n-1]
        

        tmp = self.c[0]
        self.c[0] = 0.0

        # STEP 1
        for i in range(1, n-1): # don't include n-1 column
            R = 1/self.b[i] ; self.b[i] = 1.0
            self.p[i] *= R; self.q[i] *= R; self.f[i] *= R
            fv[i] *= R
            if i < n-2:
                self.c[i] *= R
            else: # if i == n-2:
                self.c[i] = self.q[i]

            R = self.a[i+1] ; self.a[i+1] = 0.0
            self.p[i+1] -= self.p[i]*R
            self.q[i+1] -= self.q[i]*R
            self.f[i+1] -= self.f[i]*R
            fv[i+1] -= fv[i]*R
            if i < n-2:
                self.b[i+1] -= self.c[i]*R
            else: # if i == n-2:
                self.c[n-2] = self.q[n-2]
                self.b[n-1] = self.q[n-1]

            self.p[0] -= self.p[i]*tmp
            self.q[0] -= self.q[i]*tmp
            self.f[0] -= self.f[i]*tmp
            fv[0] -= fv[i]*tmp
            #tmp -= self.b[i]*tmp = 0
            if i < n-2:
                tmp = -self.c[i] * tmp

        # STEP 2
        R = 1/self.p[0]; self.p[0] = 1.0
        self.q[0] *= R; self.f[0] *= R;
        fv[0] *= R
        self.b[0] = self.p[0]

        for i in range(1,n):
            self.q[i] -= self.q[0]*self.p[i]
            self.f[i] -= self.f[0]*self.p[i]
            fv[i] -= fv[0]*self.p[i]
            self.p[i] = 0.0

        self.a[1] = self.p[1]

        # STEP 3
        self.f[n-1] /= self.q[n-1]
        fv[n-1] /= self.q[n-1]
        self.q[n-1] = self.b[n-1] = 1.0

        for i in range(n-2,-1,-1):
            self.f[i] -= self.f[n-1] * self.q[i]
            fv[i] -= fv[n-1] * self.q[i]
            self.q[i] = 0.0

        self.c[n-2] = self.q[n-2]

        # STEP 4
        x = [None] * n
        x[0] = self.f[0]
        x[n-2] = self.f[n-2]
        x[n-1] = self.f[n-1]

        xv = [None] * n
        xv[0] = fv[0]
        xv[n-2] = fv[n-2]
        xv[n-1] = fv[n-1]


        for i in range(n-3, 0, -1):
            x[i] = self.f[i] - self.c[i]*x[i+1]
            xv[i] = fv[i] - self.c[i]*xv[i+1]

        accuracy = max([ abs(xv[i]-1) for i in range(n)])
        delta = [0.0 for _ in range(n)]
        q = 0.01
        for i in range(n):
            if abs(x[i]-xz[i]) > q:
                delta[i] = abs((x[i]-xz[i])/xz[i])
            else:# abs(x[i]-xz[i]) <= q:
                delta[i] = abs(x[i]-xz[i])
        error = max(delta)
        return accuracy, error

if __name__ == "__main__":
    print("\n\
Lab 1, numerical analysis\n\
Terekhov Danila Evgen'evich\n\
Course: 3\n\
Group: 8\n")

    size,ranges = [int(a) for a in input("Enter size and range: (10,100,1000) : ").split()]
    print()

    count_succes = 0
    acc = [] ; err = []
    while count_succes<10:
        m = Matrix(size,ranges)
        try:
            a,e = m.calculation()
        except ZeroDivisionError:
            continue
        else:
            acc.append(a)
            err.append(e)
            count_succes += 1

    a = sum(err)/len(err)
    e = sum(acc)/len(acc)
#   print("Size of matrix: %d x %d"  % (m.n, m.n))
    print("Input ", size,ranges)
    print("Accuracy: %.3g" % a)
    print("Error: %.3g" % e)
    ##print(len(err),len(acc),m.n)
