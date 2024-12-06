NAME = christmasIsComing

all:
	clang++ main.cpp -o $(NAME) -std=c++17 -fsanitize=address -g

clean: fclean
fclean:
	rm -f $(NAME)

re: fclean all

run: all
	./$(NAME)
