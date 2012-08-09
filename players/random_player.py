#!/usr/bin/python
import random

random.seed("This kind of phrase is what happens when I have to come up with a seed at 11PM")

try:
    while True:
        board=raw_input()
        x=random.randrange(64)
        while board[x]!="0":
            x=random.randrange(64)
        print x
except EOFError:
    pass
