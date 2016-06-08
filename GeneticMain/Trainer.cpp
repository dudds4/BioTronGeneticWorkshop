#include "globals.cpp"
#include "Trainer.h"
#include "Player.h"
#include "BoardGenerator.h"
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <iostream>

Player* Trainer::createOptimizedPlayer() {
    //Generate One player
    Player* p = Player::random();
 
    BoardGenerator boardGen;
    int boardInput[3][3];
    int scoreMap[3][3];
    double output[9];
	for (int i=0; i<1500; i++) {
        int numMoves = i%9;
        //Generate Random Board
        boardGen.generateBoard(boardInput, numMoves);
        //Generate Expected Output Score Map
        boardGen.generateScoreMap(boardInput, scoreMap, (numMoves%2) + 1);
        //Player plays on board
        p->makeMove(boardInput, (numMoves%2) + 1, output);
        //multiply output matrix term by term with output score map
        //Backprop

        //change player slightly
	}

	return p;
}

void Trainer::generatePlayerPool() {
	for (int i=0; i<POOL_SIZE; i++) {
		playerPool.push_back(Player::random());
		statsPool.push_back(PlayerStats());
	}
}

int Trainer::simulateGames(Player* player1, Player* player2, int numGames) {
	int player1Wins = 0;
	for (int i=0; i<numGames; i++) {
		Match m(player1, player2);
		if (m.playOut() == 1) {
			player1Wins++;
		}
	}
	return player1Wins;
}

void Trainer::starTrekNextGeneration() {
	srand(time(0));
	int numIndividuals = playerPool.size();
	float leastFitness = 0, fitnessSum = 0;

    //Players are tested, we generate a fitness score based on their reaction to certain boards
	for (int i=0; i<numIndividuals; i++) {
		for (int j=0; j<numIndividuals; j++) {
			if(i!=j) {

				Match* matchUp = new Match(playerPool[i], playerPool[j]);
				matchUp->playOut();
				statsPool[i].addMatchStats(matchUp, playerPool[i]);
				statsPool[j].addMatchStats(matchUp, playerPool[j]);
			}
		}
	}

    //normalize fitness values
    //find least value of fitness
    for(int i = 0; i < numIndividuals; i++) {
        playerPool[i]->fitness = statsPool[i].getFitness();
        fitnessSum += playerPool[i]->fitness;
        if (playerPool[i]->fitness < leastFitness || i == 0) {
            leastFitness = playerPool[i]->fitness;
        }
    }
	
    //shift values over so that least fitness value is zero
    //then divide by fitness sum
    //this way all the fitnesses sum to 1
	fitnessSum += (-1)*leastFitness*numIndividuals;
	for (int i=0; i<numIndividuals; i++) {
		playerPool[i]->fitness = (playerPool[i]->fitness - leastFitness)/fitnessSum;
	}
	std::sort(playerPool.begin(), playerPool.end(), compare);

	std::vector <Player*> newPool;
	for (int i=0; i<numIndividuals/4; i++) {
		float R = (rand()%10000)/10000.0;
		float accumulatedSum = 0;
		for (int j=0; j<numIndividuals; j++) {
			accumulatedSum += playerPool[j]->fitness;
			if(accumulatedSum > R) {
				newPool.push_back(playerPool[j]->copy());
				newPool.push_back(playerPool[j]->mutate());

				j = numIndividuals;
			}
		}
	}

	int size = newPool.size();
	for (int i=0; i<size-2; i+=2) {
		newPool.push_back(playerPool[i]->mate(playerPool[i+2]));
	}
	for (int i=0; i<numIndividuals/8; i++) {
		newPool.push_back(Player::random());
	}

	int idx = 0;
	while (newPool.size() < (unsigned int)numIndividuals) {
		newPool.push_back(playerPool[idx]->copy());
		idx++;
	}

	Player* player;
	while (playerPool.size() > 0) {
		player = playerPool.back();
		playerPool.pop_back();
		delete (player);
	}
	playerPool = newPool;

	for(unsigned int i = 0; i < statsPool.size(); i++)
		statsPool[i] = PlayerStats();
}

bool compare(Player* p1, Player* p2) {
	return p1->fitness > p2->fitness;
}

float Trainer::PlayerStats::getFitness() {
	if(games == 0) std::cout << "Finna divide bai zero faaaaaaaack (games)\n";
	if(numMoves == 0) std::cout << "Finna divide bai zero faaaaaaaack (numMoves)\n";

	return WIN_WEIGHT*((float)wins)/games + DRAW_WEIGHT*((float)draws)/games - ILLEGAL_WEIGHT*((float)illegalMoves)/numMoves;
}

void Trainer::PlayerStats::addMatchStats(Match* match, Player* player) {
	wins += (match->getWinningPlayer() == player);
	draws += (match->getWinningPlayer() == NULL);
	games++;
	numMoves += match->getNumMoves();
	illegalMoves += match->getIllegalMoves(player);
}
