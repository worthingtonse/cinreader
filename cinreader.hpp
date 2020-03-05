/*
 * CinReader, v2.02
 *
 * Copyright 2019 J Boyd Trolinger
 * 
 * Contributors: Samuel Fuller, Andrew Mattly
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to
 * deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

/*
 * REQUIREMENTS
 *   - must be compiled with std=c++11 or newer
 *   - must include this header file    -> #include "cinreader.hpp"
 *   - must create a CinReader instance -> CinReader reader;
 *
 * EXAMPLES OF USAGE
 *
 * Reading bools
 *
 *   bool b1 = reader.readBool();
 *   bool b2;
 *   reader >> b2;
 *
 * Reading chars
 *
 *   char c1 = reader.readChar();         // any single character accepted
 *   char c2 = reader.readChar("YyNn");   // 'Y', 'y', 'N', 'n' only accepted
 *   char c3;
 *   reader >> c3;                        // any single character accepted
 *
 * Reading doubles
 *
 *   double d1 = reader.readDouble();
 *   double d2;
 *   reader >> d2;
 *
 * Reading floats
 *
 *   float f1 = reader.readFloat();
 *   float f2;
 *   reader >> f2;
 *
 * Reading integers
 *
 *   int i1 = reader.readInt();            // any signed integer value accepted
 *   int i2 = reader.readInt(-10, 10);     // between -10 and 10 (inclusive) only accepted
 *   int i3;
 *   reader >> i3;                         // any signed integer value accepted
 *
 * Reading strings
 *
 *   string s1 = reader.readString();      // any string, including empty string accepted
 *   string s2 = reader.readString(false); // any string, will not accept empty string
 *
 *   // only accepts "yes", "no", or "maybe"; case sensitive
 *   string s3 = reader.readString(true, {"yes", "no", "maybe"})
 *
 *   // only accepts "yes", "no", or "maybe"; case insensitive
 *   string s4 = reader.readString(false, {"yes", "no", "maybe"})
 *
 *   string s5;
 *   reader >> s5;                         // any string, including empty string accepted
 *
 * Changing error messages displayed by CinReader
 *   - note that the error messages become a secondary prompt for input
 *
 *   reader.setMessage(MessageType::INT_INVALID, "Your input is invalid. Try again: ")
 *
 *   Message types: INT_INVALID, INT_OUT_OF_RANGE, STRING_CANNOT_BE_EMPTY, CHAR_NOT_ALLOWED,
 *                  DOUBLE_INVALID, FLOAT_INVALID, BOOL_INVALID, STRING_NOT_ALLOWED
 */
#pragma once

#if __cplusplus < 201103L
#error CinReader requires C++11 or newer.
#else

#include <algorithm>
#include <array>
#include <initializer_list>
#include <iostream>
#include <limits>
#include <stdexcept>
#include <string>
#include <vector>
using std::array;
using std::cin;
using std::cout;
using std::initializer_list;
using std::invalid_argument;
using std::stod;
using std::stof;
using std::stoi;
using std::string;
using std::vector;

#define MIN_INT std::numeric_limits<int>::min()
#define MAX_INT std::numeric_limits<int>::max()

enum MessageType {
  INT_INVALID=0,
  INT_OUT_OF_RANGE=1,
  STRING_CANNOT_BE_EMPTY=2,
  CHAR_NOT_ALLOWED=3,
  DOUBLE_INVALID=4,
  FLOAT_INVALID=5,
  BOOL_INVALID=6,
  STRING_NOT_ALLOWED=7,
  INT_TOO_LARGE=8
};

class CinReader {
public:
  CinReader() {
    this->defaultMessages();
  }

  bool readBool() {
    bool input(false);

    bool validInput(false);
    while (!validInput) {
      char boolChar = toupper(this->readString(false).at(0));
      if (boolChar == 'T') {
        input = true;
        validInput = true;
      } else if (boolChar == 'F') {
        input = false;
        validInput = true;
      } else {
        cout << this->messages[BOOL_INVALID];
      }
    }

    return input;
  }

  CinReader& operator>>(bool& input) {
    input = this->readBool();
    return *this;
  }

  char readChar(string allowed="") {
    char input('x');

    bool validInput(false);
    while (!validInput) {
      input = this->readString(false)[0];
      for (char a : allowed) {
        if (input == a) {
          validInput = true;
          break;
        }
      }
      if (allowed.size() > 0 && !validInput) {
        cout << this->messages[CHAR_NOT_ALLOWED];
      } else {
        break;
      }
    }

    return input;
  }

  CinReader& operator>>(char& input) {
    input = this->readChar();
    return *this;
  }

  double readDouble() {
    double input(0.0);

    bool validInput(false);
    while (!validInput) {
      try {
        size_t last;
        string doubleStr = this->readString(false);
        input = stod(doubleStr, &last);
        if (last != doubleStr.size()) {
          cout << this->messages[DOUBLE_INVALID];
          continue;
        }
        validInput = true;
      } catch (invalid_argument &e) {
        cout << this->messages[DOUBLE_INVALID];
      }
    }

    return input;
  }

  CinReader& operator>>(double& input) {
    input = this->readDouble();
    return *this;
  }

  float readFloat() {
    float input(0.0);

    bool validInput(false);
    while (!validInput) {
      try {
        string floatStr = this->readString(false);
        size_t last;
        input = stof(floatStr, &last);
        if (last != floatStr.size()) {
          cout << this->messages[FLOAT_INVALID];
          continue;
        }
        validInput = true;
      } catch (invalid_argument &e) {
        cout << this->messages[FLOAT_INVALID];
      }
    }

    return input;
  }

  CinReader& operator>>(float& input) {
    input = this->readFloat();
    return *this;
  }

  int readInt(int min=MIN_INT, int max=MAX_INT) {
    int input(0);

    bool validInput(false);
    while (!validInput) {
      try {
        size_t last;
        string intStr = this->readString(false);
        if (intStr.size() > 9){
            cout << this->messages[INT_TOO_LARGE];
            continue;
        }
        input = stoi(intStr, &last);
        if (input < min || input > max) {
          cout << this->messages[INT_OUT_OF_RANGE];
          continue;
        } else if (last != intStr.size()) {
          cout << this->messages[INT_INVALID];
          continue;
        }
        validInput = true;
      } catch (invalid_argument &e) {
        cout << this->messages[INT_INVALID];
      }
    }

    return input;
  }

  CinReader& operator>>(int& input) {
    input = this->readInt();
    return *this;
  }

  string readString(bool allowEmpty=true) {
    string input;

    bool validInput(false);
    while (!validInput) {
      getline(cin, input);
      if (!allowEmpty && input.size() == 0) {
        cout << this->messages[STRING_CANNOT_BE_EMPTY];
        continue;
      }
      validInput = true;
    }

    return input;
  }

  string readString(bool caseSensitive, initializer_list<string> allowedStrings) {
    string input;

    vector<string> allowed(allowedStrings);
    if (!caseSensitive) {
      for (string& s : allowed) {
        transform(s.begin(), s.end(),  s.begin(), ::toupper);
      }
    }

    bool validInput(false);
    while (!validInput) {
      input = this->readString();
      if (!caseSensitive) {
        transform(input.begin(), input.end(),  input.begin(), ::toupper);
      }

      for (string a : allowed) {
        if (a == input) {
          validInput = true;
          break;
        }
      }

      if (!validInput) {
        cout << this->messages[STRING_NOT_ALLOWED];
      }
    }

    return input;
  }

  CinReader& operator>>(string& input) {
    input = this->readString();
    return *this;
  }

  void setMessage(MessageType type, string message) {
    if (type >= INT_INVALID && type <= STRING_NOT_ALLOWED) {
      this->messages[type] = message;
    }
  }

private:
  array<string, 9> messages;

  void defaultMessages() {
    this->messages[INT_INVALID] = "Input is not a valid integer. Re-enter: ";
    this->messages[FLOAT_INVALID] = "Input is not a valid float. Re-enter: ";
    this->messages[DOUBLE_INVALID] = "Input is not a valid double. Re-enter: ";
    this->messages[INT_OUT_OF_RANGE] = "Input is not in the required range. Re-enter: ";
    this->messages[STRING_CANNOT_BE_EMPTY] = "Input cannot be empty. Re-enter: ";
    this->messages[CHAR_NOT_ALLOWED] = "Input character is not allowed. Re-enter: ";
    this->messages[BOOL_INVALID] = "Input is not valid for boolean. Re-enter: ";
    this->messages[STRING_NOT_ALLOWED] = "Input is not allowed. Re-enter: ";
    this->messages[INT_TOO_LARGE] = "Input is too large, Re-enter: ";
  }
};

#endif
