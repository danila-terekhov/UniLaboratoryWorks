#!/usr/bin/env python3
from collections import namedtuple
from typing import List


def solveTridiagonalSystem(A: List[float], C: List[float], B: List[float], F: List[float],
                           x0: float, v0: float, xN: float, vN: float, N: int):
    X = [0.0] * (N + 1)
    V = [0.0] * (N + 1)
    Z = [0.0] * (N + 1)

    X[0] = x0
    V[0] = v0
    X[N] = xN
    V[N] = vN

    for k in range(1, N):
        D = C[k - 1] - A[k - 1] * X[k - 1]
        if D == 0:
            raise Exception('Знаменатель равен нулю')

        X[k] = B[k - 1] / D
        V[k] = (A[k - 1] * V[k - 1] - F[k - 1]) / D

    Z[N] = (V[N] + X[N] * V[N - 1])/(1 - X[N] * X[N - 1])

    for k in range(N - 1, -1, -1):
        Z[k] = X[k] * Z[k + 1] + V[k]

    return Z

INPUT_FILENAME = 'input3.txt'
OUTPUT_FILENAME = 'output3.txt'

EquationData = namedtuple('EquationData', ['c2', 'a', 'b', 'T', 'a1', 'b1', 'a2', 'b2', 'M', 'N'], defaults=[0])


class ThermalConductivityEquation:

    def __init__(self, data: EquationData, f, mu1, mu2, mu3):
        self.data = data
        self.f = f
        self.h = (data.b - data.a) / data.N
        self.tau = data.T / data.M
        self.r = 1/2
        self.mu1 = mu1
        self.mu2 = mu2
        self.mu3 = mu3

    def xi(self, i):
        return self.data.a + self.h * i

    def tj(self, j):
        return self.tau * j

    def solve(self, errorCallback, maxErrorCallback):
        M, N = int(self.data.M), int(self.data.N)
        print(f'h is {self.h}')
        print(f'tau is {self.tau}')

        sigma = (pow(self.h, 2) / (self.data.c2 * self.tau))
        ksi = pow(self.h, 2) / self.data.c2  # кси

        A = [1 for _ in range(N - 1)]
        B = [1 for _ in range(N - 1)]
        C = [2 + sigma for _ in range(N - 1)]

        y = [self.mu1(self.xi(i)) for i in range(N + 1)]

        maxError = 0

        for j in range(M):
            F = [0] * (N - 1)
            v0 = self.mu2(self.tj(j + 1))
            vN = self.mu3(self.tj(j + 1))



            for i in range(N - 1):
                #F[i] = - sigma * y[i + 1] - ksi * self.f(self.xi(i + 1), self.tj(j))

                phi = self.f(self.xi(i), self.tj(j) + self.tau / 2)
                F[i] = (2 * (1-self.r)/self.r)*y[i] - (1-self.r)/self.r*(y[i-1]+y[i+1]) - ksi/self.r*phi

            yCap = solveTridiagonalSystem(A, C, B, F, 0, v0, 0, vN, N)

            maxError = max(errorCallback(self.data, j + 1, yCap), maxError)

            y = yCap

        maxErrorCallback(maxError)


def readInputData(inputFile):
    inputData = [float(num) for num in inputFile.readline().split()]
    inputData[4] = int(inputData[4])
    inputData[5] = int(inputData[5])

    return EquationData._make(inputData)


def main():
    with open(INPUT_FILENAME, 'r') as file:
        data = readInputData(file)

    # u = lambda x, t: x + t
    # f = lambda x, t: 1
    # mu1 = lambda x: x
    # mu2 = lambda t: data.a + t
    # mu3 = lambda t: data.b + t
    u = lambda x, t: x**2 + t ** 2
    f = lambda x, t: 2 * t - 2 * data.c2
    mu1 = lambda x: x ** 2
    mu2 = lambda t: data.a ** 2 + t ** 2
    mu3 = lambda t: data.b ** 2 + t ** 2

    outputFile = open(OUTPUT_FILENAME, 'w')

    def writeDataAndReturnError(passedData, j, y):
        tau = passedData.T / passedData.M
        h = (passedData.b - passedData.a) / passedData.N
        tj = tau * j

        maxError = 0
        #outputFile.write(f'Level {j}\n')

        for i in range(len(y)):
            xi = passedData.a + h * i
            error = abs(y[i] - u(xi, tj))
            outputFile.write(f'{i}\t{xi}\t\t{y[i]}\t\t{u(xi, tj)}\t\t{error}\n')

            maxError = max(maxError, error)

        outputFile.write(f'Max error: {maxError}\n')

        return maxError

    def writeMaxError(error):
        outputFile.write(f'Global max error is {error}')

    equation = ThermalConductivityEquation(data, f, mu1, mu2, mu3)

    equation.solve(writeDataAndReturnError, writeMaxError)

    outputFile.close()


if __name__ == '__main__':
    main()
