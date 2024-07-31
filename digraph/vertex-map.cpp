/**vertex-map.cpp
 *
 * Custom vertex map that maps node IDs to adjacency list
 * array indices. This hash table will be designed to
 * minimize memory overhead compared to std::unordered_map
 * and handle integers only.
 */

#include "vertex-map.hpp"

// Hash table construct
VertexMap::Bucket::Bucket(int key, int value) : key(key), value(value) {}
unsigned int VertexMap::hash(unsigned int key) const
{
    // Signed values are casted to unsigned
    key = ((key >> 16) ^ key) * 0x45d9f3b;
    key = ((key >> 16) ^ key) * 0x45d9f3b;
    key = (key >> 16) ^ key;
    return key;
}

unsigned int VertexMap::unhash(unsigned int hashVal) const
{
    hashVal = ((hashVal >> 16) ^ hashVal) * 0x119de1f3;
    hashVal = ((hashVal >> 16) ^ hashVal) * 0x119de1f3;
    hashVal = (hashVal >> 16) ^ hashVal;
    return hashVal;
}

size_t VertexMap::getBucketIndex(int key) const { return hash(key) % numBuckets; }

void VertexMap::rehash()
{
    size_t newNumBuckets = numBuckets * 2;
    std::vector<std::list<Bucket>> newBuckets(newNumBuckets);

    for (const auto &bucket : buckets)
    {
        for (const auto &entry : bucket)
        {
            // Copy buckets using new indices
            size_t newBucketIndex = hash(entry.key) % newNumBuckets;
            newBuckets[newBucketIndex].emplace_back(entry.key, entry.value);
        }
    }

    buckets = std::move(newBuckets);
    numBuckets = newNumBuckets;
}

// Constructors
VertexMap::VertexMap(size_t init_size) : numBuckets(init_size), sz(0) { buckets.resize(numBuckets); }
VertexMap::VertexMap(const VertexMap &other)
{
    this->buckets = other.buckets; // Deep copy
    this->numBuckets = other.numBuckets;
    this->sz = other.sz;
}

// Accessors
size_t VertexMap::size() { return sz; }
bool VertexMap::contains(int key)
{
    size_t bucketIndex = getBucketIndex(key);

    // Check each entry of separate chaining list
    for (const auto &entry : buckets[bucketIndex])
    {
        if (entry.key == key)
            return true;
    }
    return false;
}

int VertexMap::at(int key)
{
    size_t bucketIndex = getBucketIndex(key);
    for (const auto &entry : buckets[bucketIndex])
    {
        if (entry.key == key)
            return entry.value;
    }

    // Key not found
    return -1;
}

// Mutators
void VertexMap::insert(int key, int value)
{
    size_t bucketIndex = getBucketIndex(key);
    for (auto &entry : buckets[bucketIndex])
    {
        if (entry.key == key)
        {
            entry.value = value;
            return;
        }
    }
    // Make new if not found
    if (sz / numBuckets > colTolerance)
        rehash();
    buckets[bucketIndex].emplace_back(key, value);
    sz++;
}

void VertexMap::erase(int key)
{
    size_t bucketIndex = getBucketIndex(key);
    auto &bucket = buckets[bucketIndex];
    for (auto it = bucket.begin(); it != bucket.end(); ++it)
    {
        if (it->key == key)
        {
            bucket.erase(it);
            sz--;
            return;
        }
    }
}

int &VertexMap::operator[](int key)
{
    size_t bucketIndex = getBucketIndex(key);
    for (auto &entry : buckets[bucketIndex])
    {
        if (entry.key == key)
            return entry.value;
    }
    // Make new and return reference if not found
    if (sz / numBuckets > colTolerance)
        rehash();
    buckets[bucketIndex].emplace_back(key, -1);
    sz++;
    return buckets[bucketIndex].back().value;
}