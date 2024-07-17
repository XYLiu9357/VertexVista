/**linked-list.hpp
 *
 * Linked list for digraph adjacency list
 */

#ifndef LINKED_LIST
#define LINKED_LIST
#include <initializer_list>
#include <memory>

class List
{
private:
    struct Node
    {
        int val;
        std::unique_ptr<Node> next;
        Node(int v);
    };
    std::unique_ptr<Node> head;
    size_t sz;

public:
    List();
    List(std::initializer_list<int> init);
    List(const List &that);
    List &operator=(const List &other);

    bool empty() const;
    size_t size() const;

    void insert(int val);
    void erase(int val);

    class Iterator
    {
    private:
        Node *cur;

    public:
        Iterator(Node *node);
        int &operator*();
        int *operator->();
        bool operator==(Iterator that) const;
        bool operator!=(Iterator that) const;
        void operator++();
    };

    Iterator begin() const;
    Iterator end() const;
    Iterator find(int key);
};

#endif /*LINKED_LIST*/