CC = clang
CFLAGS = -Wall

SRC_DIR = src

clean_download_dir: clean_download_dir.o
	$(CC) $(CFLAGS) -o clean_download_dir clean_download_dir.o

clean_download_dir.o: $(SRC_DIR)/main.c
	$(CC) $(CFLAGS) -c $(SRC_DIR)/main.c -o clean_download_dir.o

clean:
	rm -f clean_download_dir clean_download_dir.o