class Game(object):
    def __init__(self):
        self._board=[0]*64 #0 is an unplayed square
        self.next_player=1 #player 1 plays first (obviously)
        self.finished=False
        self.score1=0
        self.score2=0
        self.winner=0 #0 refers to no one having won

    def play(self, n):
        if n>64:
            raise IndexError, str(n) + " is bigger than 63 so is not a valid move"

        if self._board[n]==0:
            self._board[n]=self.next_player
        else:
            raise ValueError, "square " +str(n) + " has already been played in"

        if self.finished:
            raise RuntimeError, "the game is already finished"

        if self.next_player==1:
            self.next_player=2
        else:
            self.next_player=1

        if self._board.count(0)==0: #if every square has been played one
            self.finished=True

        self.score()

    def score(self):
        self.score1=0
        self.score2=0
        for i in range(8):
            self._score_line(self._board[i*8:(i+1)*8]) #score the vertical lines
            self._score_line(self._board[i::8]) #score the horizontal lines

        if self.finished:
            self._pick_winner()
        
        #Notice no scores for diagonal lines

    def _score_line(self, line): #line is an array that represents a line of the board
        current_player=0
        length=0
        for square in line:
            if square!=current_player or square==0:
                current_player=square
                length=0

            length+=1

            if length>=3:
                if current_player==1:
                    self.score1+=1
                else:
                    self.score2+=1

            if length>=6:
                self.finished=True
                self.winner=current_player
                return #avoid the pick winner function being run, as the winner is decided independant of the score in this case

    def _pick_winner(self):
        if self.score1>self.score2:
            self.winner=1
        elif self.score2>self.score1:
            self.winner=2
        else:
            self.winner=0

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
            if n%8==0:
                ret+="\n________________\n"
        return ret

if __name__=="__main__":
    g=Game()
    while not g.finished:
        try:
            print
            print "Player " + str(g.next_player) + " is next to play"
            print "Player 1: " + str(g.score1) + "\t Player 2: " + str(g.score2)
            print g.board_string()
            square=int(raw_input("Where would you like to play? "))
            g.play(square)
        except:
            print "It appears there was something wrong with that move"
        
    print "The winner is: Player " + str(g.score2)

