## Makefile для сборки и запуска проекта (main.cpp и main2.cpp)

# Компилятор и флаги
CXX := g++
CXXFLAGS := -std=c++17 -O2 -Wall -Wextra -pedantic

# Источники и бинарники
SRC1 := horner.cpp
SRC2 := newtone.cpp
BIN1 := app_horner
BIN2 := app_newton

.PHONY: all build run run1 run2 clean

all: build

build: $(BIN1) $(BIN2)

$(BIN1): $(SRC1)
	$(CXX) $(CXXFLAGS) $(SRC1) -o $(BIN1)

$(BIN2): $(SRC2)
	$(CXX) $(CXXFLAGS) $(SRC2) -o $(BIN2)

# Запуск метода Горнера (main.cpp)
run1: $(BIN1)
	./$(BIN1)

# Запуск метода Ньютона (main2.cpp)
run2: $(BIN2)
	./$(BIN2)

# Запуск обоих программ
run: run1 run2

clean:
	rm -f $(BIN1) $(BIN2)


