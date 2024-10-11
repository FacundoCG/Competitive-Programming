def pickingNumbers(arr):
    n:int = len(arr)
    arr.sort()

    res:int = 1
    currentLength:int = 1
    currentElement:int = arr[0]

    for i in range(1,n):
        if (abs(arr[i]-currentElement) <= 1):
            currentLength += 1
            res = max(res, currentLength)
        else:
            currentLength = 1
            currentElement = arr[i]
    
    return res


