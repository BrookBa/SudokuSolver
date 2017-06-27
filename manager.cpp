//Implemementation file for the manager class
#include "manager.h"

const char * file_in = "puzzle.txt";
const char * file_out = "solution.txt";

//Default constructor for manager class
manager::manager(){
	reset_num = 0;
	head = NULL;
}

//Reads the puzzle in from the external file
bool manager::read_in()
{
	ifstream in;
	char c;
	int row = 0;
	int column = 0;
	int square = 0;
	in.open(file_in);
	if(in){
		in >> c;
		while(!in.eof() && row < 9){
			//This for loop reads in one row
			for(column = 0;column < 9; ++column){

				//Give the cell its value
				grid[row][column].set(c, given, 
						&rows[row], &columns[column],
						&squares[square]);

				//Add the cell to the row, column and square
				rows[row].add_cell(&grid[row][column]);
				columns[column].add_cell(&grid[row][column]);
				squares[square].add_cell(&grid[row][column]);

				//change squares if need be
				if(column == 2 || column == 5){
					++square;
				}
				in >> c;
			}
			//clear the newline
			//in.ignore(100, '\n');
			//in >> c;

			//Go to the next row
			++row;
			if(row == 0 || row == 1 || row == 2)
				square = 0;
			else if(row == 3 || row == 4 || row == 5)
				square = 3;
			else
				square = 6;
		}
		in.close();
		in.clear();
	}

	//Set the elimination for all the rows and columns
	for(int r = 0; r < 9; ++r){
		for(int c = 0; c < 9; ++c){
			if(grid[r][c].get_val() != 0){
				grid[r][c].set_elimination();
			}
		}
	}
}

//Display The Grid 
void manager::display(){
	for(int r = 0; r < 9; ++r){
		for(int c = 0; c < 9; ++c){
			grid[r][c].display();
			if(c == 2 || c == 5){
				cout << "| ";
			}
		}
		if(r == 2 || r == 5)
			cout << endl<<  "------|-------|-------" << endl;
		else
			cout << endl;
	}

// FOR ERROR TESTING
#ifdef tests
/*
	cout << RED << "present" << C_START << " missing" << C_END << endl;
	cout << "\nDisplaying rows " << endl;
	for(int r = 0; r < 9; ++r){
		rows[r].display();
	}
	cout << "\nDisplaying Columns " << endl;
	for(int c = 0; c < 9; ++c){
		columns[c].display();
	}
	cout << "\nDisplaying Squares " << endl;
	for(int s = 0; s < 9; ++s){
		squares[s].display();
	}
*/
#endif
}

//Checks if the puzzle has been solved
bool manager::is_done(){
	bool done = true;
	for(int r = 0; r < 9 && done; ++r){
		done = rows[r].check() && done;
	}
	for(int c = 0; c < 9 && done; ++c){
		done = columns[c].check() && done;
	}
	for(int s = 0; s < 9 && done; ++s){
		done = squares[s].check() && done;
	}
	return done;

}


//Outputs the puzzle to the output file
bool manager::output(){
	ofstream out;
	out.open(file_out);
	if(out){
		for(int r = 0; r < 9; ++r){
			for(int c = 0; c < 9; ++c){
				out << grid[r][c].get_val();
			}
			out << "\n";
		}
		out.close();
		out.clear();
	}
}


//Checks each position in the grid to see if there is
//only one number that could go there.
bool manager::tactic1(){
	bool changed = false;
	for(int r = 0; r < 9; ++r){
		for(int c = 0; c < 9; ++c){
			if(grid[r][c].get_val() == '0'){
				//It is changed if we changed something here
				//OR it had already been changed
				changed = grid[r][c].find_unique(reset_num) || changed;
			}
		}

	}
#ifdef tests
cout << "Tactic 1: " << changed << " -- ";
#endif
	return changed;
}

//Find where it's the only cell that could hold that number in a group
bool manager::tactic2(){
	bool changed = false;
	char missing = '0';
	for(int r = 0; r < 9; ++r){
		missing = '0';
		do{
			try{
				missing = rows[r].missing_num(missing );
				changed = rows[r].check_missing(missing, reset_num) 
							|| changed;
			}catch(contradiction * c){
				missing = 'E';
			}
		}while(missing != 'E');
	}
	for(int c = 0; c < 9; ++c){
		missing = '0';
		do{
			try{
				missing = columns[c].missing_num(missing);
				changed = columns[c].check_missing(missing, reset_num) 
							|| changed;
			}catch(contradiction * c){
				missing = 'E';
			}
		}while(missing != 'E');
	}
	for(int s = 0; s < 9; ++s){
		missing = '0';
		do{
			try{
				missing = squares[s].missing_num(missing);
				changed = squares[s].check_missing(missing, reset_num)
							|| changed;
			}catch(contradiction * c){
				missing = 'E';
			}
		}while(missing != 'E');
	}
#ifdef tests
cout << "Tactic 2: " << changed << "  -- ";
#endif
	return changed;
}


bool manager::tactic3(){
	bool changed = false;

	for(int r = 0; r < 9; ++r){
		changed = rows[r].tactic3(reset_num) || changed;
	}

	
	for(int c = 0; c < 9; ++c){
		changed = columns[c].tactic3(reset_num) || changed;
	}

	for(int s = 0; s < 9; ++s){
		changed = squares[s].tactic3(reset_num) || changed;
	}

#ifdef tests
cout << "Tactic 3: " << changed << endl;
#endif
	return changed;
}


bool manager::tactic_guess(){
	bool guessed = false;
	bool done = false;
	int guessed_coor[2] = {0, 0};
	bool correct = true;
	char again;
	do{
	
#ifdef tests
cout << "Press any char to guess: ";
cin >> again;
cin.ignore(100, '\n');
cout << "\n\n";
#endif
		
		try{
		//Guess a cell:
			correct = true;
			guessed = false;
			for(int r = guessed_coor[0]; r < 9 && !guessed; ++r){
				for(int c = guessed_coor[1]; c < 9 && !guessed; ++c){
					if(grid[r][c].get_val() == '0'){
						++reset_num;
						grid[r][c].guess_cell(reset_num);
						guessed = true;
						guessed_coor[0] = r;
						guessed_coor[1] = c;
#ifdef tests
cerr << "Guessed " << grid[r][c].get_val() << " for cell " << r  
	 << ", " << c << "]\n";
display();
#endif
					}
				}
			}
		}catch(contradiction * c){
			--reset_num;
			correct = false;
#ifdef tests
cerr << "The guess was not correct!!! " << c -> location << endl;
display();
#endif	
		//Run other tactics until they're done:
		}
		if(correct){
			bool test = true;
			while(test){
				test = tactic1() || tactic2() || tactic3();
			}
#ifdef tests
cerr << "The grid after trying tactics from the guess:\n";
display();
#endif
		}
		//Check if there's a contradiction
		if(!correct || !is_correct()){
			//Add guessed cell and guessed value to 
			//special elimination list:
			elim_node * temp = head;
			head = new elim_node;
			head -> row = guessed_coor[0];
			head -> col = guessed_coor[1];
			head -> val = grid[guessed_coor[0]][guessed_coor[1]]
													.get_val();
			head -> next = temp;
			
			reset();
	
#ifdef tests
cerr << "Trying tactics again after resetting: ";
#endif
			while(tactic1() || tactic2() || tactic3());
	
#ifdef tests
cerr << "The grid after trying the tactics after resetting is: " 
	 << endl;
display();
#endif
		}
//		}
		//Check if it's complete
		done = is_done();
	}while(!done);
}

//Check that there are no contradictions
bool manager::is_correct(){
	bool correct = true;
	for(int i = 0; i < 9 && correct; ++i){
#ifdef tests
cout << "Checking " << i << ": Row: ";
#endif
		correct = rows[i].check_correct() && correct;
#ifdef tests
cout << " Column: ";
#endif
		correct = columns[i].check_correct() && correct;
#ifdef tests
cout << " Square: ";
#endif
		correct = squares[i].check_correct() && correct;
#ifdef tests
cout << endl;
#endif
	}
	return correct;
}


//Resets the grid
void manager::reset(){
	elim_node * temp = NULL;
	//Reset all the cells back to before the guess
	for(int i = 0; i < 9; ++i){
		rows[i].reset(reset_num);
		columns[i].reset(reset_num);
		squares[i].reset(reset_num);
	}
	--reset_num;

	//Reset the elimination for all the rows and columns
	for(int r = 0; r < 9; ++r){
		for(int c = 0; c < 9; ++c){
			if(grid[r][c].get_val() != 0){
				grid[r][c].set_elimination();
			}
		}
	}
	//Eliminate the values that have already been guessed
	temp = head;
	while(temp){
		grid[temp->row][temp->col].eliminate(temp->val);
		temp = temp -> next;
	}

#ifdef tests
cerr << "The grid after resetting: " << endl;
display();
#endif
}
