#ifndef LIST_H
#define LIST_H

using namespace std;

// ���� ������������ ������
struct Node {
    string data;      // ������ ����
    Node* next;       // ��������� �� ��������� ����

    // ����������� ��� ������������� ����
    Node(const string& data) : data(data), next(nullptr) {}
};

// ����������� ������
struct LinkedList {
    Node* head;       // ��������� �� ������ ���� (������) ������
    Node* tail;       // ��������� �� ��������� ���� (�����) ������

    // �����������, ���������������� ������ ������
    LinkedList() : head(nullptr), tail(nullptr) {}

    // ���������� ��� ������������ ������
    ~LinkedList() {
        while (head) {
            Node* temp = head; // ��������� ��������� �� ������� ����
            head = head->next; // ���������� ��������� �� ��������� ����
            delete temp; // ����������� ������ �������� ����
        }
    }

    // ���������� �������� � ������ ������
    void addHead(const string& element) {
        Node* newNode = new Node(element); // ������� ����� ����
        newNode->next = head; // ����� ���� ��������� �� ������� ������ ������
        head = newNode; // ��������� ��������� �� ������ ������
        if (!tail) tail = head; // ���� ������ ��� ������, ��������� ��������� �� �����
    }

    // ���������� �������� � ����� ������
    void addTail(const string& element) {
        Node* newNode = new Node(element); // ������� ����� ����
        if (tail) {
            tail->next = newNode; // ���� ������ �� ������, ��������� ����� ���� ����� ������
        }
        else {
            head = newNode; // ���� ������ ��� ������, ��������� ��������� �� ������
        }
        tail = newNode; // ��������� ��������� �� �����
    }

    // �������� ������ ������
    void removeHead() {
        if (!head) return; // ���� ������ ����, ������ �� ������
        Node* temp = head; // ��������� ��������� �� ������� ������
        head = head->next; // ���������� ��������� �� ��������� ����
        if (!head) tail = nullptr; // ���� ������ ���� ������, �������� ��������� �� �����
        delete temp; // ����������� ������ �������� ����
    }

    // �������� ������ ������
    void removeTail() {
        if (!head) return; // ���� ������ ����, ������ �� ������
        if (head == tail) { // ���� � ������ ������ ���� �������
            delete head; // ����������� ������
            head = tail = nullptr; // �������� ���������
            return;
        }
        Node* current = head; // ��������� ��� ������� �� ������
        while (current->next != tail) { // ������� ���� ����� �������
            current = current->next; // ������������ � ���������� ����
        }
        delete tail; // ����������� ������ ������
        tail = current; // ��������� ��������� �� �����
        tail->next = nullptr; // ������� ��������� �� ��������� �������
    }

    // ����� ��������� ������ �� �����
    void read() const {
        Node* current = head; // ��������� ��� ������� �� ������
        size_t index = 0; // ������ �������� ��������
        while (current) {
            cout << index++ << ": " << current->data << endl; // ������� ������ � ������ ����
            current = current->next; // ������������ � ���������� ����
        }
    }

    // ����� �������� �� �������� � ������� �������
    int find(const string& element) const {
        Node* current = head; // ��������� ��� ������� �� ������
        int index = 0; // ������ �������� ��������
        while (current) {
            if (current->data == element) { // ���� ������� ������
                return index; // ���������� ��� ������
            }
            current = current->next; // ������������ � ���������� ����
            index++;
        }
        return -1; // ������� �� ������, ���������� -1
    }

    // �������� ������ �� �����
    void loadFromFile(const string& filename) {
        // ������� ������������� ������
        while (head) {
            removeHead(); // ������� ��� �������� �� ������
        }

        // ������ ������ �� �����
        ifstream file(filename); // ��������� ���� ��� ������
        if (!file.is_open()) throw runtime_error("Unable to open file"); // �������� ��������� �������� �����
        string line;
        while (getline(file, line)) {
            addTail(line); // ���������� ������ � ����� ������
        }
        file.close(); // ��������� ����
    }

    // ���������� ������ � ����
    void saveToFile(const string& filename) const {
        ofstream file(filename); // ��������� ���� ��� ������
        if (!file.is_open()) throw runtime_error("Unable to open file"); // �������� ��������� �������� �����
        Node* current = head; // ��������� ��� ������� �� ������
        while (current) {
            file << current->data << endl; // ���������� ������ ���� � ����
            current = current->next; // ������������ � ���������� ����
        }
        file.close(); // ��������� ����

        // ������� ������ ����� ����������
        const_cast<LinkedList*>(this)->clear(); // ���������� const_cast, ����� �������� ������
    }

    // ������� ����� ������
    void clear() {
        while (head) {
            removeHead(); // ������� ��� �������� �� ������
        }
    }
};

#endif
