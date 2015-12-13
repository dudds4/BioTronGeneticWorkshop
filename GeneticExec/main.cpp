#include "Trainer.h"
#include "Player.h"
#include <iostream>
int main() {
    
	Trainer ash_ketchum;
	Player* pickachu = ash_ketchum.createOptimizedPlayer();
	std::cout << "Made out of optimization. \n";
	pickachu->toFile("pickachu.txt");

    return 0;
}
