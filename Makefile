.PHONY: clean

CXXFLAGS = -Wall -Wextra -Wshadow -Werror -Wconversion -Wpedantic -std=c++20 -O3
CPPFLAGS = -I./include
CXX = g++
SUBDIR = $(day)/$(part)


$(SUBDIR)/aocmain:
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -o $@ $(wildcard $(SUBDIR)/*.cpp)

clean:
	find -type f -name aocmain -delete
	find -type f -name a.out -delete
