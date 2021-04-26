The function isValidMove determines if the move made by the AI or the player is 
a valid move in the sense that if there is a "." blocking the player's next move
then the function will prompt to tell the user that it's an "invalid move."
The function isStraight determines if the next move the 
player and AI makes is a straight line, if not then the function will prompt to
tell the user that it's an "invalid move."
Since the gameBoard is in char, there is a function to convert the points from 1-3.
The function numFound is the function for the AI. It goes through the array determining
what is the greatest value of point is available and will prompt the AI to go to that position
if the path allows. 
The function isOver determines if the game is over. When the game is over, the points are 
added up and the winner is determined regarding who has the greatest number of points in the end.

