CC := g++
OBJ := objects
SRC := sources

ifeq ($(OS),Windows_NT)
	CFLAGS	:= -DDGLEW_NO_GLU -DGLEW_STATIC -static -std=c++17 
	LLIB   	:= -I .\libraries\include -L .\libraries\lib
	LFLAGS  := -lglfw3 -lopengl32 -luser32 -lgdi32 -lshell32 -lglu32 -lglew32s
else
	CFLAGS 	:= -std=c++17 -fsanitize=address 
	LLIB   	:= 
	LFLAGS 	:= -lglfw3 -lopengl32 -luser32 -lgdi32 -lshell32 -lglu32 -lglew32s
endif

TARGET 	:= main
# main code
SOURCES := $(wildcard $(SRC)/*/*.cpp $(SRC)/*.cpp)
# SOURCES := $(shell find $(SRC)/ -type f -name '*.cpp')
OBJECTS := $(patsubst $(SRC)/%.cpp, $(OBJ)/%.o, $(SOURCES))

$(TARGET): sources
	$(CC) $(OBJECTS) -o $(TARGET) $(CFLAGS) $(LLIB) $(LFLAGS)

# make source
sources: $(OBJECTS)
$(OBJ)/%.o: $(SRC)/%.cpp
	$(CC) -c $< -o $@ $(LLIB) $(CFLAGS) $(LFLAGS)

clean:
	rm -f $(TARGET) $(OBJ)/*.o $(OBJ)/*/*.o core

check: $(TARGET)
	valgrind --leak-check=full ./$(TARGET)