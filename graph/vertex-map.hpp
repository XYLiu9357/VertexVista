/**vertex-map.hpp
 *
 * Custom vertex map that maps node IDs to adjacency list
 * array indices. This hash table will be designed to
 * minimize memory overhead compared to std::unordered_map
 * and handle integers only.
 */

#ifndef VERTEX_MAP
#define VERTEX_MAP

#include <string>
#include <list>
#include <vector>

class VertexMap
{
private:
    struct Bucket
    {
        int key;
        int value;
        Bucket(int key, int value);
    };

    // Separate chaining
    std::vector<std::list<Bucket>> buckets;
    size_t numBuckets;
    size_t sz;

    // Hash table construct
    double colTolerance = 0.75;

    unsigned int
    hash(unsigned int key) const;
    unsigned int unhash(unsigned int hashVal) const;
    size_t getBucketIndex(int key) const;
    void rehash();

public:
    VertexMap(size_t init_size = 16);
    VertexMap(const VertexMap &other);

    // Accessors
    size_t size() const;
    bool contains(int key) const;
    int at(int key) const;

    // Mutators
    void insert(int key, int value);
    void erase(int key);
    int &operator[](int key);
    int operator[](int key) const;

private:
    class Iterator
    {
    private:
        const VertexMap *map;
        size_t bucketIndex;
        std::list<Bucket>::const_iterator listIterator;

        void advance();

    public:
        Iterator(const VertexMap *map, size_t bucketIndex, std::list<Bucket>::const_iterator listIterator);
        Iterator &operator++();
        bool operator!=(const Iterator &other) const;
        const Bucket &operator*() const;
    };

public:
    Iterator begin() const;
    Iterator end() const;
};

#endif /*VERTEX_MAP*/