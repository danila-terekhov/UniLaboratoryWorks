#!/usr/bin/env python3
inp_path = "input2.txt"
out_path = "result.txt"


"""
y(x) = x+1
y'(x) = 1
y''(x) = 0

p(x) = 1
q(x) = -2
f(x) == 2x+2

(p(x)*y'(x))'-q(x)*y(x)=f(x)
"""

def f(x):
   return 2*x+2


def p(x):
    return 1


def q(x):
    return -2


def u(x, z, y):
    return f(x) + q(x)*y


def v(x, z, y):
    return z


def func_11(x, y1, y2):
    return q(x) - (y1 ** 2) / p(x)


def func_12(x, y1, y2):
    return f(x) - (y1 * y2) / p(x)


def func_21(x, y1, y2):
    return 1 / (p(x)) - q(x) * y1 ** 2


def func_22(x, y1, y2):
    return f(x) * y1 - q(x) * y1 * y2


#WORKS 100%
def rg2(x, y1, y2, h, func_1, func_2):
    a = 1

    k1_1 = h * func_1(x, y1, y2)
    k1_2 = h * func_2(x, y1, y2)

    k2_1 = h * func_1((x + a * h), (y1 + a * k1_1), (y2 + a * k1_2))
    k2_2 = h * func_2((x + a * h), (y1 + a * k1_1), (y2 + a * k1_2))

    y1 = y1 + (k1_1 + k2_1) / 2
    y2 = y2 + (k1_2 + k2_2) / 2
    return y1, y2


def transfer(a, b, a3_c, b3_c, func1, func2, y):
    print("Перенос краевого условия для точки x=a в точку x=b")
    h = 0.1
    a3i, b3i = rg2(a, a3_c, b3_c, h, func1, func2)

    for ind in range(1, len(y)):
        i, xi = ind, y[ind]

        #print("i:", i, " xi: ", xi, " a3i: ", round(a3i, 5), " b3i: ", round(b3i, 5))


        a3i, b3i = rg2(xi, a3i, b3i, h, func1, func2)

    return a3i, b3i


def solve(a, b, z_b, y_b, y):
    print("Получение решение y(x) дифференциальной краевой задачи")

    outfile = open(out_path, "w")

    h = -0.1

    zi, yi = rg2(b, z_b, y_b, h, v, u)

    for k in range(len(y)-2, -1, -1):
        i, xi = k, y[k]


        writeOutput(outfile, int(i)+1, xi-h, yi, zi)
        zi, yi = rg2(xi, zi, yi, h, u, v)

    writeOutput(outfile, int(i), xi, yi, zi)
    outfile.close()
    return zi, yi


def writeOutput(outfile, i, xi, yi, zi):
    s = "x" + str(i) + " = " + str(round(xi, 4))
    s += ", y" + str(i) + " = " + str(round(yi, 4))
    s += ", y'" + str(i) + " = " + str(round(zi, 4)) + ';\n'
    print(s)
    #outfile.write(s)

def main():
    # чтение данных
    data = []
    f = open(inp_path, 'r')
    for line in f:
        data.append(line.replace('\n', '').split(" "))
    first_row = data[0]
    a1 = float(first_row[0])
    b1 = float(first_row[1])
    c1 = float(first_row[2])
    a2 = float(first_row[3])
    b2 = float(first_row[4])
    c2 = float(first_row[5])
    second_row = data[1]
    a = float(second_row[0])
    b = float(second_row[1])
    n = int(second_row[2])
    y = []
    for i in range(2, n+2):
        y.append(float(data[i][0]))

    icod = 0

    if a1*a1 + b1*b1 <= 0:
        print("Краевые условие не подходят для этого программного решения!")
        return

    # перенос краевого условия для точки x=a в точку x=b
    is_transferred = False
    c = a
    if a1 != 0 and not is_transferred:
        a3_c = -(b1 * p(c)) / a1
        b3_c = (c1 * p(c)) / a1
        #print("a3_c := %s, b3_c := %s" % (a3_c, b3_c))
        a3, b3 = transfer(a, b, a3_c, b3_c, func_11, func_12, y)
        print("a3 := %s, b3 := %s" % (a3, b3))
        c3 = b3
        b3 = -a3
        a3 = p(b)
        is_transferred = True

    if b1 != 0 and not is_transferred:
        phi_c = -a1 / (b1 * p(c))
        psi_c = -c1 / b1
        #print("phi_c := %s, psi_c := %s" % (phi_c, psi_c))
        phi, psi = transfer(a, b, phi_c, psi_c, func_21, func_22, y)
        #print("phi := %s, psi := %s" % (phi_c, psi_c))
        c3 = psi
        b3 = -1
        a3 = phi * p(a)
        is_transferred = True

    if not is_transferred:
        print("Ошибка в кроевом условии")
        icod = 2
        return icod

    if a3 == a1 and b3 == b1 and c3 == c1:
        print("Бесконечное множество решений")
        icod = 1
        return icod

    # получение решение y(x) дифференциальной краевой задачи
    det = a3*b2-a2*b3
    if det != 0:
        y_diff_b = (c3 * b2 - c2 * b3) / det
        y_b = (a3 * c2 - a2 * c3) / det
        #print("y_diff_b := %s, y_b := %s" % (y_diff_b, y_b))
        y_diff, y_sol = solve(a, b, y_diff_b, y_b, y)
        #print("y_diff := %s, y := %s" % (y_diff, y_sol))
    else:
        print("Система несовместна")
        icod = 2
        return icod


if __name__ == "__main__":
    main()
