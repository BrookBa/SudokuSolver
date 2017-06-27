//Brook Baise Summer 2016
//A class that keeps track of a bool array of size 9
#include <iostream>
#include <cstring>
#include <fstream>
//Will display additional output if defined
//#define tests

using namespace std;
extern const char * VALUES; 
extern const char * C_START;
extern const char * C_END; 
extern const char * C2_START;
extern const char * C3_START;
extern const char * RED;


int convert(char);

struct contradiction{
 	char * location;
	contradiction(const char *);
};

class bool_arr{
	public:
		bool_arr();
		bool eliminate(char c);
		bool check(char c);
		char true_after(char c);
		int num_true();
		void display();
		void dispTrue();
		bool compare(bool_arr);
		void reset();

	private:
		bool arr[9];
	
};
