//Brook Baise Summer 2016

#include "bool_arr.h"

#ifndef CONSTANTS
#define CONSTANTS
const char * VALUES = "123456789"; 
const char * C_START = "\033[34m"; //Blue
const char * C_END = "\033[39m"; //Default
const char * C2_START = "\033[32m"; //Green
const char * C3_START = "\033[33m"; //Yellow
const char * RED = "\033[31m"; //Red
#endif

//Converts a char into an int
int convert(char c){
	switch(c){
		case '0': 
			return 0;
		case '1':
			return 1;
		case '2':
			return 2;
		case '3':
			return 3;
		case '4':
			return 4;
		case '5':
			return 5;
		case '6':	
			return 6;
		case '7':
			return 7;
		case '8':
			return 8;
		case '9':
			return 9;
		default:
			return -1;
	}
}


contradiction::contradiction(const char * c){
	location = new char[strlen(c) + 1];
	strcpy(location, c);
}

//Sets all the positions to true
bool_arr::bool_arr(){
	for(int i = 0; i < 9; ++i){
		arr[i] = true;
	}
}

//Sets the given character to false
//returns true if it was changed
bool bool_arr::eliminate(char c){
	int index = convert(c) -1;
	if(index >= 0 && arr[index] != false){
		arr[index] = false;
		return true;
	}
	return false;
}

//Checks the value of the passed in character
bool bool_arr::check(char c){
	int index = convert(c) -1;
	if(index >= 0){
		return arr[index];
	}
	throw new contradiction("INVALID INPUT TO CHECK IN BOOL ARRAY");
	return false;
}

//Returns the character of the first true after
//the passed in character. E if error
char bool_arr::true_after(char c){
	int index = -1;
	int i = convert(c);
	if(i < 0){
		throw new contradiction("True After Contradiction: Passed in char was E");
	}
	for(; i < 9 && index < 0; ++i){
		if(arr[i] == true)
			index = i;	
	}
	if(index >= 0 && index < 9){
		return VALUES[index];
	}
	throw new contradiction("True After Contradiction");
	
}

//Returns the number of trues
int bool_arr::num_true(){
	int num = 0;
	for(int i = 0; i < 9; ++i){
		if(arr[i] == true)
			++num;
	}
	return num;
}

//Displays Red for false and Blue for true
void bool_arr::display(){
	for(int i = 0; i < 9; ++i){
		if(arr[i])
			cout << C_START;
		else
			cout << RED;
		cout << i + 1 << " " << C_END;
	}
}


//Compares two bool arrays
bool bool_arr::compare(bool_arr comp){
	bool equal = true;
	for(int i = 0; i < 9 && equal; ++i){
		equal = arr[i] == comp.arr[i];
	}
	return equal;
}


//Resets all values to true
void bool_arr::reset(){
	for(int i = 0; i < 9; ++i){
		arr[i] = true;
	}
}

//display the true values
void bool_arr::dispTrue(){
	cout << "[";
	bool started = false;
	for(int i = 0; i < 9; ++ i){
		if(arr [i]){
			if(!started){
				started = true;
				cout << i + 1;
			}
			else{
				cout << ", " << i + 1;
			}
		}	
	}
	cout << "]";
}
