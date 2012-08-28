#!/usr/bin/python
import random

try:
    while True:
        board=raw_input()
        x=random.randrange(9)
        while board[x]!="0":
            x=random.randrange(9)
        print x
except EOFError:
    pass
