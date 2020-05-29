CXXFLAGS += -O3 -m64
CXXFLAGS += -Wall
CXXFLAGS += -Wextra
CXXFLAGS += -pedantic
CXXFLAGS += -Weffc++
CXXFLAGS += -std=c++17

ASFLAGS64  = --64

all:
	$(info For Windows use: $(MAKE) windows)
	$(info For Linux use: $(MAKE) linux)
	$(error Missing argument: windows or linux)

compile:
	$(CXX) -c argv_parser.cpp -o argv_parser.o $(CXXFLAGS)
	$(CXX) -c main.cpp -o main.o $(CXXFLAGS)

linux: compile
	$(AS) rdrand_func_linux.S ${ASFLAGS64} -o rdrand_func_linux.o
	$(CXX) main.o argv_parser.o rdrand_func_linux.o -o dd_rand

windows: compile
	$(AS) rdrand_func_windows.S ${ASFLAGS64} -o rdrand_func_windows.o
	$(CXX) main.o argv_parser.o rdrand_func_linux.o -o dd_rand.exe
