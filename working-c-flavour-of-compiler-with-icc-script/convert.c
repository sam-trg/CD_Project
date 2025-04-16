#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE 1024
#define MAX_STACK 1024

typedef struct {
    int data[MAX_STACK];
    int top;
} Stack;

void push(Stack *s, int value) {
    if (s->top < MAX_STACK) s->data[s->top++] = value;
}

int pop(Stack *s) {
    return s->top > 0 ? s->data[--s->top] : 0;
}

int peek(Stack *s) {
    return s->top > 0 ? s->data[s->top - 1] : 0;
}

int ends_with_colon(const char *line) {
    int len = strlen(line);
    while (len > 0 && (line[len - 1] == '\n' || line[len - 1] == '\r' || line[len - 1] == ' '))
        len--;
    return len > 0 && line[len - 1] == ':';
}

int leading_spaces(const char *line) {
    int count = 0;
    while (*line == ' ') {
        count++;
        line++;
    }
    return count;
}

int is_blank_or_comment(const char *line) {
    while (*line == ' ') line++;
    return *line == '\0' || strncmp(line, "//", 2) == 0;
}

void rstrip(char *line) {
    int len = strlen(line);
    while (len > 0 && (line[len - 1] == '\n' || line[len - 1] == '\r'))
        len--;
    line[len] = '\0';
}

int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <input.ic>\n", argv[0]);
        return 1;
    }

    FILE *in = fopen(argv[1], "r");
    if (!in) {
        perror("File open failed");
        return 1;
    }

    char output_file[256];
    strncpy(output_file, argv[1], sizeof(output_file));
    char *dot = strrchr(output_file, '.');
    if (dot) strcpy(dot, ".c");
    else strcat(output_file, ".c");

    FILE *out = fopen(output_file, "w");
    if (!out) {
        perror("File create failed");
        fclose(in);
        return 1;
    }

    char line[MAX_LINE];
    Stack indent = {.top = 0};
    push(&indent, 0);

    while (fgets(line, sizeof(line), in)) {
        rstrip(line);
        if (is_blank_or_comment(line)) {
            fprintf(out, "%s\n", line);
            continue;
        }

        int curr_indent = leading_spaces(line);
        int prev_indent = peek(&indent);

        while (curr_indent < prev_indent) {
            fprintf(out, "%*s}\n", prev_indent, "");
            pop(&indent);
            prev_indent = peek(&indent);
        }

        if (ends_with_colon(line)) {
            line[strlen(line) - 1] = '\0';
            fprintf(out, "%*s%s {\n", curr_indent, "", line + curr_indent);
            push(&indent, curr_indent + 4);
        } else {
            fprintf(out, "%s\n", line);
        }
    }

    while (indent.top > 1) {
        fprintf(out, "%*s}\n", peek(&indent), "");
        pop(&indent);
    }

    fclose(in);
    fclose(out);
    return 0;
}
