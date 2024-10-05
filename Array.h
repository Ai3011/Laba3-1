#ifndef ARRAY_H
#define ARRAY_H

#include <iostream>
#include <fstream>
#include <stdexcept>
#include <string>

using namespace std;

// Структура для динамического массива строк
struct StringArray {
    string* data;      // Указатель на массив строк
    size_t size;       // Текущий размер массива (количество элементов)
    size_t capacity;   // Вместимость массива (максимальное количество элементов)

    // Конструктор, инициализирующий массив заданной начальной вместимости
    StringArray(size_t initialCapacity = 10) : size(0), capacity(initialCapacity) {
        data = new string[capacity]; // Выделение памяти для массива
    }

    // Деструктор для освобождения памяти
    ~StringArray() {
        delete[] data; // Освобождаем память, выделенную под массив строк
    }

    // Метод для добавления элемента в массив
    void add(const string& element) {
        if (size >= capacity) resize(); // Увеличиваем размер массива, если он заполнен
        data[size++] = element; // Добавляем элемент и увеличиваем размер
    }

    // Метод для вставки элемента по индексу
    void insert(size_t index, const string& element) {
        if (index > size) throw out_of_range("Index out of range"); // Проверка на допустимый индекс
        if (size >= capacity) resize(); // Увеличиваем размер массива, если он заполнен
        for (size_t i = size; i > index; --i) { // Сдвигаем элементы вправо, чтобы освободить место
            data[i] = data[i - 1];
        }
        data[index] = element; // Вставляем новый элемент
        ++size; // Увеличиваем размер массива
    }

    // Метод для получения элемента по индексу
    string get(size_t index) const {
        if (index >= size) throw out_of_range("Index out of range"); // Проверка на допустимый индекс
        return data[index]; // Возвращаем элемент по индексу
    }

    // Метод для удаления элемента по индексу
    void remove(size_t index) {
        if (index >= size) throw out_of_range("Index out of range"); // Проверка на допустимый индекс
        for (size_t i = index; i < size - 1; ++i) { // Сдвигаем элементы влево, чтобы удалить элемент
            data[i] = data[i + 1];
        }
        --size; // Уменьшаем размер массива
    }

    // Метод для замены элемента по индексу
    void replace(size_t index, const string& element) {
        if (index >= size) throw out_of_range("Index out of range"); // Проверка на допустимый индекс
        data[index] = element; // Заменяем элемент по индексу
    }

    // Метод для получения текущего размера массива
    size_t length() const {
        return size; // Возвращаем количество элементов в массиве
    }

    // Метод для вывода содержимого массива
    void read() const {
        for (size_t i = 0; i < size; ++i) {
            cout << i << ": " << data[i] << endl; // Выводим индекс и значение элемента
        }
    }

    // Метод для очистки массива (сброс размера до 0)
    void clear() {
        size = 0; // Сбрасываем размер
    }

    // Метод для загрузки данных из файла в массив
    void loadFromFile(const string& filename) {
        clear(); // Очищаем массив перед загрузкой
        ifstream file(filename); // Открываем файл для чтения
        if (!file.is_open()) throw runtime_error("Unable to open file"); // Проверка успешного открытия файла
        string line;
        while (getline(file, line)) add(line); // Читаем строки из файла и добавляем их в массив
        file.close(); // Закрываем файл
    }

    // Метод для сохранения данных из массива в файл
    void saveToFile(const string& filename) const {
        ofstream file(filename); // Открываем файл для записи
        if (!file.is_open()) throw runtime_error("Unable to open file"); // Проверка успешного открытия файла
        for (size_t i = 0; i < size; ++i) {
            file << data[i] << endl; // Записываем элементы массива в файл
        }
        file.close(); // Закрываем файл
        const_cast<StringArray*>(this)->clear(); // Очищаем массив после сохранения
    }

    // Метод для изменения размера массива
    void resize() {
        capacity *= 2; // Увеличиваем вместимость в 2 раза
        string* newData = new string[capacity]; // Выделяем новую память для увеличенного массива
        for (size_t i = 0; i < size; ++i) { // Копируем данные в новый массив
            newData[i] = data[i];
        }
        delete[] data; // Освобождаем старый массив
        data = newData; // Обновляем указатель на массив
    }
};

#endif
