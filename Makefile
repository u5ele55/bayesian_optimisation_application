CC = g++ -Wall
EXECUTABLE = run.exe

SOURCES = main.cpp   \
		utils\Matrix.cpp \
		utils\Vector.cpp \
		forward_problem\system.cpp \
		forward_problem\AbstractForwardSolver.cpp \
		forward_problem\RK4Solver.cpp

OBJECTS = $(SOURCES:.cpp=.o)

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(OBJECTS) -o $@ 

.cpp.o:
	$(CC) -c $< -o $@

clean: 
	del $(OBJECTS)