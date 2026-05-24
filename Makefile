CXX = g++
CXXFLAGS = -O3 -std=c++23 -DLOCAL  -fsanitize=address -Wall -Wextra -Wshadow
TARGET = main
SRC = main.cpp

all:
	@clear
	@$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC)
	@./$(TARGET)
	@rm -f $(TARGET)
