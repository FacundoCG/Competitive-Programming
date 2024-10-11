string = input()

if string == string[::-1]:
    print(string)

else:
    print(string+string[::-1])