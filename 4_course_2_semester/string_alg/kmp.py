#!/usr/bin/env python3
#import re
# O(m+n) , where O(m) - pf search

def sho(text, substr, shift, count):
    print(text)
    print(' ' * shift + substr,'\t |', count)


# prefix function
# наибольшая грань подстроки
def pf(substr):
    n = len(substr)
    pi = [0] * n
    j = 0
    for i in range(1, n):
        if substr[i] == substr[j]:
            pi[i] = j + 1
            j += 1
        else:
            if j == 0:
                pi[i] = 0
            else:
                j = pi[j - 1]
    print("PF =",pi)
    return pi


def kmp(text, substr):
    result = []
    count = 0
    shift = pf(substr)
    i = 0
    n = len(text)
    j = 0
    m = len(substr)

    while i + (m - j) <= n: # i <= n - m + j

        # match (i, j, m)
        while j < m:
            count += 1
            if substr[j] == text[i]:
                j += 1
                i += 1
            else:
                break

        if j == m:
            print(f'index {i - m} was found')
            result.append(i - m)
        if j == 0:
            print(f'i={i}')
            i += 1
        else:
            print(f'j={j}')
            print(f'Shift = {shift[j-1]}')
            j = shift[j - 1]
    return result


substr = "ababa"
text = "ababcabababa"

print(kmp(text, substr))



#data = [('abaaaaabaaa', 'baaa'),
#        ('baabaabaaa', 'baaa'),
#        ('ackcbccbcbcaaccbc', 'cbccbc'),
#        ('cbccbccbccbc', 'cbccbc')]
#
#for d in data:
#    print('\n======')
#    print(kmp(d[0], d[1]))
#    print([m.start() for m in re.finditer(d[1], d[0])])
#    print('========\n')
