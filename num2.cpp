#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <fstream>
#include <sstream>

class HashTable {
private:
    struct HashNode {
        std::string key;
        std::string value;
    };

    std::vector<std::list<HashNode> > table;
    size_t tableSize;
    size_t currentSize;
    std::hash<std::string> hashFunction;

    size_t getTableIndex(const std::string &key) const {
        return hashFunction(key) % tableSize;
    }

public:
    explicit HashTable(size_t initialSize = 101) : tableSize(initialSize), currentSize(0) {
        if (tableSize == 0) tableSize = 101;
        table.resize(tableSize);
    }

    // Вставка (сообщение об обновлении убрано для тихой загрузки из файла)
    void insert(const std::string &key, const std::string &value) {
        size_t hashIndex = getTableIndex(key);
        auto &chain = table[hashIndex];

        for (auto &node: chain) {
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
    bool search(const std::string &key, std::string &foundValue) const {
        size_t hashIndex = getTableIndex(key);
        const auto &chain = table[hashIndex];
        for (const auto &node: chain) {
            if (node.key == key) {
                foundValue = node.value;
                return true;
            }
        }
        return false;
    }

    // Отображение (не требуется по Заданию 2, но оставляем)
    void display() const {
        std::cout << "--- Содержимое Хеш-таблицы ---" << std::endl;
        for (size_t i = 0; i < table.size(); ++i) {
            std::cout << "[" << i << "]: ";
            if (table[i].empty()) {
                std::cout << "(пусто)";
            } else {
                for (const auto &node: table[i]) {
                    std::cout << "(" << node.key << ", " << node.value << ") -> ";
                }
                std::cout << "null";
            }
            std::cout << std::endl;
        }
        std::cout << "-----------------------------" << std::endl;
    }

    size_t getSize() const {
        return currentSize;
    }
};


int main() {
    setlocale(LC_ALL, "ru_RU.UTF-8");
#ifdef WIN32
    system("chcp 65001");
#endif

    HashTable phoneBook;
    std::ifstream inputFile("phonebook.txt");

    if (!inputFile.is_open()) {
        std::cerr << "Ошибка: Не удалось открыть файл phonebook.txt" << std::endl;
        return 1;
    }

    std::string line, name, number;
    int linesRead = 0;
    // Читаем файл и заполняем хеш-таблицу
    while (std::getline(inputFile, line)) {
        std::stringstream ss(line);
        // Простое чтение: первое слово - имя, второе - номер
        // Не обрабатывает имена или номера с пробелами!
        if (ss >> name >> number) {
            phoneBook.insert(name, number);
            linesRead++;
        } else if (!line.empty()) {
            // Игнорируем пустые строки
            std::cerr << "Предупреждение: Некорректный формат строки в файле: " << line << std::endl;
        }
    }
    inputFile.close();

    if (linesRead > 0) {
        std::cout << "Телефонный справочник загружен. Записей: " << phoneBook.getSize() << std::endl;
        phoneBook.display();
    } else std::cout << "Телефонный справочник пуст или не удалось прочитать данные." << std::endl;
    std::cout << "Введите имя для поиска (или 'exit' для выхода):" << std::endl;

    std::string searchName;
    while (true) {
        std::cout << "> ";
        if (!getline(std::cin, searchName)) {
            std::cout << "Ошибка ввода." << std::endl;
            std::cin.clear();
            continue;
        }

        if (searchName == "exit") break;

        std::string foundNumber;

        if (phoneBook.search(searchName, foundNumber))
            std::cout << "Номер телефона: " << foundNumber << std::endl;
        else std::cout << "Имя не найдено" << std::endl;
    }

    std::cout << "Завершение программы." << std::endl;
    return 0;
}
