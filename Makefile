CXX = clang++
CXXFLAGS = -Wall -Werror -Wextra

SRC = 	src/main.cpp \
		src/Entity.cpp \
		src/Player.cpp \
		src/Enemy.cpp \
		src/Missile.cpp

LD_FLAGS = -lncurses
INCLUDES = src/
OBJ = $(SRC:src/.cpp=build/.o)
EXEC = ft_retro

all: $(EXEC)

$(EXEC): $(OBJ)
		$(CXX) $(CXXFLAGS) -o $@ $(OBJ) $(LD_FLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -o $@ -c $< $(INCLUDES)

clean:
	/bin/rm $(OBJ)

fclean:
	/bin/rm $(OBJ) $(EXEC)

re: fclean all

.PHONY = all clean fclean re