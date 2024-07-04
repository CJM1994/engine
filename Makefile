CXX=g++
SDL_CFLAGS=-Wall -I/usr/include/SDL2 -D_REENTRANT
SDL_LFLAGS=-lSDL2
BUILD_DIR = build
SOURCE_DIR = src
ASSETS_DIR = assets

exec: ${SOURCE_DIR}/main.cpp
	${CXX} ${SDL_CFLAGS} ${SDL_LFLAGS} ${SOURCE_DIR}/main.cpp -o ${BUILD_DIR}/main
	cp ${ASSETS_DIR}/* ${BUILD_DIR}

clean:
	rm -rf ${BUILD_DIR}/*
