#ifndef ARRAY_H
#define ARRAY_H

#include <iostream>
#include <fstream>
#include <stdexcept>
#include <string>

using namespace std;

// ��������� ��� ������������� ������� �����
struct StringArray {
    string* data;      // ��������� �� ������ �����
    size_t size;       // ������� ������ ������� (���������� ���������)
    size_t capacity;   // ����������� ������� (������������ ���������� ���������)

    // �����������, ���������������� ������ �������� ��������� �����������
    StringArray(size_t initialCapacity = 10) : size(0), capacity(initialCapacity) {
        data = new string[capacity]; // ��������� ������ ��� �������
    }

    // ���������� ��� ������������ ������
    ~StringArray() {
        delete[] data; // ����������� ������, ���������� ��� ������ �����
    }

    // ����� ��� ���������� �������� � ������
    void add(const string& element) {
        if (size >= capacity) resize(); // ����������� ������ �������, ���� �� ��������
        data[size++] = element; // ��������� ������� � ����������� ������
    }

    // ����� ��� ������� �������� �� �������
    void insert(size_t index, const string& element) {
        if (index > size) throw out_of_range("Index out of range"); // �������� �� ���������� ������
        if (size >= capacity) resize(); // ����������� ������ �������, ���� �� ��������
        for (size_t i = size; i > index; --i) { // �������� �������� ������, ����� ���������� �����
            data[i] = data[i - 1];
        }
        data[index] = element; // ��������� ����� �������
        ++size; // ����������� ������ �������
    }

    // ����� ��� ��������� �������� �� �������
    string get(size_t index) const {
        if (index >= size) throw out_of_range("Index out of range"); // �������� �� ���������� ������
        return data[index]; // ���������� ������� �� �������
    }

    // ����� ��� �������� �������� �� �������
    void remove(size_t index) {
        if (index >= size) throw out_of_range("Index out of range"); // �������� �� ���������� ������
        for (size_t i = index; i < size - 1; ++i) { // �������� �������� �����, ����� ������� �������
            data[i] = data[i + 1];
        }
        --size; // ��������� ������ �������
    }

    // ����� ��� ������ �������� �� �������
    void replace(size_t index, const string& element) {
        if (index >= size) throw out_of_range("Index out of range"); // �������� �� ���������� ������
        data[index] = element; // �������� ������� �� �������
    }

    // ����� ��� ��������� �������� ������� �������
    size_t length() const {
        return size; // ���������� ���������� ��������� � �������
    }

    // ����� ��� ������ ����������� �������
    void read() const {
        for (size_t i = 0; i < size; ++i) {
            cout << i << ": " << data[i] << endl; // ������� ������ � �������� ��������
        }
    }

    // ����� ��� ������� ������� (����� ������� �� 0)
    void clear() {
        size = 0; // ���������� ������
    }

    // ����� ��� �������� ������ �� ����� � ������
    void loadFromFile(const string& filename) {
        clear(); // ������� ������ ����� ���������
        ifstream file(filename); // ��������� ���� ��� ������
        if (!file.is_open()) throw runtime_error("Unable to open file"); // �������� ��������� �������� �����
        string line;
        while (getline(file, line)) add(line); // ������ ������ �� ����� � ��������� �� � ������
        file.close(); // ��������� ����
    }

    // ����� ��� ���������� ������ �� ������� � ����
    void saveToFile(const string& filename) const {
        ofstream file(filename); // ��������� ���� ��� ������
        if (!file.is_open()) throw runtime_error("Unable to open file"); // �������� ��������� �������� �����
        for (size_t i = 0; i < size; ++i) {
            file << data[i] << endl; // ���������� �������� ������� � ����
        }
        file.close(); // ��������� ����
        const_cast<StringArray*>(this)->clear(); // ������� ������ ����� ����������
    }

    // ����� ��� ��������� ������� �������
    void resize() {
        capacity *= 2; // ����������� ����������� � 2 ����
        string* newData = new string[capacity]; // �������� ����� ������ ��� ������������ �������
        for (size_t i = 0; i < size; ++i) { // �������� ������ � ����� ������
            newData[i] = data[i];
        }
        delete[] data; // ����������� ������ ������
        data = newData; // ��������� ��������� �� ������
    }
};

#endif
