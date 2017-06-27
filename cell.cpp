#include "cell.h"

//Group Functions
group::group(){
	for(int i = 0; i < 9; ++i){
		members[i] = NULL;	
	}
}

//Adds a cell to the group at the first empty position
bool group::add_cell(cell * c){
	bool done = false;
	for(int i = 0; i < 9 && !done; ++i){
		if(!members[i]){
			members[i] = c;
			done = true;
			missing_nums.eliminate(members[i]->get_val());
		}
	}
	return done;
}

//Display a group
void group::display(){
	for(int i = 0; i < 9; ++i){
		if(members[i])
			members[i] -> display();
		else
			cout << "E ";
	}
#ifdef tests
	cout << "\t";
	missing_nums.display();
#endif
	cout << endl;
}

//Finds if a value is in the group already.
//if it is, returns true, else false
bool group::find_val(char c){
	return !missing_nums.check(c);
}

//Checks that the group is complete
bool group::check(){
	bool done = true;
	for(int i = 0; i < 9 && done; ++i){
		//Check that all the members are full
		if(members[i] -> get_val() == '0'){
			done = false;
		}
	}
	//Check that all the values are accounted for
	if(done && missing_nums.num_true() == 0){
	 	done = true;
	}
	return done;
}

//Checks for contradictions
bool group::check_correct(){
	int num_miss = missing_nums.num_true();
	int num_empty = 0;
	for(int i = 0; i < 9; ++i){
		if(members[i] -> get_val() == '0'){
			++num_empty;
		}
	}
#ifdef tests
if(num_empty != num_miss){
	cout << "Group not correct!" << endl;
}
#endif
	return num_empty == num_miss;
}

//Finds the first missing character after
//the one passed in.
//Returns E if no number was found
char group::missing_num(char start){
	return missing_nums.true_after(start);
}

//Finds if there is only one place the missing number could go
bool group::check_missing(char c, int reset){
	
	int num_pos = 0; 
			//THe number of places it could go
	cell * place = NULL; //The place it could go

	for(int i = 0; i < 9 && num_pos < 2; ++i){
		if(members[i] -> check_valid(c)){
			++num_pos;
			place = members[i];
		}
	}
	if(num_pos == 0){
		throw new contradiction("The number has no place it could go");
	}
	else if(num_pos == 1){
		return place -> set(c, two, reset);
	}
	return false;

}

void group::eliminate(char c){
	missing_nums.eliminate(c);
	for(int i = 0; i < 9; ++i){
		if(members[i])
			members[i] -> eliminate(c);
	}
}

bool group::tactic3(int reset){
	bool changed = false;
	cell * found = NULL;
	char elim1, elim2= '0';
	
	int index = 0;
	if(missing_nums.num_true() <= 2)
		return false;
	//For each cell in the group
	for(;index < 9; ++index){
		//Find one with two possibilities
		if(members[index] -> num_possibles() == 2){
			found = members[index];
			//find another iwth two possibilities
			for(int i = index +1; i < 9; ++i){
				if(members[i] -> num_possibles() == 2){
					elim1 = found -> get_possible(); 
					elim2 = found -> get_possible(elim1);
					//check if they match
					if(members[index] -> compare( *members[i])){
						//Eliminate those possibilities from the
						//rest of the group
						for(int j =0; j < 9; ++j){
							if(j == index)
								++j;
							if(j == i)
								++j;
							if(j < 9){
								changed = 
									members[j] -> eliminate(elim1)
									|| members[j] -> eliminate(elim2);
							}
						}
					}
				}
			}
		}
	}
	return changed;
}

void group::reset(int reset_num){
	missing_nums.reset();
	for(int i = 0; i < 9; ++i){
		members[i] -> reset(reset_num);
	}
}

//Cell functions
//cell basic constructor
cell::cell():value('0'), tactic(empty), row(NULL), column(NULL), square(NULL){}

//cell constructor with arguments
cell::cell(char v, solution_type k, group * r, group* c , group* s)
		:value(v), tactic(k), row(r), column(c), square(s)
{
	row -> eliminate(v);
	column -> eliminate(v);
	square -> eliminate(v);
}

//Display a cell 
void cell::display(){
	switch(tactic){
		case given:
			cout << C_START;
			break;
		case one:
			cout << C2_START;
			break;
		case two:
			cout << C3_START;
			break;
		case guess: 
			cout << RED;
			break;
		default:
			cout << C_END;
	}
#ifndef tests
	cout << value << C_END << " ";
#else
//	cout << value << C_END << " ";
	if(value != '0')
		cout << value << "[" << guess_num << "]"<< C_END << " ";
	else{
		possibles.dispTrue();
//		cout << value << C_END << " ";
	}
#endif
}

//Sets the values in a cell
bool cell::set(char v, solution_type k, group * r, group * c, group * s){
	if(tactic == given){
		cerr << "Attempting to set known cell." << endl;
		return false;
	}
	value = v; 
	tactic = v != '0'? given: empty;
	row = r;
	column = c;
	square = s;
	guess_num = 0;
	row -> eliminate(v);
	column -> eliminate(v);
	square -> eliminate(v);
	return true;
}

//Set a cell to a certain value
bool cell::set(char v, solution_type t, int guess){
	if(tactic == given){
		cerr << "Attempting to set known cell." << endl;
		return false;
	}
	value = v;
	tactic = t;
	guess_num = guess;
	row -> eliminate(v);
	column -> eliminate(v);
	square -> eliminate(v);
	return true;
}

//Returns the value in a cell
char cell::get_val(){
	return value;
}

//Finds if the cell could only have one possible value
//Changes the cell and returns true if it can
bool cell::find_unique(int reset){
	if(tactic == given)
		return false;
	if(possibles.num_true() == 1){
		char pos = possibles.true_after('0');
		if(pos == 'E'){
			throw new contradiction("Find Unique Contradiction");
			cout << "UNIQUE VALUE IS E WHAAAAAAT????\t";
			possibles.display();
			cout << endl;

		}
		return set(pos, one, reset);
	}
	return false;
}

//Checks if this cell could hold the passed in value
bool cell::check_valid(char c){
	if(value != '0')
		return false;
	return possibles.check(c);
}

//Eliminates the value from the possibles
bool cell::eliminate(char c){
	if(value != c){
		return possibles.eliminate(c);
	}
}

//Eliminates the cell's value from it's row, column and square
void cell::set_elimination(){
	row -> eliminate(value);
	column -> eliminate(value);
	square -> eliminate(value);
}

//Returns the number of possibilities this cell has
int cell::num_possibles(){
	return possibles.num_true();
}

//Returns the first possible value after start
char cell::get_possible(char start){
	return possibles.true_after(start);
}

//Compares the possibilities arrays of the two cells
bool cell::compare(cell & comp){
	return possibles.compare(comp.possibles);
}

void cell::reset(int reset_num){
	possibles.reset();
	if(guess_num < reset_num){ 
		return;
	}
	value = '0';
	reset_num = 0;
 	tactic = empty;
}

void cell::guess_cell(int reset_num){
	char guessing = possibles.true_after('0');
	set(guessing, guess, reset_num); 
}
