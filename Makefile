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

all: $(INCLUDE)/gameVars.h	$(LIB)/lib_gameAction.a	$(LIB)/lib_gameCore.a $(LIB)/lib_utilities.a $(LIB)/lib_gameRoom.a $(LIB)/lib_gamePlayer.a $(BIN)/$(EXECUTABLE_SERVER)
	@echo "All Completed"

rebuild: clean all
	@echo "Rebuilding all components"

run: clean all
	clear
	./$(BIN)/$(EXECUTABLE_SERVER) &
	./$(BIN)/$(EXECUTABLE_CLIENT) 

$(BIN)/$(EXECUTABLE_SERVER): $(SRC)/g_server.c
	@echo "Compiling $(EXECUTABLE_SERVER)"
	@$(CXX) $(CXX_FLAGS) -I $(INCLUDE) $^ -o $@ $(LIBRARIES)

$(BIN)/$(EXECUTABLE_CLIENT): $(SRC)/g_client.c
	@echo "Compiling $(EXECUTABLE_CLIENT)"
	@$(CXX) $(CXX_FLAGS) -I $(INCLUDE) $^ -o $@ $(LIBRARIES)

$(LIB)/lib_utilities.a:	c_libraries/utilities/src/utilities.c
	@echo "Building Library utilities"
	@rm $(INCLUDE)/utilities.h
	@cp c_libraries/utilities/src/utilities.h $(INCLUDE)/utilities.h
	$(CXX) $(CXX_L_FLAGS) $^ -o c_libraries/utilities/bin/lib_utilities.o 
	@ar rsc $@ c_libraries/utilities/bin/lib_utilities.o
	
$(LIB)/lib_gameRoom.a: c_libraries/gameRoom/src/gameRoom.c
	@echo "Building Library lib_gameRoom.a"
	@$(CXX) $(CXX_L_FLAGS) -I $(INCLUDE) $^ -o c_libraries/gameRoom/bin/lib_gameRoom.o 
	@ar rsc $@ c_libraries/gameRoom/bin/lib_gameRoom.o
	@cp c_libraries/gameRoom/src/gameRoom.h $(INCLUDE)/gameRoom.h

$(LIB)/lib_gameCore.a: c_libraries/gameCore/src/gameCore.c
	@echo "Building Library gameCore"
	@$(CXX) $(CXX_L_FLAGS) -I $(INCLUDE) $^ -o c_libraries/gameCore/bin/lib_gameCore.o 
	@ar rsc $@ c_libraries/gameCore/bin/lib_gameCore.o
	@cp c_libraries/gameCore/src/gameCore.h $(INCLUDE)/gameCore.h

$(LIB)/lib_gamePlayer.a: c_libraries/gamePlayer/src/gamePlayer.c
	@echo "Building Library gamePlayer"
	@$(CXX) $(CXX_L_FLAGS) -I $(INCLUDE) $^ -o c_libraries/gamePlayer/bin/lib_gamePlayer.o 
	@ar rsc $@ c_libraries/gamePlayer/bin/lib_gamePlayer.o
	@cp c_libraries/gamePlayer/src/gamePlayer.h $(INCLUDE)/gamePlayer.h

$(LIB)/lib_gameAction.a: c_libraries/gameAction/src/gameAction.c
	@echo "Building Library gameAction"
	@$(CXX) $(CXX_L_FLAGS) -I $(INCLUDE) $^ -o c_libraries/gameAction/bin/lib_gameAction.o 
	@ar rsc $@ c_libraries/gameAction/bin/lib_gameAction.o
	@cp c_libraries/gameAction/src/gameAction.h $(INCLUDE)/gameAction.h

$(INCLUDE)/gameVars.h: c_libraries/gameVars/src/gameVars.h
	@echo "Building Library gameVars"
	@cp c_libraries/gameVars/src/gameVars.h $(INCLUDE)/gameVars.h

runServer:	all
	@echo "Compiling Libraries and running Server"
	./$(BIN)/$(EXECUTABLE_SERVER)

debugServer:	all
	@echo "Compiling Libraries and running Server in debug mode"
	@gdb ./$(BIN)/$(EXECUTABLE_SERVER)

clean:
	-rm $(BIN)/*
	-rm $(LIB)/*
