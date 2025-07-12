#include <iostream>
#include <vector>
#include <clocale>

class Graph {
private:
    int numVertices;
    std::vector<std::vector<int> > adj; // Список смежности
    std::vector<bool> visited; // Массив флагов посещения для DFS

    void dfs(int v, std::vector<int> &currentComponent) {
        visited[v] = true;
        currentComponent.push_back(v); // Добавляем вершину в текущую компоненту

        for (int neighbor: adj[v]) {
            if (!visited[neighbor]) {
                dfs(neighbor, currentComponent);
            }
        }
    }

public:
    Graph(int V) : numVertices(V) {
        adj.resize(numVertices);
    }

    void addEdge(int u, int v) {
        if (u >= 0 && u < numVertices && v >= 0 && v < numVertices) {
            adj[u].push_back(v);
            adj[v].push_back(u); // Для неориентированного графа
        } else {
            std::cerr << "Ошибка: некорректные индексы вершин (" << u << ", " << v << ")." << std::endl;
        }
    }

    std::vector<std::vector<int> > findAllConnectedComponents() {
        std::vector<std::vector<int> > components; // Вектор для хранения всех компонент
        visited.assign(numVertices, false); // Сброс всех вершин как непосещенных

        // Итерируемся по всем вершинам графа
        for (int i = 0; i < numVertices; ++i) {
            // Если вершина еще не посещена, это начало новой компоненты
            if (!visited[i]) {
                std::vector<int> currentComponent; // Вектор для текущей компоненты
                dfs(i, currentComponent); // Запускаем DFS для сбора вершин компоненты
                components.push_back(currentComponent); // Добавляем найденную компоненту
            }
        }
        return components;
    }
};

int main() {
#ifdef _WIN32
    std::setlocale(LC_ALL, "ru_RU.UTF-8");
    system("chcp 65001 > nul");
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

    std::cout << "Введите " << M << " пар вершин (u v) для каждого ребра (вершины нумеруются с 0 до " << N - 1 << "):"
            << std::endl;
    for (int i = 0; i < M; ++i) {
        int u, v;
        std::cin >> u >> v;
        graph.addEdge(u, v);
    }

    // Находим все компоненты связности
    std::vector<std::vector<int> > components = graph.findAllConnectedComponents();

    std::cout << "Найдено " << components.size() << " компонент связности:" << std::endl;
    for (size_t i = 0; i < components.size(); ++i) {
        std::cout << "Компонента " << i + 1 << ": ";
        if (components[i].empty()) std::cout << "(пусто)";
        else
            for (size_t j = 0; j < components[i].size(); ++j)
                std::cout << components[i][j] << (j == components[i].size() - 1 ? "" : " ");
        std::cout << std::endl;
    }

    return 0;
}
