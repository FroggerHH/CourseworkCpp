#include <iostream>
#include <vector>

class Graph {
private:
    int numVertices;
    std::vector<std::vector<int> > adj; // Список смежности
    std::vector<bool> visited;
    int visitedCount;

    void dfs(int v) {
        visited[v] = true;
        visitedCount++;
        for (int neighbor: adj[v])
            if (!visited[neighbor])
                dfs(neighbor);
    }

public:
    Graph(int V) : numVertices(V) { adj.resize(numVertices); }

    void addEdge(int u, int v) {
        if (u >= 0 && u < numVertices && v >= 0 && v < numVertices) {
            adj[u].push_back(v);
            adj[v].push_back(u); // Добавляем обратное ребро для неориентированного графа
        } else
            std::cerr << "Ошибка: некорректные индексы вершин (" << u << ", " << v << ")." << std::endl;
    }

    bool isConnected() {
        if (numVertices <= 1) return true;

        // Сброс состояния для нового DFS обхода
        visited.assign(numVertices, false);
        visitedCount = 0;

        dfs(0);

        return visitedCount == numVertices;
    }
};

int main() {
#ifdef _WIN32
    std::setlocale(LC_ALL, "ru_RU.UTF-8");
    system("chcp 65001 > nul");
    system("cls");
#endif

    int N, M; // N - количество вершин, M - количество ребер

    std::cout << "Введите количество вершин графа: ";
    std::cin >> N;
    if (N < 0) {
        std::cerr << "Ошибка: количество вершин не может быть отрицательным." << std::endl;
        return 1;
    }

    Graph graph(N);

    std::cout << "Введите количество ребер графа: ";
    std::cin >> M;
    if (M < 0) {
        std::cerr << "Ошибка: количество ребер не может быть отрицательным." << std::endl;
        return 1;
    }

    std::cout << "Введите " << M << " пар вершин (u v) для каждого ребра (вершины нумеруются с 0 до " << N - 1 << "):" << std::endl;
    for (int i = 0; i < M; ++i) {
        int u, v;
        std::cin >> u >> v;
        graph.addEdge(u, v);
    }

    if (graph.isConnected()) std::cout << "Граф является связным." << std::endl;
    else std::cout << "Граф не является связным." << std::endl;

    return 0;
}
