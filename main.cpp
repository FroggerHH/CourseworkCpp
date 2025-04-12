#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <functional>
#include <stdexcept>
#include <limits>
using namespace std;

template<typename KeyType, typename ValueType, typename Hasher = hash<KeyType> >
class HashTable {
private:
    struct HashNode {
        KeyType key;
        ValueType value;
    };

    vector<list<HashNode> > table{};
    size_t tableSize;
    size_t currentSize;
    Hasher hashFunction;

    // Получение индекса в таблице по ключу
    size_t getTableIndex(const KeyType &key) const {
        return hashFunction(key) % tableSize;
    }

public:
    explicit HashTable(const size_t initialSize = 101) : tableSize(initialSize), currentSize(0) {
        if (tableSize == 0) tableSize = 101;
        table.resize(tableSize);
    }

    void insert(const KeyType &key, const ValueType &value) {
        size_t hashIndex = getTableIndex(key);
        list<HashNode> &chain = table[hashIndex];

        for (HashNode &node: chain) {
            if (node.key == key) {
                node.value = value;
                cout << "Ключ '" << key << "' уже существует. Значение обновлено на " << value << "." << endl;
                return;
            }
        }

        chain.push_front({key, value});
        currentSize++;
        cout << "Элемент (" << key << ", " << value << ") добавлен." << endl;
    }

    bool search(const KeyType &key, ValueType &foundValue) const {
        size_t hashIndex = getTableIndex(key);
        const list<HashNode> &chain = table[hashIndex]; // Получаем константную ссылку

        for (const auto &node: chain) {
            if (node.key == key) {
                foundValue = node.value; // Записываем найденное значение
                return true;
            }
        }
        // Ключ не найден
        return false;
    }

    bool remove(const KeyType &key) {
        size_t hashIndex = getTableIndex(key);
        list<HashNode> &chain = table[hashIndex];

        for (auto it = chain.begin(); it != chain.end(); ++it) {
            if (it->key == key) {
                chain.erase(it); // Удаляем узел из списка
                currentSize--;
                cout << "Элемент с ключом '" << key << "' удален." << endl;
                return true;
            }
        }

        cout << "Элемент с ключом '" << key << "' не найден для удаления." << endl;
        return false;
    }

    void display() const {
        cout << "--- Содержимое Хеш-таблицы ---" << endl;
        for (size_t i = 0; i < table.size(); ++i) {
            cout << "[" << i << "]: ";
            if (table[i].empty()) cout << "(пусто)";
            else {
                for (const auto &node: table[i])
                    cout << "(" << node.key << ", " << node.value << ") -> ";
                cout << "null";
            }
            cout << endl;
        }
        cout << "-----------------------------" << endl;
    }

    size_t getSize() const { return currentSize; }
};

template<typename T>
class BinaryHeap {
private:
    vector<T> heap{};

    static int parent(const int i) { return (i - 1) / 2; }
    static int leftChild(const int i) { return 2 * i + 1; }
    static int rightChild(const int i) { return 2 * i + 2; }

    // Просеивание вверх
    void siftUp(int i) {
        // Пока не дошли до корня и текущий элемент БОЛЬШЕ родителя
        while (i > 0 && heap[i] > heap[parent(i)]) {
            swap(heap[i], heap[parent(i)]);
            i = parent(i); // Переходим на позицию родителя
        }
    }

    // Просеивание вниз
    void siftDown(int i) {
        int maxIndex = i; // Индекс наибольшего элемента (сначала текущий)

        int l = leftChild(i);
        // Если левый потомок существует и он БОЛЬШЕ текущего максимума
        if (l < heap.size() && heap[l] > heap[maxIndex]) maxIndex = l;

        int r = rightChild(i);
        // Если правый потомок существует и он БОЛЬШЕ текущего максимума
        if (r < heap.size() && heap[r] > heap[maxIndex]) maxIndex = r;

        // Если наибольший элемент не текущий, меняем и продолжаем просеивание
        if (i != maxIndex) {
            swap(heap[i], heap[maxIndex]);
            siftDown(maxIndex); // Рекурсивно для новой позиции
        }
    }

public:
    BinaryHeap() = default;

    bool isEmpty() const { return heap.empty(); }

    void insert(const T &value) {
        heap.push_back(value); // Добавляем в конец
        siftUp(heap.size() - 1); // Восстанавливаем свойство кучи просеиванием вверх
        cout << "Элемент " << value << " добавлен. ";
    }

    // Просмотр максимального элемента (без удаления)
    T peekMax() const {
        if (isEmpty()) throw runtime_error("Куча пуста (peekMax)");
        return heap[0]; // Максимальный элемент всегда в корне
    }

    // Извлечение максимального элемента
    T extractMax() {
        if (isEmpty()) throw runtime_error("Куча пуста (extractMax)");
        T result = heap[0]; // Запоминаем максимальный элемент

        // Перемещаем последний элемент в корень
        heap[0] = heap.back();
        heap.pop_back(); // Удаляем последний элемент

        // Если куча не пуста, восстанавливаем свойство просеиванием вниз
        if (!isEmpty()) siftDown(0);
        cout << "Извлечен максимальный элемент: " << result << ". ";
        return result;
    }

    void displayState() const {
        cout << "Куча: [";
        if (isEmpty())cout << "(пусто)";
        else
            for (size_t i = 0; i < heap.size(); ++i)
                cout << heap[i] << (i == heap.size() - 1 ? "" : ", ");
        cout << "]" << endl;
    }

    // Получение текущего количества элементов
    size_t getSize() const { return heap.size(); }
};

void clearInputBuffer() { cin.ignore(numeric_limits<streamsize>::max(), '\n'); }

// Интерфейс хеш таблицы
void runHashTable() {
    // Используем строки как ключи и целые числа как значения
    HashTable<string, int> hash_table{};
    string command, key;
    int value;

    cout << "\n--- Меню Хеш-таблицы ---" << endl;
    cout << "Команды: insert <key> <value>, search <key>, remove <key>, display, size, back" << endl;

    while (true) {
        cout << "HashTable> ";
        cin >> command;

        if (command == "insert") {
            if (!(cin >> key >> value)) {
                cout << "Ошибка ввода для insert. Ожидается: <key> <value>" << endl;
                cin.clear(); // Сброс флагов ошибок
                clearInputBuffer();
                continue;
            }
            hash_table.insert(key, value);
        } else if (command == "search") {
            if (!(cin >> key)) {
                cout << "Ошибка ввода для search. Ожидается: <key>" << endl;
                cin.clear();
                clearInputBuffer();
                continue;
            }
            int foundValue;
            if (hash_table.search(key, foundValue))
                cout << "Найдено значение: " << foundValue << endl;
            else cout << "Ключ '" << key << "' не найден." << endl;
        } else if (command == "remove") {
            if (!(cin >> key)) {
                cout << "Ошибка ввода для remove. Ожидается: <key>" << endl;
                cin.clear();
                clearInputBuffer();
                continue;
            }
            hash_table.remove(key);
        } else if (command == "display") hash_table.display();
        else if (command == "size")
            cout << "Текущий размер таблицы: " << hash_table.getSize() << endl;
        else if (command == "back") break; // Выход из меню
        else {
            cout << "Неизвестная команда." << endl;
            clearInputBuffer();
        }
    }
}

// Интерфейс двоичной кучи
void runBinaryHeap() {
    BinaryHeap<int> binary_heap;
    string command;
    int value;

    cout << "\n--- Меню Двоичной кучи (Max-Heap) ---" << endl;
    cout << "Команды: insert <value>, extractMax, peekMax, display, size, back" << endl;

    while (true) {
        cout << "MaxHeap> ";
        cin >> command;

        try {
            if (command == "insert") {
                if (!(cin >> value)) {
                    cout << "Ошибка ввода для insert. Ожидается: <value>" << endl;
                    cin.clear();
                    clearInputBuffer();
                    continue;
                }
                binary_heap.insert(value);
            } else if (command == "extractMax") binary_heap.extractMax();
            else if (command == "peekMax")
                cout << "Максимальный элемент: " << binary_heap.peekMax() << endl;
            else if (command == "display") binary_heap.displayState();
            else if (command == "size")
                cout << "Текущий размер кучи: " << binary_heap.getSize() << endl;
            else if (command == "back") break; // Выход из меню
            else {
                cout << "Неизвестная команда." << endl;
                clearInputBuffer();
            }
        } catch (const runtime_error &e) {
            cerr << "Ошибка: " << e.what() << endl;
            if (command != "back" && command != "display" && command != "size")
                clearInputBuffer();
        } catch (const exception &e) {
            cerr << "Произошла ошибка: " << e.what() << endl;
            clearInputBuffer();
        }
    }
}

int main() {
    int choice;
    while (true) {
        cout << "Выберите структуру данных:" << endl;
        cout << "1. Хеш-таблица" << endl;
        cout << "2. Двоичная куча (Max-Heap)" << endl;
        cout << "0. Выход" << endl;
        cout << "Ваш выбор: ";

        // Проверка корректности ввода
        if (!(cin >> choice)) {
            cout << "Некорректный ввод. Пожалуйста, введите число." << endl;
            cin.clear(); // Сброс флагов ошибок ввода
            clearInputBuffer(); // Очистка буфера
            continue; // Повтор итерации цикла
        }

        // Обработка выбора пользователя
        switch (choice) {
            case 1:
                runHashTable();
                break;
            case 2:
                runBinaryHeap();
                break;
            case 0:
                cout << "Завершение программы." << endl;
                return 0; // Выход из программы
            default:
                cout << "Неверный выбор. Попробуйте снова." << endl;
                break;
        }
    }
}
