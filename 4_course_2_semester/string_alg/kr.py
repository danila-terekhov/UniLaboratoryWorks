#!/usr/bin/env python3

Q = 7

def match(i, m, x, p):
    print("Trying to compare string on index ", i)
    count = 0
    for j in range(m):
        if x[i+j] == p[j]:
            count += 1
        else:
            break
    print("Number of comparison =",count)
    #print(x[i:i+m] == p)

    return count

def get_sigma(s): # (1)
    m = len(s)
    result = 0
    for i in range(m):
        result = (result + ord(s[i])) % Q
    return result

def get_sigma_iter(i, m, x, prev): # (2)
    return (2 * (prev - ((2 ** (m-1)) % Q) * ord(x[i-1])) + ord(x[i - 1 + m])) % Q

def kr_search(x: str, p: str):
    n = len(x)
    m = len(p)
    sigma_x = [get_sigma(x[:m])]
    sigma_p = get_sigma(p)
    result = []

    for i in range(0, n - m + 1):
        if i >= 1:
            sigma_i = get_sigma_iter(i, m, x, sigma_x[i-1])
            sigma_x.append(sigma_i)
        else:
            sigma_i = sigma_x[0]

        if sigma_i == sigma_p and match(i, m, x, p):
            result.append(i)
    return result


substr = "asd"
text = "asdasdasasd"
print(kr_search(text, substr))
