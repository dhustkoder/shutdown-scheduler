
all:
	$(CC)  -std=c11 src/*.c $(shell pkg-config --cflags --libs gtk+-3.0) -o shutdown-scheduler
