// -- Andrew Mattly --
// 2/13/20 - xx/xx/xx
// test functions for cinreader.hpp
// begins with manual check and then intends to become automated with loops.

#include <iostream>
#include <string>
#include <sstream>
#include "cinreader.hpp"
using namespace std;



void test_bool();

void test_char();

void test_double();

void test_float();

void test_integer();

void test_string();

void test_stream_string();

/**errors
 *std out_of_range error (int)
 *
 */

int main(){
	//test_bool();
	//test_char();
	//test_double();
	//test_float();
	//test_integer();
	test_stream_string();
  return 0;
}


void test_bool(){
  CinReader reader; //object to control cin 
  cout << "testing bool: " <<endl;
  bool bool1 = reader.readBool();
  cout << "bool is: " << bool1 << endl;

}

void test_char(){
  cout << "testing char: "<< endl;
  CinReader reader; //object to control cin

//stream in stopping before space (except for string)
//stream cout to file
//ifstream superset?
//does changing coutputs actually change it.

  
  bool loop(true);
  char test_c = 'a';
  while(loop){
	  cout <<"type 'z' to end loop" << endl;
	  test_c = reader.readChar();
	  cout << "char is: " << test_c << endl;
	  if(test_c == 'z'){
	     cout << "exiting" << endl;
	     loop = false;
	  }  
  }
}



void test_double(){
  cout << "testing double: " << endl;
  
  CinReader reader; //object to control cin
  bool loop(true);
  double test_d;

  while(loop){
    cout << "type 1.11 to end loop" << endl;
    test_d = reader.readDouble();
    cout << "double is: " << test_d << endl;
    if(test_d == 1.11){
    cout << "exiting double loop" << endl;
    loop= false;
    }   
  }
}
void test_float(){
  cout << "testing float: " << endl;

  CinReader reader;
  bool loop(true);
  float test_f;

  while(loop){
	cout << "type 2.22 to end loop" << endl;
	test_f = reader.readFloat();
	cout << "float is: " << test_f << endl;
	if(test_f == 2.22){
		cout << "ending float loop" << endl;
		loop = false;
	}
  }
}
void test_integer(){
	CinReader reader;
	cout << "testing integer: " << endl;
	bool loop(true);
	int test_i;

	while(loop){
		cout << "type 0 to end loop" << endl;
		test_i = reader.readInt();
		cout << "integer is: " << test_i << endl;
		if(test_i == 0){
			cout << "ending int loop" << endl;
			loop = false;
		}
	}  
}
void test_string(){
	cout << "testing string: " << endl;

	CinReader reader; //object to control cin

	bool loop(true);
	string test_s;
	
	while(loop){
		cout << "type 'null' to end loop" << endl;
		test_s = reader.readString();
		cout << "string is: " << test_s << endl;
		if(test_s == "null"){
			cout << "ending string loop" << endl;
			loop = false;
		}
	}
}

void test_stream_string(){
	cout << "testing string stream operation" << endl;
	CinReader reader;
	bool loop(true);
	string test_s1;
	string test_s2;
	while(loop){
		cout << "type 'null' to end loop" << endl;
		//test_s1 = reader.readString();
		reader >> test_s2;
		cout << "string is: " << test_s2 << endl;
		if(test_s2 == "null"){
			cout << "ending string loop" << endl;
			loop = false;
		}
	
	}
}


