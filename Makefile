ARGS = -std=c++11 -Wall -Wextra -Werror -pedantic-errors

test: test.cpp
	g++ test.cpp -o test.exe
manual_test: manual_test.cpp
	g++ $(ARGS) -g manual_test.cpp -o  manual_test.exe
test_char: test_char.cpp
	g++ $(ARGS) -g test_char.cpp -o test_char.exe
clean:
	rm -f test.exe manual_test.exe testChar.exe

