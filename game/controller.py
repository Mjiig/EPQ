import game
import pexpect
import sys
import os
import sys
import breeder_link

#needs to be rewritten for 3*3 noughts and crosses
def score(g):
    score=0
    if g.winner==2:
        score+=20 #big score if we won
    if g.winner==0:
        score+=10 #smaller score if we drew

    score+=g._board.count(2)
    return score

#note this function changes the cwd
def calculate_generation(opponent_path, gen):
    scores=[]

    opponent=os.path.abspath(opponent_path)

    os.chdir(os.path.dirname(os.path.abspath(__file__))) #move to the same directory as this source file
    os.chdir("../population/")

    os.chdir(str(gen))

    for i in xrange(1000):

        p1=pexpect.spawn(opponent)
        p1.setecho(False)
        p1.delaybeforesend=0 #we can't afford the default delay of 0.2 seconds, which is unnecessary anyway
        p2=pexpect.spawn("../../vm/vm " + ("%0*d" % (3, i) + ".dna"))
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

            move=int(process.after)%9

            if g._board[move]!=0:
                move=-1

            g.play(move)

        scores.append(score(g))
        print str(i) + "   \r",
        sys.stdout.flush()

    print
    print max(scores)
    os.chdir("..")
    breeder_link.next_generation(scores, gen)
