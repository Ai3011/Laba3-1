#ifndef LIST_H
#define LIST_H

using namespace std;

// Узел односвязного списка
struct Node {
    string data;      // Данные узла
    Node* next;       // Указатель на следующий узел

    // Конструктор для инициализации узла
    Node(const string& data) : data(data), next(nullptr) {}
};

// Односвязный список
struct LinkedList {
    Node* head;       // Указатель на первый узел (голову) списка
    Node* tail;       // Указатель на последний узел (хвост) списка

    // Конструктор, инициализирующий пустой список
    LinkedList() : head(nullptr), tail(nullptr) {}

    // Деструктор для освобождения памяти
    ~LinkedList() {
        while (head) {
            Node* temp = head; // Сохраняем указатель на текущий узел
            head = head->next; // Перемещаем указатель на следующий узел
            delete temp; // Освобождаем память текущего узла
        }
    }

    // Добавление элемента в начало списка
    void addHead(const string& element) {
        Node* newNode = new Node(element); // Создаем новый узел
        newNode->next = head; // Новый узел указывает на текущую голову списка
        head = newNode; // Обновляем указатель на голову списка
        if (!tail) tail = head; // Если список был пустым, обновляем указатель на хвост
    }

    // Добавление элемента в конец списка
    void addTail(const string& element) {
        Node* newNode = new Node(element); // Создаем новый узел
        if (tail) {
            tail->next = newNode; // Если список не пустой, добавляем новый узел после хвоста
        }
        else {
            head = newNode; // Если список был пустым, обновляем указатель на голову
        }
        tail = newNode; // Обновляем указатель на хвост
    }

    // Удаление головы списка
    void removeHead() {
        if (!head) 
            return; // Если список пуст, ничего не делаем
        Node* temp = head; // Сохраняем указатель на текущую голову
        head = head->next; // Перемещаем указатель на следующий узел
        if (!head) 
            tail = nullptr; // Если список стал пустым, обнуляем указатель на хвост
        delete temp; // Освобождаем память текущего узла
    }

    // Удаление хвоста списка
    void removeTail() {
        if (!head) 
            return; // Если список пуст, ничего не делаем
        if (head == tail) { // Если в списке только один элемент
            delete head; // Освобождаем память
            head = tail = nullptr; // Обнуляем указатели
            return;
        }
        Node* current = head; // Указатель для прохода по списку
        while (current->next != tail) { // Находим узел перед хвостом
            current = current->next; // Перемещаемся к следующему узлу
        }
        delete tail; // Освобождаем память хвоста
        tail = current; // Обновляем указатель на хвост
        tail->next = nullptr; // Убираем указатель на следующий элемент
    }

    // Вывод элементов списка на экран
    void read() const {
        Node* current = head; // Указатель для прохода по списку
        size_t index = 0; // Индекс текущего элемента
        while (current) {
            cout << index++ << ": " << current->data << endl; // Выводим индекс и данные узла
            current = current->next; // Перемещаемся к следующему узлу
        }
    }

    // Поиск элемента по значению с выводом индекса
    int find(const string& element) const {
        Node* current = head; // Указатель для прохода по списку
        int index = 0; // Индекс текущего элемента
        while (current) {
            if (current->data == element) { // Если элемент найден
                return index; // Возвращаем его индекс
            }
            current = current->next; // Перемещаемся к следующему узлу
            index++;
        }
        return -1; // Элемент не найден, возвращаем -1
    }

    bool removeByValue(const string& value){
        Node* current = head;
        Node* previous = nullptr;

        while(current) {
            if (current ->data == value) {
                if(previous) {
                    previous ->next = current -> next;
                } else {
                    head = current -> next;
                }
                delete current;
                return true;
            }
            previous = current;// переход к след узлу
            current = current->next;
        }
        return false;
    }

    // Загрузка данных из файла
    void loadFromFile(const string& filename) {
        // Очистка существующего списка
        while (head) {
            removeHead(); // Удаляем все элементы из списка
        }

        // Чтение данных из файла
        ifstream file(filename); // Открываем файл для чтения
        if (!file.is_open()) 
            throw runtime_error("Unable to open file"); // Проверка успешного открытия файла
        string line;
        while (getline(file, line)) {
            addTail(line); // Добавление строки в конец списка
        }
        file.close(); // Закрываем файл
    }

    // Сохранение данных в файл
    void saveToFile(const string& filename) const {
        ofstream file(filename); // Открываем файл для записи
        if (!file.is_open()) 
            throw runtime_error("Unable to open file"); // Проверка успешного открытия файла
        Node* current = head; // Указатель для прохода по списку
        while (current) {
            file << current->data << endl; // Записываем данные узла в файл
            current = current->next; // Перемещаемся к следующему узлу
        }
        file.close(); // Закрываем файл

        // Очистка списка после сохранения
        const_cast<LinkedList*>(this)->clear(); // Используем const_cast, чтобы очистить список
    }

    // Очистка всего списка
    void clear() {
        while (head) {
            removeHead(); // Удаляем все элементы из списка
        }
    }
};

#endif
