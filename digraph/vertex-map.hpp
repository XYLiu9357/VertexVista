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
    size_t size();
    bool contains(int key);
    int at(int key);

    // Mutators
    void insert(int key, int value);
    void erase(int key);
    int &operator[](int key);
};

#endif /*VERTEX_MAP*/