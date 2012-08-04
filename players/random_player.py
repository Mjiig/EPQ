import random

try:
    while True:
        board=raw_input()
        x=random.randrange(64)
        print x
        print board[x]
        while board[x]!="0":
            x=random.randrange(64)
        print x
except EOFError:
    pass
