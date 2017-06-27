

#include "manager.h"

int main(){
//	cell grid[9][9];
//	cell test1('4', true, NULL, NULL, NULL);
//	cell test1;
//	test1.display();
//	cout << endl;
	manager game;
	bool done;
	game.read_in();

	cout << "The original puzzle: \n";
	game.display();
	while(game.tactic1() || game.tactic2() || game.tactic3());
	cout << endl;

	cout << "What we have from the first three tactics: \n";
	game.display();
	done = game.is_done();
	
	if(!done){
		cout << "\nAttempting to guess: \n";
		game.tactic_guess();
		game.display();
	}

	if(done || game.is_done()){
		cout << "Puzzle solved.\n";
		game.output();
	}
	else
		cout << "The game is not finished.\n";

	return 0;
}
