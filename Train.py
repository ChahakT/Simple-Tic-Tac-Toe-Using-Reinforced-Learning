from Game import TicTacToe
from QLearning import  Qlearning

game = TicTacToe(True) #init game, true implies training
agent1= Qlearning() #learning agent 1
agent2= Qlearning() #learning agent 2

game.startTraining(agent1,agent2) #train agents
game.train(250000) #250,000 iterations

game.saveStates() #save Qtable
