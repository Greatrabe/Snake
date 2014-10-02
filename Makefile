CXX = g++ 
CXXFLAGS = -Wall -MMD -g -lncurses  -L/usr/X11R6/lib -lX11
OBJECTS = main.o bitmap.o window.o character.o map.o food.o tail.o
DEPENDS = ${OBJECTS:.o=.d}
EXEC = test

${EXEC} : ${OBJECTS}
	${CXX} ${OBJECTS} ${CXXFLAGS} -o ${EXEC}

-include ${DEPENDS}

.PHONY : clean
clean :
	rm -rf ${DEPENDS} ${OBJECTS} ${EXEC}
