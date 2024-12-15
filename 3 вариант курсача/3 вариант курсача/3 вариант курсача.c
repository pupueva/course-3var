//курсач
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <time.h>

// Прототипы функций
int** create_matrix(int rows, int columns);
void free_matrix(int** matrix, int rows);
int** input_matrix(int** matrix, int rows, int cols);
int** generate_matrix(int** matrix, int rows, int cols, int min, int max);
void print_matrix(int** matrix, int rows, int cols);
void count_negatives_in_rows_with_zero(int** matrix, int rows, int cols);
void find_saddle_points(int** matrix, int rows, int cols);

int main() {
    setlocale(LC_CTYPE, "RUS");
    int rows, cols, choice, randomize;
    int** matrix = NULL;

    puts("***************************************************************************");
    puts("*                                                                         *");
    puts("*Курсовой проект по дисцплине \"осовы программирования и алгоритмизации\"   *");
    puts("*Тема:\"Реализация динамического и многомерно массива\"                     *");
    puts("*Выполнила:Пуляева.Л.Ю,группа бИД-241                                     *");
    puts("*                                                                         *");
    puts("***************************************************************************");

    puts("Программа выводит массив,\nколичество строк с нулями, \nсумму отрицательных элементов и найденные седловые точки по выбору пользователя.");

    puts("***************************************************************************");

    while (1) {
        printf("\nМеню:\n");
        printf("1. Инициализировать матрицу\n");
        printf("2. Показать матрицу\n");
        printf("3. Подсчитать отрицательные элементы в строках с нулями\n");
        printf("4. Найти седловые точки\n");
        printf("5. Завершить программу\n");
        printf("Выберите действие: ");
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            if (matrix) free_matrix(matrix, rows);
            printf("Введите количество строк и столбцов: ");
            scanf("%d %d", &rows, &cols);
            matrix = create_matrix(rows, cols);

            printf("Выберите способ инициализации:\n1. Случайные числа\n2. Ввод с консоли\n");
            scanf("%d", &randomize);

            if (randomize == 1) {
                generate_matrix(matrix, rows, cols, -10, 10);
            }
            else {
                input_matrix(matrix, rows, cols);
            }
            break;

        case 2:
            if (matrix) {
                print_matrix(matrix, rows, cols);
            }
            else {
                printf("Матрица не инициализирована.\n");
            }
            break;

        case 3:
            if (matrix) {
                count_negatives_in_rows_with_zero(matrix, rows, cols);
            }
            else {
                printf("Матрица не инициализирована.\n");
            }
            break;

        case 4:
            if (matrix) {
                find_saddle_points(matrix, rows, cols);
            }
            else {
                printf("Матрица не инициализирована.\n");
            }
            break;

        case 5:
            if (matrix) free_matrix(matrix, rows);
            printf("Завершение программы.\n");
            return 0;

        default:
            printf("Некорректный ввод. Повторите попытку.\n");
        }
    }
    return 0;
}

// Функция выделения памяти под матрицу
int** create_matrix(int rows, int columns) {
    int** matrix = (int**)calloc(rows, sizeof(int*));
    if (matrix != NULL) {
        for (int i = 0; i < rows; i++) {
            matrix[i] = (int*)calloc(columns, sizeof(int));
        }
    }
    else {
        printf("Ошибка выделения памяти!\n");
    }
    return matrix;
}

// Функция освобождения памяти матрицы
void free_matrix(int** matrix, int rows) {
    if (matrix) {
        for (int i = 0; i < rows; i++) {
            free(matrix[i]);
        }
        free(matrix);
    }
}

// Функция для ввода матрицы с консоли
int** input_matrix(int** matrix, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("[%d][%d]: ", i + 1, j + 1);
            scanf("%d", &matrix[i][j]);
        }
    }
    return matrix;
}

// Функция для генерации случайной матрицы
int** generate_matrix(int** matrix, int rows, int cols, int min, int max) {
    srand(time(NULL));
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            matrix[i][j] = rand() % (max - min + 1) + min;
        }
    }
    return matrix;
}

// Функция для печати матрицы
void print_matrix(int** matrix, int rows, int cols) {
    printf("Матрица:\n");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%4d ", *(*(matrix + i) + j));
        }
        printf("\n");
    }
}

// Подсчет отрицательных элементов в строках, содержащих хотя бы один ноль
void count_negatives_in_rows_with_zero(int** matrix, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        int has_zero = 0, negative_count = 0;
        for (int j = 0; j < cols; j++) {
            if (*(*(matrix + i) + j) == 0) has_zero = 1;
            if (*(*(matrix + i) + j) < 0) negative_count++;
        }
        if (has_zero) {
            printf("Строка %d содержит %d отрицательных элементов.\n", i + 1, negative_count);
        }
    }
}

// Поиск седловых точек в матрице
void find_saddle_points(int** matrix, int rows, int cols) {
    printf("Седловые точки:\n");
    int found = 0;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            int is_min_in_row = 1, is_min_in_col = 1;
            for (int k = 0; k < cols; k++) {
                if (matrix[i][k] < matrix[i][j]) {
                    is_min_in_row = 0;
                    break;
                }
            }
            for (int k = 0; k < rows; k++) {
                if (matrix[k][j] < matrix[i][j]) {
                    is_min_in_col = 0;
                    break;
                }
            }
            if (is_min_in_row && is_min_in_col) {
                printf("Седловая точка найдена на позиции [%d][%d]: %d\n", i + 1, j + 1, matrix[i][j]);
                found = 1;
            }
        }
    }
    if (!found) {
        printf("Седловых точек не найдено.\n");
    }
}
