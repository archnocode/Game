TARGET = game
CC = g++

PREF_SRC = ./SRC/
PREF_OBJ = ./OBJ/

SRC = $(wildcard $(PREF_SRC)*.cpp)
OBJ = $(patsubst $(PREF_SRC)%.cpp, $(PREF_OBJ)%.o, $(SRC))

$(TARGET) : $(OBJ)
	$(CC) $(OBJ) -o $(TARGET) -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -lsfml-network

$(PREF_OBJ)%.o : $(PREF_SRC)%.cpp
	$(CC) -c $< -o $@

clean :
	rm -f $(TARGET) $(PREF_OBJ)*.o
