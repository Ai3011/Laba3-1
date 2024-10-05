#ifndef STACK_H
#define STACK_H

#include "List.h" // ����������� ��������� LinkedList

// ��������� �����
struct Stack {
    LinkedList list; // ������ ������ ��� �������� ��������� �����

    // ���������� �������� � ����
    void push(const std::string& element) {
        list.addHead(element); // ��������� ������� � ������ ������ (������� �����)
    }

    // �������� �������� �� �����
    void pop() {
        list.removeHead(); // ������� ������� � ������� �����
    }

    // ����� ����������� �����
    void read() const {
        list.read(); // ������� �������� ������
    }

    // �������� ������ �� �����
    void loadFromFile(const std::string& filename) {
        list.loadFromFile(filename); // ���������� �������� ������ ������
    }

    // ���������� ������ � ����
    void saveToFile(const std::string& filename) const {
        list.saveToFile(filename); // ���������� ���������� ������ ������
    }

    // ������� �����
    void clear() {
        while (list.head) {
            list.removeHead(); // ������� ��� �������� �� �����
        }
    }
};

#endif // STACK_H
