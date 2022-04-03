#!/usr/bin/env python3

def naive_search(text: str, substr: str):
    start_pos = []
    count = 0
    for i in range(len(text) - len(substr) + 1):
        is_substring = True
        for j in range(len(substr)):
            count += 1
            if text[i + j] != substr[j]:
                is_substring = False
                break

        if is_substring:
            start_pos.append(i)
    print(count)
    return start_pos


string = 'aaabaaaa'
substring = 'aaa'
print(naive_search(string, substring))
