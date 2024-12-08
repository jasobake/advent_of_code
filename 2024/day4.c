#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char** read_file_2d(const char* filename, int num_lines, int line_length) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        fprintf(stderr, "Error opening file '%s'\n", filename);
        return NULL;
    }

    // Allocate memory for the 2D array
    char** lines = (char**)malloc(num_lines * sizeof(char*));
    if (lines == NULL) {
        fprintf(stderr, "Memory allocation failed for lines array\n");
        fclose(file);
        return NULL;
    }

    // Allocate memory for each line
    for (int i = 0; i < num_lines; i++) {
        lines[i] = (char*)malloc(line_length + 1);  // +1 for null terminator
        if (lines[i] == NULL) {
            fprintf(stderr, "Memory allocation failed for line %d\n", i);
            for (int j = 0; j < i; j++) {
                free(lines[j]);
            }
            free(lines);
            fclose(file);
            return NULL;
        }
    }

    // Read the file content
    char buffer[line_length + 2];  // +1 for newline, +1 for null terminator
    for (int i = 0; i < num_lines; i++) {
        if (fgets(buffer, sizeof(buffer), file) == NULL) {
            fprintf(stderr, "Error reading line %d\n", i);
            for (int j = 0; j <= i; j++) {
                free(lines[j]);
            }
            free(lines);
            fclose(file);
            return NULL;
        }
        // Remove newline character if present
        size_t len = strlen(buffer);
        if (len > 0 && buffer[len-1] == '\n') {
            buffer[len-1] = '\0';
            len--;
        }
        if (len > line_length) {
            fprintf(stderr, "Line %d is longer than specified length (%zu > %d)\n", i, len, line_length);
            for (int j = 0; j <= i; j++) {
                free(lines[j]);
            }
            free(lines);
            fclose(file);
            return NULL;
        }
        strncpy(lines[i], buffer, line_length);
        lines[i][line_length] = '\0';  // Ensure null-termination
    }

    fclose(file);
    return lines;
}

int main() {

    char **d = read_file_2d("data/advent_day4.txt", 140, 140);

    size_t result = 0;

for (size_t i = 0; i < 140; ++i) {
    for(size_t n = 0; n < 140; ++n) {
        if (
            // Horizontal "XMAS"
            (n <= 136 && d[i][n] == 'X' && d[i][n+1] == 'M' && d[i][n+2] == 'A' && d[i][n+3] == 'S') ||
            // Vertical "XMAS"
            (i <= 136 && d[i][n] == 'X' && d[i+1][n] == 'M' && d[i+2][n] == 'A' && d[i+3][n] == 'S') ||
            // Diagonal "XMAS"
            (n <= 136 && i <= 136 && d[i][n] == 'X' && d[i+1][n+1] == 'M' && d[i+2][n+2] == 'A' && d[i+3][n+3] == 'S') ||
            // Diagonal "XMAS"
            (n <= 136 && i <= 136 && d[i+3][n] == 'X' && d[i+2][n+1] == 'M' && d[i+1][n+2] == 'A' && d[i][n+3] == 'S') ||
            
            // Horizontal "SAMX"
            (n <= 136 && d[i][n] == 'S' && d[i][n+1] == 'A' && d[i][n+2] == 'M' && d[i][n+3] == 'X') ||
            // Vertical "SAMX"
            (i <= 136 && d[i][n] == 'S' && d[i+1][n] == 'A' && d[i+2][n] == 'M' && d[i+3][n] == 'X') ||
            // Diagonal "SAMX"
            (n <= 136 && i <= 136 && d[i][n] == 'S' && d[i+1][n+1] == 'A' && d[i+2][n+2] == 'M' && d[i+3][n+3] == 'X') ||
            // Diagonal "XMAS"
             (n <= 136 && i <= 136 && d[i+3][n] == 'S' && d[i+2][n+1] == 'A' && d[i+1][n+2] == 'M' && d[i][n+3] == 'X') 
           ) {
            ++result;
        }
    }
}

    printf("%zu", result);

    return 0;
}