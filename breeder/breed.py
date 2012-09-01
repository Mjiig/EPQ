import random
import os

loads = ["LOAD1", "LOAD2"] #special case as they require a literal
commands = ["NOP", "JMP", "JMPIF", "STORE", "LOAD", "SWAP2", "SWAP3", "SWAP4", "SWAP5", "TERM", "INC", "ADD", "SUB", "DIV", "MULT"]

#breeding function shamlessy taken from imagenest the owner of which (Joseph Gleason) has emailed me to say that the code this copies is released under an MIT lisence. 1209k.com/nest 
def breed(a, b): #a and b are the names of files containing dna programs
    with open(a) as f:
        a_lines=f.readlines()
    with open(b) as f:
        b_lines=f.readlines()

    length=min(len(a_lines), len(b_lines))

    output=[]

    while len(output)<length:
        chunk_len=int(random.gauss(8, 3))
        if chunk_len + len(output) > length:
            chunk_len=length-len(output)

        if chunk_len < 1:
            continue
        
        source=a_lines
        if random.choice((True, False)):
            source=b_lines

        output[len(output):]=source[len(output):len(output)+chunk_len]

    if len(a_lines) != len(b_lines):
        extra_len=random.randrange(abs(len(a_lines)-len(b_lines)))

        if len(a_lines)>len(b_lines):
            source=a_lines
        else:
            source=b_lines

        output[len(output):]=source[len(output):len(output)+extra_len]

    #add some random mutations

    while random.randrange(10)!=0: #should run roughly six times on average
        pos=random.randrange(len(output)+1)

        index = random.randrange(len(loads) + len(commands))

        if index < len(loads):
            new = loads[index]
            new+= " "
            new += str(random.randrange(255))
        else:
            new = commands[index-len(loads)]

        output=output[:pos]+[new + "\n"]+output[pos:]

    return output
    
def select(scores):
    total=0
    for item in scores:
        total+=item

    total=total*total
    target=random.randrange(total)
    current=0
    ret=0
    for i in xrange(len(scores)):
        current+=scores[i]
        if (current * current) > target:
            return i

#scores is a list giving the score for each organism in generation gen
#this **MUST** be run when the cwd is population, otherwise bad things will happen
def next_generation(scores, gen):

    try:
        os.mkdir(str(gen+1))
    except OSError:
        pass

    for i in xrange(1000):
        a=select(scores)
        b=a
        while a==b:
            b=select(scores)

        child = breed(("%d/%03d.dna" % (gen,a)), ("%d/%03d.dna" % (gen,a)))

        with open("%d/%03d.dna" % (gen+1, i), "w+") as f:
            f.writelines(child)
    
