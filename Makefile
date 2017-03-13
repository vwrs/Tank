OPT    = -Ofast
CC     = gcc
FW = -framework GLUT -framework OpenGL
MAC = -mmacosx-version-min=10.8
CFLAGS = $(FW) $(DBG) $(OPT) $(MAC)

all: tank

tank: tank.c draw.c init.c keyboardFunc.c timerFunc.c helpers.c
	$(CC) $(CFLAGS) tank.c draw.c init.c keyboardFunc.c timerFunc.c helpers.c

clean:
	/bin/rm -f a.out
