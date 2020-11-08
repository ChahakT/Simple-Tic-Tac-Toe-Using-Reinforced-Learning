# Simple-Tic-Tac-Toe-Using-Reinforced-Learning
Train agents to learn a game of Tic Tac Toe

The Agent learns to play the game using Reinforcement-learning (Q-learning). 

The agent was self trained. 

py -3 Train.py to train the agent

py -3 Play.py to play the game

Run this to train agent:

game = TicTacToe(True) #init game, true implies training

agent1= Qlearning() #learning agent 1

agent2= Qlearning() #learning agent 2

game.startTraining(agent1,agent2) #train agents

game.train(250000) #250,000 iterations

game.saveStates()  #save Qtable


Human Vs Agent Game:

game = TicTacToe() #init game

player1=Humanplayer() #human 

player2=Qlearning()  #agent

game.startGame(player1,player2)#player1: X, player2: 0

game.reset() #reset

game.render() # render display



