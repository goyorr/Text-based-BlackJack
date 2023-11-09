NAME = BlackJack

SRC = BlackJack.cpp

OBJ = ${SRC:.cpp=.o}

C++ = c++

RM = rm -f

CPPFLAGS = -std=c++11

all: ${NAME}

${NAME}: ${OBJ}
		 ${C++} ${OBJ} -o $@
 
%.o: %.cpp
	 ${C++} ${CPPFLAGS} -c $<

clean:
		${RM} ${OBJ}

fclean: clean
		${RM} ${NAME}

re: fclean all