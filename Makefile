.PHONY: clean

CXXFLAGS = -Wall -Wextra -Wshadow -Werror -Wconversion -Wpedantic -std=c++20 -O3
CPPFLAGS = -I./include
CXX = g++

main:
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -o $@ $(wildcard $(day)/*.cpp)

clean:
	rm -f main *.out
