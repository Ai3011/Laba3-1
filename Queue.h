#ifndef QUEUE_H
#define QUEUE_H

#include "List.h"


struct Queue {
    LinkedList list;

    // Добавление элемента в очередь
    void push(const string& element) {
        list.addTail(element);
    }

    // Удаление элемента из очереди
    void pop() {
        list.removeHead();
    }

    // Вывод содержимого очереди
    void read() const {
        list.read();
    }

    // Загрузка данных из файла
    void loadFromFile(const string& filename) {
        list.loadFromFile(filename); // Делегирование функции LinkedList
    }

    // Сохранение данных в файл
    void saveToFile(const string& filename) const {
        list.saveToFile(filename); // Делегирование функции LinkedList
    }

    // Очистка очереди
    void clear() {
        while (list.head) {
            list.removeHead();
        }
    }
};

#endif
