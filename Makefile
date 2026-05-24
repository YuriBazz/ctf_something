CXX = g++
CXXFLAGS = -O0 -std=c++23 -DLOCAL  -fsanitize=address
TARGET = main
SRC = main.cpp
GHC = ghc
H_SRC = Main.hs
H_TARGET = Main
H_REMOVE = Main Main.o Main.hi

cpp:
	@clear
	@$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC)
	@./$(TARGET)
	@rm -f $(TARGET)


haskell:
	@clear
	@$(GHC) $(H_SRC)
	@./$(H_TARGET)
	@rm -f  $(H_REMOVE)