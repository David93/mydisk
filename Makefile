
all:	mydisk.c
	@gcc -Wall mydisk.c `pkg-config fuse --cflags --libs` -o mydisk