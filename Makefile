CXX       := gcc
CXX_FLAGS := -std=gnu17 -ggdb  
CXX_P_FLAGS := -std=gnu17 -ggdb -D_POSIX_C_SOURCE=200112L 
CXX_L_FLAGS := -std=gnu17 -ggdb -c 

BIN     := bin
SRC     := src
INCLUDE := include
LIB     := lib

C_LIBRARIES := c_libraries

LIBRARIES   := lib/*.a
EXECUTABLE_SERVER  := gameServer
EXECUTABLE_CLIENT  := gameClient
LIBRARY_GAMEROOM   := gameRoom

all: $(INCLUDE)/gameVars.h	$(LIB)/lib_gameCore.a $(LIB)/lib_utilities.a $(LIB)/lib_gameRoom.a $(LIB)/lib_gamePlayer.a $(BIN)/$(EXECUTABLE_SERVER) $(BIN)/$(EXECUTABLE_CLIENT)
	@echo "All Completed"

rebuild: clean all
	@echo "Rebuilding all components"

run: clean all
	clear
	./$(BIN)/$(EXECUTABLE_SERVER) &
	./$(BIN)/$(EXECUTABLE_CLIENT) 

$(BIN)/$(EXECUTABLE_SERVER): $(SRC)/g_server.c
	@echo "Compiling $(EXECUTABLE_SERVER)"
	$(CXX) $(CXX_FLAGS) -I $(INCLUDE) $^ -o $@ $(LIBRARIES)

$(BIN)/$(EXECUTABLE_CLIENT): $(SRC)/g_client.c
	$(CXX) $(CXX_FLAGS) -I $(INCLUDE) $^ -o $@ $(LIBRARIES)

$(LIB)/lib_utilities.a:	c_libraries/utilities/src/utilities.c
	@echo "Library utilities"
	$(CXX) $(CXX_L_FLAGS) -I $(INCLUDE) $^ -o c_libraries/utilities/bin/lib_utilities.o 
	ar rsc $@ c_libraries/utilities/bin/lib_utilities.o
	cp c_libraries/utilities/src/utilities.h $(INCLUDE)/utilities.h

$(LIB)/lib_gameRoom.a: c_libraries/gameRoom/src/gameRoom.c
	@echo "Library gameRoom"
	$(CXX) $(CXX_L_FLAGS) -I $(INCLUDE) $^ -o c_libraries/gameRoom/bin/lib_gameRoom.o 
	ar rsc $@ c_libraries/gameRoom/bin/lib_gameRoom.o
	cp c_libraries/gameRoom/src/gameRoom.h $(INCLUDE)/gameRoom.h

$(LIB)/lib_gameCore.a: c_libraries/gameCore/src/gameCore.c
	@echo "Library gameCore"
	$(CXX) $(CXX_L_FLAGS) -I $(INCLUDE) $^ -o c_libraries/gameCore/bin/lib_gameCore.o 
	ar rsc $@ c_libraries/gameCore/bin/lib_gameCore.o
	cp c_libraries/gameCore/src/gameCore.h $(INCLUDE)/gameCore.h

$(LIB)/lib_gamePlayer.a: c_libraries/gamePlayer/src/gamePlayer.c
	@echo "Library gamePlayer"
	$(CXX) $(CXX_L_FLAGS) -I $(INCLUDE) $^ -o c_libraries/gamePlayer/bin/lib_gamePlayer.o 
	ar rsc $@ c_libraries/gamePlayer/bin/lib_gamePlayer.o
	cp c_libraries/gamePlayer/src/gamePlayer.h $(INCLUDE)/gamePlayer.h

$(INCLUDE)/gameVars.h: c_libraries/gameVars/src/gameVars.h
	@echo "Library gameVars"
	cp c_libraries/gameVars/src/gameVars.h $(INCLUDE)/gameVars.h

runServer:	all
	@echo "Compiling Libraries and running Server"
	./$(BIN)/$(EXECUTABLE_SERVER)

debugServer:	all
	@echo "Compiling Libraries and running Server in debug mode"
	gdb ./$(BIN)/$(EXECUTABLE_SERVER)

clean:
	-rm $(BIN)/*
	-rm $(LIB)/*
