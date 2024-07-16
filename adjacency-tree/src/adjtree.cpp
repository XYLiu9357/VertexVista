/**rbtree.ipp
 *
 * Implementation of the left-leaning red black tree template class.
 */

#include <cstdint>
#include <functional>
#include <initializer_list>
#include <stdexcept>
#include <string>
#include <utility>

#include "adjtree.hpp"
#include "deque.hpp"

/**
 * Constructors
 */

AdjTree::AdjTree()
    : root(nullptr) {}

AdjTree::AdjTree(const std::initializer_list<int> &init)
    : root(nullptr)
{
    for (int key : init)
        insert(key);
}

AdjTree::TreeNode *AdjTree::copyTree(TreeNode const *node)
{
    if (node == nullptr)
        return nullptr;

    TreeNode *curNode = new TreeNode(node->key, node->color);
    curNode->sz = node->sz;
    curNode->left = copyTree(node->left);
    curNode->right = copyTree(node->right);
    return curNode;
}

AdjTree::AdjTree(const AdjTree &that)
{
    TreeNode *newRoot = copyTree(that.root);
    this->root = newRoot;
}

/**
 * Utilities
 */

bool AdjTree::empty() const
{
    return root == nullptr;
}

size_t AdjTree::nodeSize(TreeNode *node) const
{
    return node == nullptr ? 0 : node->sz;
}

size_t AdjTree::size() const
{
    return nodeSize(root);
}

bool AdjTree::treeEqual(TreeNode *node1, TreeNode *node2) const
{
    if (node1 == nullptr && node2 == nullptr)
        return true;
    else if (node1 == nullptr)
        return false;
    else if (node2 == nullptr)
        return false;

    bool nodeEquality = node1->key == node2->key && node1->sz == node2->sz && node1->color == node2->color;
    return nodeEquality && treeEqual(node1->left, node2->left) && treeEqual(node1->right, node2->right);
}

AdjTree &AdjTree::operator=(const AdjTree &that)
{
    // Copy and swap
    AdjTree temp(that);
    std::swap(this->root, temp.root);

    return *this;
}

bool AdjTree::operator==(const AdjTree &that) const
{
    return treeEqual(this->root, that.root);
}

bool AdjTree::operator!=(const AdjTree &that) const
{
    return !treeEqual(this->root, that.root);
}

/**
 * Search
 */

AdjTree::TreeNode *AdjTree::_at(TreeNode *node, int key) const
{
    if (node == nullptr)
        return nullptr;

    if (key < node->key)
        return _at(node->left, key);
    else if (key > node->key)
        return _at(node->right, key);
    else
        return node;
}

int AdjTree::at(int key) const
{
    if (empty())
        throw std::out_of_range("Invalid search in empty container");

    TreeNode *queryNode = _at(root, key);
    if (queryNode == nullptr)
        throw std::out_of_range("Query key not found");

    int queryValue = queryNode->key;
    return queryValue;
}

bool AdjTree::contains(int key) const
{
    TreeNode *queryNode = _at(root, key);
    return queryNode != nullptr;
}

/**
 * Ordered symbol table operations
 */

int AdjTree::_rank(TreeNode *node, int key) const
{
    if (node == nullptr)
        return 0;

    if (key < node->key)
        return _rank(node->left, key);
    else if (key > node->key)
        return nodeSize(node->left) + 1 + _rank(node->right, key);
    else
        return nodeSize(node->left);
}

int AdjTree::rank(int key) const
{
    if (empty())
        throw std::out_of_range("Invalid rank query with empty container");
    return _rank(root, key);
}

key_t AdjTree::min() const
{
    if (empty())
        throw std::out_of_range("Invalid call to min() with empty container");

    TreeNode *cur = root;
    while (cur->left != nullptr)
        cur = cur->left;

    return cur->key;
}

key_t AdjTree::max() const
{
    if (empty())
        throw std::out_of_range("Invalid call to max() with empty container");

    TreeNode *cur = root;
    while (cur->right != nullptr)
        cur = cur->right;

    return cur->key;
}

AdjTree::TreeNode *AdjTree::_floor(TreeNode *node, int key) const
{
    if (node == nullptr)
        return nullptr;

    if (key == node->key)
        return node;
    else if (key < node->key)
        return _floor(node->left, key);

    // Query key is greater than node->key
    TreeNode *rightFloor = _floor(node->right, key);
    if (rightFloor == nullptr)
        return node;
    else
        return rightFloor;
}

key_t AdjTree::floor(int key)
{
    if (empty())
        throw std::out_of_range("Invalid call to floor() with empty container");

    TreeNode *queryNode = _floor(root, key);
    if (queryNode == nullptr)
        throw std::out_of_range("Argument to floor() is too small");
    else
        return queryNode->key;
}

AdjTree::TreeNode *AdjTree::_ceiling(TreeNode *node, int key) const
{
    if (node == nullptr)
        return node;

    if (key == node->key)
        return node;
    else if (key > node->key)
        return _ceiling(node->right, key);

    // Query key is less than node->key
    TreeNode *leftCeiling = _ceiling(node->left, key);
    if (leftCeiling == nullptr)
        return node;
    else
        return leftCeiling;
}

key_t AdjTree::ceiling(int key)
{
    if (empty())
        throw std::out_of_range("Invalid call to ceiling() with empty container");

    TreeNode *queryNode = _ceiling(root, key);
    if (queryNode == nullptr)
        throw std::out_of_range("Argument to ceiling() is too large");
    else
        return queryNode->key;
}

int AdjTree::_rankSelect(TreeNode *node, int rank) const
{
    if (node == nullptr)
        throw std::logic_error("Rank select did not find key matching query rank");

    size_t leftSize = nodeSize(node->left);
    if (rank < leftSize)
        return _rankSelect(node->left, rank);
    else if (rank > leftSize)
        return _rankSelect(node->right, rank - leftSize - 1);
    else
        return node->key;
}

key_t AdjTree::rankSelect(int rank)
{
    if (empty())
        throw std::out_of_range("Invalid call to rankSelect() with empty container");
    if (rank < 0 || rank >= size())
        throw std::out_of_range("Argument to rankSelect() is invalid");

    key_t queryKey = _rankSelect(root, rank); // Defensive copy
    return queryKey;
}

/**
 * Red-black scheme helpers
 */

// Tree rotation & coloring

bool AdjTree::isRed(TreeNode *node)
{
    if (node == nullptr)
        return TreeNode::BLACK;
    else
        return node->color;
}

AdjTree::TreeNode *AdjTree::rotateLeft(TreeNode *node)
{
    TreeNode *newNode = node->right;
    node->right = newNode->left;
    newNode->left = node;

    // Enforce color
    newNode->color = newNode->left->color;
    newNode->left->color = TreeNode::RED;

    // Size update
    newNode->sz = node->sz;
    node->sz = 1 + nodeSize(node->left) + nodeSize(node->right);
    return newNode;
}

AdjTree::TreeNode *AdjTree::rotateRight(TreeNode *node)
{
    TreeNode *newNode = node->left;
    node->left = newNode->right;
    newNode->right = node;

    // Enforce color
    newNode->color = newNode->right->color;
    newNode->right->color = TreeNode::RED;

    // Size update
    newNode->sz = node->sz;
    node->sz = 1 + nodeSize(node->left) + nodeSize(node->right);
    return newNode;
}

void AdjTree::flipColors(TreeNode *node)
{
    node->color = !node->color;
    node->left->color = !node->left->color;
    node->right->color = !node->right->color;
}

// Fixup during insertion

AdjTree::TreeNode *AdjTree::rbFix(TreeNode *node)
{
    if (isRed(node->right) && !isRed(node->left))
        node = rotateLeft(node);
    if (isRed(node->left) && isRed(node->left->left))
        node = rotateRight(node);
    if (isRed(node->left) && isRed(node->right))
        flipColors(node);

    node->sz = 1 + nodeSize(node->left) + nodeSize(node->right);
    return node;
}

// Deletion 2-node fixups

AdjTree::TreeNode *AdjTree::moveRedLeft(TreeNode *node)
{
    flipColors(node);
    if (isRed(node->right->left))
    {
        node->right = rotateRight(node->right);
        node = rotateLeft(node);
        flipColors(node);
    }

    return node;
}

AdjTree::TreeNode *AdjTree::moveRedRight(TreeNode *node)
{
    flipColors(node);
    if (isRed(node->left->left))
    {
        node = rotateRight(node);
        flipColors(node);
    }

    return node;
}

/**
 * Insertion
 */

AdjTree::TreeNode *AdjTree::_insert(TreeNode *node, int key)
{
    // Recursive insertion
    if (node == nullptr)
    {
        TreeNode *newNode = new TreeNode(key, TreeNode::RED);
        if (!newNode)
            throw std::bad_alloc();
        return newNode;
    }

    if (key < node->key)
        node->left = _insert(node->left, key);
    else if (key > node->key)
        node->right = _insert(node->right, key);
    else
        node->key = key;

    // Maintain red-black scheme
    node = rbFix(node);

    node->sz = 1 + nodeSize(node->left) + nodeSize(node->right);
    return node;
}

void AdjTree::insert(int key)
{
    root = _insert(root, key);
    root->color = TreeNode::BLACK;
}

/**
 * Deletion
 */

AdjTree::TreeNode *AdjTree::_eraseMin(TreeNode *node)
{
    if (node->left == nullptr)
    {
        delete node;
        return nullptr;
    }

    // Fix 2-node if necessary
    if (!isRed(node->left) && !isRed(node->left->left))
        node = moveRedLeft(node);

    node->left = _eraseMin(node->left);

    // Backtrack clean up transformation
    return rbFix(node);
}

AdjTree::TreeNode *AdjTree::_erase(TreeNode *node, int key)
{
    if (key < node->key)
    {
        // Push red link right if 2-node
        if (!isRed(node->left) && !isRed(node->left->left))
            node = moveRedLeft(node);

        node->left = _erase(node->left, key);
    }
    else
    {
        if (isRed(node->left))
            node = rotateRight(node);

        // Simple case: leaf node deletion
        if (key == node->key && node->right == nullptr)
        {
            delete node;
            return nullptr;
        }

        // Push red right if two black nodes
        if (!isRed(node->right) && !isRed(node->right->left))
            node = moveRedRight(node);

        // Complex case: branch node deletion
        if (key == node->key)
        {
            auto subtreeMin = [](TreeNode *start)
            {
                TreeNode *cur = start;
                while (cur->left != nullptr)
                    cur = cur->left;
                return cur->key;
            };
            node->key = subtreeMin(node->right);
            node->right = _eraseMin(node->right);
        }
        else
            node->right = _erase(node->right, key);
    }

    // Backtrack clean up transformation
    return rbFix(node);
}

void AdjTree::erase(int key)
{
    if (root == nullptr)
        throw std::out_of_range("Invalid erase from empty container");
    if (!contains(key))
        throw std::out_of_range("Erase query key not found");

    if (!isRed(root->left) && !isRed(root->right))
        root->color = TreeNode::RED;

    root = _erase(root, key);

    if (!empty())
        root->color = TreeNode::BLACK;
}

/**
 * Inorder iterator
 */

AdjTree::Iterator::Iterator(const AdjTree &tree)
{
    TreeNode *temp = tree.root;
    while (temp)
    {
        nodeStack.push_front(temp);
        temp = temp->left;
    }
}

int &AdjTree::Iterator::operator*()
{
    if (nodeStack.empty())
        throw std::out_of_range("Invalid attempt to dereference null iterator");
    return nodeStack.front()->key;
}

int *AdjTree::Iterator::operator->()
{
    if (nodeStack.empty())
        throw std::out_of_range("Invalid attempt access pointer with null iterator");
    return &(nodeStack.front()->key);
}

bool AdjTree::Iterator::operator==(Iterator that) const
{
    if (this->nodeStack.empty() && that.nodeStack.empty())
        return true;
    else if (this->nodeStack.empty() || that.nodeStack.empty())
        return false;
    return this->nodeStack.front() == that.nodeStack.front();
}

bool AdjTree::Iterator::operator!=(Iterator that) const
{
    return !(*this == that);
}

void AdjTree::Iterator::operator++()
{
    if (nodeStack.empty())
        throw std::out_of_range("Iterator cannot be incremented past the end");

    TreeNode *cur = nodeStack.pop_front();

    if (cur->right)
    {
        cur = cur->right;
        while (cur)
        {
            nodeStack.push_front(cur);
            cur = cur->left;
        }
    }
}

AdjTree::Iterator AdjTree::begin()
{
    Iterator iter(*this);
    return iter;
}

AdjTree::Iterator AdjTree::end()
{
    Iterator iter(*this);
    iter.nodeStack.clear();
    return iter;
}

AdjTree::Iterator AdjTree::find(int key)
{
    TreeNode *cur = root;

    while (cur)
    {
        if (key == cur->key)
        {
            // Build iterator an clear stack
            Iterator iter(*this);
            iter.nodeStack.clear();
            iter.nodeStack.push_front(cur);
            return iter;
        }
        else if (key < cur->key)
            cur = cur->left;
        else
            cur = cur->right;
    }

    return end();
}

/**
 * Tree processing
 */

std::string AdjTree::serialize(const std::string &delim, const std::string &nilStr) const
{
    if (empty())
        throw std::out_of_range("Invalid serialization of empty container");

    // Reserve space: there will be 3 / 8 * size nil nodes on average.
    // Reserve 1 additional byte for the null character.
    std::string serializedTree;
    size_t sizeDiv8 = size() >> 3;
    size_t reserveSize = size() + (sizeDiv8 + sizeDiv8 + sizeDiv8) + 1;

    // Set upper bound to avoid buffer overflow
    size_t requestSize = reserveSize < 512 ? reserveSize : 512;
    serializedTree.reserve(requestSize);

    // Preorder DFS to serialize tree
    Deque<const TreeNode *> nodeStack;
    TreeNode const *cur;
    TreeNode const *curLeft;
    TreeNode const *curRight;
    nodeStack.push_back(root);

    while (nodeStack.size() > 0)
    {
        cur = nodeStack.pop_back();
        curLeft = cur->left;
        curRight = cur->right;

        serializedTree += std::to_string(cur->key) + delim;
        if (curRight != nullptr)
            nodeStack.push_back(curRight);
        if (curLeft != nullptr)
            nodeStack.push_back(curLeft);

        if (curLeft == nullptr && curRight == nullptr)
            serializedTree += nilStr;
    }

    return serializedTree;
}

size_t AdjTree::depth() const
{
    if (empty())
        return 0;

    Deque<TreeNode *> nodeQueue;
    Deque<size_t> depthQueue;

    nodeQueue.push_back(root);
    depthQueue.push_back(1);
    size_t maxDepth = 0;

    // Use BFS to find depth of the tree
    while (!nodeQueue.empty())
    {
        TreeNode *cur = nodeQueue.pop_front();
        size_t curDepth = depthQueue.pop_front();

        maxDepth = curDepth > maxDepth ? curDepth : maxDepth;

        if (cur->left != nullptr)
        {
            nodeQueue.push_back(cur->left);
            depthQueue.push_back(curDepth + 1);
        }
        if (cur->right != nullptr)
        {
            nodeQueue.push_back(cur->right);
            depthQueue.push_back(curDepth + 1);
        }
    }

    return maxDepth;
}

/**
 * Delete Tree
 */

void AdjTree::_deleteTree(TreeNode *node)
{
    if (node == nullptr)
        return;

    _deleteTree(node->left);
    _deleteTree(node->right);
    delete node;
}

AdjTree::~AdjTree()
{
    _deleteTree(root);
}
