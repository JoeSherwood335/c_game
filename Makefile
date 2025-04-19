CXX       := gcc
CXX_FLAGS := -std=gnu17 -ggdb  
CXX_P_FLAGS := -std=gnu17 -ggdb -D_POSIX_C_SOURCE=200112L 

BIN     := bin
SRC     := src
INCLUDE := include

LIBRARIES   := lib/*.a
EXECUTABLE  := gameServer

all: $(BIN)/$(EXECUTABLE)

run: clean all
	clear
	./$(BIN)/$(EXECUTABLE)

$(BIN)/$(EXECUTABLE): $(SRC)/*.c
	$(CXX) $(CXX_FLAGS) -I $(INCLUDE) $^ -o $@ $(LIBRARIES)

p_$(BIN)/$(EXECUTABLE): $(SRC)/*.c
	$(CXX) $(CXX_P_FLAGS) -I $(INCLUDE) $^ -o $@ $(LIBRARIES)


pre: $(SRC)/*.c
	$(CXX) $(CXX_FLAGS) -I$(INCLUDE) $^ $(LIBRARIES) -E > preprocess

clean:
	-rm $(BIN)/*
