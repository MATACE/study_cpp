# Source file.
# Automatically finds all.c and.cpp files and defines the target as a.o file with the same name.
# The *.c save in src directory.
SOURCE  := $(wildcard ./src/*.c) $(wildcard ./src/*.cpp)
OBJS    := $(patsubst %.c,%.o,$(patsubst %.cpp,%.o,$(SOURCE)))

# Target you can change test to what you want.
TARGET  := demo

# Compile and lib parameter.
CC      := g++
LIBS    := 
LDFLAGS := -ldl -lglog -lpthread -lboost_regex -lboost_system -lboost_timer
DEFINES :=
# The *.o save in include directory.
INCLUDE := -I ./include
CFLAGS  :=  -Wall  $(DEFINES) $(INCLUDE) -std=c++11
CXXFLAGS:= $(CFLAGS) -DHAVE_CONFIG_H


.PHONY : everything objs clean veryclean rebuild

everything : $(TARGET)

all : $(TARGET)

objs : $(OBJS)

rebuild: veryclean everything

clean :
	rm -fr ./src/*.so
	rm -fr ./src/*.o
	rm -rf $(TARGET)

veryclean : clean
	rm -fr $(TARGET)

$(TARGET) : $(OBJS)
	$(CC)  -o $@ $(OBJS) $(LDFLAGS) $(LIBS)
