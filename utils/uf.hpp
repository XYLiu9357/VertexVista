/**uf.hpp
 *
 * Generic union-find data structure implemented to support
 * graph routines.
 */

#ifndef UnionFind
#define UnionFind

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
    UF() {}
    UF(int numItems) {}
    UF(std::initializer_list<T> init) {}
    UF(const UF &other) {}

    void connect(const T &p, const T &q) {}
    void isConnected(const T &p, const T &q) {}
};

#endif /*UnionFind*/