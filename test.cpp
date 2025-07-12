#include <list>;
#include <vector>;
#include <string>;
#include <fstream>;
#include <iostream>
#include <sstream>;

using namespace std;

class HashTable {
private:
    struct HashNode {
        string key;
        int value;
    };

    vector<list<HashNode> > table;
    int tableSize;
    int size;
    hash<string> hashFunction;

    size_t getHashIndex(string &key) {
        size_t hash = hashFunction(key);
        hash = hash % tableSize;
        return hash;
    }

public:
    HashTable() {
        tableSize = 25;
        size = 0;
        table.resize(tableSize);
    }

    void insert(string &key, int &value) {
        size_t hashIndex = getHashIndex(key);
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

    int serach(string &key) {
        auto index = getHashIndex(key);
        auto chain = table[index];

        for (HashNode &node: chain)
            if (node.key == key) return node.value;

        return -1;
    }
};

int main() {
    auto table = HashTable{};

    ifstream data("phonebook.txt");

    string line;

    while (getline(data, line)) {
        stringstream ss(line);
        string key;
        int value;
        ss >> key >> value;

        table.insert(key, value);
        cout << "pair added: key=" << key << ", value=" << value << endl;
    }

    return 0;
}
