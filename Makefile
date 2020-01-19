CXX = clang++
CXXFLAGS = -Wall -Werror -Wextra -g

INCLUDES = -I src/
RAW_SRC = main \
					Game \
					Logger \
					Entity \
					Player \
					Enemy \
					Missile \
					Bonus \
					Boss \
					Asteroid
SRC = $(addprefix src/, $(addsuffix .cpp, $(RAW_SRC)))
OBJ = $(addprefix build/, $(addsuffix .o, $(RAW_SRC)))
LDLIBS = -lncurses

EXEC = ft_retro

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJ) $(LDLIBS)

./build/%.o: ./src/%.cpp
	$(CXX) $(CXXFLAGS) -o $@ -c $< $(INCLUDES)

clean:
	/bin/rm $(OBJ)

fclean:
	/bin/rm $(OBJ) $(EXEC)

re: fclean all

.PHONY = all clean fclean re