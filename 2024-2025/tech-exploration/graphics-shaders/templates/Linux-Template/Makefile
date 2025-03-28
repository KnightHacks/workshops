.PHONY: clean

EXE = graphics

CC = g++
LIBS = -lglfw -lGL -lX11 -lpthread -lXrandr -lXi -ldl -lm
SRCS = main.cpp glad.c
HEADERS = glad.h

${EXE}: ${SRCS} ${HEADERS}
	${CC} ${SRCS} -o ${EXE} ${LIBS}

clean:
	rm -f ${EXE}