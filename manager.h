//Brook Baise Summer 2016
//Describes the manager class for a Sudoku solver
#include "cell.h"

struct elim_node{
	int row;
	int col;
	char val;
	elim_node * next;
};


class manager{
	public:
		manager();
		bool read_in();
		void display();
		bool output();
		bool is_done();

		bool tactic1(); //Only possible number for that cell
		bool tactic2(); //Only possible cell for that number
		bool tactic3();

		bool tactic_guess();
		void reset();
		bool is_correct();


	private:
		cell grid[9][9];
		group rows[9];
		group columns[9];
		group squares[9];
		int reset_num;
		elim_node * head;


};
