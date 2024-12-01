NAME = christmasIsComing

all:
	clang++ main.cpp -o $(NAME) -std=c++17 -Wall -Wextra -Werror

clean: fclean
fclean:
	rm -f $(NAME)

re: fclean all

run: all
	./$(NAME)
