def f(i,k):
    firstTerm = i*i
    secondTerm = i * (2*k + 1)
    res = firstTerm + secondTerm
    return res

def leftBinarySearch(start, end, value, k):
    leftLimit = start - 1
    rightLimit = end + 1

    while (rightLimit - leftLimit > 1):
        midPoint = (leftLimit + rightLimit)//2
        currentValue = f(midPoint, k)

        if (currentValue < value):
            leftLimit = midPoint
        else:
            rightLimit = midPoint
    
    return rightLimit

t = int(input())

for _ in range(t):
    n, k = [int(x) for x in input().split()]
    z = 2*k - k*n - n*(n-1)//2
    res = None

    if (z >= 0):
        res = abs(f(0,k) + z)
    else:
        i_0 = leftBinarySearch(0,n-1,abs(z),k)

        if (i_0 == 0):
            res = abs(f(0,k) + z)
        else:
            res = min(abs(f(i_0,k) + z), abs(f(i_0-1,k) + z))

    print(res)

