CC=g++
STD=-std=c++17
CFLAGS=-Wall -Wextra
INC_PATH=-I"./libs/"
SRC=src/*.cpp \
	src/Game/*.cpp \
	src/ECS/*.cpp \
	src/AnimationManager/*.cpp \
	src/AssetManager/*.cpp \
	src/ControllerManager/*.cpp \
	src/SceneManager/*.cpp \
	src/AudioManager/*.cpp \
	src/StatsManager/*.cpp
LFLAGS=-lSDL2 -lSDL2_image -lSDL2_ttf -llua5.3 -ltinyxml2 -lSDL2_mixer

build:
	$(CC) $(STD) $(CFLAGS) $(INC_PATH) $(SRC) $(LFLAGS) -o gameEngine

run:
	./gameEngine

clean:
	rm gameEngine