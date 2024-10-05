#include <iostream>
#include <windows.h>
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
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);


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
                cout << "Команды для массива (add, insert, get, remove, replace, read, lenght, save, load, exit): ";
                getline(cin, arrayCommand);

                if (arrayCommand == "add") {
                    string element;
                    cout << "Введите элемент: ";
                    getline(cin, element);
                    arr.add(element);
                }
                else if (arrayCommand == "lenght") {
                    string element;
                    cout << "Длина массива : " << arr.length() << endl;
                }
                else if (arrayCommand == "insert") {
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
                else if (arrayCommand == "get") {
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
                else if (arrayCommand == "remove") {
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
                else if (arrayCommand == "replace") {
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
                else if (arrayCommand == "read") {
                    arr.read();
                }
                else if (arrayCommand == "save") {
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
                else if (arrayCommand == "load") {
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
                else if (arrayCommand == "exit") {
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
                cout << "Команды для односвязного списка (addHead, addTail, removeHead, removeTail, read, find, save, load, exit): ";
                getline(cin, listCommand);

                if (listCommand == "addHead") {
                    string element;
                    cout << "Введите элемент: ";
                    getline(cin, element);
                    linkedList.addHead(element);
                }
                else if (listCommand == "addTail") {
                    string element;
                    cout << "Введите элемент: ";
                    getline(cin, element);
                    linkedList.addTail(element);
                }
                else if (listCommand == "find") {
                    string element;
                    cout << "Введите элемент для поиска: ";
                    getline(cin, element);
                    int index = linkedList.find(element); // Метод теперь возвращает индекс
                    if (index != -1) {
                        cout << "Элемент найден на позиции: " << index << endl;
                    }
                    else {
                        cout << "Элемент не найден." << endl;
                    }
                }
                else if (listCommand == "removeHead") {
                    linkedList.removeHead();
                }
                else if (listCommand == "removeTail") {
                    linkedList.removeTail();
                }
                else if (listCommand == "read") {
                    linkedList.read();
                }
                else if (listCommand == "save") {
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
                else if (listCommand == "load") {
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
                else if (listCommand == "exit") {
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
                cout << "Команды для двусвязного списка (addHead, addTail, removeHead, removeTail, read, find, save, load, exit): ";
                getline(cin, doublyListCommand);

                if (doublyListCommand == "addHead") {
                    string element;
                    cout << "Введите элемент: ";
                    getline(cin, element);
                    doublyLinkedList.addHead(element);
                }
                else if (doublyListCommand == "addTail") {
                    string element;
                    cout << "Введите элемент: ";
                    getline(cin, element);
                    doublyLinkedList.addTail(element);
                }
                else if (doublyListCommand == "removeHead") {
                    doublyLinkedList.removeHead();
                }
                else if (doublyListCommand == "removeTail") {
                    doublyLinkedList.removeTail();
                }
                else if (doublyListCommand == "read") {
                    doublyLinkedList.read();
                }
                else if (doublyListCommand == "find") {
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

                else if (doublyListCommand == "save") {
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
                else if (doublyListCommand == "load") {
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
                else if (doublyListCommand == "exit") {
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
                cout << "Команды для стека (push, pop, read, save, load, exit): ";
                getline(cin, stackCommand);

                if (stackCommand == "push") {
                    string element;
                    cout << "Введите элемент: ";
                    getline(cin, element);
                    stack.push(element);
                }
                else if (stackCommand == "pop") {
                    stack.pop();
                }
                else if (stackCommand == "read") {
                    stack.read();
                }
                else if (stackCommand == "save") {
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
                else if (stackCommand == "load") {
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
                else if (stackCommand == "exit") {
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
                cout << "Команды для очереди (push, pop, read, save, load, exit): ";
                getline(cin, queueCommand);

                if (queueCommand == "push") {
                    string element;
                    cout << "Введите элемент: ";
                    getline(cin, element);
                    queue.push(element);
                }
                else if (queueCommand == "pop") {
                    queue.pop();
                }
                else if (queueCommand == "read") {
                    queue.read();
                }
                else if (queueCommand == "save") {
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
                else if (queueCommand == "load") {
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
                else if (queueCommand == "exit") {
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
                cout << "Команды для AVL-дерева (add, remove, print, save, load, find, exit): ";
                getline(cin, avlCommand);

                if (avlCommand == "add") {
                    int key;
                    cout << "Введите ключ: ";
                    cin >> key;
                    cin.ignore();
                    avlTree = avlInsert(avlTree, key);
                }
                else if (avlCommand == "remove") {
                    int key;
                    cout << "Введите ключ для удаления: ";
                    cin >> key;
                    cin.ignore();
                    avlTree = avlRemove(avlTree, key);
                }
                else if (avlCommand == "print") {
                    cout << "Дерево (по уровням): \n";
                    avlPrintByLevels(avlTree);
                    cout << endl;
                }
                else if (avlCommand == "save") {
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
                else if (avlCommand == "load") {
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
                else if (avlCommand == "find") {
                    int key;
                    cout << "Введите ключ для поиска: ";
                    cin >> key;
                    cin.ignore();
                    AVLNode* found = avlFind(avlTree, key);
                    if (found) {
                        cout << "Элемент с ключом " << key << " найден." << endl;
                    }
                    else {
                        cout << "Элемент с ключом " << key << " не найден." << endl;
                    }
                }
                else if (avlCommand == "exit") {
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
            cout << "Команды для хэш-таблицы (insert, get, remove, clear, print, load, save, exit): ";
            getline(cin, hashTableCommand);

            if (hashTableCommand == "insert") {
                string key, value;
                cout << "Введите ключ: ";
                getline(cin, key);
                cout << "Введите значение: ";
                getline(cin, value);
                insert(ht, key, value);
                cout << "Элемент добавлен." << endl;
            }
            else if (hashTableCommand == "get") {
                string key;
                int index;
                cout << "Введите ключ: ";
                getline(cin, key);
                cout << "Введите индекс узла (1 для первого, 2 для второго и т.д.): ";
                cin >> index;
                cin.ignore(); // Игнорируем оставшийся символ новой строки

                try {
                    string value = get(ht, key, index);
                    cout << "Значение: " << value << endl;
                }
                catch (const runtime_error& e) {
                    cerr << "Ошибка: " << e.what() << endl; // Обработка исключения и вывод сообщения об ошибке
                }
            }
            else if (hashTableCommand == "remove") {
                string key;
                cout << "Введите ключ для удаления: ";
                getline(cin, key);
                remove(ht, key);
                cout << "Элемент удалён." << endl;
            }
            else if (hashTableCommand == "clear") {
                clearHashTable(ht);
                cout << "Хэш-таблица очищена." << endl;
                initHashTable(ht); // Реинициализация после очистки
            }
            else if (hashTableCommand == "print") {
                cout << "Содержимое хэш-таблицы:" << endl;
                printHashTable(ht); // Выводим содержимое хэш-таблицы
            }
            else if (hashTableCommand == "load") {
                string filename;
                cout << "Введите имя файла для загрузки: ";
                getline(cin, filename);
                try {
                    loadFromFile(ht, filename); // Загрузка хэш-таблицы из файла
                    cout << "Хэш-таблица успешно загружена из файла " << filename << endl;
                }
                catch (const runtime_error& e) {
                    cerr << "Ошибка: " << e.what() << endl;
                }
            }
            else if (hashTableCommand == "save") {
                string filename;
                cout << "Введите имя файла для сохранения: ";
                getline(cin, filename);
                try {
                    saveToFileAndClear(ht, filename); // Сохранение в файл
                    cout << "Хэш-таблица успешно сохранена в файл " << filename << endl;
                }
                catch (const runtime_error& e) {
                    cerr << "Ошибка: " << e.what() << endl;
                }
            }
            else if (hashTableCommand == "exit") {
                clearHashTable(ht); // Очистка перед выходом
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