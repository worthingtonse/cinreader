#include <iostream>
#include <fstream>
#include "cinreader.hpp"
using namespace std;



void useChar(char c){
    cout << c << endl;
}




int main(int argc, char* argv[]){
    CinReader reader;
    if (argc < 2){
        cout << "Usage: " << argv[0] << " FILENAME.TXT" << endl;
    }else {
        cout << "Opening " << argv[1] << "..." << endl;
        string nextline;
        ifstream inputFile(argv[1]);
        if (inputFile.is_open()){
            while(inputFile.is_open()){
                getline(inputFile, nextline);
                for( char const &c: nextline ){
                    // char test;
                   useChar( c >> reader.readChar());
                    // reader >> test;
                }
            }
        }
    }





    return 0;
}




