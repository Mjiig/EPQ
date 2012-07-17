class Game(object):
    def __init__(self):
        self._board=[0]*64 #0 is an unplayed square
        self._next_player=1 #player 1 plays first (obviously)
        self._finished=False
        self._score1=0
        self._score2=0
        self._winner=0 #0 refers to no one having won

    def play(self, n):
        if n>64:
            raise IndexError, str(n) + "is bigger than 63 so is not a valid move"

        if self._board[n]==0:
            self._board[n]=self._next_player
        else:
            raise ValueError, "square " +str(n) + " has already been played in"

        if self._next_player==1:
            self._next_player=2
        else:
            self._next_player=1

    def score(self):
        self._score1=0
        self._score2=0
        for i in range(8):
            self._score_line(self._board[i*8:(i+1)*8]) #score the vertical lines
            self._score_line(self._board[i::8]) #score the horizontal lines
        
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
                    self._score1+=1
                else:
                    self._score2+=1

            if length>=6:
                self._finished=True
                self._winner=current_player






