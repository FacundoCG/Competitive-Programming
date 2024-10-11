def caesarCipher(s:str, k:int):
    lowerLetters = [chr(asciCode) for asciCode in range(ord('a'), ord('z') + 1)]
    upperLetters = [chr(asciCode) for asciCode in range(ord('A'), ord('Z') + 1)]
    res:str = str()
    
    for char in s:
        if char in lowerLetters: 
           asciNumber = ord(char)
           
           if (asciNumber + k <= ord('z')):
               char = chr(asciNumber + k)
           else:
               difference = asciNumber + k - ord('z') - 1
               difference %= 26
               newAsciCode = ord('a') + difference
               char = chr(newAsciCode)
        elif char in upperLetters:
           asciNumber = ord(char)

           if (asciNumber + k <= ord('Z')):
               char = chr(asciNumber + k)
           else:
               difference = asciNumber + k - ord('Z') - 1
               difference %= 26
               newAsciCode = ord('A') + difference
               char = chr(newAsciCode)

        res += char
    
    return res

s = input()
k = int(input())

print(caesarCipher(s,k))