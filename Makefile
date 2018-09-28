CC := g++
OBJ := objects
SRC := sources

ifeq ($(OS),Windows_NT)
	CFLAGS	:= -DDGLEW_NO_GLU -DGLEW_BUILD -static -std=c++17 -g 
	LLIB   	:= -I .\libraries\include -L .\libraries\lib
	LDFLAGS := -lglfw3 -lopengl32 -luser32 -lgdi32 -lshell32 -lglu32 -lglew32
	WFLAGS	:= -Wall
else
	CFLAGS 	:= -std=c++17 -fsanitize=address 
	LLIB   	:= 
	LDFLAGS := -lglfw3 -lopengl32 -luser32 -lgdi32 -lshell32 -lglu32 -lglew32
	WFLAGS	:= -Wall
endif

rwildcard=$(foreach d,$(wildcard $1*),$(call rwildcard,$d/,$2) $(filter $(subst *,%,$2),$d))

TARGET 	:= main
# main code
SOURCES := $(call rwildcard, $(SRC)/, *.cpp)
# SOURCES := $(powershell.exe dir -Path $(SRC)/ -Filter *.cpp -Recurse | ForEach-Object FullName | Resolve-Path -Relative)
OBJECTS := $(patsubst $(SRC)/%.cpp, $(OBJ)/%.o, $(SOURCES))
OBJDIRS := $(dir $(OBJECTS))

DUMMY := $(shell mkdir --parents $(OBJDIRS))

$(TARGET): sources
	$(CC) $(OBJECTS) -o $(TARGET) $(CFLAGS) $(LLIB) $(LDFLAGS) $(WFLAGS)

# make source
sources: $(OBJECTS)
$(OBJ)/%.o: $(SRC)/%.cpp
	$(CC) -c $< -o $@ $(LLIB) $(CFLAGS) $(LDFLAGS)

clean:
	rm -f $(TARGET) $(OBJ)/*.o $(OBJ)/*/*.o core

check: $(TARGET)
	valgrind --leak-check=full ./$(TARGET)