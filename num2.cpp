#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <fstream>
#include <sstream>
using namespace std;

class HashTable {
private:
    struct HashNode {
        string key;
        string value;
    };

    vector<list<HashNode> > table;
    int tableSize;
    hash<string> hashFunction;

    size_t getTableIndex(string &key) {
        size_t hash = hashFunction(key);
        hash = hash % tableSize;
        return hash;
    }

public:
    int size;

    explicit HashTable(int initialSize = 101) : tableSize(initialSize), size(0) {
        if (tableSize == 0) tableSize = 101;
        table.resize(tableSize);
    }

    void insert(string &key, string &value) {
        size_t hashIndex = getTableIndex(key);
        list<HashNode> &chain = table[hashIndex];

        for (HashNode &node: chain) {
            if (node.key == key) {
                node.value = value;
                return;
            }
        }

        chain.push_front({key, value});
        size++;
    }

    bool search(string &key, string &foundValue) {
        size_t hashIndex = getTableIndex(key);
        list<HashNode> &chain = table[hashIndex];
        for (HashNode &node: chain) {
            if (node.key == key) {
                foundValue = node.value;
                return true;
            }
        }
        return false;
    }

    void display() {
        cout << "--- Содержимое Хеш-таблицы ---" << endl;
        for (int i = 0; i < tableSize; ++i) {
            list<HashNode> &chain = table[i];
            bool isEmpty = chain.empty();
            if (isEmpty == false) {
                cout << "[" << i << "]: ";
                for (HashNode &node: chain) {
                    cout << "(" << node.key << ", " << node.value << ") -> ";
                }
                cout << "null";
                cout << endl;
            }
        }
        cout << "-----------------------------" << endl;
    }
};

void loadFromFile(HashTable &phoneBook) {
    ifstream inputFile("phonebook.txt");

    string line, name, number;
    int linesRead = 0;

    while (getline(inputFile, line)) {
        stringstream ss(line);
        ss >> name >> number;

        phoneBook.insert(name, number);
        linesRead++;
    }
    inputFile.close();

    phoneBook.display();
}

int main() {
    setlocale(LC_ALL, "ru_RU.UTF-8");
#ifdef WIN32
    system("chcp 65001"); // Для UTF-8 в консоли Windows
    system("cls");
#endif

    HashTable phoneBook;
    loadFromFile(phoneBook);

    cout << "Введите имя для поиска (или 'exit' для выхода):" << endl;
    string searchName;
    while (true) {
        cout << "> ";
        getline(cin, searchName);

        if (searchName == "exit") break;

        string foundNumber;

        bool isFound = phoneBook.search(searchName, foundNumber);
        if (isFound)
            cout << "Номер телефона: " << foundNumber << endl;
        else cout << "Имя не найдено" << endl;
    }

    cout << "Завершение программы" << endl;
    return 0;
}
