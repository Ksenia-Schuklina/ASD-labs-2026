#include <iostream>
#include <windows.h>
using namespace std;

// Структура элемента очереди
struct Element {
    int value;
    int priority;
};

// Класс очередь с приоритетом
class PriorityQueue {
private:
    static const int MAX_SIZE = 100;

    Element data[MAX_SIZE];
    int size;

public:
    // Конструктор
    PriorityQueue() {
        size = 0;
    }

    // Добавление
    void push(int value, int priority) {
        if (size == MAX_SIZE) {
            cout << "Очередь переполнена!\n";
            return;
        }

        data[size].value = value;
        data[size].priority = priority;
        size++;
    }

    // Удаление элемента с максимальным приоритетом
    void pop() {
        if (size == 0) {
            cout << "Очередь пуста!\n";
            return;
        }

        // Поиск элемента с максимальным приоритетом
        int maxIndex = 0;

        for (int i = 1; i < size; i++) {
            if (data[i].priority > data[maxIndex].priority) {
                maxIndex = i;
            }
        }

        // Вывод удаляемого элемента
        cout << "Удалён элемент: "
            << data[maxIndex].value
            << " (приоритет: "
            << data[maxIndex].priority
            << ")\n";

        // Сдвиг элементов массива влево
        for (int i = maxIndex; i < size - 1; i++) {
            data[i] = data[i + 1];
        }

        // Уменьшение количества элементов
        size--;
    }

    // Проверка (не является ли очередь пустой)
    bool isEmpty() const {
        return size == 0;
    }

    // Вывод содержимого очереди
    void print() const {
        if (isEmpty()) {
            cout << "Очередь пуста!\n";
            return;
        }

        cout << "Значение\tПриоритет\n";
        cout << "-------------------------\n";

        for (int i = 0; i < size; i++) {
            cout << data[i].value << "\t\t"
                << data[i].priority << "\n";
        }
    }
};

int main() {
    // РУССКИЙ ЯЗЫК напишись пожалуйста
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);

    // Создание очереди
    PriorityQueue queue;

    // Добавление элементов (значение, приоритет)
    queue.push(10, 2);
    queue.push(20, 5);
    queue.push(30, 1);
    queue.push(40, 4);
    queue.push(50, 3);
    queue.push(60, 5);

    // Вывод исходной очереди
    cout << "Исходная очередь:\n";
    queue.print();

    cout << "\nУдаление элемента с высшим приоритетом:\n";
    queue.pop();

    cout << "\nОчередь после удаления:\n";
    queue.print();

    // Последовательное удаление оставшихся элементов
    cout << "\nПоследовательное удаление элементов:\n";

    while (!queue.isEmpty()) {
        queue.pop();
    }

    // Проверка пустой очереди
    cout << "\nПроверка состояния очереди:\n";
    queue.print();

    // Попытка удаления из пустой очереди
    cout << "\nПопытка удаления из пустой очереди:\n";
    queue.pop();

    return 0;
}
