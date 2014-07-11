# the compiler to use.
COMPILER=clang++

# include path
INCLUDE=-Iinclude

# program souce files
SOURCES=source/manpage/*.cpp

# build source
BUILD_SOUCES=$(SOURCES) main.cpp

# test source files
TEST_SOURCES=$(SOURCES) test/manpage/*.cpp

# depencences
LIBS=-lgtest

# flags for compiling
FLAGS=-std=c++11

# executable name
EXECUTABLE=marketzilla
TEST_EXEC=marketzillaTest

all: test build

test: $(TEST_SOURCES)
	$(COMPILER) -o $(TEST_EXEC) $(TEST_SOURCES) $(INCLUDE) $(LIBS) $(FLAGS)
	./$(TEST_EXEC)

build: $(BUILD_SOUCES)
	$(COMPILER) -o $(EXECUTABLE) $(BUILD_SOUCES) $(INCLUDE) $(LIBS) $(FLAGS)
	#./$(EXECUTABLE)

clean:
	rm -rf *.o $(EXECUTABLE) $(TEST_EXEC)