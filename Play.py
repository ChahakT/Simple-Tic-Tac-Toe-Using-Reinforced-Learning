from Game import TicTacToe, Humanplayer, Randomplayer
from QLearning import  Qlearning

game = TicTacToe() #init game
player1=Humanplayer() #human
player2=Qlearning() #agent

game.startGame(player1,player2)#player1: X, player2: 0

game.reset() #reset
game.render() # render display
