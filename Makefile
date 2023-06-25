.PHONY: build clean test

CXXFLAGS = -Wall -Wextra -Wshadow -Werror -Wconversion -Wpedantic -std=c++20 -O3
CPPFLAGS = -I./include
CXX = g++
SUBDIR = $(day)/$(part)

$(SUBDIR)/aocmain:
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -o $@ $(wildcard $(SUBDIR)/*.cpp)

clean:
	find -type f -name aocmain -delete
	find -type f -name a.out -delete
	find . -name __pycache__ -type d -exec rm -rf {} +

build:
	@docker build . -t aoc22  # just a single-stage build

test:
	@docker run --rm aoc22:latest
