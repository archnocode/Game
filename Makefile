
TARGET = game
CC = g++

PREF_SRC = ./SRC/
PREF_OBJ = ./OBJ/

SRC = $(wildcard $(PREF_SRC)*.cpp)
OBJ = $(patsubst $(PREF_SRC)%.cpp, $(PREF_OBJ)%.o, $(SRC))

$(TARGET) : $(OBJ)
    $(CC) $(OBJ) -o $(TARGET) -lncurses

$(PREF_OBJ)%.o : $(PREF_SRC)%.cpp
    $(CC) -c $< -o $@

clean :
    rm -f $(TARGET) $(PREF_OBJ)*.o