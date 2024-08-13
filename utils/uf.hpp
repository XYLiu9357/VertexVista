/**uf.hpp
 *
 * Generic union-find data structure implemented to support
 * graph routines.
 */

#ifndef UnionFind
#define UnionFind

#include <algorithm>
#include <type_traits>
#include <vector>
#include <unordered_map>

template <typename T>
class UF
{
private:
    std::unordered_map<T, int> toId;
    std::vector<int> connections;
    std::vector<int> sizes;
    int nextId;

    // Find root id
    int rootFromId(int id)
    {
        int cur = id;
        while (cur != connections[cur])
        {
            // Path compression
            connections[cur] = connections[connections[cur]];
            cur = connections[cur];
        }
        return cur;
    }

    // Connect id
    void connectId(int p, int q)
    {
        int rootP = rootFromId(p);
        int rootQ = rootFromId(q);

        if (rootP == rootQ)
            return;

        // weighted union
        if (sizes[rootP] > sizes[rootQ])
        {
            connections[rootQ] = rootP;
            sizes[rootP] += sizes[rootQ];
        }
        else
        {
            connections[rootP] = rootQ;
            sizes[rootQ] += sizes[rootP];
        }
    }

    // Connectivity query based on id
    bool isIdConnected(int p, int q) { return connections[rootFromId(p)] == connections[rootFromId(q)]; }

public:
    UF() : toId(std::unordered_map<T, int>()),
           connections(std::vector<int>()),
           sizes(std::vector<int>()),
           nextId(0) {}

    UF(int numItems) : nextId(numItems)
    {
        static_assert(std::is_integral<T>::value, "UF integer constructor is only valid for integral types");
        connections.resize(numItems);
        sizes.resize(numItems);

        for (int i = 0; i < numItems; i++)
        {
            toId.insert({T(i), i});
            connections[i] = i;
            sizes[i] = 1;
        }
    }

    UF(std::initializer_list<T> init) : nextId(init.size())
    {
        int numItems = init.size();
        connections.resize(numItems);
        sizes.resize(numItems);

        int i = 0;
        for (const T &entryRef : init)
        {
            T entry(entryRef); // Copy made
            toId.insert({entry, i});

            connections[i] = i;
            sizes[i] = 1;
            i++;
        }
    }

    UF(const UF &other)
    {
        this->toId = std::unordered_map<T, int>(other.toId);
        this->connections = std::vector<int>(other.connections);
        this->sizes = std::vector<int>(other.sizes);
        this->nextId = other.nextId;
    }

    UF &operator=(const UF &other)
    {
        // Copy and swap
        UF copy(other);
        std::swap(this->toId, copy.toId);
        std::swap(this->connections, copy.connections);
        std::swap(this->sizes, copy.sizes);
        std::swap(this->nextId, copy.nextId);
        return *this;
    }

    void insert(const T &p)
    {
        T pCopy(p); // Defensive copy
        toId.insert({pCopy, nextId});

        // Resize vectors
        if (nextId >= connections.size())
        {
            connections.resize(connections.size() * 2);
            sizes.resize(sizes.size() * 2);
        }

        connections[nextId] = nextId;
        sizes[nextId] = 1;
        nextId++;
    }

    size_t size() { return toId.size(); }
    bool contains(const T &query) { return toId.find(query) != toId.end(); }

    void connect(const T &p, const T &q)
    {
        if (toId.find(p) == toId.end())
            throw std::out_of_range("First operand not found in connect operation");
        if (toId.find(q) == toId.end())
            throw std::out_of_range("Second operand not found in connect operation");

        connectId(toId.at(p), toId.at(q));
    }

    bool isConnected(const T &p, const T &q)
    {
        if (toId.find(p) == toId.end())
            throw std::out_of_range("First operand not found in connectivity query");
        if (toId.find(q) == toId.end())
            throw std::out_of_range("Second operand not found connectivity query");

        return isIdConnected(toId.at(p), toId.at(q));
    }
};

#endif /*UnionFind*/