/**uf.hpp
 *
 * Generic union-find data structure implemented to support
 * graph routines.
 */

#ifndef UnionFind
#define UnionFind

#include <algorithm>
#include <vector>
#include <unordered_map>

template <typename T>
class UF
{
private:
    std::unordered_map<T, int> toId;
    std::vector<int> ids;
    std::vector<int> sizes;
    int nextId;

    // Find root id
    int rootFromId(int id)
    {
        int cur = id;
        while (cur != ids[cur])
        {
            // Path compression
            ids[cur] = ids[ids[cur]];
            cur = ids[cur];
        }
        return cur;
    }

    // Connect id
    void connectId(int p, int q)
    {
        int rootP = getRoot(p);
        int rootQ = getRoot(q);

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
    bool isIdConnected(int p, int q) { return connections[getRoot(p)] == connections[getRoot(q)]; }

public:
    UF() : toId(std::unordered_map<T, int>()),
           ids(std::vector<int>()),
           sizes(std::vector<int>()),
           nextId(0) {}

    UF(int numItems) : nextId(numItems)
    {
        ids.resize(numItems);
        sizes.resize(numItems);

        for (int i = 0; i < numItems; i++)
        {
            toId.insert({T(i), i});
            ids[i] = i;
            sizes[i] = 1;
        }
    }

    UF(std::initializer_list<T> init) : nextId(init.size())
    {
        int numItems = init.size();
        ids.resize(numItems);
        sizes.resize(numItems);

        for (int i = 0; i < numItems; i++)
        {
            toId.insert({init[i], i});
            ids[i] = i;
            sizes[i] = 1;
        }
    }

    UF(const UF &other)
    {
        this->toId = std::unordered_map<T, int>(other.toId);
        this->ids = std::vector<int>(other.ids);
        this->sizes = std::vector<int>(other.sizes);
        this->nextId = other.nextId;
    }

    UF &operator=(const UF &other)
    {
        UF copy(other);
        std::swap(this->toId, copy.toId);
        std::swap(this->ids, copy.ids);
        std::swap(this->sizes, copy.sizes);
        std::swap(this->nextId, copy.nextId);
        return *this;
    }

    void insert(const T &p)
    {
        T pCopy(p); // Defensive copy
        toId.insert({pCopy, nextId});
        ids[nextId] = nextId;
        sizes[nextId] = 1;
        nextId++;
    }

    void erase(const T &p)
    {
        int substituteId = -1;
    }

    void connect(const T &p, const T &q) { connectId(toId.at(p), toId.at(q)); }
    bool isConnected(const T &p, const T &q) { return isIdConnected(toId.at(p), toId.at(q)); }
};

#endif /*UnionFind*/