#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#define MAX_IDENTIFIER_LENGTH 15
#define MAX_KEYWORDS 7

// 定义关键字
const char* keywords[MAX_KEYWORDS] = {"if", "else", "while", "read", "put", "write", "get"};

// 判断是否为关键字
int is_keyword(const char* str) {
    for (int i = 0; i < MAX_KEYWORDS; i++) {
        if (strcmp(str, keywords[i]) == 0) {
            return 1;
        }
    }
    return 0;
}

// 判断是否为运算符或分隔符
int is_operator_or_delimiter(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/' || c == '%' ||
           c == '<' || c == '>' || c == '=' || c == '!' ||
           c == '(' || c == ')' || c == '{' || c == '}' || c == ';';
}

// 处理整数常量
void process_integer(const char* str) {
    printf("[literal:0x%x]\n", (unsigned int)strtol(str, NULL, 10));
}

// 处理字符常量
void process_character(char c) {
    printf("[literal:0x%x]\n", (unsigned int)c);
}

// 处理运算符或分隔符
void process_operator_or_delimiter(char c) {
    printf("[op:%c]\n", c);
}

// 处理关系运算符
void process_relational_operator(const char* str) {
    printf("[op:%s]\n", str);
}

// 处理标识符或关键字
void process_identifier_or_keyword(const char* str) {
    if (is_keyword(str)) {
        printf("[keyword:%s]\n", str);
    } else {
        printf("[id:%s]\n", str);
    }
}

// 主函数中处理逻辑
int main() {
    char buffer[MAX_IDENTIFIER_LENGTH + 1];
    char c, last_char = 0;
    int index = 0;

    while ((c = getchar()) != EOF) {
        // 处理空白字符和换行符
        if (isspace(c)) {
            if (index > 0) {
                buffer[index] = '\0';
                process_identifier_or_keyword(buffer);
                index = 0;
            }
            continue;
        }

        // 处理关系运算符
        if (c == '>' || c == '<' || c == '=' || c == '!') {
            if (index > 0) {
                buffer[index] = '\0';
                process_identifier_or_keyword(buffer);
                index = 0;
            }
            char next_char = getchar();
            if ((c == '>' && next_char == '=') ||
                (c == '<' && next_char == '=') ||
                (c == '=' && next_char == '=') ||
                (c == '!' && next_char == '=')) {
                char rel_op[3] = {c, next_char, '\0'};
                process_relational_operator(rel_op);
            } else {
                ungetc(next_char, stdin);
                char single_op[2] = {c, '\0'};
                process_relational_operator(single_op);
            }
            continue;
        }

        // 处理其他运算符或分隔符
        if (is_operator_or_delimiter(c)) {
            if (index > 0) {
                buffer[index] = '\0';
                process_identifier_or_keyword(buffer);
                index = 0;
            }
            process_operator_or_delimiter(c);
            continue;
        }

        // 处理整数常量
        if (isdigit(c)) {
            if (index > 0 && !isdigit(last_char)) {
                buffer[index] = '\0';
                process_identifier_or_keyword(buffer);
                index = 0;
            }
            buffer[index++] = c;
            if (!isdigit(c = getchar())) {
                ungetc(c, stdin);
                buffer[index] = '\0';
                process_integer(buffer);
                index = 0;
            }
            continue;
        }

        // 处理字符常量
        if (c == '\'') {
            if (index > 0) {
                buffer[index] = '\0';
                process_identifier_or_keyword(buffer);
                index = 0;
            }
            char char_const = getchar();
            if (char_const == '\\') {
                char_const = getchar(); // 处理转义字符
            }
            process_character(char_const);
            getchar(); // 跳过结尾的单引号
            continue;
        }

        // 处理标识符
        if (islower(c)) {
            buffer[index++] = c;
        } else {
            if (index > 0) {
                buffer[index] = '\0';
                process_identifier_or_keyword(buffer);
                index = 0;
            }
        }

        last_char = c;
    }

    // 处理最后一个词元
    if (index > 0) {
        buffer[index] = '\0';
        process_identifier_or_keyword(buffer);
    }

    return 0;
}