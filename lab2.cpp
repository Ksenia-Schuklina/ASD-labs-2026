#include <iostream>
#include <iomanip>
#include <windows.h>

using namespace std;

const int MAX_SIZE = 100;

// Структура разреженной матрицы CCS
struct CCS {
    int rows;
    int cols;
    int nonZero;

    int values[MAX_SIZE];
    int row_index[MAX_SIZE];
    int col_ptr[MAX_SIZE + 1];
};

// Вывод массивов CCS
void printCCS(const CCS& matrix) {
    cout << "values:    ";
    for (int i = 0; i < matrix.nonZero; i++) {
        cout << matrix.values[i] << " ";
    }

    cout << "\nrow_index: ";
    for (int i = 0; i < matrix.nonZero; i++) {
        cout << matrix.row_index[i] << " ";
    }

    cout << "\ncol_ptr:   ";
    for (int i = 0; i <= matrix.cols; i++) {
        cout << matrix.col_ptr[i] << " ";
    }

    cout << "\n";
}

// Вывод матрицы в обычном виде
void printMatrix(const CCS& matrix) {
    for (int i = 0; i < matrix.rows; i++) {
        for (int j = 0; j < matrix.cols; j++) {
            int value = 0;

            // Поиск элемента в столбце j
            for (int k = matrix.col_ptr[j];
                k < matrix.col_ptr[j + 1]; k++) {

                if (matrix.row_index[k] == i) {
                    value = matrix.values[k];
                    break;
                }
            }

            cout << setw(4) << value;
        }
        cout << "\n";
    }
}

// Циклический сдвиг всей матрицы вправо
CCS shiftRight(const CCS& matrix) {
    CCS result{};

    result.rows = matrix.rows;
    result.cols = matrix.cols;
    result.nonZero = matrix.nonZero;

    int rows = matrix.rows;
    int cols = matrix.cols;
    int nonZero = matrix.nonZero;

    // Новые координаты ненулевых элементов
    int newRows[MAX_SIZE];
    int newCols[MAX_SIZE];

    // Вычисление новых позиций
    for (int j = 0; j < cols; j++) {
        for (int k = matrix.col_ptr[j];
            k < matrix.col_ptr[j + 1]; k++) {

            int i = matrix.row_index[k];

            // Позиция в построчном порядке
            int index = i * cols + j;

            // Циклический сдвиг на одну позицию
            int newIndex = (index + 1) % (rows * cols);

            newRows[k] = newIndex / cols;
            newCols[k] = newIndex % cols;
        }
    }

    // Обнуление указателей столбцов
    for (int j = 0; j <= cols; j++) {
        result.col_ptr[j] = 0;
    }

    // Подсчёт элементов в каждом новом столбце
    for (int k = 0; k < nonZero; k++) {
        result.col_ptr[newCols[k] + 1]++;
    }

    // Формирование указателей начала столбцов
    for (int j = 0; j < cols; j++) {
        result.col_ptr[j + 1] += result.col_ptr[j];
    }

    // Позиции записи в столбцах
    int positions[MAX_SIZE + 1];

    for (int j = 0; j <= cols; j++) {
        positions[j] = result.col_ptr[j];
    }

    // Заполнение новых массивов CCS
    for (int k = 0; k < nonZero; k++) {
        int col = newCols[k];
        int pos = positions[col]++;

        result.values[pos] = matrix.values[k];
        result.row_index[pos] = newRows[k];
    }

    return result;
}

int main() {
    // Настройка кодировки UTF-8 для Windows
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);

    CCS matrix{};

    matrix.rows = 4;
    matrix.cols = 5;
    matrix.nonZero = 8;

    // Исходная матрица:
    //
    // 1  0  2  0  0
    // 0  3  0  0  4
    // 5  0  0  6  0
    // 0  7  0  0  8

    // Ненулевые значения по столбцам
    int values[] = { 1, 5, 3, 7, 2, 6, 4, 8 };

    // Индексы строк
    int row_index[] = { 0, 2, 1, 3, 0, 2, 1, 3 };

    // Указатели начала столбцов
    int col_ptr[] = { 0, 2, 4, 5, 6, 8 };

    // Заполнение структуры CCS
    for (int i = 0; i < matrix.nonZero; i++) {
        matrix.values[i] = values[i];
        matrix.row_index[i] = row_index[i];
    }

    for (int i = 0; i <= matrix.cols; i++) {
        matrix.col_ptr[i] = col_ptr[i];
    }

    cout << "ИСХОДНАЯ МАТРИЦА:\n";
    printMatrix(matrix);

    cout << "\nИсходное CCS-представление:\n";
    printCCS(matrix);

    // Выполнение циклического сдвига
    CCS shifted = matrix;

    int shiftCount = 2; // Количество сдвигов

    for (int i = 0; i < shiftCount; i++) {
        shifted = shiftRight(shifted);
    }

    cout << "\nМАТРИЦА ПОСЛЕ ЦИКЛИЧЕСКОГО СДВИГА:\n";
    printMatrix(shifted);

    cout << "\nCCS-представление после сдвига:\n";
    printCCS(shifted);

    return 0;
}
