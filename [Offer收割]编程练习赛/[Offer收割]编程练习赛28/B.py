s = raw_input()
ans = 0

def get_length_odd(index):
    length = 0
    while index - length >= 0 and index + length < len(s) and \
          s[index - length] == s[index + length]:
        length += 1
    return length

def get_length_even(index):
    length = 0
    while index - length >= 0 and index + 1 + length < len(s) and \
          s[index - length] == s[index + 1 + length]:
        length += 1
    return length

for i in range(len(s)):
    length = get_length_odd(i)
    #print i, length
    ans += length

for i in range(len(s)):
    length = get_length_even(i)
    #print i, length
    ans += length

print ans
