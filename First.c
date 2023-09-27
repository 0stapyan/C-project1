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
        if (choice == 6) {
            int lineIndex, symbolIndex;
            printf("Choose line and symbol index: ");
            scanf("%d %d", &lineIndex, &symbolIndex);

            if (lineIndex >= 0 && lineIndex <= currentLine && symbolIndex >= 0) {
                char input[100];
                printf("Enter text to insert: ");
                scanf(" %[^\n]", input); // Read a line of text (including spaces)

                // Визначення розміру поточного рядка
                int currentLineSize = 0;
                for (int j = 0; j < textCounts[lineIndex]; j++) {
                    currentLineSize += strlen(textArrays[lineIndex][j]);
                }

                // Перевірка, чи індекс вставки не перевищує розмір поточного рядка
                if (symbolIndex <= currentLineSize) {
                    // Вставка тексту в поточний рядок за вказаними індексами
                    int currentSymbolIndex = 0;
                    for (int j = 0; j < textCounts[lineIndex]; j++) {
                        int lineLength = strlen(textArrays[lineIndex][j]);
                        if (currentSymbolIndex + lineLength >= symbolIndex) {
                            // Знайдено місце для вставки
                            int insertIndex = symbolIndex - currentSymbolIndex;
                            char *newLine = malloc(lineLength + strlen(input) + 1);
                            strncpy(newLine, textArrays[lineIndex][j], insertIndex);
                            strcpy(newLine + insertIndex, input);
                            strcpy(newLine + insertIndex + strlen(input), textArrays[lineIndex][j] + insertIndex);
                            free(textArrays[lineIndex][j]);
                            textArrays[lineIndex][j] = newLine;
                            textCounts[lineIndex]++;
                            break;
                        }
                        currentSymbolIndex += lineLength;
                    }
                    printf("Text inserted successfully\n");
                } else {
                    printf("Symbol index is out of range\n");
                }
            } else {
                printf("Invalid line index\n");
            }
        }

        if (choice == 7) {
            char search[100];
            printf("Enter text to search: ");
            scanf(" %[^\n]", search); // Read a line of text (including spaces)

            printf("Text is present in these positions:\n");

            // Пошук введеного тексту у поточному тексті
            for (int i = 0; i <= currentLine; i++) {
                for (int j = 0; j < textCounts[i]; j++) {
                    char *found = strstr(textArrays[i][j], search);
                    while (found != NULL) {
                        // Виведення позиції знайденого тексту
                        int position = found - textArrays[i][j];
                        printf("Line %d, Symbol %d\n", i, position);

                        // Пошук наступного входження
                        found = strstr(found + 1, search);
                    }
                }
            }
        }

    }

}
