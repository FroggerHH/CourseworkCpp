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

    vector<list<HashNode>> table;
    int tableSize;
    int currentSize;
    hash<string> hashFunction;

    int getTableIndex(const string &key) const {
        return hashFunction(key) % tableSize;
    }

public:
    explicit HashTable(int initialSize = 101) : tableSize(initialSize), currentSize(0) {
        if (tableSize == 0) tableSize = 101;
        table.resize(tableSize);
    }

    // Вставка (сообщение об обновлении убрано для тихой загрузки из файла)
    void insert(const string &key, const string &value) {
        int hashIndex = getTableIndex(key);
        auto &chain = table[hashIndex];

        for (HashNode &node: chain) {
            if (node.key == key) {
                node.value = value; // Обновляем существующий
                return;
            }
        }
        // Добавляем новый
        chain.push_front({key, value});
        currentSize++;
    }

    // Поиск
    bool search(string &key, string &foundValue) {
        int hashIndex = getTableIndex(key);
        list<HashNode> &chain = table[hashIndex];
        for (const auto &node: chain) {
            if (node.key == key) {
                foundValue = node.value;
                return true;
            }
        }
        return false;
    }

    // Отображение (не требуется по Заданию 2, но оставляем)
    void display() {
        cout << "--- Содержимое Хеш-таблицы ---" << endl;
        for (int i = 0; i < table.size(); ++i) {
            if (table[i].empty() == false) {
                cout << "[" << i << "]: ";
                for (HashNode &node: table[i]) {
                    cout << "(" << node.key << ", " << node.value << ") -> ";
                }
                cout << "null";
                cout << endl;
            }
        }
        cout << "-----------------------------" << endl;
    }

    int getSize() {
        return currentSize;
    }
};


int main() {
    setlocale(LC_ALL, "ru_RU.UTF-8");
#ifdef WIN32
    system("chcp 65001"); // Для UTF-8 в консоли Windows
    system("cls");
#endif
    
    HashTable phoneBook;
    ifstream inputFile("phonebook.txt");

    if (!inputFile.is_open()) {
        cerr << "Ошибка: Не удалось открыть файл phonebook.txt" << endl;
        return 1;
    }

    string line, name, number;
    int linesRead = 0;
    // Читаем файл и заполняем хеш-таблицу
    while (getline(inputFile, line)) {
        stringstream ss(line);
        // Простое чтение: первое слово - имя, второе - номер
        // Не обрабатывает имена или номера с пробелами!
        if (ss >> name >> number) {
            phoneBook.insert(name, number);
            linesRead++;
        } else if (!line.empty()) {
            // Игнорируем пустые строки
            cerr << "Предупреждение: Некорректный формат строки в файле: " << line << endl;
        }
    }
    inputFile.close();

    if (linesRead > 0) {
        cout << "Телефонный справочник загружен. Записей: " << phoneBook.getSize() << endl;
        phoneBook.display();
    } else cout << "Телефонный справочник пуст или не удалось прочитать данные." << endl;
    cout << "Введите имя для поиска (или 'exit' для выхода):" << endl;

    string searchName;
    while (true) {
        cout << "> ";
        if (!getline(cin, searchName)) {
            cout << "Ошибка ввода." << endl;
            cin.clear();
            continue;
        }

        if (searchName == "exit") break;

        string foundNumber;

        if (phoneBook.search(searchName, foundNumber))
            cout << "Номер телефона: " << foundNumber << endl;
        else cout << "Имя не найдено" << endl;
    }

    cout << "Завершение программы." << endl;
    return 0;
}
