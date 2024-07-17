/**linked-list.hpp
 *
 * Linked list for digraph adjacency list
 */

#include "linked-list.hpp"
#include <initializer_list>
#include <memory>
#include <utility>

List::Node::Node(int v)
    : val(v) {}

List::List()
    : sz(0) {}

List::List(std::initializer_list<int> init)
{
    for (int v : init)
        this->insert(v);
}

bool List::empty() { return sz == 0; }
size_t List::size() { return sz; }

void List::insert(int val)
{
    if (this->empty())
        head = std::make_unique<Node>(Node(val));
    else
    {
        std::unique_ptr<Node> newHead = std::make_unique<Node>(Node(val));
        newHead->next = std::move(head); // head is null after this
        head = std::move(newHead);
    }
    sz++;
}

void List::erase(int val)
{
    // Empty
    if (this->empty())
        return;

    // Remove head
    if (head->val == val)
    {
        head = std::move(head->next);
        sz--;
        return;
    }

    Node *cur = head.get();

    // Remove and reconnect
    while (cur->next && cur->next->val != val)
        cur = cur->next.get();
    if (cur->next && cur->next->val == val)
    {
        cur->next = std::move(cur->next->next);
        sz--;
    }
}

List::Iterator::Iterator(Node *node) : cur(node) {}

int &List::Iterator::operator*()
{
    return cur->val;
}

int *List::Iterator::operator->()
{
    return &(cur->val);
}

bool List::Iterator::operator==(Iterator that) const
{
    return this->cur == that.cur;
}

bool List::Iterator::operator!=(Iterator that) const
{
    return this->cur != that.cur;
}

void List::Iterator::operator++()
{
    if (cur)
    {
        cur = cur->next.get();
    }
}

List::Iterator List::begin() const { return Iterator(head.get()); }
List::Iterator List::end() const { return Iterator(nullptr); }
List::Iterator List::find(int key)
{
    Node *query = head.get();
    while (query != nullptr)
    {
        if (query->val == key)
            return Iterator(query);
        query = query->next.get();
    }
    return end();
}
