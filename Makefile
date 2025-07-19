EXE_NAME := lookpath2
DEBUG := true

OBJ_DIR := ./obj
SRC_DIR := ./src

CC := cc

CPPFLAGS := \
	-I$(SRC_DIR) \
	-D_POSIX_C_SOURCE=200809L \
	-D_XOPEN_SOURCE=500 \
	-DDEBUG=1 \
	-Wno-unused-command-line-argument

LDFLAGS := #-lpthread

CCFLAGS_DIST := -O3
CCFLAGS_DEBUG := \
	-ggdb -Wno-unused-variable -Wno-unused-parameter \
	-Wno-unused-but-set-variable -Wno-unused-function

CCFLAGS := -std=c99 -Wall -Wextra -Werror
ifeq ($(DEBUG),true)
	CCFLAGS += $(CCFLAGS_DEBUG)
else
	CCFLAGS += $(CCFLAGS_DIST)
endif

SRC := $(shell find $(SRC_DIR) -name "*.c")
OBJ := $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC))

PREFIX ?= $(HOME)/.local

all: $(OBJ)
	$(CC) $(CPPFLAGS) $(LDFLAGS) -o $(EXE_NAME) $^

clean:
	rm -fr $(OBJ_DIR) $(EXE_NAME)

install: all
	install -m 0755 $(EXE_NAME) "$(PREFIX)/bin"

uninstall:
	test -f "$(PREFIX)/bin/$(EXE_NAME)" || rm "$(PREFIX)/bin/$(EXE_NAME)"

compile_commands.json:
	@bear -- make

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(SRC_DIR)/%.h
	@mkdir -p $(dir $@) || true
	$(CC) $(CCFLAGS) $(CPPFLAGS) $(LDFLAGS) -c -o $@ $<

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@) || true
	$(CC) $(CCFLAGS) $(CPPFLAGS) $(LDFLAGS) -c -o $@ $<

.PHONY: all clean install compile_commands.json
