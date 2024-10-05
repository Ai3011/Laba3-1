#ifndef HASH_H
#define HASH_H

const int TABLE_SIZE = 100; // ���������� ������ ���-������� ��� ���������

// ��������� ��� ���� (��������) ���-�������
struct HNode {
    string key;   // ���� ��������
    string value; // �������� ��������
    HNode* next;  // ��������� �� ��������� ������� � ������� (��� ��������� ��������)
};

// ��������� ��� ���-�������
struct HashTable {
    HNode** table; // ������ ���������� �� ���� (������� � ��������� ��� ��������� ��������)
};

// ���-������� ��� ���������� ������� �� �����
unsigned hashFunction(const string& key) {
    unsigned hash = 0;
    for (auto ch : key) {
        // ��������� ���, ������� �� 31 � �������� �������� �������, ����� ����� �� ������ ������� �������
        hash = (hash * 31 + ch) % TABLE_SIZE;
    }
    return hash;
}

// ������� ������������� ���-�������
// �������� ������ ��� ������� ���������� � �������������� ��� �������� ��� nullptr
void initHashTable(HashTable& ht) {
    ht.table = new HNode * [TABLE_SIZE]; // ��������� ������ ��� ������ ���������� �� HNode
    for (int i = 0; i < TABLE_SIZE; i++) {
        ht.table[i] = nullptr; // �������������� ������ ������� nullptr
    }
}

// ������� ��� ������� �������� (���� ����-��������) � ���-�������
// ������� ����������� � ������ ������ �� �������, ����������� �� ���-�������
void insert(HashTable& ht, const string& key, const string& value) {
    unsigned index = hashFunction(key); // ��������� ������ ����� ���-�������
    // ������� ����� ����, ������� ����� ������ � ������� ��� ������� �������
    HNode* newNode = new HNode{ key, value, ht.table[index] };
    ht.table[index] = newNode; // ������ ����� ���� ������ � �������
}

// ������� ��� ��������� �������� ���� �� ��� ������� � �������
// index - ������ ���� (1 ��� �������, 2 ��� ������� � �.�.)
string get(HashTable& ht, const string& key, int index) {
    unsigned tableIndex = hashFunction(key); // ��������� ������ ����� ���-�������
    HNode* curNode = ht.table[tableIndex];   // �������� ������ ������� ������� �� �������
    int count = 0; // ������� ��� ������������ ������� ����

    // ���� ���� � �������
    while (curNode) {
        // ���������, ��������� �� ����
        if (curNode->key == key) {
            count++; // ����������� ������� ��� �������� � ���������� ����

            if (count == index) { // ���� ������� ������������� �������������� �������
                return curNode->value; // ���������� �������� ����
            }
        }

        curNode = curNode->next; // ��������� � ���������� ����
    }

    // ���� ���� � ����� ������ �� ������ ��� ����� ���� ��������� ���������� �����, ������� ����������
    throw runtime_error("Key not found or node index out of range");
}


// ������� ��� �������� �������� �� �����
// ������� ������� � ������� ��� �� �������, ���������� ������
void remove(HashTable& ht, const string& key) {
    unsigned index = hashFunction(key); // ��������� ������ ����� ���-�������
    HNode* curNode = ht.table[index];   // �������� ������ ������� �������
    HNode* tmp = nullptr;               // ���������� ��� �������� ����������� ����

    // ���� ���� � ������ ������
    while (curNode && curNode->key != key) {
        tmp = curNode;         // ���������� ���������� ����
        curNode = curNode->next; // ��������� � ���������� ����
    }

    // ���� ���� �� ������, ������ �� ������ (��� ����� ������� ����������)
    if (curNode == nullptr) {
        return; // ������������: throw runtime_error("Key not found");
    }

    // ���� ����� ����, ������� ��� �� �������
    if (tmp) {
        tmp->next = curNode->next; // "����������" ��������� ���� � �������
    }
    else {
        ht.table[index] = curNode->next; // ���� ��������� ���� ��� ������, ��������� ������ �������
    }

    delete curNode; // ����������� ������, ������� ��������� �����
}

// ������� ��� ������� ���-�������
// �������� �� ���� ������� ������� � ����������� ������ ��� ������� ����
void clearHashTable(HashTable& ht) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        HNode* current = ht.table[i]; // ����� ������ ������� �������
        // ������� ��� ���� � �������
        while (current != nullptr) {
            HNode* temp = current; // ��������� ���������� ��� �������� �������� ����
            current = current->next; // ��������� � ���������� ����
            delete temp; // ����������� ������ �������� ����
        }
        ht.table[i] = nullptr; // �������� ��������� �� �������
    }
    delete[] ht.table; // ����������� ������, ���������� ��� ������ ����������
}

// ������� ��� ������ ���� ���-�������
void printHashTable(const HashTable& ht) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        HNode* curNode = ht.table[i]; // ����� ������ ������� �������
        if (curNode) { // ���� � ������� ���� ��������
            cout << "������ " << i << " � ";
            while (curNode) {
                cout << "[" << curNode->key << ": " << curNode->value << "] ";
                curNode = curNode->next; // ��������� � ���������� ����
            }
            cout << endl; // ��������� ������ ����� ������ ���� �������
        }
    }
}

// ������� ��� ������ ���-������� � ���� � ����������� �������
void saveToFileAndClear(HashTable& ht, const string& filename) {
    ofstream outFile(filename); // ��������� ���� ��� ������
    if (!outFile) { // �������� ��������� �������� �����
        throw runtime_error("�� ������� ������� ���� ��� ������");
    }

    // �������� �� ���� ������� ���-�������
    for (int i = 0; i < TABLE_SIZE; i++) {
        HNode* curNode = ht.table[i]; // ����� ������ ������� �������
        while (curNode) {
            // ���������� ���� � �������� � ����
            outFile << curNode->key << "=" << curNode->value << endl;
            curNode = curNode->next; // ��������� � ���������� ����
        }
    }

    outFile.close(); // ��������� ����

    // ������� ���-�������
    clearHashTable(ht);
    initHashTable(ht);
}

void loadFromFile(HashTable& ht, const string& filename) {
    clearHashTable(ht); // ������� ���-������� ����� ���������
    initHashTable(ht);

    ifstream inFile(filename); // ��������� ���� ��� ������
    if (!inFile) { // �������� ��������� �������� �����
        throw runtime_error("�� ������� ������� ���� : " + filename);
    }

    string line;
    while (getline(inFile, line)) { // ������ ���� ���������
        if (line.empty()) { // �������� �� ������ ������
            continue; // ���������� ������ ������
        }

        size_t pos = line.find('='); // ������� ������� ������� '='
        if (pos == string::npos) { // ���� ������ �� ������, ���������� ������
            continue; // ���������� ������ ��� ������� '='
        }

        string key = line.substr(0, pos); // ��������� ����
        string value = line.substr(pos + 1); // ��������� ��������

        // ���������� ��������� � ����������� ����
        cout << "����������� ����: " << key << " = " << value << endl;

        insert(ht, key, value); // ��������� ���� ����-�������� � ���-�������
    }

    inFile.close(); // ��������� ����
    cout << "�������� ���������." << endl;
}

#endif // !HASH_H
