/**adj-tree.hpp
 *
 * Header for the adjacency tree class.
 */

#ifndef ADJTREE
#define ADJTREE

#include <cstdint>
#include <functional>
#include <initializer_list>
#include <string>
#include <utility>

#include "deque.hpp"

class AdjTree
{
private:
    /**
     * TreeNode
     */

    class TreeNode
    {
    public:
        const static bool RED = true;
        const static bool BLACK = false;

        int key;
        TreeNode *left;
        TreeNode *right;
        size_t sz;
        bool color;

        TreeNode(int val, bool c)
            : key(val), left(nullptr), right(nullptr), sz(1), color(c) {}
    };

    // Tree attributes
    TreeNode *root;

    // Utilities
    size_t nodeSize(TreeNode *node) const;
    bool treeEqual(TreeNode *node1, TreeNode *node2) const;

    // Recursive deep copy
    TreeNode *copyTree(TreeNode const *node);

    // Tree rotation & coloring
    bool isRed(TreeNode *node);
    TreeNode *rotateLeft(TreeNode *node);
    TreeNode *rotateRight(TreeNode *node);
    void flipColors(TreeNode *node);

    // Fixup during insertion
    TreeNode *rbFix(TreeNode *node);

    // Deletion 2-node fixups
    TreeNode *moveRedLeft(TreeNode *node);
    TreeNode *moveRedRight(TreeNode *node);

    // Recursive helpers
    TreeNode *_at(TreeNode *node, int key) const;
    int _rank(TreeNode *node, int key) const;
    TreeNode *_floor(TreeNode *node, int key) const;
    TreeNode *_ceiling(TreeNode *node, int key) const;
    int _rankSelect(TreeNode *node, int rank) const;

    TreeNode *_insert(TreeNode *node, int key);
    TreeNode *_eraseMin(TreeNode *node);
    TreeNode *_erase(TreeNode *node, int key);

public:
    /**
     * Constructors
     */

    AdjTree();
    AdjTree(const std::initializer_list<int> &init);
    AdjTree(const AdjTree &that); // Deep copy

    /**
     * Utilities
     */

    size_t size() const;
    bool empty() const;

    AdjTree &operator=(const AdjTree &that); // Deep copy
    bool operator==(const AdjTree &that) const;
    bool operator!=(const AdjTree &that) const;

    /**
     * Search
     */

    int at(int key) const;
    bool contains(int key) const;

    /**
     * Ordered symbol table operations
     */

    int rank(int key) const;
    int min() const;
    int max() const;

    int floor(int key);
    int ceiling(int key);
    int rankSelect(int rank);

    /**
     * Insertion
     */

    void insert(int key);

    /**
     * Deletion
     */

    void erase(int key);

    /**
     * Tree processing
     */

    std::string serialize(const std::string &delim = ",", const std::string &nilStr = ")") const;
    size_t depth() const; // BFS: ~2n node accesses

    /**
     * Delete tree
     */

    void _deleteTree(TreeNode *node);
    ~AdjTree();

    /**
     * Inorder iterator
     */
private:
    class Iterator
    {
    public:
        Deque<TreeNode *> nodeStack;

        Iterator(const AdjTree &tree);
        int &operator*();
        int *operator->();
        bool operator==(Iterator that) const;
        bool operator!=(Iterator that) const;
        void operator++();
    };

public:
    Iterator begin();
    Iterator end();
    Iterator find(int key);
};

#endif /*ADJTREE*/