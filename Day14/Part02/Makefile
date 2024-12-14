NAME = christmasIsComing
CXX = clang++
CXXFLAGS = -std=c++17 -O3 -Ofast -march=native -mtune=native -flto \
			-fno-rtti -fomit-frame-pointer \
			-funroll-loops -fstrict-aliasing -ffunction-sections -fdata-sections \
			-DNDEBUG -Wall -Wextra -Wpedantic -Wno-unused-function
			-fsanitize=address -fno-omit-frame-pointer -g
LDFLAGS = -flto -Wl,-O3 -Wl,-dead_strip

all: $(NAME)

$(NAME): main.o
	$(CXX) $(CXXFLAGS) $(LDFLAGS) main.o -o $(NAME)

main.o: main.cpp
	$(CXX) $(CXXFLAGS) -c main.cpp -o main.o

clean: fclean
fclean:
	rm -f $(NAME) main.o

re: fclean all

run: all
	./$(NAME)
