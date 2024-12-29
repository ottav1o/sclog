CC = gcc
AR = ar
CFLAGS = -Wall -Wextra -pedantic

SRC = ./source
BUILD_DIR = ./bin
TARGET = $(BUILD_DIR)/libsclog.a

DEST_DIR = /usr/local/include/sclog
TARGET_DEST_DIR = /usr/local/lib
HEADERS = $(wildcard $(SRC)/*.h)
CFILES  = $(wildcard $(SRC)/*.c)

OBJS = $(CFILES:$(SRC)/%.c=$(BUILD_DIR)/%.o)

all: $(TARGET) 

build: $(TARGET)

install: $(TARGET)
	sudo mkdir -p $(DEST_DIR)
	sudo cp -v $(HEADERS) $(DEST_DIR)
	sudo mkdir -p $(TARGET_DEST_DIR)
	sudo cp -v $(TARGET) $(TARGET_DEST_DIR)

uninstall:
	sudo rm -rfv $(DEST_DIR)
	sudo rm -rfv $(TARGET_DEST_DIR)/$(notdir $(TARGET))


$(BUILD_DIR):
	mkdir -p $@

$(TARGET): $(OBJS)
	$(AR) rcs $(TARGET) $^

$(BUILD_DIR)/%.o: $(SRC)/%.c $(SRC)/%.h | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(BUILD_DIR)

.PHONY: all clean install uninstall
