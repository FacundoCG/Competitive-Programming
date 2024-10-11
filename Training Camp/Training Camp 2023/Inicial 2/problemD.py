k = int(input())
ranks_known = {int(x) for x in input().split()}
top_25 = {x for x in range(1,26)}

invitations = ranks_known - top_25
invitation = [x for x in invitations]
invitation.sort()
declinations = 0

if len(invitation) != 0:
    for i in range(1,len(invitation)):
        declinations += invitation[i] - invitation[i-1] - 1
    
    declinations += invitation[0] - 26

    declinations += len(invitation)

    print(declinations)

else:
    print(0)