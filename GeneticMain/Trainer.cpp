#include "GameSimulator.h"
#include "globals.cpp"
#include "Trainer.h"
#include "Player.h"
#include "Match.h"
#include <cstdlib>

Player* Trainer::createOptimizedPlayer() {
	generatePlayerPool();
	for (int i=0; i<GENERATIONS; i++) {
		starTrekNextGeneration();
	}
	Player* bestPlayer = playerPool[0];
	for (int i=1; i<POOL_SIZE; i++) {
		if (simulateGames(playerPool[i], bestPlayer, GAMES_PER_MATCH) > GAMES_PER_MATCH/2) {
			bestPlayer = playerPool[i];
		}
	}
	return bestPlayer;
}

void Trainer::generatePlayerPool() {
	for (int i=0; i<POOL_SIZE; i++) {
		playerPool.push_back(Player::random());
	}
}

int Trainer::simulateGames(Player* player1, Player* player2, int numGames) {
	int player1Wins = 0;
	Match* matchUp = new Match(player1, player2);
	for (int i=0; i<numGames; i++) {
		if (matchUp->playOut() == 1) {
			player1Wins++;
		}
	}
	return player1Wins;
}

void Trainer::starTrekNextGeneration() {
	srand(time(0));
	int numIndividuals = playerPool.size();
	float leastFitness = 0, fitnessSum = 0;
	
	for (int i=0; i<numIndividuals; i++) {
		for (int j=0; j<numIndividuals; j++) {
			if (i != j) {
				Match* matchUp = new Match(playerPool[i], playerPool[j]);
				matchUp->playOut();
				statsPool[i].addMatchStats(match, playerPool[i]);
				statsPool[j].addMatchStats(match, playerPool[j]);
			}
		}
	}
	for (int i=0; i<numIndividuals; i++) {
		playerPool[i]->fitness = fitness(statsPool[i]);
		fitnessSum += playerPool[i]->fitness;
		if (playerPool[i]->fitness < leastFitness || i == 0) {
			leastFitness = playerPool[i]->fitness;
		}
	}
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
	while (newPool.size() < numIndividuals) {
		newPool.push_back(playerPool[idx]->copy());
		idx++;
	}

	Player* player;
	while (playerPool.size() > 0) {
		player = playerPool.pop_back()
		delete (player);
	}
	playerPool = newPool;
}

bool compare(Player* p1, Player* p2) {
	return p1->fitness > p2->fitness;
}

float fitness(PlayerStats ps) {
	float games = ps.games;
	float moves = ps.moves;
	return WIN_WIGHT*ps.wins/games + DRAW_WIEGHT*ps.draws/games - ILLEGAL_WEIGHT*ps.illegalMoves/moves;
}

void Trainer::PlayerStats::addMatchStats(Match* match, Player* player) {
	wins += (match->getWinningPlayer() == player);
	draws += (match->getWinningPlayer() == NULL);
	games++;
	moves += match->getNumMoves();
	illegalMoves += getIllegalMoves(player);
}