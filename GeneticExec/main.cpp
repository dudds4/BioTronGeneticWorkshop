#include "Trainer.h"
#include "Player.h"
#include "Match.h"
#include <iostream>

using namespace std;

int main() {
    
//	Trainer ash_ketchum;
//	Player* pikachu = ash_ketchum.createOptimizedPlayer();
//	std::cout << "Made out of optimization. \n";
//	pickachu->toFile("pickachu.txt");

	int skill1, skill2;

	cout << "Please enter skill level of Player 1: ";
	cin >> skill1;
	cout << "Please enter skill level of Player 2: ";
	cin >> skill2;

	Player* p1 = new Player(skill1);
	Player* p2 = new Player(skill2);

	Match m(p1, p2);
	m.playOut();
	if (m.getWinningPlayer() == p1) {
		cout << "P1 Wins\n";
	} else {
		cout << "P2 Wins\n";
	}

    return 0;
}
