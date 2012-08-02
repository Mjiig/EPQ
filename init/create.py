import random

loads = ["LOAD1", "LOAD2"] #special case as they require a literal
commands = ["NOP", "JMP", "JMPIF", "STORE", "LOAD", "SWAP2", "SWAP3", "SWAP4", "SWAP5", "TERM", "INC", "ADD", "SUB", "DIV", "MULT"]

length = random.randrange(256)

output = ""

for i in xrange(length):
    index = random.randrange(len(loads) + len(commands))

    if index < len(loads):
        line = loads[index]
        line+= " "
        line += str(random.randrange(255))
    else:
        line = commands[index-len(loads)]

    line += "\n"
    
    output += line

print output
