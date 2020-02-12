ARGS = -std=c++11 -Wall -Wextra -Werror -pedantic-errors

test: test.cpp
	g++ test.cpp -o test.exe

clean:
	rm -f test.exe
