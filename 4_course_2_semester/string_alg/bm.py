#!/usr/bin/env python3

def show(text, substr, h, count):
    print(text)
    print(' ' * h + substr,'\t |', count)

def precalc_dict(p):
    out = {}
    m = len(p)
    for i in range(len(p) - 1):
        out[p[i]] = m - i - 1
    if p[m - 1] not in out:
        out[p[m - 1]] = m
    print(out)
    return out

def bm_search(x: str, p: str):
    result = []
    count = 0

    d = precalc_dict(p)

    m = len(p)
    i = m - 1
    while i < len(x):
        h = 0
        while h < m:
            count += 1
            if x[i - h] != p[m - h - 1]:
                break
            h += 1
        show(x, p, i - m + 1, count)
        if h == m:
            result.append(i - m + 1)
            i += 1
        elif x[i - h] not in d:
            print(1)
            i += m - h
        elif h != 0:
            print(2)
            i += d[p[m - 1]]
        else:
            print(3)
            i += d[x[i - h]]
    return result


substr = "abacb"
text = "abakbabaababacb"
print(bm_search(text, substr))

#data = [('abaaaaabaaa', 'baa'),
#        ('abaaaaabaa', 'bca'),
#        ('baabaabaaa', 'baaa'),
#        ('ackcbccbcbcaaccbc', 'cbccbc')]

# for d in data:
#     print('======')
#     print(bm_search(d[0], d[1]))
#     print([m.start() for m in re.finditer(d[1], d[0])])
#     print('========')
