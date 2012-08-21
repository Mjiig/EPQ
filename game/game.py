class Game(object):
    def __init__(self):
        self._board=[0]*9 #0 is an unplayed square
        self.next_player=1 #player 1 plays first (obviously)
        self.finished=False
        self.winner=0 #0 refers to no one having won
        self._prev_pass=False

    def play(self, n):
        if n>=9:
            raise IndexError, str(n) + " is bigger than 8 so is not a valid move"

        if self.finished:
            raise RuntimeError, "the game is already finished"

        if n==-1:
            if self._prev_pass:
                self.finished=True
            self._prev_pass=True
        else:
            self._prev_pass=False
            if self._board[n]==0:
                    self._board[n]=self.next_player
            else:
                raise ValueError, "square " +str(n) + " has already been played in"

        if self.next_player==1:
            self.next_player=2
        else:
            self.next_player=1

        if self._board.count(0)==0: #if every square has been played one
            self.finished=True

        self.score()

    def score(self):
        column_starts=(0, 1, 2)
        row_starts=(0, 3, 6)
        
        for start in column_starts:
            if self._board[start] == self._board[start+3] and self._board[start]==self._board[start+6] and self._board[start]!=0:
                self.winner=self._board[start]
                self.finished=True
        
        for start in row_starts:
            if self._board[start] == self._board[start+1] and self._board[start]==self._board[start+2] and self._board[start]!=0:
                self.winner=self._board[start]
                self.finished=True

        if self._board[0]==self._board[4] and self._board[0]==self._board[8] and self._board[0]!=0:
            self.winner=self._board[0]
            self.finished=True

        if self._board[2]==self._board[4] and self._board[2]==self._board[6] and self._board[2]!=0:
            self.winner=self._board[2]
            self.finished=True


    def board_string(self):
        ret=""
        n=0
        for i in self._board:
            if i==1:
                ret+="o"
            elif i==2:
                ret+="x"
            else:
                ret+=" "
            ret+="|"
            n+=1
            if n%3==0:
                ret+="\n_____\n"
        return ret

    def get_player_string(self, player):
        result=""
        for square in self._board:
            if square==0:
                result+="0"
            elif square==player:
                result+="1"
            else:
                result+="2"
        return result

if __name__=="__main__":
    g=Game()
    while not g.finished:
        try:
            print
            print "Player " + str(g.next_player) + " is next to play"
            print g.board_string()
            square=int(raw_input("Where would you like to play? "))
            g.play(square)
        except Exception as e:
            print "\n\nIt appears there was something wrong with that move. Python says: "+ e.args[0] + "\nTry again!\n\n"
        
    print "The winner is: Player " + str(g.winner)

