#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include "Array.h"
#include "List.h"
#include "Dlist.h"
#include "Stack.h"
#include "Queue.h"
#include "AVL.h"
#include "Hash.h"

using namespace std;


int main() {
    setlocale(LC_ALL, "RU");

    StringArray arr;
    LinkedList linkedList;
    DoublyLinkedList doublyLinkedList;
    Stack stack;
    Queue queue;
    AVLNode* avlTree = nullptr;
    HashTable ht;
    initHashTable(ht); // Инициализация хэш-таблицы

    string command;
    while (true) {
        cout << "\nВведите команду (array, list, doubly_list, stack, queue, avl, hashtable, exit): ";
        getline(cin, command);

        // Работа с массивом
        if (command == "array") {
            string arrayCommand;
            while (true) {
                cout << "Команды для массива (MPUSH, MINSERT, MGET, MREMOVE, MREPLACE, PRINT, MLENGHT, SAVE, LOAD, EXIT): ";
                getline(cin, arrayCommand);

                if (arrayCommand == "MPUSH") {
                    string element;
                    cout << "Введите элемент: ";
                    getline(cin, element);
                    arr.add(element);
                }
                else if (arrayCommand == "MLENGHT") {
                    string element;
                    cout << "Длина массива : " << arr.length() << endl;
                }
                else if (arrayCommand == "MINSERT") {
                    size_t index;
                    string element;
                    cout << "Введите индекс и элемент: ";
                    cin >> index;
                    cin.ignore();
                    getline(cin, element);
                    try {
                        arr.insert(index, element);
                    }
                    catch (const exception& e) {
                        cerr << "Ошибка: " << e.what() << endl;
                    }
                }
                else if (arrayCommand == "MGET") {
                    size_t index;
                    cout << "Введите индекс: ";
                    cin >> index;
                    cin.ignore();
                    try {
                        cout << "Элемент: " << arr.get(index) << endl;
                    }
                    catch (const exception& e) {
                        cerr << "Ошибка: " << e.what() << endl;
                    }
                }
                else if (arrayCommand == "MREMOVE") {
                    size_t index;
                    cout << "Введите индекс: ";
                    cin >> index;
                    cin.ignore();
                    try {
                        arr.remove(index);
                    }
                    catch (const exception& e) {
                        cerr << "Ошибка: " << e.what() << endl;
                    }
                }
                else if (arrayCommand == "MREPLACE") {
                    size_t index;
                    string element;
                    cout << "Введите индекс и элемент: ";
                    cin >> index;
                    cin.ignore();
                    getline(cin, element);
                    try {
                        arr.replace(index, element);
                    }
                    catch (const exception& e) {
                        cerr << "Ошибка: " << e.what() << endl;
                    }
                }
                else if (arrayCommand == "PRINT") {
                    arr.read();
                }
                else if (arrayCommand == "SAVE") {
                    string saveFilename;
                    cout << "Введите имя файла для сохранения: ";
                    getline(cin, saveFilename);
                    try {
                        arr.saveToFile(saveFilename);
                        cout << "Данные сохранены в файл." << endl;
                    }
                    catch (const exception& e) {
                        cerr << "Ошибка: " << e.what() << endl;
                    }
                }
                else if (arrayCommand == "LOAD") {
                    string loadFilename;
                    cout << "Введите имя файла для загрузки: ";
                    getline(cin, loadFilename);
                    try {
                        arr.loadFromFile(loadFilename);
                        cout << "Данные загружены из файла." << endl;
                    }
                    catch (const exception& e) {
                        cerr << "Ошибка: " << e.what() << endl;
                    }
                }
                else if (arrayCommand == "EXIT") {
                    break;
                }
                else {
                    cout << "Неизвестная команда." << endl;
                }
            }
        }
        // Работа с односвязным списком
        else if (command == "list") {
            string listCommand;
            while (true) {
                cout << "Команды для односвязного списка (LPUSHHEAD, LPUSHTAIL, LDELHEAD, LDELTAIL, PRINT, LFIND, SAVE, LOAD, EXIT): ";
                getline(cin, listCommand);

                if (listCommand == "LPUSHHEAD") {
                    string element;
                    cout << "Введите элемент: ";
                    getline(cin, element);
                    linkedList.addHead(element);
                }
                else if (listCommand == "LPUSHTAIL") {
                    string element;
                    cout << "Введите элемент: ";
                    getline(cin, element);
                    linkedList.addTail(element);
                }
                else if (listCommand == "LFIND") {
                    string element;
                    cout << "Введите элемент для поиска: ";
                    getline(cin, element);
                    int index = linkedList.find(element); 
                    if (index != -1) {
                        cout << "Элемент найден на позиции: " << index << endl;
                    }
                    else {
                        cout << "Элемент не найден." << endl;
                    }
                }
                else if (listCommand == "LDELHEAD") {
                    linkedList.removeHead();
                }
                else if (listCommand == "LDELTAIL") {
                    linkedList.removeTail();
                }
                else if (listCommand == "LDELVALUE") {  // Команда для удаления по значению
                    string element;
                    cout << "Введите элемент для удаления: ";
                    getline(cin, element);
                    bool removed = linkedList.removeByValue(element); // Удаляем элемент по значению
                    if (removed) {
                        cout << "Элемент '" << element << "' был удален." << endl;
                    } else {
                        cout << "Элемент '" << element << "' не найден." << endl;
                    }
                } 
                else if (listCommand == "PRINT") {
                    linkedList.read();
                }
                else if (listCommand == "SAVE") {
                    string saveFilename;
                    cout << "Введите имя файла для сохранения: ";
                    getline(cin, saveFilename);
                    try {
                        linkedList.saveToFile(saveFilename);
                        cout << "Данные сохранены в файл." << endl;
                    }
                    catch (const exception& e) {
                        cerr << "Ошибка: " << e.what() << endl;
                    }
                }
                else if (listCommand == "LOAD") {
                    string loadFilename;
                    cout << "Введите имя файла для загрузки: ";
                    getline(cin, loadFilename);
                    try {
                        linkedList.loadFromFile(loadFilename);
                        cout << "Данные загружены из файла." << endl;
                    }
                    catch (const exception& e) {
                        cerr << "Ошибка: " << e.what() << endl;
                    }
                }
                else if (listCommand == "EXIT") {
                    break;
                }
                else {
                    cout << "Неизвестная команда." << endl;
                }
            }
        }
        //Двусвязный список
        else if (command == "doubly_list") {
            string doublyListCommand;
            while (true) {
                cout << "Команды для двусвязного списка (DLPUSHHEAD, DLPUSHTAIL, DLDELHEAD, DLDELTAIL, PRINT, DLFIND, DLDELVALUE, SAVE, LOAD, EXIT): ";
                getline(cin, doublyListCommand);

                if (doublyListCommand == "DLPUSHHEAD") {
                    string element;
                    cout << "Введите элемент: ";
                    getline(cin, element);
                    doublyLinkedList.addHead(element);
                }
                else if (doublyListCommand == "DLPUSHTAIL") {
                    string element;
                    cout << "Введите элемент: ";
                    getline(cin, element);
                    doublyLinkedList.addTail(element);
                }
                else if (doublyListCommand == "DLDELHEAD") {
                    doublyLinkedList.removeHead();
                }
                else if (doublyListCommand == "DLDELTAIL") {
                    doublyLinkedList.removeTail();
                }
                else if (doublyListCommand == "DDELVALUE") {  // Команда для удаления по значению
                    string element;
                    cout << "Введите элемент для удаления: ";
                    getline(cin, element); 
                    bool removed = doublyLinkedList.removeValue(element); // Удаляем элемент по значению
                    if (removed) {
                        cout << "Элемент '" << element << "' был удален." << endl;
                    } else {
                        cout << "Элемент '" << element << "' не найден." << endl;
                    }
                } 

                else if (doublyListCommand == "PRINT") {
                    doublyLinkedList.read();
                }
                else if (doublyListCommand == "DLFIND") {
                    string element;
                    cout << "Введите элемент для поиска: ";
                    getline(cin, element);
                    int index = doublyLinkedList.find(element); // Метод теперь возвращает индекс
                    if (index != -1) {
                        cout << "Элемент найден на позиции: " << index << endl;
                    }
                    else {
                        cout << "Элемент не найден." << endl;
                    }
                }

                else if (doublyListCommand == "SAVE") {
                    string saveFilename;
                    cout << "Введите имя файла для сохранения: ";
                    getline(cin, saveFilename);
                    try {
                        doublyLinkedList.saveToFile(saveFilename);
                        cout << "Данные сохранены в файл." << endl;
                    }
                    catch (const exception& e) {
                        cerr << "Ошибка: " << e.what() << endl;
                    }
                }
                else if (doublyListCommand == "LOAD") {
                    string loadFilename;
                    cout << "Введите имя файла для загрузки: ";
                    getline(cin, loadFilename);
                    try {
                        doublyLinkedList.loadFromFile(loadFilename);
                        cout << "Данные загружены из файла." << endl;
                    }
                    catch (const exception& e) {
                        cerr << "Ошибка: " << e.what() << endl;
                    }
                }
                else if (doublyListCommand == "EXIT") {
                    break;
                }
                else {
                    cout << "Неизвестная команда." << endl;
                }
            }
        }
        //Стек
        else if (command == "stack") {
            string stackCommand;
            while (true) {
                cout << "Команды для стека (SPUSH, SPOP, PRINT, SAVE, LOAD, EXIT): ";
                getline(cin, stackCommand);

                if (stackCommand == "SPUSH") {
                    string element;
                    cout << "Введите элемент: ";
                    getline(cin, element);
                    stack.push(element);
                }
                else if (stackCommand == "SPOP") {
                    stack.pop();
                }
                else if (stackCommand == "PRINT") {
                    stack.read();
                }
                else if (stackCommand == "SAVE") {
                    string saveFilename;
                    cout << "Введите имя файла для сохранения: ";
                    getline(cin, saveFilename);
                    try {
                        stack.saveToFile(saveFilename);
                        cout << "Данные сохранены в файл." << endl;
                    }
                    catch (const exception& e) {
                        cerr << "Ошибка: " << e.what() << endl;
                    }
                }
                else if (stackCommand == "LOAD") {
                    string loadFilename;
                    cout << "Введите имя файла для загрузки: ";
                    getline(cin, loadFilename);
                    try {
                        stack.loadFromFile(loadFilename);
                        cout << "Данные загружены из файла." << endl;
                    }
                    catch (const exception& e) {
                        cerr << "Ошибка: " << e.what() << endl;
                    }
                }
                else if (stackCommand == "EXIT") {
                    break;
                }
                else {
                    cout << "Неизвестная команда." << endl;
                }
            }
        }
        //Очередь
        else if (command == "queue") {
            string queueCommand;
            while (true) {
                cout << "Команды для очереди (QPUSH, QPOP, PRINT, SAVE, LOAD, EXIT): ";
                getline(cin, queueCommand);

                if (queueCommand == "QPUSH") {
                    string element;
                    cout << "Введите элемент: ";
                    getline(cin, element);
                    queue.push(element);
                }
                else if (queueCommand == "QPOP") {
                    queue.pop();
                }
                else if (queueCommand == "PRINT") {
                    queue.read();
                }
                else if (queueCommand == "SAVE") {
                    string saveFilename;
                    cout << "Введите имя файла для сохранения: ";
                    getline(cin, saveFilename);
                    try {
                        queue.saveToFile(saveFilename);
                        cout << "Данные сохранены в файл." << endl;
                    }
                    catch (const exception& e) {
                        cerr << "Ошибка: " << e.what() << endl;
                    }
                }
                else if (queueCommand == "LOAD") {
                    string loadFilename;
                    cout << "Введите имя файла для загрузки: ";
                    getline(cin, loadFilename);
                    try {
                        queue.loadFromFile(loadFilename);
                        cout << "Данные загружены из файла." << endl;
                    }
                    catch (const exception& e) {
                        cerr << "Ошибка: " << e.what() << endl;
                    }
                }
                else if (queueCommand == "EXIT") {
                    break;
                }
                else {
                    cout << "Неизвестная команда." << endl;
                }
            }
        }
        else if (command == "avl") {
        string avlCommand;
        while (true) {
            cout << "Команды для AVL-дерева (TINSERT, TDEL, PRINT, SAVE, LOAD, TFIND, EXIT): ";
            getline(cin, avlCommand);

            if (avlCommand == "TINSERT") {
                string input;
                int key;
                cout << "Введите ключ: ";
                while (true) {
                    getline(cin, input);
                    stringstream ss(input);
                    if (ss >> key && ss.eof()) { // Проверяем, удалось ли успешно считать целое число и это конец строки
                        break; // Выходим из цикла, если ввод корректный
                    }
                    else {
                        cout << "Неверный ввод. Пожалуйста, введите целое число: ";
                    }
                }
                avlTree = avlInsert(avlTree, key);
            }
            else if (avlCommand == "TDEL") {
                string input;
                int key;
                cout << "Введите ключ для удаления: ";
                while (true) {
                    getline(cin, input);
                    stringstream ss(input);
                    if (ss >> key && ss.eof()) { // Проверяем, удалось ли успешно считать целое число и это конец строки
                        break; // Выходим из цикла, если ввод корректный
                    }
                    else {
                        cout << "Неверный ввод. Пожалуйста, введите целое число: ";
                    }
                }
                avlTree = avlRemove(avlTree, key);
            }
            else if (avlCommand == "PRINT") {
                cout << "Дерево (по уровням): \n";
                avlPrintByLevels(avlTree);
                cout << endl;
            }
            else if (avlCommand == "SAVE") {
                string filename;
                cout << "Введите имя файла для сохранения: ";
                getline(cin, filename);
                ofstream file(filename);
                if (file.is_open()) {
                    avlSaveToFile(avlTree, file);
                    file.close();
                    cout << "Дерево сохранено в файл." << endl;
                }
                else {
                    cout << "Ошибка открытия файла!" << endl;
                }
            }
            else if (avlCommand == "LOAD") {
                string filename;
                cout << "Введите имя файла для загрузки: ";
                getline(cin, filename);
                ifstream file(filename);
                if (file.is_open()) {
                    avlTree = avlLoadFromFile(avlTree, file);
                    file.close();
                    cout << "Дерево загружено из файла." << endl;
                }
                else {
                    cout << "Ошибка открытия файла!" << endl;
                }
            }
            else if (avlCommand == "TFIND") {
                string input;
                int key;
                cout << "Введите ключ для поиска: ";
                while (true) {
                    getline(cin, input);
                    stringstream ss(input);
                    if (ss >> key && ss.eof()) { // Проверяем, удалось ли успешно считать целое число и это конец строки
                        break; // Выходим из цикла, если ввод корректный
                    }
                    else {
                        cout << "Неверный ввод. Пожалуйста, введите целое число: ";
                    }
                }
                AVLNode* found = avlFind(avlTree, key);
                if (found) {
                    cout << "Элемент с ключом " << key << " найден." << endl;
                }
                else {
                    cout << "Элемент с ключом " << key << " не найден." << endl;
                }
            }
            else if (avlCommand == "EXIT") {
                break;
            }
            else {
                cout << "Неизвестная команда." << endl;
            }
        }
}

        // Хэш-таблица
        else if (command == "hashtable") {
        string hashTableCommand;
        while (true) {
            cout << "Команды для хэш-таблицы (HSET, HGET, HREMOVE, HCLEAR, PRINT, LOAD, SAVE, EXIT): ";
            getline(cin, hashTableCommand);

            if (hashTableCommand == "HSET") {
                string key, value;
                cout << "Введите ключ: ";
                getline(cin, key);
                cout << "Введите значение: ";
                getline(cin, value);
                insert(ht, key, value);
            }
            else if (hashTableCommand == "HGET") {
                string key;
                cout << "Введите ключ: ";
                getline(cin, key);

                string value = get(ht, key);
                if (value != "") {
                    cout << "Значение: " << value << endl;
                }
                else {
                    cout << "Элемент не найден." << endl;
                }
            }
            else if (hashTableCommand == "HREMOVE") {
                string key;
                cout << "Введите ключ для удаления: ";
                getline(cin, key);
                remove(ht, key);
                cout << "Элемент удалён." << endl;
            }
            else if (hashTableCommand == "PRINT") {
                cout << "Содержимое хэш-таблицы:" << endl;
                printHashTable(ht);
            }
            else if (hashTableCommand == "LOAD") {
                string filename;
                cout << "Введите имя файла для загрузки: ";
                getline(cin, filename);
                try {
                    loadFromFile(ht, filename);
                    cout << "Хэш-таблица успешно загружена из файла " << filename << endl;
                }
                catch (const runtime_error& e) {
                    cerr << "Ошибка: " << e.what() << endl;
                }
            }
            else if (hashTableCommand == "SAVE") {
                string filename;
                cout << "Введите имя файла для сохранения: ";
                getline(cin, filename);
                try {
                    saveToFileAndClear(ht, filename);
                    cout << "Хэш-таблица успешно сохранена в файл " << filename << endl;
                }
                catch (const runtime_error& e) {
                    cerr << "Ошибка: " << e.what() << endl;
                }
            }
            else if (hashTableCommand == "EXIT") {
                clearHashTable(ht);
                break;
            }
            else {
                cout << "Неизвестная команда." << endl;
            }
        }
}

        // Завершение программы
        else if (command == "exit") {
        break;
        }
        else {
        cout << "Неизвестная команда." << endl;
        }
    }

    return 0;
}
