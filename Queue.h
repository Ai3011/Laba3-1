#ifndef QUEUE_H
#define QUEUE_H

#include "List.h"


struct Queue {
    LinkedList list;

    // ���������� �������� � �������
    void push(const string& element) {
        list.addTail(element);
    }

    // �������� �������� �� �������
    void pop() {
        list.removeHead();
    }

    // ����� ����������� �������
    void read() const {
        list.read();
    }

    // �������� ������ �� �����
    void loadFromFile(const string& filename) {
        list.loadFromFile(filename); // ������������� ������� LinkedList
    }

    // ���������� ������ � ����
    void saveToFile(const string& filename) const {
        list.saveToFile(filename); // ������������� ������� LinkedList
    }

    // ������� �������
    void clear() {
        while (list.head) {
            list.removeHead();
        }
    }
};

#endif