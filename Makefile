CC = clang
CFLAGS = -Wall -I$(SRC_DIR)

SRC_DIR = src

OBJS = main.o config.o organizer.o

clean_download_dir: $(OBJS)
	$(CC) $(CFLAGS) -o clean_download_dir $(OBJS)

main.o: $(SRC_DIR)/main.c
	$(CC) $(CFLAGS) -c $(SRC_DIR)/main.c -o main.o

config.o: $(SRC_DIR)/config.c
	$(CC) $(CFLAGS) -c $(SRC_DIR)/config.c -o config.o

organizer.o: $(SRC_DIR)/organizer.c
	$(CC) $(CFLAGS) -c $(SRC_DIR)/organizer.c -o organizer.o

clean:
	rm -f clean_download_dir $(OBJS)