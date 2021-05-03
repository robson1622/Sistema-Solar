# this variable will contain the names of all cpp source files
SRCS:=$(wildcard *.cpp)

# this will contain the names of all intermediate object files
OBJECTS:=$(patsubst %.cpp,bin/%.o,$(SRCS))

# $< are the names of all prerequisites (the object files)
# $@ is the name of the target (obj/myprogram in this case)
main.exe: $(OBJECTS)
	g++ $^ -o $@ -lsfml-graphics -lsfml-window -lsfml-system

# but now we have to tell make how to build the object files
# -c option tells g++ to only compile one source file at a tile
#  $< is the name of the first prerequisite (the cpp file in this case)
bin/%.o: %.cpp
	g++ $< -c -o $@ 

clean:
	rm main.exe -f bin/*.o