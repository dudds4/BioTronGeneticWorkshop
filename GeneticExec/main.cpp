#include "Trainer.h"
#include "ImmutablePlayer.h"
#include "Match.h"
#include "NeuralNet.h"
#include <iostream>

using namespace std;

int main() {

	Trainer ash_ketchum;
	Player* pikachu = ash_ketchum.createOptimizedPlayer();
	std::cout << "Made out of optimization. \n";
	pikachu->toFile("pikachu.txt");

/*
	Player* trained = new Player();
	trained = trained->fromFile("1000Gen5040brain_2.txt");

	int skill1, skill2;

	cout << "Please enter skill level of Player 1: ";
	cin >> skill1;

	ImmutablePlayer* p1 = new ImmutablePlayer(skill1);

	Match m(p1, trained);
	m.playOutVerbose();
	if (m.getWinningPlayer() == p1) {
		cout << "Trained Player Wins\n";
	} else {
		cout << "Traditional Player Wins\n";
	}
*/

    return 0;
}
