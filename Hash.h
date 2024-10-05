#ifndef HASH_H
#define HASH_H

const int TABLE_SIZE = 100; // Определяем размер хэш-таблицы как константу

// Структура для узла (элемента) хэш-таблицы
struct HNode {
    string key;   // Ключ элемента
    string value; // Значение элемента
    HNode* next;  // Указатель на следующий элемент в цепочке (для обработки коллизий)
};

// Структура для хэш-таблицы
struct HashTable {
    HNode** table; // Массив указателей на узлы (таблица с цепочками для обработки коллизий)
};

// Хэш-функция для вычисления индекса по ключу
unsigned hashFunction(const string& key) {
    unsigned hash = 0;
    for (auto ch : key) {
        // Обновляем хэш, умножая на 31 и добавляя значение символа, затем берем по модулю размера таблицы
        hash = (hash * 31 + ch) % TABLE_SIZE;
    }
    return hash;
}

// Функция инициализации хэш-таблицы
// Выделяем память для массива указателей и инициализируем все элементы как nullptr
void initHashTable(HashTable& ht) {
    ht.table = new HNode * [TABLE_SIZE]; // Выделение памяти под массив указателей на HNode
    for (int i = 0; i < TABLE_SIZE; i++) {
        ht.table[i] = nullptr; // Инициализируем каждый элемент nullptr
    }
}

// Функция для вставки элемента (пары ключ-значение) в хэш-таблицу
// Элемент добавляется в начало списка по индексу, полученному от хэш-функции
void insert(HashTable& ht, const string& key, const string& value) {
    unsigned index = hashFunction(key); // Вычисляем индекс через хэш-функцию
    // Создаем новый узел, который будет первым в цепочке для данного индекса
    HNode* newNode = new HNode{ key, value, ht.table[index] };
    ht.table[index] = newNode; // Ставим новый узел первым в цепочке
}

// Функция для получения значения узла по его индексу в цепочке
// index - индекс узла (1 для первого, 2 для второго и т.д.)
string get(HashTable& ht, const string& key, int index) {
    unsigned tableIndex = hashFunction(key); // Вычисляем индекс через хэш-функцию
    HNode* curNode = ht.table[tableIndex];   // Получаем первый элемент цепочки по индексу
    int count = 0; // Счетчик для отслеживания позиции узла

    // Ищем узел в цепочке
    while (curNode) {
        // Проверяем, совпадает ли ключ
        if (curNode->key == key) {
            count++; // Увеличиваем счетчик при переходе к следующему узлу

            if (count == index) { // Если счетчик соответствует запрашиваемому индексу
                return curNode->value; // Возвращаем значение узла
            }
        }

        curNode = curNode->next; // Переходим к следующему узлу
    }

    // Если узел с таким ключом не найден или номер узла превышает количество узлов, бросаем исключение
    throw runtime_error("Key not found or node index out of range");
}


// Функция для удаления элемента по ключу
// Находим элемент и удаляем его из цепочки, освобождая память
void remove(HashTable& ht, const string& key) {
    unsigned index = hashFunction(key); // Вычисляем индекс через хэш-функцию
    HNode* curNode = ht.table[index];   // Получаем первый элемент цепочки
    HNode* tmp = nullptr;               // Переменная для хранения предыдущего узла

    // Ищем узел с нужным ключом
    while (curNode && curNode->key != key) {
        tmp = curNode;         // Запоминаем предыдущий узел
        curNode = curNode->next; // Переходим к следующему узлу
    }

    // Если узел не найден, ничего не делаем (или можно бросить исключение)
    if (curNode == nullptr) {
        return; // Альтернатива: throw runtime_error("Key not found");
    }

    // Если нашли узел, удаляем его из цепочки
    if (tmp) {
        tmp->next = curNode->next; // "Пропускаем" удаляемый узел в цепочке
    }
    else {
        ht.table[index] = curNode->next; // Если удаляемый узел был первым, обновляем начало цепочки
    }

    delete curNode; // Освобождаем память, занятую удаляемым узлом
}

// Функция для очистки хэш-таблицы
// Проходим по всем ячейкам таблицы и освобождаем память для каждого узла
void clearHashTable(HashTable& ht) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        HNode* current = ht.table[i]; // Берем первый элемент цепочки
        // Удаляем все узлы в цепочке
        while (current != nullptr) {
            HNode* temp = current; // Временная переменная для хранения текущего узла
            current = current->next; // Переходим к следующему узлу
            delete temp; // Освобождаем память текущего узла
        }
        ht.table[i] = nullptr; // Обнуляем указатель на цепочку
    }
    delete[] ht.table; // Освобождаем память, выделенную под массив указателей
}

// Функция для вывода всей хэш-таблицы
void printHashTable(const HashTable& ht) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        HNode* curNode = ht.table[i]; // Берем первый элемент цепочки
        if (curNode) { // Если в цепочке есть элементы
            cout << "Индекс " << i << " – ";
            while (curNode) {
                cout << "[" << curNode->key << ": " << curNode->value << "] ";
                curNode = curNode->next; // Переходим к следующему узлу
            }
            cout << endl; // Переносим строку после вывода всей цепочки
        }
    }
}

// Функция для записи хэш-таблицы в файл и последующей очистки
void saveToFileAndClear(HashTable& ht, const string& filename) {
    ofstream outFile(filename); // Открываем файл для записи
    if (!outFile) { // Проверка успешного открытия файла
        throw runtime_error("Не удалось открыть файл для записи");
    }

    // Проходим по всем ячейкам хэш-таблицы
    for (int i = 0; i < TABLE_SIZE; i++) {
        HNode* curNode = ht.table[i]; // Берем первый элемент цепочки
        while (curNode) {
            // Записываем ключ и значение в файл
            outFile << curNode->key << "=" << curNode->value << endl;
            curNode = curNode->next; // Переходим к следующему узлу
        }
    }

    outFile.close(); // Закрываем файл

    // Очищаем хэш-таблицу
    clearHashTable(ht);
    initHashTable(ht);
}

void loadFromFile(HashTable& ht, const string& filename) {
    clearHashTable(ht); // Очистка хэш-таблицы перед загрузкой
    initHashTable(ht);

    ifstream inFile(filename); // Открываем файл для чтения
    if (!inFile) { // Проверка успешного открытия файла
        throw runtime_error("Не удалось открыть файл : " + filename);
    }

    string line;
    while (getline(inFile, line)) { // Читаем файл построчно
        if (line.empty()) { // Проверка на пустую строку
            continue; // Пропускаем пустые строки
        }

        size_t pos = line.find('='); // Находим позицию символа '='
        if (pos == string::npos) { // Если символ не найден, пропускаем строку
            continue; // Пропускаем строки без символа '='
        }

        string key = line.substr(0, pos); // Извлекаем ключ
        string value = line.substr(pos + 1); // Извлекаем значение

        // Отладочное сообщение о загружаемой паре
        cout << "Загруженная пара: " << key << " = " << value << endl;

        insert(ht, key, value); // Вставляем пару ключ-значение в хэш-таблицу
    }

    inFile.close(); // Закрываем файл
    cout << "Загрузка завершена." << endl;
}

#endif // !HASH_H
