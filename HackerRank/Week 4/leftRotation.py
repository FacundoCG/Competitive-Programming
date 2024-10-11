def rotateLeft(d, arr):
    n: int = len(arr)
    copyArr = arr.copy()

    for i in range(d, n):
        arr[i-d] = arr[i]
    
    for i in range(d):
        j = d-(i+1)
        arr[n-1-j] = copyArr[i]
    
    return arr