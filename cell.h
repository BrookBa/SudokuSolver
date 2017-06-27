//Brook Baise Summer 2016 
//Describes the cell and group classes for a Sudoku solver
#include "bool_arr.h"

bool read_in(class cell** &);


enum solution_type{ given, one, two, empty, guess};

class group{
	public:
		group();
		bool add_cell(cell *);
		void display();
		bool find_val(char);
		bool check();//checks if the group is complete
		char missing_num(char start);//finds the first missing num post s
		bool check_missing(char, int reset = 0); 
								//Finds if there's only one place for 
								//the missing number
		void eliminate(char);
		bool tactic3(int reset = 0);

		void reset(int reset_num);
		bool check_correct();
	private: 
		class cell * members[9];
		bool_arr missing_nums;
};


class cell{
	public:
		cell();
		cell(char, solution_type, group *, group*, group*);
		void display();
		bool set(char, solution_type, group *, group *, group *);
		bool set(char, solution_type, int guess = 0);
		char get_val();
		bool find_unique(int reset = 0);//cell could only have one val
		bool check_valid(char); //can cell hold this val
		bool eliminate(char);
		void set_elimination(); 
		//Tactic 3
		int num_possibles();
		char get_possible(char start = '0');
		bool compare(cell & comp);

		void reset(int reset_num);
		void guess_cell(int);

	private: 
		char value;
		//bool is_known;
		solution_type tactic;
		bool_arr possibles;
		group * row;
		group * column;
		group * square;
		int guess_num;
};

