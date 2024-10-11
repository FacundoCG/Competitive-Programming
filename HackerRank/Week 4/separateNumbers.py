def separateNumbers(s):
    n:int = len(s)

    if (n == 1):
        print(f"YES {int(s)}")

    flag = False
    
    for i in range(1,n):
        firstNumber = int(s[0:i])
        currentNumber = firstNumber
        j = i

        while (j < n):
            nextNumber = currentNumber + 1
            m = len(str(nextNumber))

            if (j + m - 1 < n):
                numberSequence = int(s[j:j+m])
                if (numberSequence == nextNumber):
                    currentNumber = nextNumber
                    j += m
                else:
                    break
            else:
                break

            if (j >= n):
                flag = True
        
        if (flag):
            print(f"YES {firstNumber}")
            break
    
    if (not flag):
        print("NO")
            