# CXX = g++
# CXXFLAGS = -std=c++11 -pthread
# TARGET = main
# SRC = main.cpp

# all: $(TARGET)

# $(TARGET): $(SRC)
# 	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET)

# run: $(TARGET)
# 	./$(TARGET)

# clean:
# 	rm -f $(TARGET)

# .PHONY: all run clean


CXX      := g++
CXXFLAGS := -std=c++17 -Wall -Wextra -O2
TARGET   := architetrix

SRCS := \
	src/main.cpp \
	src/game/GameLoop.cpp \
	src/board/Board.cpp \
	src/board/RowGenerator.cpp \
	src/engine/BitwiseEngine.cpp \
	src/engine/CollisionChecker.cpp \
	src/engine/EliminationChecker.cpp \
	src/input/InputReader.cpp \
	src/render/Renderer.cpp \
	src/piece/Piece.cpp \
	src/piece/FallingPiece.cpp \
	src/piece/PieceLoader.cpp \
	src/piece/PieceController.cpp

OBJS := $(SRCS:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

	$(CXX) $(CXXFLAGS) -c -o $@ $<

clean:
	find src -name "*.o" -delete
	rm -f $(TARGET)

.PHONY: all clean
