#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char ***textArrays = NULL; // Масив масивів рядків тексту
    int *textCounts = NULL;    // Кількість рядків в кожному масиві
    int currentLine = 0;       // Поточний рядок для вводу тексту

    printf("Choose the command:\n");
    printf("1. Enter text to append\n");
    printf("2. Start a new line\n");
    printf("3. Save text to a file\n");
    printf("4. Load text from a file\n");
    printf("5. Print current text\n");
    printf("6. Insert text by line and symbol index\n");
    printf("7. Search for text\n");
    printf("8. Clear the console\n");

    while (1) {
        int choice;
        printf("Enter your choice: ");
        scanf("%d", &choice);

        if (choice == 1) {
            char input[100];
            printf("Enter text to append: ");
            scanf(" %[^\n]", input); // Read a line of text (including spaces)

            // Allocate memory for the new text and add it to the current line's array
            textArrays = realloc(textArrays, (currentLine + 1) * sizeof(char **));
            textCounts = realloc(textCounts, (currentLine + 1) * sizeof(int));

            textCounts[currentLine]++; // Збільшуємо кількість рядків у поточному масиві

            textArrays[currentLine] = realloc(textArrays[currentLine], textCounts[currentLine] * sizeof(char *));
            textArrays[currentLine][textCounts[currentLine] - 1] = malloc(strlen(input) + 1); // +1 for null terminator

            // Copy the entered text to the allocated memory
            strcpy(textArrays[currentLine][textCounts[currentLine] - 1], input);

            printf("Text appended: %s\n", textArrays[currentLine][textCounts[currentLine] - 1]);
        }

        if (choice == 2) {
            currentLine++; // Переходимо на наступний рядок
            printf("New line is started\n");
        }

        if (choice == 3) {
            char fileName[100];
            printf("Enter the file name for saving: ");
            scanf(" %[^\n]", fileName); // Введення імені файлу

            // Відкриття файлу для запису
            FILE *file = fopen(fileName, "w");
            if (file != NULL) {
                // Запис тексту в файл
                for (int i = 0; i <= currentLine; i++) {
                    for (int j = 0; j < textCounts[i]; j++) {
                        fprintf(file, "%s", textArrays[i][j]);
                    }
                    fprintf(file, "\n");
                }
                fclose(file);
                printf("Text has been saved successfully\n");
            }
        }

        if (choice == 5) {
            // Print current text for each line
            printf("Current Text:\n");
            for (int i = 0; i <= currentLine; i++) {
                for (int j = 0; j < textCounts[i]; j++) {
                    printf("%s", textArrays[i][j]);
                }
                printf("\n");
            }
        }
    }

}
