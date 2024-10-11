def digitsOfNumberInBinary(n, arr):
    rest = n%2
    quotient = n//2
    arr.append(rest)

    if (quotient != 0):
        digitsOfNumberInBinary(quotient, arr)

def flippingBits(n):
    # Variables
    res = 0
    arr = []
    digitsOfNumberInBinary(n, arr) 
    m = len(arr)
   
    # I invert the digits of the number
    for i in range(m):
        if (arr[i] == 0):
           arr[i] = 1
        else:
            arr[i] = 0

    # I need to check how many left digits I miss
    for i in range(m,32):
        res += pow(2,i)
    
    # Calculate the number with the flipping bits
    for i in range(m):
        digit = arr[i]

        if (digit == 1):
            res += pow(2,i)
    
    return res

n = int(input())
arr = []
digitsOfNumberInBinary(n,arr)

for i in range(len(arr)):
    print(arr[i])

print(flippingBits(9))