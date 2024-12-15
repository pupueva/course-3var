//������
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <time.h>

// ��������� �������
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
    puts("*�������� ������ �� ��������� \"����� ���������������� � ��������������\"   *");
    puts("*����:\"���������� ������������� � ���������� �������\"                     *");
    puts("*���������:�������.�.�,������ ���-241                                     *");
    puts("*                                                                         *");
    puts("***************************************************************************");

    puts("��������� ������� ������,\n���������� ����� � ������, \n����� ������������� ��������� � ��������� �������� ����� �� ������ ������������.");

    puts("***************************************************************************");

    while (1) {
        printf("\n����:\n");
        printf("1. ���������������� �������\n");
        printf("2. �������� �������\n");
        printf("3. ���������� ������������� �������� � ������� � ������\n");
        printf("4. ����� �������� �����\n");
        printf("5. ��������� ���������\n");
        printf("�������� ��������: ");
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            if (matrix) free_matrix(matrix, rows);
            printf("������� ���������� ����� � ��������: ");
            scanf("%d %d", &rows, &cols);
            matrix = create_matrix(rows, cols);

            printf("�������� ������ �������������:\n1. ��������� �����\n2. ���� � �������\n");
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
                printf("������� �� ����������������.\n");
            }
            break;

        case 3:
            if (matrix) {
                count_negatives_in_rows_with_zero(matrix, rows, cols);
            }
            else {
                printf("������� �� ����������������.\n");
            }
            break;

        case 4:
            if (matrix) {
                find_saddle_points(matrix, rows, cols);
            }
            else {
                printf("������� �� ����������������.\n");
            }
            break;

        case 5:
            if (matrix) free_matrix(matrix, rows);
            printf("���������� ���������.\n");
            return 0;

        default:
            printf("������������ ����. ��������� �������.\n");
        }
    }
    return 0;
}

// ������� ��������� ������ ��� �������
int** create_matrix(int rows, int columns) {
    int** matrix = (int**)calloc(rows, sizeof(int*));
    if (matrix != NULL) {
        for (int i = 0; i < rows; i++) {
            matrix[i] = (int*)calloc(columns, sizeof(int));
        }
    }
    else {
        printf("������ ��������� ������!\n");
    }
    return matrix;
}

// ������� ������������ ������ �������
void free_matrix(int** matrix, int rows) {
    if (matrix) {
        for (int i = 0; i < rows; i++) {
            free(matrix[i]);
        }
        free(matrix);
    }
}

// ������� ��� ����� ������� � �������
int** input_matrix(int** matrix, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("[%d][%d]: ", i + 1, j + 1);
            scanf("%d", &matrix[i][j]);
        }
    }
    return matrix;
}

// ������� ��� ��������� ��������� �������
int** generate_matrix(int** matrix, int rows, int cols, int min, int max) {
    srand(time(NULL));
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            matrix[i][j] = rand() % (max - min + 1) + min;
        }
    }
    return matrix;
}

// ������� ��� ������ �������
void print_matrix(int** matrix, int rows, int cols) {
    printf("�������:\n");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%4d ", *(*(matrix + i) + j));
        }
        printf("\n");
    }
}

// ������� ������������� ��������� � �������, ���������� ���� �� ���� ����
void count_negatives_in_rows_with_zero(int** matrix, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        int has_zero = 0, negative_count = 0;
        for (int j = 0; j < cols; j++) {
            if (*(*(matrix + i) + j) == 0) has_zero = 1;
            if (*(*(matrix + i) + j) < 0) negative_count++;
        }
        if (has_zero) {
            printf("������ %d �������� %d ������������� ���������.\n", i + 1, negative_count);
        }
    }
}

// ����� �������� ����� � �������
void find_saddle_points(int** matrix, int rows, int cols) {
    printf("�������� �����:\n");
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
                printf("�������� ����� ������� �� ������� [%d][%d]: %d\n", i + 1, j + 1, matrix[i][j]);
                found = 1;
            }
        }
    }
    if (!found) {
        printf("�������� ����� �� �������.\n");
    }
}
