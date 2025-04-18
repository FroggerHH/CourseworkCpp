#include <iostream>
#include <vector>
#include <list>
#include <limits>
#include <algorithm>
using namespace std;

class BinaryHeap {
private:
    vector<int> heap{};

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

    void insert(const int &value) {
        heap.push_back(value); // Добавляем в конец
        siftUp(heap.size() - 1); // Восстанавливаем свойство кучи просеиванием вверх
        cout << "Элемент " << value << " добавлен. " << endl;
    }

    // Просмотр максимального элемента (без удаления)
    int peekMax() const {
        if (isEmpty()) {
            cout << "Куча пуста (peekMax)" << endl;
            return -1;
        }
        return heap[0]; // Максимальный элемент всегда в корне
    }

    // Извлечение максимального элемента
    int extractMax() {
        if (isEmpty()) {
            cout << "Куча пуста (extractMax)" << endl;
            return -1;
        }
        int result = heap[0]; // Запоминаем максимальный элемент

        // Перемещаем последний элемент в корень
        heap[0] = heap.back();
        heap.pop_back(); // Удаляем последний элемент

        // Если куча не пуста, восстанавливаем свойство просеиванием вниз
        if (!isEmpty()) siftDown(0);
        cout << "Извлечен максимальный элемент: " << result << ". " << endl;
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

// Интерфейс двоичной кучи
void runBinaryHeap() {
    BinaryHeap binary_heap;
    string command;
    int value;

    cout << "\n--- Меню Двоичной кучи (Max-Heap) ---" << endl;
    cout << "Команды: insert <value>, extractMax, peekMax, display, size, back" << endl;

    while (true) {
        cout << "MaxHeap> ";
        cin >> command;

        if (command == "insert") {
            if (!(cin >> value)) {
                cout << "Ошибка ввода для insert. Ожидается: <value>" << endl;
                cin.clear();
                clearInputBuffer();
                continue;
            }
            binary_heap.insert(value);
        } else if (command == "extractMax") binary_heap.extractMax();
        else if (command == "peekMax") {
            int peekMaxResult = binary_heap.peekMax();
            if (peekMaxResult != -1)
                cout << "Максимальный элемент: " << peekMaxResult << endl;
        } else if (command == "display") binary_heap.displayState();
        else if (command == "size")
            cout << "Текущий размер кучи: " << binary_heap.getSize() << endl;
        else if (command == "back") break; // Выход из меню
        else {
            cout << "Неизвестная команда." << endl;
            clearInputBuffer();
        }
    }
}

int main() {
    setlocale(LC_ALL, "ru_RU.UTF-8");
#ifdef WIN32
    system("chcp 65001");
#endif

    while (true) {
        runBinaryHeap();
    }
}
