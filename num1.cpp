#include <iostream>
#include <vector>
#include <limits>

using namespace std;

class BinaryHeap {
private:
    vector<int> heap{};

    static int parent(int i) { return (i - 1) / 2; }
    static int leftChild(int i) { return 2 * i + 1; }
    static int rightChild(int i) { return 2 * i + 2; }

    // Просеивание вверх
    void siftUp(int i) {
        // Пока не дошли до корня и текущий элемент БОЛЬШЕ родителя
        while (i > 0) {
            int el = heap[i];
            int p = heap[parent(i)];
            if (el > p) {
                swap(heap[i], heap[parent(i)]);
                i = parent(i); // Переходим на позицию родителя}
            } else break;
        }
    }

    // Просеивание вниз
    void siftDown(int i) {
        int maxIndex = i; // Индекс наибольшего элемента (сначала текущий)

        int leftIndex = leftChild(i);

        int size = heap.size();
        // Если левый потомок существует и он БОЛЬШЕ текущего максимума
        if (leftIndex < size && heap[leftIndex] > heap[maxIndex]) maxIndex = leftIndex;

        int rightIndex = rightChild(i);
        // Если правый потомок существует и он БОЛЬШЕ текущего максимума
        if (rightIndex < size && heap[rightIndex] > heap[maxIndex]) maxIndex = rightIndex;

        // Если наибольший элемент не текущий, меняем и продолжаем просеивание
        if (i != maxIndex) {
            swap(heap[i], heap[maxIndex]);
            siftDown(maxIndex); // Рекурсивно для новой позиции
        }
    }

public:
    BinaryHeap() = default;

    int getSize() {
        int size = heap.size();
        return size;
    }

    bool isEmpty() {
        bool isEmpty = heap.empty();
        return isEmpty;
    }

    void insert(int value) {
        heap.push_back(value); // Добавляем в конец
        siftUp(heap.size() - 1); // Восстанавливаем свойство кучи просеиванием вверх
        cout << "Элемент " << value << " добавлен. " << endl;
    }

    // Просмотр максимального элемента (без удаления)
    int peekMax() {
        bool flag = isEmpty();
        if (flag) {
            cout << "Куча пуста (peekMax)" << endl;
            return -1;
        }
        int result = heap[0];
        return result; // Максимальный элемент всегда в корне
    }

    // Извлечение максимального элемента
    int extractMax() {
        bool flag = isEmpty();
        if (flag) {
            cout << "Куча пуста (extractMax)" << endl;
            return -1;
        }
        int result = heap[0]; // Запоминаем максимальный элемент

        // Перемещаем последний элемент в корень
        int back = heap.back();
        heap[0] = back;
        heap.pop_back(); // Удаляем последний элемент

        // Если куча не пуста, восстанавливаем свойство просеиванием вниз
        flag = isEmpty();
        if (!flag) siftDown(0);
        return result;
    }

    void displayState() {
        cout << "Куча: [";
        bool flag = isEmpty();
        if (flag) cout << "(пусто)";
        else {
            int size = getSize();
            for (int i = 0; i < size; ++i) {
                int el = heap[i];
                cout << el << " ";
            }
        }
        cout << "]" << endl;
    }
};

void clearInputBuffer() {
    long long max = numeric_limits<streamsize>::max();
    cin.ignore(max, '\n');
}

// Интерфейс двоичной кучи
void runBinaryHeap() {
    BinaryHeap binary_heap{};

    cout << "\n--- Меню Двоичной кучи (Max-Heap) ---" << endl;
    cout << "Команды: insert <value>, extractMax, peekMax, display, size, back" << endl;

    while (true) {
        cout << "MaxHeap> ";
        string command;
        cin >> command;

        if (command == "insert") {
            int value;
            cin >> value;
            binary_heap.insert(value);
        } else if (command == "extractMax") {
            int result = binary_heap.extractMax();
            if (result != -1)
                cout << "Извлечен максимальный элемент: " << result << ". " << endl;
        } else if (command == "peekMax") {
            int result = binary_heap.peekMax();
            if (result != -1)
                cout << "Максимальный элемент: " << result << endl;
        } else if (command == "display") binary_heap.displayState();

        else if (command == "size") {
            int size = binary_heap.getSize();
            cout << "Текущий размер кучи: " << size << endl;
        } else if (command == "back") break; // Выход из меню

        else {
            cout << "Неизвестная команда." << endl;
            clearInputBuffer();
        }
    }
}

int main() {
    setlocale(LC_ALL, "ru_RU.UTF-8");
#ifdef WIN32
    system("chcp 65001"); // Для UTF-8 в консоли Windows
    system("cls");
#endif

    runBinaryHeap();

    return 0;
}
