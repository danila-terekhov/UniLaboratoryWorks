from random import *

class Matrix:
    def __init__(self, size=10, rang=10):
        self.n = size
        self.a = sample(range(rang), self.n)
        self.b = sample(range(rang), self.n)
        self.c = sample(range(rang), self.n)
        self.p = sample(range(rang), self.n)
        self.q = sample(range(rang), self.n)
        self.f = [1 for _ in range(self.n)]
        self.a[0] = self.c[self.n-1] = 0
        self.p[0] = self.b[0]
        self.p[1] = self.a[1]
        self.q[self.n-1] = self.b[self.n-1]
        self.q[self.n-2] = self.c[self.n-2]


    def show(self):
        matrix = [[0 for _ in range(self.n)] for _ in range(self.n)]
        for i in range(self.n):
            matrix[i][0] = self.p[i]
            matrix[i][self.n-1]= self.q[i]
            matrix[i][i] = self.b[i]
            if i>0:
                matrix[i][i-1] = self.a[i]
            if i<self.n-2:
                matrix[i][i+1] = self.c[i]
            print(matrix[i]," | ", self.f[i])


m = Matrix()
m.show()



