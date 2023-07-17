#include <stdio.h>
#include <stdlib.h>

// Структура для представления узла AVL-дерева
struct Node {
    int key;
    struct Node *left;
    struct Node *right;
    int height;
};

// Функция для получения высоты узла
int height(struct Node *node) {
    if (node == NULL)
        return 0;
    return node->height;
}

// Функция для получения максимального значения из двух чисел
int max(int a, int b) {
    return (a > b) ? a : b;
}

// Создание нового узла дерева
struct Node *newNode(int key) {
    struct Node *node = (struct Node *)malloc(sizeof(struct Node));
    node->key = key;
    node->left = NULL;
    node->right = NULL;
    node->height = 1;
    return node;
}

// Функция для поворота узла влево
struct Node *leftRotate(struct Node *node) {
    struct Node *x = node->right;
    struct Node *T2 = x->left;

    // Выполнение поворота
    x->left = node;
    node->right = T2;

    // Обновление высоты узлов
    node->height = max(height(node->left), height(node->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    // Возврат нового корневого узла
    return x;
}

// Функция для поворота узла вправо
struct Node *rightRotate(struct Node *node) {
    struct Node *y = node->left;
    struct Node *T2 = y->right;

    // Выполнение поворота
    y->right = node;
    node->left = T2;

    // Обновление высоты узлов
    node->height = max(height(node->left), height(node->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    // Возврат нового корневого узла
    return y;
}

// Получение разницы высот двух поддеревьев узла
int getBalance(struct Node *node) {
    if (node == NULL)
        return 0;
    return height(node->left) - height(node->right);
}

// Функция для вставки ключа в AVL-дерево
struct Node *insert(struct Node *node, int key) {
    // Шаг 1: Выполнение стандартной вставки в бинарное дерево поиска
    if (node == NULL)
        return newNode(key);

    if (key < node->key)
        node->left = insert(node->left, key);
    else if (key > node->key)
        node->right = insert(node->right, key);
    else // Дублирующиеся ключи не допускаются в AVL-дереве
        return node;

    // Шаг 2: Обновление высоты текущего узла
    node->height = 1 + max(height(node->left), height(node->right));

    // Шаг 3: Получение фактора сбалансированности этого узла
    int balance = getBalance(node);

    // Шаг 4: Если узел несбалансирован, то выполняем четыре возможные вращения

    // Несбалансированность влево-лево (LL)
    if (balance > 1 && key < node->left->key)
        return rightRotate(node);

    // Несбалансированность вправо-право (RR)
    if (balance < -1 && key > node->right->key)
        return leftRotate(node);

    // Несбалансированность влево-право (LR)
    if (balance > 1 && key > node->left->key) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    // Несбалансированность вправо-лево (RL)
    if (balance < -1 && key < node->right->key) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    // Если узел сбалансирован, просто возвращаем его
    return node;
}

// Функция для вывода дерева в порядке обхода инфикса (in-order)
void inOrderTraversal(struct Node *node) {
    if (node != NULL) {
        inOrderTraversal(node->left);
        printf("%d ", node->key);
        inOrderTraversal(node->right);
    }
}

// Пример использования
int main() {
    struct Node *root = NULL;

    root = insert(root, 10);
    root = insert(root, 20);
    root = insert(root, 30);
    root = insert(root, 40);
    root = insert(root, 50);
    root = insert(root, 25);

    printf("Дерево в порядке обхода инфикса (in-order): ");
    inOrderTraversal(root);
    printf("\n");

    return 0;
}
