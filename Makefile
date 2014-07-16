# the compiler to use.
COMPILER=clang++

# include path
INCLUDE=-Iinclude

# program souce files
GENERATE_SOURCE=source/generate/*.cpp
SEARCH_SOURCE=source/search/*.cpp

# build source
GENERATE_BUILD_SOUCE=$(GENERATE_SOURCE)
SEARCH_BUILD_SOURCE=$(SEARCH_SOURCE)

# depencences
LIBS=-lgtest

# flags for compiling
FLAGS=-std=c++11

# executable name
GENERATE_EXE=generate
SEARCH_EXE=search


all: build

build: $(GENERATE_BUILD_SOUCE) $(SEARCH_BUILD_SOURCE)
	$(COMPILER) -o $(GENERATE_EXE) $(GENERATE_BUILD_SOUCE) $(INCLUDE) $(LIBS) $(FLAGS)
	$(COMPILER) -o $(SEARCH_EXE) $(SEARCH_BUILD_SOURCE) $(INCLUDE) $(LIBS) $(FLAGS)

clean:
	rm -rf $(GENERATE_EXE) $(SEARCH_EXE)