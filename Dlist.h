#ifndef DLIST_H
#define DLIST_H

// ���� ����������� ������
struct DoubleNode {
    string data; // ������, ���������� � ����
    DoubleNode* next; // ��������� �� ��������� ����
    DoubleNode* prev; // ��������� �� ���������� ����

    // ����������� ��� ������������� ����
    DoubleNode(const string& data) : data(data), next(nullptr), prev(nullptr) {}
};

// ���������� ������
struct DoublyLinkedList {
    DoubleNode* head; // ��������� �� ������ ���� ������
    DoubleNode* tail; // ��������� �� ��������� ���� ������

    // ����������� ��� ������������� ������
    DoublyLinkedList() : head(nullptr), tail(nullptr) {}

    // ���������� ��� ������������ ��������
    ~DoublyLinkedList() {
        clear(); // ������� ������ � �����������
    }

    // ���������� �������� � ������ ������
    void addHead(const string& element) {
        DoubleNode* newNode = new DoubleNode(element); // �������� ������ ����
        newNode->next = head; // ��������� ��������� �� ��������� ����
        if (head) head->prev = newNode; // ���� ������ �� ����, ���������� ��������� �� ���������� ���� � ������� ����
        head = newNode; // ��������� ������ ���� ��� �������
        if (!tail) tail = head; // ���� ������ ��� ����, ���������� ����� ���� ��� ���������
    }

    // ���������� �������� � ����� ������
    void addTail(const string& element) {
        DoubleNode* newNode = new DoubleNode(element); // �������� ������ ����
        if (tail) { // ���� ������ �� ����
            tail->next = newNode; // ���������� ��������� ���� ��� ���������� ����
            newNode->prev = tail; // ���������� ���������� ���� ��� ������ ����
        }
        else {
            head = newNode; // ���� ������ ��� ����, ���������� ����� ���� ��� ������
        }
        tail = newNode; // ��������� ������ ���� ��� ����������
    }

    // �������� ������ ������
    void removeHead() {
        if (!head) return; // ���� ������ ����, ������ �� ������
        DoubleNode* temp = head; // ��������� ��������� �� ��������� ����
        head = head->next; // ����������� ��������� �� ������ � ���������� ����
        if (head) head->prev = nullptr; // ���� ����� ���� �� ����, �������� ��������� �� ���������� ����
        else tail = nullptr; // ���� ������ ����, �������� ��������� �� �����
        delete temp; // ������������ ������ ���������� ����
    }

    // �������� ������ ������
    void removeTail() {
        if (!tail) return; // ���� ������ ����, ������ �� ������
        DoubleNode* temp = tail; // ��������� ��������� �� ��������� ����
        tail = tail->prev; // ����������� ��������� �� ����� � ����������� ����
        if (tail) tail->next = nullptr; // ���� ����� ����� �� ����, �������� ��������� �� ��������� ����
        else head = nullptr; // ���� ������ ����, �������� ��������� �� ������
        delete temp; // ������������ ������ ���������� ����
    }

    // ����� ��������� ������ �� �����
    void read() const {
        DoubleNode* current = head; // ������ � ������ ������
        size_t index = 0; // ������ ��� �����������
        while (current) { // ���������� ��� ����
            cout << index++ << ": " << current->data << endl; // ����� ������ ���� � ��� �������
            current = current->next; // ������� � ���������� ����
        }
    }

    // ����� �������� �� �������� � ������� �������
    int find(const string& element) const {
        DoubleNode* current = head; // ������ � ������ ������
        int index = 0; // ������ ��� ������������ �������
        while (current) { // ���������� ��� ����
            if (current->data == element) { // ���� ������� ������
                return index; // ������� ������
            }
            current = current->next; // ������� � ���������� ����
            index++; // ��������� ������
        }
        return -1; // ������� �� ������, ������� -1
    }

    // �������� ������ �� �����
    void loadFromFile(const string& filename) {
        clear(); // ������� ������������� ������

        ifstream file(filename); // �������� ����� ��� ������
        if (!file.is_open()) throw runtime_error("Unable to open file"); // �������� �� �������� ��������
        string line; // ���������� ��� �������� �����
        while (getline(file, line)) { // ������ ����� ���������
            addTail(line); // ���������� ������ � ����� ������
        }
        file.close(); // �������� �����
    }

    // ���������� ������ � ����
    void saveToFile(const string& filename) const {
        ofstream file(filename); // �������� ����� ��� ������
        if (!file.is_open()) throw runtime_error("Unable to open file"); // �������� �� �������� ��������
        DoubleNode* current = head; // ������ � ������ ������
        while (current) { // ���������� ��� ����
            file << current->data << endl; // ������ ������ ���� � ����
            current = current->next; // ������� � ���������� ����
        }
        file.close(); // �������� �����

        // ������� ������ ����� ����������
        const_cast<DoublyLinkedList*>(this)->clear(); // ���������� const_cast, ����� ������� ������� ��� ������������ �������
    }

    // ������� ����� ������
    void clear() {
        while (head) { // ���� � ������ ���� ��������
            removeHead(); // �������� ������ ������
        }
    }
};

#endif