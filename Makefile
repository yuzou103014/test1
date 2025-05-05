# 定义编译器
CC = gcc

# 定义编译器的标志
CFLAGS = -Wall -g

# 定义源文件和目标文件
SRC = src/lexer.c
OBJ = src/lexer.o
BIN = bin/lexer

# 定义默认目标
all: $(BIN)

# 定义如何从源文件生成目标文件
$(OBJ): $(SRC)
	$(CC) $(CFLAGS) -c $(SRC) -o $(OBJ)

# 定义如何从目标文件生成可执行文件
$(BIN): $(OBJ)
	$(CC) $(OBJ) -o $(BIN)
	@echo "Compilation successful. Executable is in $(BIN)"

# 定义如何清理生成的文件
clean:
	@echo "Cleaning up..."
	-rm -f $(OBJ)
	-rm -f $(BIN)
	@echo "Clean complete."

# 定义如何安装（将可执行文件复制到bin目录）
install: $(BIN)
	@echo "Installing..."
	-mkdir -p bin
	-cp $(BIN) bin/
	@echo "Installation complete. Executable is in $(BIN)"

# 定义默认目标
.PHONY: all clean install