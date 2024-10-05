#ifndef AVL_H
#define AVL_H

// Структура узла AVL-дерева
struct AVLNode {
    int key;              // Ключ (значение) узла
    AVLNode* left;        // Указатель на левое поддерево
    AVLNode* right;       // Указатель на правое поддерево
    int height;           // Высота узла
};

// Структура для узла очереди
struct QueueNode {
    AVLNode* treeNode;    // Указатель на узел дерева
    QueueNode* next;      // Указатель на следующий элемент очереди
};

// Самописная очередь
struct QueueForAvl {
    QueueNode* front;     // Начало очереди
    QueueNode* rear;      // Конец очереди
    int count;            // Счетчик узлов в очереди

    // Инициализация пустой очереди
    QueueForAvl() : front(nullptr), rear(nullptr), count(0) {}

    // Проверка, пуста ли очередь
    bool isEmpty() {
        return count == 0;  // Проверяем по счетчику
    }

    // Добавление узла дерева в очередь
    void enqueue(AVLNode* node) {
        QueueNode* newNode = new QueueNode();
        newNode->treeNode = node;
        newNode->next = nullptr;

        if (rear == nullptr) {
            front = rear = newNode;
        }
        else {
            rear->next = newNode;
            rear = newNode;
        }
        count++; // Увеличиваем счетчик
    }

    // Удаление узла из очереди и возвращение его
    AVLNode* dequeue() {
        if (isEmpty()) return nullptr;

        QueueNode* temp = front;
        AVLNode* result = front->treeNode;
        front = front->next;

        if (front == nullptr) {
            rear = nullptr;
        }

        delete temp;
        count--; // Уменьшаем счетчик
        return result;
    }

    // Метод получения размера очереди
    int size() const {
        return count; // Возвращаем текущее значение счетчика
    }
};


// Функция вывода дерева по уровням
void avlPrintByLevels(AVLNode* root) {
    if (!root) {
        cout << "Дерево пустое." << endl; // Сообщение, если дерево пустое
        return;
    }

    QueueForAvl q;           // Инициализируем очередь
    q.enqueue(root);         // Добавляем корень дерева в очередь

    while (!q.isEmpty()) {
        int levelSize = q.size(); // Получаем количество узлов на текущем уровне

        // Флаг, указывающий, была ли выведена хотя бы одна реальная нода
        bool hasNodes = false;

        // Проходим по всем узлам текущего уровня
        for (int i = 0; i < levelSize; ++i) {
            AVLNode* currentNode = q.dequeue(); // Берём узел из очереди

            // Если узел существует, выводим его ключ
            if (currentNode) {
                cout << currentNode->key << "\t"; // Выводим ключ текущего узла
                hasNodes = true; // Обозначаем, что есть узел для вывода
                // Добавляем потомков в очередь
                q.enqueue(currentNode->left);
                q.enqueue(currentNode->right);
            }
            else {
                cout << "-\t"; // Если узел отсутствует, выводим прочерк
                q.enqueue(nullptr); // Добавляем пустые узлы для возможных потомков
                q.enqueue(nullptr);
            }
        }

        // Если на уровне не было реальных узлов, прекращаем вывод
        if (!hasNodes) break;

        cout << endl; // Переход на новую строку после вывода одного уровня
    }
}



// Инициализация нового узла
AVLNode* avlCreateNode(int key) {
    AVLNode* node = new AVLNode(); // Выделяем память под новый узел
    node->key = key;               // Инициализируем ключ узла
    node->left = nullptr;          // Левый потомок отсутствует
    node->right = nullptr;         // Правый потомок отсутствует
    node->height = 1;              // Высота нового узла (так как он листовой)
    return node;                   // Возвращаем указатель на созданный узел
}

// Поиск элемента по ключу
AVLNode* avlFind(AVLNode* node, int key) {
    if (node == nullptr || node->key == key)
        return node; // Если узел пустой или ключ найден, возвращаем узел
    if (key < node->key)
        return avlFind(node->left, key); // Ищем в левом поддереве
    return avlFind(node->right, key); // Ищем в правом поддереве
}


// Высота узла
int avlHeight(AVLNode* node) {
    return node ? node->height : 0;  // Если узел не nullptr, возвращаем его высоту, иначе 0 (высота пустого дерева)
}

// Баланс узла
int avlBalanceFactor(AVLNode* node) {
    return avlHeight(node->right) - avlHeight(node->left);  // Разница между высотой правого и левого поддеревьев
}

// Обновление высоты узла
void avlUpdateHeight(AVLNode* node) {
    int leftHeight = avlHeight(node->left);  // Получаем высоту левого поддерева
    int rightHeight = avlHeight(node->right); // Получаем высоту правого поддерева
    node->height = (leftHeight > rightHeight ? leftHeight : rightHeight) + 1; // Новая высота текущего узла — максимум из высот потомков + 1
}

// Правый поворот
AVLNode* avlRotateRight(AVLNode* p) {
    AVLNode* q = p->left;           // Берём левое поддерево узла p
    p->left = q->right;             // Переносим правое поддерево узла q на место левого поддерева узла p
    q->right = p;                   // Делаем p правым потомком узла q
    avlUpdateHeight(p);             // Обновляем высоту узла p
    avlUpdateHeight(q);             // Обновляем высоту узла q
    return q;                       // Возвращаем новый корень поддерева (узел q)
}

// Левый поворот
AVLNode* avlRotateLeft(AVLNode* q) {
    AVLNode* p = q->right;          // Берём правое поддерево узла q
    q->right = p->left;             // Переносим левое поддерево узла p на место правого поддерева узла q
    p->left = q;                    // Делаем q левым потомком узла p
    avlUpdateHeight(q);             // Обновляем высоту узла q
    avlUpdateHeight(p);             // Обновляем высоту узла p
    return p;                       // Возвращаем новый корень поддерева (узел p)
}

// Балансировка узла
AVLNode* avlBalance(AVLNode* node) {
    avlUpdateHeight(node);          // Обновляем высоту текущего узла
    if (avlBalanceFactor(node) == 2) {  // Если балансировка нарушена: правое поддерево слишком высокое
        if (avlBalanceFactor(node->right) < 0)  // Если правый потомок имеет левое смещение
            node->right = avlRotateRight(node->right);  // Выполняем правый поворот правого поддерева
        return avlRotateLeft(node);    // Выполняем левый поворот текущего узла
    }
    if (avlBalanceFactor(node) == -2) { // Если балансировка нарушена: левое поддерево слишком высокое
        if (avlBalanceFactor(node->left) > 0)  // Если левый потомок имеет правое смещение
            node->left = avlRotateLeft(node->left);  // Выполняем левый поворот левого поддерева
        return avlRotateRight(node);   // Выполняем правый поворот текущего узла
    }
    return node;                       // Возвращаем сбалансированный узел
}

// Вставка узла в дерево
AVLNode* avlInsert(AVLNode* node, int key) {
    if (node == nullptr) return avlCreateNode(key);  // Если узел пустой, создаем новый с переданным ключом
    if (key < node->key)                             // Если ключ меньше текущего, идём в левое поддерево
        node->left = avlInsert(node->left, key);     // Рекурсивно вставляем ключ в левое поддерево
    else                                             // Если ключ больше или равен текущему
        node->right = avlInsert(node->right, key);   // Рекурсивно вставляем ключ в правое поддерево
    return avlBalance(node);                         // После вставки выполняем балансировку
}

// Поиск минимального узла
AVLNode* avlFindMin(AVLNode* node) {
    return node->left ? avlFindMin(node->left) : node;  // Ищем минимальный элемент, спускаясь по левым потомкам
}

// Удаление минимального узла
AVLNode* avlRemoveMin(AVLNode* node) {
    if (!node->left) return node->right;  // Если нет левого поддерева, возвращаем правое поддерево
    node->left = avlRemoveMin(node->left); // Рекурсивно удаляем минимальный узел в левом поддереве
    return avlBalance(node);               // Выполняем балансировку после удаления
}

// Удаление узла с ключом
AVLNode* avlRemove(AVLNode* node, int key) {
    if (node == nullptr) return nullptr;           // Если узел пустой, возвращаем nullptr
    if (key < node->key)                           // Если ключ меньше текущего, идём в левое поддерево
        node->left = avlRemove(node->left, key);   // Рекурсивно удаляем узел в левом поддереве
    else if (key > node->key)                      // Если ключ больше текущего, идём в правое поддерево
        node->right = avlRemove(node->right, key); // Рекурсивно удаляем узел в правом поддереве
    else {                                         // Если нашли узел с нужным ключом
        AVLNode* left = node->left;                // Сохраняем левое поддерево
        AVLNode* right = node->right;              // Сохраняем правое поддерево
        delete node;                               // Удаляем текущий узел
        if (!right) return left;                   // Если нет правого поддерева, возвращаем левое
        AVLNode* min = avlFindMin(right);          // Находим минимальный узел в правом поддереве
        min->right = avlRemoveMin(right);          // Удаляем минимальный узел из правого поддерева
        min->left = left;                          // Присоединяем левое поддерево к минимальному узлу
        return avlBalance(min);                    // Выполняем балансировку после удаления
    }
    return avlBalance(node);                       // Возвращаем сбалансированный узел
}

// Очистка дерева (удаление всех узлов)
void avlClear(AVLNode*& node) {
    if (node) {
        avlClear(node->left);  // Рекурсивно удаляем левое поддерево
        avlClear(node->right); // Рекурсивно удаляем правое поддерево
        delete node;           // Удаляем текущий узел
        node = nullptr;        // Устанавливаем указатель на узел в nullptr
    }
}



// Сохранение дерева в файл и его очистка
void avlSaveToFile(AVLNode*& node, ofstream& file) {
    if (!file.is_open()) {
        throw runtime_error("Error: Unable to open file for writing.");
    }
    if (node) {
        file << node->key << " ";
        avlSaveToFile(node->left, file);
        avlSaveToFile(node->right, file);
    }
    avlClear(node);  // Очищаем дерево после сохранения
}

// Загрузка дерева из файла (с предварительной очисткой)
AVLNode* avlLoadFromFile(AVLNode*& node, ifstream& file) {
    avlClear(node);  // Очищаем дерево перед загрузкой
    int key;
    while (file >> key) {
        node = avlInsert(node, key);  // Вставляем ключи по мере чтения
    }
    return node;
}

#endif