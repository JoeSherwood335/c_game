CXX       := gcc
CXX_FLAGS := -std=gnu17 -ggdb  
CXX_P_FLAGS := -std=gnu17 -ggdb -D_POSIX_C_SOURCE=200112L 

BIN     := bin
SRC     := src
INCLUDE := include

LIBRARIES   := lib/*.a
EXECUTABLE_SERVER  := gameServer
EXECUTABLE_CLIENT  := gameClient

all: $(BIN)/$(EXECUTABLE_CLIENT) $(BIN)/$(EXECUTABLE_SERVER)
	@echo "Compiling $(EXECUTABLE_SERVER) and $(EXECUTABLE_CLIENT) in $(BIN) directory"

run: clean all
	clear
	./$(BIN)/$(EXECUTABLE_SERVER) &
	./$(BIN)/$(EXECUTABLE_CLIENT) 

$(BIN)/$(EXECUTABLE_SERVER): $(SRC)/g_server.c
	$(CXX) $(CXX_FLAGS) -I $(INCLUDE) $^ -o $@ $(LIBRARIES)

$(BIN)/$(EXECUTABLE_CLIENT): $(SRC)/g_client.c
	$(CXX) $(CXX_FLAGS) -I $(INCLUDE) $^ -o $@ $(LIBRARIES)
	@echo "Compiling $(EXECUTABLE_CLIENT) in $(BIN) directory"

clean:
	-rm $(BIN)/*
