#include "AbstractPlayer.h"
#include "Player.h"
#include <vector>

bool compare(Player* p1, Player* p2);

class Trainer {
public:
	Player* createOptimizedPlayer();
private:
	std::vector<Player*> playerPool;
	std::vector<playerStats> statsPool;
	class PlayerStats {
	public:
		int wins;
		int illegalMoves;
		int numMoves;
		int draws;
		int games;
		PlayerStats() wins(0), illegalMoves(0), numMoves(0), draws(0), games(0) {}
		void addMatchStats(Match* match, int player);
	};

	void generatePlayerPool();
	int simulateGames(Player* player1, Player* player2, int numGames);
	void starTrekNextGeneration();
};