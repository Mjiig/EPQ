import random

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

    extra_len=random.randrange(abs(len(a_lines)-len(b_lines)))

    if len(a_lines)>len(b_lines):
        source=a_lines
    else:
        source=b_lines

    output[len(output):]=source[len(output):len(output)+extra_len]

    return output
    

