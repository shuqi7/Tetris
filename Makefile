CXX = g++-5
CXXFLAGS = -std=c++14 -Wall -Werror=vla -MMD -g
EXEC = quadris
OBJECTS = main.o Block.o gameInterface.o controlInput.o punishBlock.o Cell.o IBlock.o JBlock.o LBlock.o OBlock.o SBlock.o TBlock.o ZBlock.o TextDisplay.o GraphicsDisplay.o window.o Subject.o hintBlock.o 
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC} -lX11

-include ${DEPENDS}

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}
.PHONY: clean
