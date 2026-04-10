CC = gcc-15
CFLAGS = -Wall -Wextra
TARGET = pf_int
SRCS = main.c stack.c lexer.c parser.c evaluate.c
BUILD_DIR = build
OBJS = $(addprefix $(BUILD_DIR)/,$(SRCS:.c=.o))

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

$(BUILD_DIR)/%.o: %.c
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(BUILD_DIR) $(TARGET)

.PHONY: clean