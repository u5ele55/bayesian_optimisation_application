CC = g++ -Wall
EXECUTABLE = run.exe

SOURCES = main.cpp   \
		utils\Matrix.cpp \
		utils\Vector.cpp \
		forward_problem\system.cpp \
		forward_problem\AbstractForwardSolver.cpp \
		forward_problem\RK4Solver.cpp \
		utils\CholeskyMaster.cpp

EXECUTABLE_UNIX = run

SOURCES_UNIX = main.cpp   \
		utils/Matrix.cpp \
		utils/Vector.cpp \
		forward_problem/system.cpp \
		forward_problem/AbstractForwardSolver.cpp \
		forward_problem/RK4Solver.cpp \
		utils/CholeskyMaster.cpp


OBJECTS = $(SOURCES:.cpp=.o)

OBJECTS_UNIX = $(SOURCES_UNIX:.cpp=.o)

all: $(SOURCES) $(EXECUTABLE)

unix: $(SOURCES_UNIX) $(EXECUTABLE_UNIX)

$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(OBJECTS) -o $@

$(EXECUTABLE_UNIX): $(OBJECTS_UNIX)
	$(CC) $(OBJECTS_UNIX) -o $@

.cpp.o:
	$(CC) -c $< -o $@

clean: 
	del $(OBJECTS)

clean_unix:
	rm -f $(OBJECTS_UNIX)