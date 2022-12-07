.PHONY: clean

CXXFLAGS = -Wall -Wextra -Wshadow -Werror -Wconversion -Wpedantic -std=c++20 -O3
CPPFLAGS = -I./include
CXX = g++
SUBDIR = $(day)/$(part)


$(SUBDIR)/main:
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -o $@ $(wildcard $(SUBDIR)/*.cpp)
	./$(SUBDIR)/main $(day)/input.txt
clean:
	rm -f main *.out
