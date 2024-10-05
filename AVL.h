#ifndef AVL_H
#define AVL_H

// ��������� ���� AVL-������
struct AVLNode {
    int key;              // ���� (��������) ����
    AVLNode* left;        // ��������� �� ����� ���������
    AVLNode* right;       // ��������� �� ������ ���������
    int height;           // ������ ����
};

// ��������� ��� ���� �������
struct QueueNode {
    AVLNode* treeNode;    // ��������� �� ���� ������
    QueueNode* next;      // ��������� �� ��������� ������� �������
};

// ���������� �������
struct QueueForAvl {
    QueueNode* front;     // ������ �������
    QueueNode* rear;      // ����� �������
    int count;            // ������� ����� � �������

    // ������������� ������ �������
    QueueForAvl() : front(nullptr), rear(nullptr), count(0) {}

    // ��������, ����� �� �������
    bool isEmpty() {
        return count == 0;  // ��������� �� ��������
    }

    // ���������� ���� ������ � �������
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
        count++; // ����������� �������
    }

    // �������� ���� �� ������� � ����������� ���
    AVLNode* dequeue() {
        if (isEmpty()) return nullptr;

        QueueNode* temp = front;
        AVLNode* result = front->treeNode;
        front = front->next;

        if (front == nullptr) {
            rear = nullptr;
        }

        delete temp;
        count--; // ��������� �������
        return result;
    }

    // ����� ��������� ������� �������
    int size() const {
        return count; // ���������� ������� �������� ��������
    }
};


// ������� ������ ������ �� �������
void avlPrintByLevels(AVLNode* root) {
    if (!root) {
        cout << "������ ������." << endl; // ���������, ���� ������ ������
        return;
    }

    QueueForAvl q;           // �������������� �������
    q.enqueue(root);         // ��������� ������ ������ � �������

    while (!q.isEmpty()) {
        int levelSize = q.size(); // �������� ���������� ����� �� ������� ������

        // ����, �����������, ���� �� �������� ���� �� ���� �������� ����
        bool hasNodes = false;

        // �������� �� ���� ����� �������� ������
        for (int i = 0; i < levelSize; ++i) {
            AVLNode* currentNode = q.dequeue(); // ���� ���� �� �������

            // ���� ���� ����������, ������� ��� ����
            if (currentNode) {
                cout << currentNode->key << "\t"; // ������� ���� �������� ����
                hasNodes = true; // ����������, ��� ���� ���� ��� ������
                // ��������� �������� � �������
                q.enqueue(currentNode->left);
                q.enqueue(currentNode->right);
            }
            else {
                cout << "-\t"; // ���� ���� �����������, ������� �������
                q.enqueue(nullptr); // ��������� ������ ���� ��� ��������� ��������
                q.enqueue(nullptr);
            }
        }

        // ���� �� ������ �� ���� �������� �����, ���������� �����
        if (!hasNodes) break;

        cout << endl; // ������� �� ����� ������ ����� ������ ������ ������
    }
}



// ������������� ������ ����
AVLNode* avlCreateNode(int key) {
    AVLNode* node = new AVLNode(); // �������� ������ ��� ����� ����
    node->key = key;               // �������������� ���� ����
    node->left = nullptr;          // ����� ������� �����������
    node->right = nullptr;         // ������ ������� �����������
    node->height = 1;              // ������ ������ ���� (��� ��� �� ��������)
    return node;                   // ���������� ��������� �� ��������� ����
}

// ����� �������� �� �����
AVLNode* avlFind(AVLNode* node, int key) {
    if (node == nullptr || node->key == key)
        return node; // ���� ���� ������ ��� ���� ������, ���������� ����
    if (key < node->key)
        return avlFind(node->left, key); // ���� � ����� ���������
    return avlFind(node->right, key); // ���� � ������ ���������
}


// ������ ����
int avlHeight(AVLNode* node) {
    return node ? node->height : 0;  // ���� ���� �� nullptr, ���������� ��� ������, ����� 0 (������ ������� ������)
}

// ������ ����
int avlBalanceFactor(AVLNode* node) {
    return avlHeight(node->right) - avlHeight(node->left);  // ������� ����� ������� ������� � ������ �����������
}

// ���������� ������ ����
void avlUpdateHeight(AVLNode* node) {
    int leftHeight = avlHeight(node->left);  // �������� ������ ������ ���������
    int rightHeight = avlHeight(node->right); // �������� ������ ������� ���������
    node->height = (leftHeight > rightHeight ? leftHeight : rightHeight) + 1; // ����� ������ �������� ���� � �������� �� ����� �������� + 1
}

// ������ �������
AVLNode* avlRotateRight(AVLNode* p) {
    AVLNode* q = p->left;           // ���� ����� ��������� ���� p
    p->left = q->right;             // ��������� ������ ��������� ���� q �� ����� ������ ��������� ���� p
    q->right = p;                   // ������ p ������ �������� ���� q
    avlUpdateHeight(p);             // ��������� ������ ���� p
    avlUpdateHeight(q);             // ��������� ������ ���� q
    return q;                       // ���������� ����� ������ ��������� (���� q)
}

// ����� �������
AVLNode* avlRotateLeft(AVLNode* q) {
    AVLNode* p = q->right;          // ���� ������ ��������� ���� q
    q->right = p->left;             // ��������� ����� ��������� ���� p �� ����� ������� ��������� ���� q
    p->left = q;                    // ������ q ����� �������� ���� p
    avlUpdateHeight(q);             // ��������� ������ ���� q
    avlUpdateHeight(p);             // ��������� ������ ���� p
    return p;                       // ���������� ����� ������ ��������� (���� p)
}

// ������������ ����
AVLNode* avlBalance(AVLNode* node) {
    avlUpdateHeight(node);          // ��������� ������ �������� ����
    if (avlBalanceFactor(node) == 2) {  // ���� ������������ ��������: ������ ��������� ������� �������
        if (avlBalanceFactor(node->right) < 0)  // ���� ������ ������� ����� ����� ��������
            node->right = avlRotateRight(node->right);  // ��������� ������ ������� ������� ���������
        return avlRotateLeft(node);    // ��������� ����� ������� �������� ����
    }
    if (avlBalanceFactor(node) == -2) { // ���� ������������ ��������: ����� ��������� ������� �������
        if (avlBalanceFactor(node->left) > 0)  // ���� ����� ������� ����� ������ ��������
            node->left = avlRotateLeft(node->left);  // ��������� ����� ������� ������ ���������
        return avlRotateRight(node);   // ��������� ������ ������� �������� ����
    }
    return node;                       // ���������� ���������������� ����
}

// ������� ���� � ������
AVLNode* avlInsert(AVLNode* node, int key) {
    if (node == nullptr) return avlCreateNode(key);  // ���� ���� ������, ������� ����� � ���������� ������
    if (key < node->key)                             // ���� ���� ������ ��������, ��� � ����� ���������
        node->left = avlInsert(node->left, key);     // ���������� ��������� ���� � ����� ���������
    else                                             // ���� ���� ������ ��� ����� ��������
        node->right = avlInsert(node->right, key);   // ���������� ��������� ���� � ������ ���������
    return avlBalance(node);                         // ����� ������� ��������� ������������
}

// ����� ������������ ����
AVLNode* avlFindMin(AVLNode* node) {
    return node->left ? avlFindMin(node->left) : node;  // ���� ����������� �������, ��������� �� ����� ��������
}

// �������� ������������ ����
AVLNode* avlRemoveMin(AVLNode* node) {
    if (!node->left) return node->right;  // ���� ��� ������ ���������, ���������� ������ ���������
    node->left = avlRemoveMin(node->left); // ���������� ������� ����������� ���� � ����� ���������
    return avlBalance(node);               // ��������� ������������ ����� ��������
}

// �������� ���� � ������
AVLNode* avlRemove(AVLNode* node, int key) {
    if (node == nullptr) return nullptr;           // ���� ���� ������, ���������� nullptr
    if (key < node->key)                           // ���� ���� ������ ��������, ��� � ����� ���������
        node->left = avlRemove(node->left, key);   // ���������� ������� ���� � ����� ���������
    else if (key > node->key)                      // ���� ���� ������ ��������, ��� � ������ ���������
        node->right = avlRemove(node->right, key); // ���������� ������� ���� � ������ ���������
    else {                                         // ���� ����� ���� � ������ ������
        AVLNode* left = node->left;                // ��������� ����� ���������
        AVLNode* right = node->right;              // ��������� ������ ���������
        delete node;                               // ������� ������� ����
        if (!right) return left;                   // ���� ��� ������� ���������, ���������� �����
        AVLNode* min = avlFindMin(right);          // ������� ����������� ���� � ������ ���������
        min->right = avlRemoveMin(right);          // ������� ����������� ���� �� ������� ���������
        min->left = left;                          // ������������ ����� ��������� � ������������ ����
        return avlBalance(min);                    // ��������� ������������ ����� ��������
    }
    return avlBalance(node);                       // ���������� ���������������� ����
}

// ������� ������ (�������� ���� �����)
void avlClear(AVLNode*& node) {
    if (node) {
        avlClear(node->left);  // ���������� ������� ����� ���������
        avlClear(node->right); // ���������� ������� ������ ���������
        delete node;           // ������� ������� ����
        node = nullptr;        // ������������� ��������� �� ���� � nullptr
    }
}



// ���������� ������ � ���� � ��� �������
void avlSaveToFile(AVLNode*& node, ofstream& file) {
    if (!file.is_open()) {
        throw runtime_error("Error: Unable to open file for writing.");
    }
    if (node) {
        file << node->key << " ";
        avlSaveToFile(node->left, file);
        avlSaveToFile(node->right, file);
    }
    avlClear(node);  // ������� ������ ����� ����������
}

// �������� ������ �� ����� (� ��������������� ��������)
AVLNode* avlLoadFromFile(AVLNode*& node, ifstream& file) {
    avlClear(node);  // ������� ������ ����� ���������
    int key;
    while (file >> key) {
        node = avlInsert(node, key);  // ��������� ����� �� ���� ������
    }
    return node;
}

#endif