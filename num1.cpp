#include <iostream>
#include <vector>
#include <limits>

using namespace std;

class Graph {
private:
    int numVertices; // Количество вершин в графе
    std::vector<std::vector<int> > adj; // Список смежности
    std::vector<bool> visited; // Флаги посещения вершин для DFS
    int countVisited; // Количество вершин, посещенных в текущем DFS

    /**
     * @brief Рекурсивная реализация алгоритма поиска в глубину (DFS).
     *        Посещает все достижимые вершины из заданной, помечает их
     *        как посещенные и увеличивает счетчик посещенных вершин.
     * @param v Текущая вершина, с которой начинается обход.
     */
    void dfsRecursive(int v) {
        visited[v] = true; // Помечаем текущую вершину как посещенную
        countVisited++; // Увеличиваем счетчик посещенных вершин

        // Проходим по всем смежным вершинам
        for (int neighbor: adj[v]) {
            // Если соседняя вершина еще не посещена, рекурсивно запускаем DFS от нее
            if (!visited[neighbor]) {
                dfsRecursive(neighbor);
            }
        }
    }

public:
    /**
     * @brief Конструктор класса Graph.
     *        Инициализирует граф с заданным количеством вершин.
     * @param V Количество вершин.
     */
    Graph(int V) : numVertices(V) {
        // Инициализируем список смежности для каждой вершины
        adj.resize(numVertices);
    }

    /**
     * @brief Добавляет неориентированное ребро между двумя вершинами.
     *        Добавляет v в список смежности u, и u в список смежности v.
     * @param u Первая вершина ребра.
     * @param v Вторая вершина ребра.
     */
    void addEdge(int u, int v) {
        // Проверка на корректность индексов вершин
        if (u >= 0 && u < numVertices && v >= 0 && v < numVertices) {
            adj[u].push_back(v);
            adj[v].push_back(u); // Для неориентированного графа
        } else {
            std::cerr << "Ошибка: некорректные индексы вершин для добавления ребра ("
                    << u << ", " << v << ")." << std::endl;
        }
    }

    /**
     * @brief Проверяет, является ли граф связным.
     *        Запускает DFS из вершины 0 и сравнивает количество
     *        посещенных вершин с общим количеством вершин в графе.
     * @return true, если граф связный, false в противном случае.
     */
    bool checkConnectivity() {
        // Если граф пустой или состоит из одной вершины (без ребер), он считается связным
        if (numVertices <= 1) {
            return true;
        }

        // Инициализируем массив посещенных вершин и счетчик для нового обхода
        visited.assign(numVertices, false);
        countVisited = 0;

        // Запускаем DFS из первой вершины (с индексом 0)
        dfsRecursive(0);

        // Граф связный, если все вершины были посещены
        return countVisited == numVertices;
    }
};

int main() {
    setlocale(LC_ALL, "ru_RU.UTF-8");
#ifdef WIN32
    system("chcp 65001"); // Для UTF-8 в консоли Windows
    // system("cls");
#endif

    int N, M; // N - количество вершин, M - количество ребер

    std::cout << "Введите количество вершин графа: ";
    std::cin >> N;

    // Проверка на корректность ввода количества вершин
    if (N < 0) {
        std::cerr << "Ошибка: количество вершин не может быть отрицательным."
                << std::endl;
        return 1;
    }

    Graph graph(N); // Создаем объект графа

    std::cout << "Введите количество ребер графа: ";
    std::cin >> M;

    // Проверка на корректность ввода количества ребер
    if (M < 0) {
        std::cerr << "Ошибка: количество ребер не может быть отрицательным."
                << std::endl;
        return 1;
    }

    std::cout << "Введите " << M
            << " пар вершин (u v) для каждого ребра (вершины нумеруются с 0 до "
            << N - 1 << "):" << std::endl;
    for (int i = 0; i < M; ++i) {
        int u, v;
        std::cin >> u >> v;
        graph.addEdge(u, v);
    }

    // Проверяем связность графа и выводим результат
    if (graph.checkConnectivity()) {
        std::cout << "Граф является связным." << std::endl;
    } else {
        std::cout << "Граф не является связным." << std::endl;
    }

    return 0;
}
