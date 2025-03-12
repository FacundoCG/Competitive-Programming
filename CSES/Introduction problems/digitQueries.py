def leftBinarySearch(start, end, intervals, value):
    l = start - 1
    r = end + 1
    #El primer intervalo que contiene al digito en la posición >= k
    while (r - l > 1):
        mid = (l + r)//2
        if intervals[mid] < value: 
            l = mid
        else:
            r = mid

    return r 

def numberToArray(n, arr):
    if n <= 9:
        arr.append(n)
    else:
        arr.append(n%10)
        numberToArray(n//10, arr)

q = int(input())
queries = []
k = 0

for _ in range(q):
    digitRequested = int(input())
    k = max(k,digitRequested)
    queries.append(digitRequested)

intervals = [9]

while (intervals[-1] < k): # El intervalo en la posición i va a comprender el intervalo: [10^i, 10^(i+1)-1]
    i = len(intervals)
    newInterval = 9*pow(10, i)*(i+1) + intervals[i-1]
    intervals.append(newInterval)

for j in range(q):
    currenDigitToFind = queries[j]
    positionOfGoodInterval = leftBinarySearch(0, len(intervals)-1, intervals, currenDigitToFind)
    #print("Good position: " + str(positionOfGoodInterval))

    if positionOfGoodInterval == 0:
        print(currenDigitToFind)
        continue

    restingNumber = currenDigitToFind - intervals[positionOfGoodInterval-1]
    digitsOfMyNumbers = positionOfGoodInterval + 1
    currentNumber = pow(10, i)
    res = None
    ##print("Digits left: " + str(restingNumber))

    while (restingNumber >= 0):
        #print("Resting: " + str(restingNumber))
        #print("Current number: " + str(currentNumber))
        if (restingNumber - digitsOfMyNumbers <= 0):
            digits = []
            numberToArray(currentNumber, digits)
            digits.reverse()
            res = digits[restingNumber-1]
            break
            # Convert the number to an array an access the digit that corresponds
        else:
            currentNumber += 1
            restingNumber -= digitsOfMyNumbers

    print(res)

