import game
import pexpect
import sys
import os

def score(g):
    score=0
    if g.winner==2:
        score+=10000 #big score if we won
    if g.winner==0:
        score+=5000 #smaller score if we drew

    score+=g.score2*100 #add 10 for every point we scored 

    score+=g._board.count(2) #and a point for every cross we actually played :) should probably be removed long term, but good to encourage initial evolution
    
    return score



p1=pexpect.spawn(sys.argv[1])

os.chdir(os.path.dirname(os.path.abspath(__file__))) #move to the same directory as this source file
os.chdir("../population/")

gen=int(sys.argv[2])

p1.setecho(False)
p1.delaybeforesend=0 #we can't afford the default delay of 0.2 seconds, which is unnecessary anyway
for i in xrange(1000):

    p2=pexpect.spawn("../vm/vm " + str(gen) + "_" + ("%0*d" % (3, i) + ".dna"))
    p2.setecho(False)
    p2.delaybeforesend=0

    g=game.Game()
    
    while not g.finished:
        if g.next_player==1:
            process=p1
        else:
            process=p2

        process.sendline(g.get_player_string(g.next_player))
        process.expect("\d*\r\n")

        move=int(process.after)%64

        if g._board[move]!=0:
            move=-1

        g.play(move)

    print str(i) + " - " + str(score(g))
