
all:
	$(CC)  src/*.c $(shell pkg-config --cflags --libs gtk+-3.0) -o shutdown-scheduler
