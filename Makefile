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

libraries: $(INCLUDE)/gameVars.h	$(LIB)/lib_network.a	$(LIB)/lib_gameConsoleUI.a	$(LIB)/lib_gameAction.a	$(LIB)/lib_gameCore.a $(LIB)/lib_utilities.a $(LIB)/lib_gameRoom.a $(LIB)/lib_gamePlayer.a $(LIB)/lib_network.a 
	@echo "All Libraries Completed"

rebuild: clean libraries bin/$(EXECUTABLE_SERVER) bin/$(EXECUTABLE_CLIENT)
	@echo "Rebuilding all components"

$(BIN)/$(EXECUTABLE_SERVER): $(SRC)/g_server.c
	@echo "Compiling $(EXECUTABLE_SERVER)"
	@$(CXX) $(CXX_FLAGS) -I $(INCLUDE) $^ -o $@ $(LIBRARIES)

$(BIN)/$(EXECUTABLE_CLIENT): $(SRC)/g_client.c
	@echo "Compiling $(EXECUTABLE_CLIENT)"
	@$(CXX) $(CXX_FLAGS) -I $(INCLUDE) $^ -o $@ $(LIBRARIES)

$(LIB)/lib_utilities.a:	c_libraries/utilities/src/utilities.c
	@echo "updating utilities library"
	@cp c_libraries/utilities/src/utilities.h $(INCLUDE)/utilities.h
	$(CXX) $(CXX_L_FLAGS) $^ -o c_libraries/utilities/bin/lib_utilities.o 
	@ar rsc $@ c_libraries/utilities/bin/lib_utilities.o
	
$(LIB)/lib_gameRoom.a: c_libraries/gameRoom/src/gameRoom.c
	@echo "updating gameRoom library"
	@cp c_libraries/gameRoom/src/gameRoom.h $(INCLUDE)/gameRoom.h
	@$(CXX) $(CXX_L_FLAGS) -I $(INCLUDE) $^ -o c_libraries/gameRoom/bin/lib_gameRoom.o 
	@ar rsc $@ c_libraries/gameRoom/bin/lib_gameRoom.o
	

$(LIB)/lib_gameCore.a: c_libraries/gameCore/src/gameCore.c
	@echo "updating Library gameCore"
	@cp c_libraries/gameCore/src/gameCore.h $(INCLUDE)/gameCore.h
	@$(CXX) $(CXX_L_FLAGS) -I $(INCLUDE) $^ -o c_libraries/gameCore/bin/lib_gameCore.o 
	@ar rsc $@ c_libraries/gameCore/bin/lib_gameCore.o
	

$(LIB)/lib_gamePlayer.a: c_libraries/gamePlayer/src/gamePlayer.c
	@echo "updating Library gamePlayer"
	@cp c_libraries/gamePlayer/src/gamePlayer.h $(INCLUDE)/gamePlayer.h
	@$(CXX) $(CXX_L_FLAGS) -I $(INCLUDE) $^ -o c_libraries/gamePlayer/bin/lib_gamePlayer.o 
	@ar rsc $@ c_libraries/gamePlayer/bin/lib_gamePlayer.o
	

$(LIB)/lib_gameAction.a: c_libraries/gameAction/src/gameAction.c
	@echo "updating Library gameAction"
	@cp c_libraries/gameAction/src/gameAction.h $(INCLUDE)/gameAction.h
	@$(CXX) $(CXX_L_FLAGS) -I $(INCLUDE) $^ -o c_libraries/gameAction/bin/lib_gameAction.o 
	@ar rsc $@ c_libraries/gameAction/bin/lib_gameAction.o
	

$(INCLUDE)/gameVars.h: c_libraries/gameVars/src/gameVars.h
	@echo "updating Library gameVars"
	@cp c_libraries/gameVars/src/gameVars.h $(INCLUDE)/gameVars.h

$(LIB)/lib_gameConsoleUI.a:	c_libraries/gameConsoleUI/src/gameConsoleUI.c
	@echo "updating Library gameConsoleUI"
	@cp c_libraries/gameConsoleUI/src/gameConsoleUI.h $(INCLUDE)/gameConsoleUI.h
	@$(CXX) $(CXX_L_FLAGS) -I $(INCLUDE) $^ -o c_libraries/gameConsoleUI/bin/lib_gameConsoleUI.o
	@ar rsc $@ c_libraries/gameConsoleUI/bin/lib_gameConsoleUI.o

$(LIB)/lib_network.a:	c_libraries/network/src/network.c
	@echo "updating Library network"
	@cp c_libraries/network/src/network.h $(INCLUDE)/network.h
	@$(CXX) $(CXX_L_FLAGS) -I $(INCLUDE) $^ -o c_libraries/network/bin/lib_network.o
	@ar rsc $@ c_libraries/network/bin/lib_network.o

runServer:	libraries ${BIN}/$(EXECUTABLE_SERVER)
	@echo "Compiling Libraries and running Server"
	./$(BIN)/$(EXECUTABLE_SERVER)

debugServer:	libraries ${BIN}/$(EXECUTABLE_SERVER)
	@echo "Compiling Libraries and running Server in debug mode"
	@gdb ./$(BIN)/$(EXECUTABLE_SERVER)

client: libraries ${BIN}/$(EXECUTABLE_CLIENT)
	@echo "Compiling Libraries and running Client"
	./$(BIN)/$(EXECUTABLE_CLIENT)
	
clean:
	-rm $(BIN)/*
	-rm $(LIB)/*
