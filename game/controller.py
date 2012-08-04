#the first argument is the program we want to test the fitness of, the second argument is it's opponent
#in any given generation the same oponent should be used for the whole population

import game
import pexpect
import sys

g=game.Game()

p1=pexpect.spawn(sys.argv[1])
p2=pexpect.spawn(sys.argv[2])

p1.setecho(False)
p2.setecho(False)

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


score=0

if g.winner==1:
    score+=1000 #big score if we won
if g.winner==0:
    score+=500 #smaller score if we drew

score+=g.score1*10 #add 10 for every point we scored 

score+=g._board.count(1) #and a point for every cross we actually played :) should probably be removed long term, but good to encourage initial evolution

print score
