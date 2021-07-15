CC := gcc
BUILD_DIR := bin
SOURCE_DIR := src
INCLUDE_DIR := include

all: build client server

build:
	@mkdir -p $(BUILD_DIR)

client: $(SOURCE_DIR)/client.c $(SOURCE_DIR)/udp.c
	$(CC) $(SOURCE_DIR)/client.c $(SOURCE_DIR)/udp.c -o $(BUILD_DIR)/client

server: $(SOURCE_DIR)/server.c $(SOURCE_DIR)/udp.c
	$(CC) $(SOURCE_DIR)/server.c $(SOURCE_DIR)/udp.c -o $(BUILD_DIR)/server

clean:
	rm $(BUILD_DIR)/*