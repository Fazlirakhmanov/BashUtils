CC = gcc
CFLAGS = -Wall -Werror -Wextra -std=c11

# Исходные файлы
SRCS = s21_grep.c 

# Объектные файлы
OBJS = $(SRCS:.c=.o)

# Имя исполняемого файла
TARGET = s21_grep

# Интеграционный тест
TEST = bash GREP_integration_test.sh

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

test:
	$(TEST)