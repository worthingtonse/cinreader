#include "cinreader.hpp"

#include <iostream>
using std::boolalpha;
using std::cout;
using std::endl;

void basicTest();
void stringTest();
void extractionTest();

int main() {
  basicTest();
  extractionTest();
  stringTest();

  return 0;
}

void stringTest() {
  CinReader reader;

  string s;
  cout << "Enter yes/no/maybe (case sensitive): ";
  s = reader.readString(true, {"yes", "no", "maybe"});
  cout << "STRING INPUT = " << s << endl;

  reader.setMessage(MessageType::STRING_NOT_ALLOWED, "Oops. Try again: ");

  cout << "Enter yes/no/maybe (case insensitive): ";
  cout << "Enter yes/no/maybe: ";
  s = reader.readString(false, {"yes", "no", "maybe"});
  cout << "STRING INPUT = " << s << endl;
}

void basicTest() {
  CinReader reader;

  int i(0);
  cout << "Enter any integer: ";
  i = reader.readInt();
  cout << "INT INPUT = " << i << endl;

  cout << "Enter an integer between -10 and 10: ";
  i = reader.readInt(-10, 10);
  cout << "INT INPUT = " << i << endl;

  char c('x');
  cout << "Enter any character: ";
  c = reader.readChar();
  cout << "CHAR INPUT = " << c << endl;

  cout << "Enter Yy or Nn: ";
  c = reader.readChar("YyNn");
  cout << "CHAR INPUT = " << c << endl;

  double d(0.0);
  cout << "Enter a double: ";
  d = reader.readDouble();
  cout << "DOUBLE INPUT = " << d << endl;

  float f(0.0);
  cout << "Enter a float: ";
  f = reader.readFloat();
  cout << "FLOAT INPUT = " << f << endl;

  bool b(false);
  cout << "Enter T[rue] or F[alse]: ";
  b = reader.readBool();
  cout << "BOOL INPUT = " << boolalpha << b << endl;
}

void extractionTest() {
  CinReader reader;

  int i(0);
  cout << "Enter an integer: ";
  reader >> i;
  cout << "INT INPUT = " << i << endl;

  bool b(false);
  cout << "Enter a bool: ";
  reader >> b;
  cout << "BOOL INPUT = " << boolalpha << b << endl;

  char c('x');
  cout << "Enter a char: ";
  reader >> c;
  cout << "CHAR INPUT = " << c << endl;

  float f(0);
  cout << "Enter a float: ";
  reader >> f;
  cout << "FLOAT INPUT = " << f << endl;

  double d(0);
  cout << "Enter a double: ";
  reader >> d;
  cout << "DOUBLE INPUT = " << d << endl;

  string s;
  cout << "Enter a string: ";
  reader >> s;
  cout << "STRING INPUT = " << s << endl;
}
