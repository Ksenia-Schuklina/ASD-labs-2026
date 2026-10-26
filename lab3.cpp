#include <iostream>
#include <Windows.h>
using namespace std;

// Структура узла дерева
struct Node {
    int data;
    Node* left;
    Node* right;

    Node(int value) {
        data = value;
        left = nullptr;
        right = nullptr;
    }
};

// Добавление элемента в дерево
Node* insert(Node* root, int value) {
    if (root == nullptr)
        return new Node(value);

    if (value < root->data)
        root->left = insert(root->left, value);
    else
        root->right = insert(root->right, value);

    return root;
}

// Информация о поддереве
struct Info {
    int height;
    int leaves;
};

// Переменные для результатов
double maxRatio = -1;
double minRatio = 1e9;

Node* maxNode = nullptr;
Node* minNode = nullptr;

// Высота и листья найденных поддеревьев
int maxHeight = 0;
int maxLeaves = 0;
int minHeight = 0;
int minLeaves = 0;

// Анализ поддеревьев
Info analyze(Node* root) {
    if (root == nullptr)
        return { 0, 0 };

    Info left = analyze(root->left);
    Info right = analyze(root->right);

    Info current;

    // Вычисление высоты
    if (left.height > right.height)
        current.height = left.height + 1;
    else
        current.height = right.height + 1;

    // Подсчет количества листьев
    if (root->left == nullptr && root->right == nullptr)
        current.leaves = 1;
    else
        current.leaves = left.leaves + right.leaves;

    // Вычисление отношения
    double ratio = (double)current.height / current.leaves;

    // Поиск максимального отношения
    if (ratio > maxRatio) {
        maxRatio = ratio;
        maxNode = root;
        maxHeight = current.height;
        maxLeaves = current.leaves;
    }

    // Поиск минимального отношения
    if (ratio < minRatio) {
        minRatio = ratio;
        minNode = root;
        minHeight = current.height;
        minLeaves = current.leaves;
    }

    return current;
}

// Наглядный вывод дерева
void printTreeVisual(Node* root, int level = 0) {
    if (root == nullptr)
        return;

    // Правое поддерево
    printTreeVisual(root->right, level + 1);

    // Отступы
    for (int i = 0; i < level; i++)
        cout << "    ";

    cout << root->data << endl;

    // Левое поддерево
    printTreeVisual(root->left, level + 1);
}

// Освобождение памяти
void deleteTree(Node* root) {
    if (root == nullptr)
        return;

    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
}

int main() {

    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    Node* root = nullptr;

    // Элементы дерева заданы заранее
    int values[] = { 8, 4, 12, 2, 6, 10, 14 };
    int n = sizeof(values) / sizeof(values[0]);

    // Создание дерева
    for (int i = 0; i < n; i++)
        root = insert(root, values[i]);

    cout << "Исходное бинарное дерево:\n\n";
    printTreeVisual(root);

    // Анализ дерева
    analyze(root);

    // Максимальное отношение
    cout << "\nМаксимальное отношение:\n";
    cout << "Высота: " << maxHeight << endl;
    cout << "Количество листьев: " << maxLeaves << endl;
    cout << "Соотношение: " << maxHeight << " / "
        << maxLeaves << " = " << maxRatio << endl;
    cout << "Корень поддерева: " << maxNode->data << endl;
    cout << "Поддерево:\n";
    printTreeVisual(maxNode);

    // Минимальное отношение
    cout << "\nМинимальное отношение:\n";
    cout << "Высота: " << minHeight << endl;
    cout << "Количество листьев: " << minLeaves << endl;
    cout << "Соотношение: " << minHeight << " / "
        << minLeaves << " = " << minRatio << endl;
    cout << "Корень поддерева: " << minNode->data << endl;
    cout << "Поддерево:\n";
    printTreeVisual(minNode);

    deleteTree(root);

    return 0;
}
