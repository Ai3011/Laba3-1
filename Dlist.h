#ifndef DLIST_H
#define DLIST_H

// Узел двусвязного списка
struct DoubleNode {
    string data; // Данные, хранящиеся в узле
    DoubleNode* next; // Указатель на следующий узел
    DoubleNode* prev; // Указатель на предыдущий узел

    // Конструктор для инициализации узла
    DoubleNode(const string& data) : data(data), next(nullptr), prev(nullptr) {}
};

// Двусвязный список
struct DoublyLinkedList {
    DoubleNode* head; // Указатель на первый узел списка
    DoubleNode* tail; // Указатель на последний узел списка

    // Конструктор для инициализации списка
    DoublyLinkedList() : head(nullptr), tail(nullptr) {}

    // Деструктор для освобождения ресурсов
    ~DoublyLinkedList() {
        clear(); // Очистка списка в деструкторе
    }

    // Добавление элемента в начало списка
    void addHead(const string& element) {
        DoubleNode* newNode = new DoubleNode(element); // Создание нового узла
        newNode->next = head; // Установка указателя на следующий узел
        if (head) 
            head->prev = newNode; // Если список не пуст, установить указатель на предыдущий узел у первого узла
        head = newNode; // Установка нового узла как первого
        if (!tail) 
            tail = head; // Если список был пуст, установить новый узел как последний
    }

    // Добавление элемента в конец списка
    void addTail(const string& element) {
        DoubleNode* newNode = new DoubleNode(element); // Создание нового узла
        if (tail) { // Если список не пуст
            tail->next = newNode; // Установить следующий узел для последнего узла
            newNode->prev = tail; // Установить предыдущий узел для нового узла
        }
        else {
            head = newNode; // Если список был пуст, установить новый узел как первый
        }
        tail = newNode; // Установка нового узла как последнего
    }

    // Удаление головы списка
    void removeHead() {
        if (!head) return; // Если список пуст, ничего не делать
        DoubleNode* temp = head; // Сохранить указатель на удаляемый узел
        head = head->next; // Перемещение указателя на голову к следующему узлу
        if (head) head->prev = nullptr; // Если новый узел не пуст, сбросить указатель на предыдущий узел
        else tail = nullptr; // Если список пуст, сбросить указатель на хвост
        delete temp; // Освобождение памяти удаляемого узла
    }

    // Удаление хвоста списка
    void removeTail() {
        if (!tail) return; // Если список пуст, ничего не делать
        DoubleNode* temp = tail; // Сохранить указатель на удаляемый узел
        tail = tail->prev; // Перемещение указателя на хвост к предыдущему узлу
        if (tail) tail->next = nullptr; // Если новый хвост не пуст, сбросить указатель на следующий узел
        else head = nullptr; // Если список пуст, сбросить указатель на голову
        delete temp; // Освобождение памяти удаляемого узла
    }

    // Вывод элементов списка на экран
    void read() const {
        DoubleNode* current = head; // Начать с головы списка
        size_t index = 0; // Индекс для отображения
        while (current) { // Перебирать все узлы
            cout << index++ << ": " << current->data << endl; // Вывод данных узла и его индекса
            current = current->next; // Переход к следующему узлу
        }
    }

    // Поиск элемента по значению с выводом индекса
    int find(const string& element) const {
        DoubleNode* current = head; // Начать с головы списка
        int index = 0; // Индекс для отслеживания позиции
        while (current) { // Перебирать все узлы
            if (current->data == element) { // Если элемент найден
                return index; // Вернуть индекс
            }
            current = current->next; // Переход к следующему узлу
            index++; // Увеличить индекс
        }
        return -1; // Элемент не найден, вернуть -1
    }

    bool removeValue(const string& value) {
        if (!head)
            return false;

        DoubleNode* current = head;


        while(current){
            if(current->data ==value){
                if(current->prev){
                    current->prev->next = current->next;
                }else { // если первый узел
                    head = current->next;
                }
                if(current->next){ // если не последний
                    current->next->prev = current->prev;
                } else{
                    tail = current->prev;
                }
                delete current;
                return true;
            }
            current = current->next;
        }
        return false;
    }

    // Загрузка данных из файла
    void loadFromFile(const string& filename) {
        clear(); // Очистка существующего списка

        ifstream file(filename); // Открытие файла для чтения
        if (!file.is_open()) throw runtime_error("Unable to open file"); // Проверка на успешное открытие
        string line; // Переменная для хранения строк
        while (getline(file, line)) { // Чтение файла построчно
            addTail(line); // Добавление строки в конец списка
        }
        file.close(); // Закрытие файла
    }

    // Сохранение данных в файл
    void saveToFile(const string& filename) const {
        ofstream file(filename); // Открытие файла для записи
        if (!file.is_open()) 
            throw runtime_error("Unable to open file"); // Проверка на успешное открытие
        DoubleNode* current = head; // Начать с головы списка
        while (current) { // Перебирать все узлы
            file << current->data << endl; // Запись данных узла в файл
            current = current->next; // Переход к следующему узлу
        }
        file.close(); // Закрытие файла

        // Очистка списка после сохранения
        const_cast<DoublyLinkedList*>(this)->clear(); // Используем const_cast, чтобы вызвать очистку для константного объекта
    }

    // Очистка всего списка
    void clear() {
        while (head) { // Пока в списке есть элементы
            removeHead(); // Удаление головы списка
        }
    }
};

#endif
