#include "Trainer.h"
#include "ImmutablePlayer.h"
#include "Match.h"
#include <iostream>

using namespace std;

int main() {
    
	Trainer ash_ketchum;
	Player* pikachu = ash_ketchum.createOptimizedPlayer();
	std::cout << "Made out of optimization. \n";
	pikachu->toFile("pikachu.txt");

	// int skill1, skill2;

	// cout << "Please enter skill level of Player 1: ";
	// cin >> skill1;
	// cout << "Please enter skill level of Player 2: ";
	// cin >> skill2;

	// ImmutablePlayer* p1 = new ImmutablePlayer(skill1);
	// ImmutablePlayer* p2 = new ImmutablePlayer(skill2);

	// Match m(p1, p2);
	// m.playOut();
	// if (m.getWinningPlayer() == p1) {
		// cout << "P1 Wins\n";
	// } else {
		// cout << "P2 Wins\n";
	// }

    return 0;
}
