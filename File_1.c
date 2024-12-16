#include <stdio.h>
#include <string.h>

#define MAX_DATA_LENGTH 100 
#define MAX_LINE_LENGTH 200
#define MAX_OUTPUT_LENGTH 1000  

void append_data(const char *filename, const char *data) {
    FILE *file = fopen(filename, "a"); 
    fprintf(file, "%s\n", data); 
    fclose(file); 
}

void search_data(const char *filename, const char *name, char *output, int *case_number) {
    FILE *file = fopen(filename, "r");
    char line[MAX_LINE_LENGTH];
    int found = 0;

    while (fgets(line, sizeof(line), file)) {
        line[strcspn(line, "\n")] = 0;

        char *token = strtok(line, "#");
        if (token && strcmp(token, name) == 0) {
            token = strtok(NULL, "#");
            if (token) {
                sprintf(output + strlen(output), "Case #%d: %s\n", (*case_number)++, token);
                found = 1;
                break;
            }
        }
    }

    if (!found) {
        sprintf(output + strlen(output), "Case #%d: N/A\n", (*case_number)++);
    }

    fclose(file);
}

int main() {
    const char *filename = "testdata.in"; 
    int input_count, search_count;

    scanf("%d", &input_count);
    getchar();  

    char data[MAX_DATA_LENGTH];

    for (int i = 0; i < input_count; i++) {
        fgets(data, sizeof(data), stdin);
        data[strcspn(data, "\n")] = 0; 
        append_data(filename, data);
    }

    scanf("%d", &search_count);
    getchar();  

    char search[MAX_DATA_LENGTH];
    char output[MAX_OUTPUT_LENGTH] = "";  

    int case_number = 1; 

    for (int i = 0; i < search_count; i++) {
        fgets(search, sizeof(search), stdin);
        search[strcspn(search, "\n")] = 0; 
        search_data(filename, search, output, &case_number);
    }

    printf("%s", output);

    return 0;
}
