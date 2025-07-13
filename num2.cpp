#include <iostream>
#include <vector>
#include <clocale>

class Graph {
private:
    int numVertices;
    std::vector<std::vector<int>> adj; // Список смежности
    std::vector<bool> visited; // Массив флагов посещения для DFS

    void dfs(int v, std::vector<int> &currentComponent) {
        visited[v] = true;
        currentComponent.push_back(v); // Добавляем вершину в текущую компоненту

        int size = adj[v].size();
        for (int i = 0; i < size; i++) {
            int neighbor = adj[v][i];
            bool isVisited = visited[neighbor];
            if (!isVisited) dfs(neighbor, currentComponent);
        }
    }

public:
    Graph(int V) : numVertices(V) { adj.resize(numVertices); }

    void addEdge(int u, int v) {
        if (u >= 0 && u < numVertices && v >= 0 && v < numVertices) {
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
    }

    std::vector<std::vector<int> > findAllConnectedComponents() {
        std::vector<std::vector<int> > components;
        visited.assign(numVertices, false); // Сброс всех вершин как непосещенных

        for (int i = 0; i < numVertices; i++) {
            // Если вершина еще не посещена, это начало новой компоненты
            bool isVisited = visited[i];
            if (!isVisited) {
                std::vector<int> current;
                dfs(i, current);
                components.push_back(current); // Добавляем найденную компоненту
            }
        }
        return components;
    }
};

int main() {
    std::setlocale(LC_ALL, "ru_RU.UTF-8");

    int N, M; // N - количество вершин, M - количество ребер

    std::cout << "Введите количество вершин графа: ";
    std::cin >> N;
    std::cout << "Введите количество ребер графа: ";
    std::cin >> M;

    Graph graph(N);

    std::cout << "Введите " << M << " пар вершин (u v) для каждого ребра (вершины нумеруются с 0 до " << N - 1 << "):"
            << std::endl;
    for (int i = 0; i < M; ++i) {
        int u, v;
        std::cin >> u >> v;
        graph.addEdge(u, v);
    }

    // Находим все компоненты связности
    std::vector<std::vector<int>> components = graph.findAllConnectedComponents();

    int size_i = components.size();
    std::cout << "Найдено " << size_i << " компонент связности:" << std::endl;
    for (int i = 0; i < size_i; i++) {
        std::cout << "Компонента " << i + 1 << ": ";
        bool isEmpty = components[i].empty();
        if (isEmpty) std::cout << "(пусто)";
        else {
          int size_j = components[i].size();
            for (int j = 0; j < size_j; j++)
              std::cout << components[i][j] << (j == size_j - 1 ? "" : " ");
        }
        std::cout << std::endl;
    }

    return 0;
}
