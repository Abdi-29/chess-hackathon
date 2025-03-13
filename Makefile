NAME = chessbot

SOURCE = src
INCLUDE = -I ./includes

SRC =   $(SOURCE)/chessboard.cpp \
		$(SOURCE)/move.cpp \
		$(SOURCE)/main.cpp

OBJ = $(SRC:%.cpp=%.o)


CFLAGS = -Wall -std=c++20

all: $(NAME)

$(NAME): $(OBJ)
	c++ $(OBJ) -o $(NAME)

%.o: %.cpp
	c++ -c  $(INCLUDE) $(CFLAGS) $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

.PHONY: clean fclean all re
re:     fclean all