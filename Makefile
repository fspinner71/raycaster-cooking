BUILD_DIR = ./objs
SRC_DIR = ./src
LIBS_DIR = ./libs
INCLUDE_DIR = ./include

CC = clang++
PROG = game.exe

SRCS = main.cpp game.cpp assetmanager.cpp math.cpp map.cpp player.cpp raycast.cpp camera.cpp strip.cpp npc.cpp scene.cpp interaction.cpp canvas.cpp frame.cpp text.cpp sprite.cpp stove.cpp table.cpp fridge.cpp
LIBS = -lSDL3 -lSDL3_image -lSDL3_ttf -lSDL3_mixer
OBJS = $(SRCS:%.cpp=$(BUILD_DIR)/%.o)
DEPS = $(SRCS:%.cpp=$(BUILD_DIR)/%.d)

#-lSDK3_mixer
open:
	@echo "Running $(PROG)"
	@./$(PROG)

game: $(OBJS)
	@echo "Producing $(PROG)"
	@$(CC) -o $(PROG) $(OBJS) -L$(LIBS_DIR) $(LIBS)

run: game
	@echo "Running $(PROG)"
	@./$(PROG)

-include $(DEPS)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp Makefile
	@echo "Compiling $(filter-out %.h,$^)"
	@$(CC) -MMD -MP -c $(filter-out %.h,$^) -o $@ -I$(INCLUDE_DIR)

clean:
	@rm $(BUILD_DIR)/*.o
	@rm $(BUILD_DIR)/*.d
