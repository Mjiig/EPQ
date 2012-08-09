import os
import re
import subprocess

def make_prog(n):

    print "Generating " + str(n)

    subprocess.call("python ../../init/create.py >" +  "%0*d" %(3, n) + ".dna", shell=True);


os.chdir(os.path.dirname(os.path.abspath(__file__))) #move to the same directory as this source file
os.chdir("..")

try:
    os.mkdir("population")
except OSError:
    pass

os.chdir("population")

try:
    os.mkdir("1")
except OSError:
    pass

os.chdir("1")

files=os.listdir(".")
files.sort()

if(len(files)>0):
    last=files[-1]

    num=re.match(r"(\d{3})\.dna$", last).group(1)

    num=int(num)
    num+=1
else:
    num=0

while num < 1000:
    make_prog(num)
    num+=1
