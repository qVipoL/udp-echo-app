CC := gcc
BUILD_DIR := bin

all: build client server

build:
	@mkdir -p $(BUILD_DIR)

run:
	make all
	gnome-terminal --title="server" -- "./$(BUILD_DIR)/server"
	gnome-terminal --title="client" -- "./$(BUILD_DIR)/client" 

client: client.c udp.h
	$(CC) -o $(BUILD_DIR)/client client.c

server: server.c udp.h
	$(CC) -o $(BUILD_DIR)/server server.c

clean:
	rm $(BUILD_DIR)/*