#ifndef MAP_H
#define MAP_H

#include <iostream>
#include <functional>       // std::less
#include <utility>          // std::move
#include <iterator>         // bidirectional iterator tag
#include <tuple>            // std::pair
#include <initializer_list> // initializer_list

template<class Key, class T, class Compare = std::less<Key>>
class Map {
    private:
        // Color type to describe if a node is black or red
        enum class Color {Red, Black};

        // Node for Red-Black Tree
        struct RB_Node;

        // Bidirectional iterator
        template<typename _Tp>
        class RB_tree_iterator;

        // Reverse iterator
        template <typename _Tp>
        class reverse_RB_tree_iterator;

    public:
        using key_type               = Key;
        using mapped_type            = T;
        using value_type             = std::pair<const Key, T>;
        using key_compare            = Compare;
        
        using reference              = value_type&;
        using const_reference        = const value_type&;
        using pointer                = value_type*;
        using const_pointer          = const value_type*;

        using iterator               = RB_tree_iterator<value_type>;
        using const_iterator         = RB_tree_iterator<const value_type>;
        using reverse_iterator       = reverse_RB_tree_iterator<value_type>;
        using const_reverse_iterator = reverse_RB_tree_iterator<const value_type>;



        //////////////////////
        // Member Functions //
        //////////////////////
    
        /*
        Map();
        Map(Map& other);
        Map(Map&& other);
        ~Map();
        Map& operator=(Map& other);
        Map& operator=(Map&& other);

        // ITERATOR FUNCTIONS
        iterator begin() noexcept;
        const_iterator begin() const noexcept;
        iterator end() noexcept;
        const_iterator end() const noexcept;
        reverse_iterator rbegin() noexcept;
        const_reverse_iterator rbegin() const noexcept;
        reverse_iterator rend() noexcept;
        const_reverse_iterator rend() const noexcept;
        const_iterator cbegin() const noexcept;
        const_iterator cend() const noexcept;
        const_reverse_iterator crbegin() const noexcept;
        const_reverse_iterator crend() const noexcept;

        // CAPACITY FUNCTIONS
        bool empty() const noexcept;
        size_t size() const noexcept;

        // ELEMENT ACCESS
        mapped_type& operator[] (const key_type& k);
        mapped_type& operator[] (key_type&& k);
        mapped_type& at (const key_type& k);
        const mapped_type& at (const key_type& k) const;

        // MODIFIER FUNCTIONS
        std::pair<iterator,bool> insert (const value_type& val);
        std::pair<iterator,bool> insert (value_type&& val);
        void clear();

        */

    private:
        // Node for Red-Black Tree
        struct RB_Node {
            using value_type = std::pair<const Key, T>;

            value_type value;
            RB_Node* parent;
            RB_Node* left;
            RB_Node* right;
            Color color;

            RB_Node(value_type value = value_type(Key(), T()), RB_Node* parent = nullptr, RB_Node* left = nullptr, RB_Node* right = nullptr, Color color = Color::Red)
             : value{value}, parent{parent}, left{left}, right{right}, color{color} {}
        };

        // Converts enum Color to a string
        std::string color_string(Color c) {
            switch(c) {
                case Color::Red:
                    return "Red";
                default:
                    return "Black";
            }
        }

        template<typename _Tp>
        class RB_tree_iterator {
            public:
                using iterator_category     = std::bidirectional_iterator_tag;
                using difference_type       = ptrdiff_t;

                using value_type            = _Tp;
                using pointer               = _Tp*;
                using reference             = _Tp&;

                using _Self                 = RB_tree_iterator<_Tp>;

            private:
                friend class Map<Key, T, Compare>;
                using Node = typename Map<Key, T, Compare>::RB_Node;

                Node* n;

                explicit RB_tree_iterator(Node* ptr) noexcept: n{ptr} {}
                explicit RB_tree_iterator(const Node* ptr) noexcept: n{const_cast<Node*>(ptr)} {} 

            public:
                RB_tree_iterator() { n = nullptr; };
                RB_tree_iterator(const _Self&) = default;
                RB_tree_iterator(_Self&&) = default;
                ~RB_tree_iterator() = default;
                _Self& operator=(const _Self&) = default;
                _Self& operator=(_Self&&) = default;

                reference operator*() const { return n->value; }
                pointer operator->() const { return &(n->value); }

                // Prefix Increment: ++a
                _Self& operator++() {
                    if (n->right) {
                        // If there is a right, leftmost node in right subtree is successor
                        n = n->right;
        
                        while (n->left) {
                            n = n->left;
                        }
                    } else {
                        // If there is no right, then go up until you find an unexplored right
                        // The ending node would be the next inorder successor
                        Node* p = n->parent;

                        while (n == p->right) {
                            n = p;
                            p = p->parent;
                        }

                        if (n->right != p) {
                            n = p;
                        }
                    }

                    return *this;
                }
                // Postfix Increment: a++
                _Self operator++(int) {
                    _Self temp(*this);
                    ++(*this);

                    return temp;
                }
                // Prefix Decrement: --a
                _Self& operator--() {
                    if (n->left) {
                        // If there is a left, rightmost node in left subtree is predecessor
                        n = n->left;
        
                        while (n->right) {
                            n = n->right;
                        }
                    } else {
                        // If there is no left, then go up until you find an unexplored left
                        // The ending node would be the next inorder predecessor
                        Node* p = n->parent;

                        while (n == p->left) {
                            n = p;
                            p = p->parent;
                        }

                        if (n->left != p) {
                            n = p;
                        }
                    }

                    return *this;
                }
                // Postfix Decrement: a--
                _Self operator--(int) {
                    _Self temp(*this);
                    --(*this);
            
                    return temp;
                }

                bool operator==(const _Self& other) const noexcept { return n == other.n; }
                bool operator!=(const _Self& other) const noexcept { return n != other.n; }
        };

        template <typename _Tp>
        class reverse_RB_tree_iterator {
            public:
                using iterator_category     = std::bidirectional_iterator_tag;
                using difference_type       = ptrdiff_t;

                using value_type            = _Tp;
                using pointer               = _Tp*;
                using reference             = _Tp&;

                using _Self                 = reverse_RB_tree_iterator<_Tp>;
            private:
                friend class Map<Key, T, Compare>;
                using Node = typename Map<Key, T, Compare>::RB_Node;

                Node* n;

                explicit reverse_RB_tree_iterator(Node* ptr) noexcept : n{ptr} {}
                explicit reverse_RB_tree_iterator(const Node* ptr) noexcept : n{const_cast<Node*>(ptr)} {}

            public:
                reverse_RB_tree_iterator() { n = nullptr; };
                reverse_RB_tree_iterator(const _Self&) = default;
                reverse_RB_tree_iterator(_Self&&) = default;
                ~reverse_RB_tree_iterator() = default;
                _Self& operator=(const _Self&) = default;
                _Self& operator=(_Self&&) = default;

                reference operator*() const { return n->value; }
                pointer operator->() const { return &(n->value); }

                // Prefix Increment: ++a
                _Self& operator++() {
                    if (n->left) {
                        // If there is a left, rightmost node in left subtree is predecessor
                        n = n->left;
        
                        while (n->right) {
                            n = n->right;
                        }
                    } else {
                        // If there is no left, then go up until you find an unexplored left
                        // The ending node would be the next inorder predecessor
                        Node* p = n->parent;

                        while (n == p->left) {
                            n = p;
                            p = p->parent;
                        }

                        if (n->left != p) {
                            n = p;
                        }
                    }

                    return *this;
                }
                // Postfix Increment: a++
                _Self operator++(int) {
                    _Self temp(*this);
                    ++(*this);

                    return temp;
                }
                // Prefix Decrement: --a
                _Self& operator--() {
                    if (n->right) {
                        // If there is a right, leftmost node in right subtree is successor
                        n = n->right;
        
                        while (n->left) {
                            n = n->left;
                        }
                    } else {
                        // If there is no right, then go up until you find an unexplored right
                        // The ending node would be the next inorder successor
                        Node* p = n->parent;

                        while (n == p->right) {
                            n = p;
                            p = p->parent;
                        }

                        if (n->right != p) {
                            n = p;
                        }
                        
                    }

                    return *this;
                }
                // Postfix Decrement: a--
                _Self operator--(int) {
                    _Self temp(*this);
                    --(*this);

                    return temp;
                }

                bool operator==(const _Self& other) const noexcept { return n == other.n; }
                bool operator!=(const _Self& other) const noexcept { return n != other.n; }
        };


    
        //////////////////////
        // Member variables //
        //////////////////////
    
        // _head.parent = root
        // _head.left = minimum
        // _head.right = maximum
        // This is for O(1) begin() and end()
        RB_Node _head;
        size_t _size;
        key_compare _comp;



        //////////////////////
        // HELPER FUNCTIONS //
        //////////////////////

        // Recursive helper function for deleting a tree
        void deleteHelper(RB_Node*& node) {
            if (node == nullptr) {
                return;
            }

            if (node->left != nullptr) {
                deleteHelper(node->left);
            }

            if (node->right != nullptr) {
                deleteHelper(node->right);
            }

            delete node;
            node = nullptr;
        }

        // Recursive helper function for copying a tree
        RB_Node* copyHelper(RB_Node* otherRoot, const RB_Node* otherHead) {
            if (otherRoot == nullptr) {
                return nullptr;
            }

            RB_Node* left = copyHelper(otherRoot->left, otherHead);
            RB_Node* right = copyHelper(otherRoot->right, otherHead);

            RB_Node* temp = new RB_Node(otherRoot->value, nullptr, left, right, otherRoot->color);

            if (left) {
                left->parent = temp;
            }

            if (right) {
                right->parent = temp;
            }

            // Ensure that the new _head has access to min and max elements
            if (otherRoot == otherHead->left) {
                _head.left = temp;
            }

            if (otherRoot == otherHead->right) {
                _head.right = temp;
            }

            return temp;

        }

        // Recursive helper function for finding a value
        RB_Node* findHelper(RB_Node* node, const key_type& x) {
            if (node == nullptr) {
                return nullptr;
            }

            if (node->value.first == x) { // If at correct node, return it
                return node;
            } else if (_comp(x, node->value.first)) { // If current node is greater, go left
                return findHelper(node->left, x);
            } else { // Otherwise, go right
                return findHelper(node->right, x);
            }
        }

        const RB_Node* findHelper(const RB_Node* node, const key_type& x) const {
            if (node == nullptr) {
                return nullptr;
            }

            if (node->value.first == x) { // If at correct node, return it
                return node;
            } else if (_comp(x, node->value.first)) { // If current node is greater, go left
                return findHelper(node->left, x);
            } else { // Otherwise, go right
                return findHelper(node->right, x);
            }
        }

        // Recursive helper function for inserting a new node into a tree
        std::pair<RB_Node*, bool> insertHelper(RB_Node* node, const value_type& x) {
            if (x.first == node->value.first) {
                //node->value.second = x.second;
                return std::pair<RB_Node*, bool>(node, false);
            } else if (_comp(x.first, node->value.first)) { // If less than current node, move left
                if (node->left == nullptr) {
                    node->left = new RB_Node(x, node);
                    node->left->parent = node;
                    _size++;
                    return std::pair<RB_Node*, bool>(node->left, true);
                } else {
                    return insertHelper(node->left, x);
                }
            } else { // If more than current node, move right
                if (node->right == nullptr) {
                    node->right = new RB_Node(x, node);
                    node->right->parent = node;
                    _size++;
                    return std::pair<RB_Node*, bool>(node->right, true);
                } else {
                    return insertHelper(node->right, x);
                }
            }
        }

        // Recursive helper function for inserting a new node into a tree
        std::pair<RB_Node*, bool> insertHelper(RB_Node* node, value_type&& x) {
            if (x.first == node->value.first) {
                //node->value.second = std::move(x.second);
                return std::pair<RB_Node*, bool>(node, false);
            } else if (_comp(x.first, node->value.first)) { // If less than current node, move left
                if (node->left == nullptr) {
                    node->left = new RB_Node(std::move(x), node);
                    node->left->parent = node;
                    _size++;
                    return std::pair<RB_Node*, bool>(node->left, true);
                } else {
                    return insertHelper(node->left, std::move(x));
                }
            } else { // If more than current node, move right
                if (node->right == nullptr) {
                    node->right = new RB_Node(std::move(x), node);
                    node->right->parent = node;
                    _size++;
                    return std::pair<RB_Node*, bool>(node->right, true);
                } else {
                    return insertHelper(node->right, std::move(x));
                }
            }
        }

        bool eraseHelper(RB_Node* node, const key_type& x) {
            if (node == nullptr) {
                return false;
            }

            if (_size == 1) {
                if (!_comp(node->value.first, x) && !_comp(x, node->value.first)) {
                    delete node;
                    _head.parent = nullptr;
                    _head.left = &_head;
                    _head.right = &_head;
                    _size--;
                    return true;
                }
                return false;
            }

            // Step 1: Find the node to delete
            if (_comp(x, node->value.first)) {
                return eraseHelper(node->left, x);
            } else if (_comp(node->value.first, x)) {
                return eraseHelper(node->right, x);
            } else { // Correct node has been found
                // Ensure that min and max behavior is preserved for O(1)
                // begin() and end()
                if (node == _head.left) {
                    _head.left = inorderSuccessor(node);
                }
                if (node == _head.right) {
                    _head.right = inorderPredecessor(node);
                }

                // Step 2: Convert to leaf node
                if (node->right) {
                    RB_Node* replacement = inorderSuccessor(node);
                    swapNodes(node, replacement);
                    return eraseHelper(node, x);
                } else if (node->left) {
                    RB_Node* replacement = inorderPredecessor(node);
                    swapNodes(node, replacement);
                    return eraseHelper(node, x);
                } else { // Node to delete is a leaf
                    // If Red, just delete
                    if (node->color == Color::Red) {
                        if (node->parent->left == node) {
                            node->parent->left = nullptr;
                        } else if (node->parent->right == node){
                            node->parent->right = nullptr;
                        } else {
                            node->parent->parent = nullptr;
                        }

                        delete node;
                        _size--;
                        return true;
                    } else { // If black, determine case to fix
                        resolveDB(node);

                        if (node->parent->left == node) {
                            node->parent->left = nullptr;
                        } else {
                            node->parent->right = nullptr;
                        }

                        delete node;
                        _size--;
                        return true;
                    }
                }
            }
        }

        void resolveDB(RB_Node* n) {
            // If DB is root, then is fine
            if (n == _head.parent) {
                return;
            }

           // Determine what side is sibling
            RB_Node* sibling;
            bool onLeft = (n->parent->left == n);

            if (onLeft) {
                // Sibling is right child 
                sibling = n->parent->right;
            } else {
                // Sibling is left child
                sibling = n->parent->left;
            }

            // Far child and near child of sibling
            RB_Node* farChild = onLeft? (sibling->right): (sibling->left);
            RB_Node* nearChild = onLeft? (sibling->left): (sibling->right);

            // If DB sibling is black
            if (sibling->color == Color::Black) {
                // If sibling has 2 black children
                if (bothChildBlack(sibling)) {
                    sibling->color = Color::Red;
                    if (n->parent->color == Color::Red) {
                        n->parent->color = Color::Black;
                    } else {
                        resolveDB(n->parent);
                    }
                // Far child is black and near child is red
                } else if ((!farChild || farChild->color == Color::Black) && nearChild->color == Color::Red) {
                    std::swap(nearChild->color, sibling->color);

                    if (onLeft) {
                        n->parent->right = rightRotation(sibling);
                        n->parent->right->parent = n->parent;
                    } else {
                        n->parent->left = leftRotation(sibling);
                        n->parent->left->parent = n->parent;
                    }

                    resolveDB(n);
                // Far child is red
                } else if (farChild->color == Color::Red) {
                    // Swap parent and sibling colors
                    std::swap(n->parent->color, sibling->color);

                    RB_Node* grandparent = n->parent->parent;
                    if (onLeft) {
                        if (grandparent->left == n->parent) {
                            grandparent->left = leftRotation(n->parent);
                        } else if (grandparent->right == n->parent) {
                            grandparent->right = leftRotation(n->parent);
                        } else if (grandparent->parent == n->parent) {
                            grandparent->parent = leftRotation(n->parent);
                        }
                        n->parent->parent->parent = grandparent;
                    } else {
                        if (grandparent->left == n->parent) {
                            grandparent->left = rightRotation(n->parent);
                        } else if (grandparent->right == n->parent) {
                            grandparent->right = rightRotation(n->parent);
                        } else if (grandparent->parent == n->parent) {
                            grandparent->parent = rightRotation(n->parent);
                        }
                        n->parent->parent->parent = grandparent;
                    }

                    farChild->color = Color::Black;
                }
            } else { // If DB sibling is red
                std::swap(n->parent->color, sibling->color);

                RB_Node* grandparent = n->parent->parent;
                if (onLeft) {
                    if (grandparent->left == n->parent) {
                        grandparent->left = leftRotation(n->parent);
                    } else if (grandparent->right == n->parent) {
                        grandparent->right = leftRotation(n->parent);
                    }
                    n->parent->parent->parent = grandparent;
                } else {
                    if (grandparent->left == n->parent) {
                        grandparent->left = rightRotation(n->parent);
                    } else if (grandparent->right == n->parent) {
                        grandparent->right = rightRotation(n->parent);
                    }
                    n->parent->parent->parent = grandparent;
                }

                resolveDB(n);
            }
        }

        bool bothChildBlack(RB_Node* n) {
            if (n->left == nullptr && n->right == nullptr) {
                return true;
            }

            if (n->left == nullptr || n->right == nullptr) {
                return false;
            }

            if (n->left->color == Color::Black && n->right->color == Color::Black) {
                return true;
            }

            return false;
        }

        // n1 and n2 should be valid nodes (not nullptr)
        // Used for eraseHelper
        void swapNodes(RB_Node* n1, RB_Node* n2) {
            if (n1 == n2) {
                return;
            } else {
                RB_Node* temp;

                // Assign new parents
                if (n1->parent->right == n1) {
                    n1->parent->right = n2;
                }
                if (n1->parent->left == n1) {
                    n1->parent->left = n2;
                }
                if (n1->parent->parent == n1) {
                    n1->parent->parent = n2;
                }
                if (n2->parent->right == n2) {
                    n2->parent->right = n1;
                } 
                if (n2->parent->left == n2) {
                    n2->parent->left = n1;
                }
                if (n2->parent->parent == n2) {
                    n2->parent->parent = n1;
                }
                temp = std::move(n2->parent);
                n2->parent = std::move(n1->parent);
                n1->parent = std::move(temp);

                // Assign new left children
                temp = std::move(n2->left);
                n2->left = std::move(n1->left);
                n1->left = std::move(temp);
                if (n1->left) {
                    n1->left->parent = n1;
                }
                if (n2->left) {
                    n2->left->parent = n2;
                }

                // Assign new right children
                temp = std::move(n2->right);
                n2->right = std::move(n1->right);
                n1->right = std::move(temp);
                if (n1->right) {
                    n1->right->parent = n1;
                }
                if (n2->right) {
                    n2->right->parent = n2;
                }

                //Preserve original colors of nodes
                Color c = std::move(n1->color);
                n1->color = std::move(n2->color);
                n2->color = std::move(c);
                
            }
        }

        RB_Node* inorderSuccessor(RB_Node* node) {
            if (node->right) {
                // If there is a right, leftmost node in right subtree is successor
                node = node->right;

                while (node->left) {
                    node = node->left;
                }
            } else {
                // If there is no right, then go up until you find an unexplored right
                // The ending node would be the next inorder successor
                RB_Node* p = node->parent;

                while (node == p->right) {
                    node = p;
                    p = p->parent;
                }

                if (node->right != p) {
                    node = p;
                }
            }

            return node;
        }

        RB_Node* inorderPredecessor(RB_Node* node) {
            if (node->left) {
                // If there is a left, rightmost node in left subtree is predecessor
                node = node->left;

                while (node->right) {
                    node = node->right;
                }
            } else {
                // If there is no left, then go up until you find an unexplored left
                // The ending node would be the next inorder predecessor
                RB_Node* p = node->parent;

                while (node == p->left) {
                    node = p;
                    p = p->parent;
                }

                if (node->left != p) {
                    node = p;
                }
            }

            return node;
        }

        RB_Node* boundHelper(RB_Node* node, const key_type& x) {
            if (node == nullptr) {
                return nullptr;
            }

            if (node->value.first == x) { // If at correct node, return it
                return node;
            } else if (_comp(x, node->value.first)) { // If current node is greater, go left
                if (node->left) {
                    return boundHelper(node->left, x);
                } else {
                    return node;
                }
            } else { // Otherwise, go right

                if (node->right) {
                    return boundHelper(node->right, x);
                } else {
                    return node;
                }
                
            }
        }

        const RB_Node* boundHelper(RB_Node* node, const key_type& x) const {
            if (node == nullptr) {
                return nullptr;
            }

            if (node->value.first == x) { // If at correct node, return it
                return node;
            } else if (_comp(x, node->value.first)) { // If current node is greater, go left
                if (node->left) {
                    return boundHelper(node->left, x);
                } else {
                    return node;
                }
            } else { // Otherwise, go right

                if (node->right) {
                    return boundHelper(node->right, x);
                } else {
                    return node;
                }
                
            }
        }


        /////////////////////////
        // REBALANCING HELPERS //
        /////////////////////////

        // Function for a right rotation
        RB_Node* rightRotation(RB_Node* root) {
            RB_Node* temp = root->left->right;
            RB_Node* newRoot = root->left;

            root->left->right = root;
            root->left = temp;
            root->parent = newRoot;
            if (temp) {
                temp->parent = root;
            }

            return newRoot;
        }

        // Function for a left rotation
        RB_Node* leftRotation(RB_Node* root) {
            RB_Node* temp = root->right->left;
            RB_Node* newRoot = root->right;

            root->right->left = root;
            root->right = temp;
            root->parent = newRoot;
            if (temp) {
                temp->parent = root;
            }

            return newRoot;
        }

        // Function for recoloring a node and its children
        void recolor(RB_Node* root) {
            root->color = Color::Red;
            root->left->color = Color::Black;
            root->right->color = Color::Black;
        }

        // Recursive helper function for rebalancing a tree
        RB_Node* rebalanceHelper(RB_Node* node) {

            // No rebalancing if nullptr
            if (node == nullptr) {
                return nullptr;
            }

            // Assign left child to rebalanced left subtree
            node->left = rebalanceHelper(node->left);
            if (node->left) {
                node->left->parent = node;
            }

            // Assign right child to rebalanced right subtree
            node->right = rebalanceHelper(node->right);
            if (node->right) {
                node->right->parent = node;
            }

            if (node->left != nullptr && node->left->left != nullptr) {

                if (node->left->color == Color::Red && node->left->left->color == Color::Red) {

                    if (node->right != nullptr && node->right->color == Color::Red) { // Uncle is red (recolor)
                        recolor(node);

                        return node;
                    } else { // Right rotation
                        RB_Node* newRoot = rightRotation(node);
                        newRoot->color = Color::Black;
                        node->color = Color::Red;

                        return newRoot;
                    }
                }
            } 
            
            if (node->left != nullptr && node->left->right != nullptr) {
                if (node->left->color == Color::Red && node->left->right->color == Color::Red) {
                    if (node->right != nullptr && node->right->color == Color::Red) { // Uncle is red (recolor)
                        recolor(node);

                        return node;
                    } else { // Double right rotation
                        node->left = leftRotation(node->left);
                        node->left->parent = node;
                        RB_Node* newRoot = rightRotation(node);
                        node->color = Color::Red;
                        newRoot->color = Color::Black;

                        return newRoot;
                    }
                }
            } 
            
            if (node->right != nullptr && node->right->right != nullptr) {

                if (node->right->color == Color::Red && node->right->right->color == Color::Red) {

                    if (node->left != nullptr && node->left->color == Color::Red) { // Uncle is red (recolor)
                        recolor(node);

                        return node;
                    } else { // Left rotation
                        RB_Node* newRoot = leftRotation(node);
                        newRoot->color = Color::Black;
                        node->color = Color::Red;

                        return newRoot;
                    }
                }
            } 
            
            if (node->right != nullptr && node->right->left != nullptr) {
                if (node->right->color == Color::Red && node->right->left->color == Color::Red) {
                    if (node->left != nullptr && node->left->color == Color::Red) { // Uncle is red (recolor)
                        recolor(node);

                        return node;
                    } else { // Double left rotation
                        node->right = rightRotation(node->right);
                        node->right->parent = node;
                        RB_Node* newRoot = leftRotation(node);
                        node->color = Color::Red;
                        newRoot->color = Color::Black;

                        return newRoot;
                    }
                }
            }

            // If no changes need to be made, return the subtree
            return node;
        }

        // Function for rebalancing a tree
        void rebalance() {
            // New root after rebalancing
            _head.parent = rebalanceHelper(_head.parent);
            _head.parent->parent = &_head;

            // Root must be black
            if (_head.parent->color != Color::Black) {
                _head.parent->color = Color::Black;
            }
        }

    public:
        Map(): _head(), _size(0) {
            _head.left = &_head;
            _head.right = &_head;
        }

        template <class InputIter>
        Map(InputIter first, InputIter last): _head(value_type(), nullptr, &_head, &_head), _size(0) {
            while (first != last) {
                insert(*first);
                first++;
            }
        }

        Map(std::initializer_list<value_type> il): _head(value_type(), nullptr, &_head, &_head), _size(0) {
            for (auto i = il.begin(); i != il.end(); i++) {
                insert(*i);
            }
        }

        Map(const Map& other): _head(), _size(other._size), _comp(other._comp) {
            _head.parent = copyHelper(other._head.parent, &other._head);
            _head.parent->parent = &_head;
        }

        Map(Map&& other): _head(), _size(other._size), _comp(other._comp) {
            _head.parent = other._head.parent;
            if (_size > 0) {
                other._head.parent->parent = &_head;
                _head.left = other._head.left;
                _head.right = other._head.right;
            } else {
                _head.parent = nullptr;
                _head.left = &_head;
                _head.right = &_head;
            }

            other._head.parent = nullptr;
            other._head.left = &other._head;
            other._head.right = &other._head;
            other._size = 0;
        } 

        ~Map() {
            clear();
        } 

        Map& operator=(const Map& other) {
            if (this == &other) {
                return *this;
            }
            
            if (!empty()) {
                clear();
            }

            _head.parent = copyHelper(other._head.parent, &other._head);
            _head.parent->parent = &_head;
            _size = other._size;
            _comp = other._comp;

            return *this;
        }

        Map& operator=(Map&& other) {
            if (this == &other) {
                return *this;
            }
            
            if (!empty()) {
                clear();
            }

            _head.parent = other._head.parent;
            if (other._size > 0) {
                other._head.parent->parent = &_head;
                _head.left = other._head.left;
                _head.right = other._head.right;
            } else {
                _head.parent = nullptr;
                _head.left = &_head;
                _head.right = &_head;
            }
            _size = other._size;
            _comp = other._comp;

            other._head.parent = nullptr;
            other._head.left = &other._head;
            other._head.right = &other._head;
            other._size = 0;

            return *this;
        }

        Map& operator=(std::initializer_list<value_type> il) {
            if (!empty()) {
                clear();
            }

            _head.parent = nullptr;
            _head.left = &_head;
            _head.right = &_head;

            for (auto i = il.begin(); i != il.end(); i++) {
                insert(*i);
            }

            return *this;
        }

        // ITERATOR FUNCTIONS
        iterator begin() noexcept {
            return iterator(_head.left);
        }

        const_iterator begin() const noexcept {
            return const_iterator(_head.left);
        }

        iterator end() noexcept {
            return iterator(&_head);
        }

        const_iterator end() const noexcept {
            return const_iterator(&_head);
        }

        reverse_iterator rbegin() noexcept {
            return reverse_iterator(_head.right);
        }

        const_reverse_iterator rbegin() const noexcept {
            return const_reverse_iterator(_head.right);
        }

        reverse_iterator rend() noexcept {
            return reverse_iterator(&_head);
        }

        const_reverse_iterator rend() const noexcept {
            return const_reverse_iterator(&_head);
        }

        const_iterator cbegin() const noexcept {
            return const_iterator(_head.left);
        }

        const_iterator cend() const noexcept {
            return const_iterator(&_head);
        }

        const_reverse_iterator crbegin() const noexcept {
            return const_reverse_iterator(_head.right);
        }

        const_reverse_iterator crend() const noexcept {
            return const_reverse_iterator(&_head);
        }

        // CAPACITY FUNCTIONS
        bool empty() const noexcept { return _size == 0; }
        size_t size() const noexcept { return _size; }

        // ELEMENT ACCESS
        mapped_type& operator[] (const key_type& k) {
            if (!_head.parent) { // Add root if tree is empty
                _head.parent = new RB_Node({k, mapped_type()});
                _head.parent->color = Color::Black;
                _head.right = _head.parent;
                _head.left = _head.parent;
                _head.parent->parent = &_head;
                _size++;

                return _head.parent->value.second;

            } else { // Insert and rebalance
                std::pair<RB_Node*, bool> temp = insertHelper(_head.parent, {std::move(k), mapped_type()});

                // If there is a new minimum, replace it
                if (_comp(temp.first->value.first, _head.left->value.first)) {
                    _head.left = temp.first;
                }

                // If there is a new maximum, replace it
                if (_comp(_head.right->value.first, temp.first->value.first)) {
                    _head.right = temp.first;
                }

                rebalance();

                return temp.first->value.second;
            }
        }

        mapped_type& operator[] (key_type&& k) {
            if (!_head.parent) { // Add root if tree is empty
                _head.parent = new RB_Node({std::move(k), mapped_type()});
                _head.parent->color = Color::Black;
                _head.right = _head.parent;
                _head.left = _head.parent;
                _head.parent->parent = &_head;
                _size++;

                return _head.parent->value.second;

            } else { // Insert and rebalance
                std::pair<RB_Node*, bool> temp = insertHelper(_head.parent, {std::move(k), mapped_type()});

                // If there is a new minimum, replace it
                if (_comp(temp.first->value.first, _head.left->value.first)) {
                    _head.left = temp.first;
                }

                // If there is a new maximum, replace it
                if (_comp(_head.right->value.first, temp.first->value.first)) {
                    _head.right = temp.first;
                }

                rebalance();

                return temp.first->value.second;
            }
        }

        mapped_type& at (const key_type& k) {
            RB_Node* x = findHelper(_head.parent, k);

            if (!x) {
                throw std::out_of_range("Given key is not in map");
            }

            return x->value.second;
        }

        const mapped_type& at (const key_type& k) const {
            RB_Node* x = findHelper(_head.parent, k);

            if (!x) {
                throw std::out_of_range("Given key is not in map");
            }

            return x->value.second;
        }

        // MODIFIER FUNCTIONS
        std::pair<iterator,bool> insert (const value_type& val) {
            if (!_head.parent) { // Add root if tree is empty
                _head.parent = new RB_Node(val);
                _head.parent->color = Color::Black;
                _head.right = _head.parent;
                _head.left = _head.parent;
                _head.parent->parent = &_head;
                _size++;

                return std::pair<iterator, bool>(iterator(_head.parent), true);

            } else { // Insert and rebalance
                std::pair<RB_Node*, bool> temp = insertHelper(_head.parent, val);
                if (!temp.second) {
                    temp.first->value.second = val.second;
                }

                // If there is a new minimum, replace it
                if (_comp(temp.first->value.first, _head.left->value.first)) {
                    _head.left = temp.first;
                }

                // If there is a new maximum, replace it
                if (_comp(_head.right->value.first, temp.first->value.first)) {
                    _head.right = temp.first;
                }

                rebalance();

                return std::pair<iterator, bool>(iterator(temp.first), temp.second);
            }
        }

        std::pair<iterator,bool> insert (value_type&& val) {
            if (!_head.parent) { // Add root if tree is empty
                _head.parent = new RB_Node(std::move(val));
                _head.parent->color = Color::Black;
                _head.right = _head.parent;
                _head.left = _head.parent;
                _head.parent->parent = &_head;
                _size++;

                return std::pair<iterator, bool>(iterator(_head.parent), true);

            } else { // Insert and rebalance
                std::pair<RB_Node*, bool> temp = insertHelper(_head.parent, std::move(val));
                if (!temp.second) {
                    temp.first->value.second = std::move(val.second);
                }

                // If there is a new minimum, replace it
                if (_comp(temp.first->value.first, _head.left->value.first)) {
                    _head.left = temp.first;
                }

                // If there is a new maximum, replace it
                if (_comp(_head.right->value.first, temp.first->value.first)) {
                    _head.right = temp.first;
                }

                rebalance();

                return std::pair<iterator, bool>(iterator(temp.first), temp.second);
            }
        }

        iterator erase( iterator pos ) {
            iterator temp(pos.n);
            temp++;
            eraseHelper(pos.n, pos->first);

            return temp;
        }

        iterator erase(const_iterator pos) {
            iterator temp(pos.n);
            temp++;
            eraseHelper(pos.n, pos->first);

            return temp;
        }

        size_t erase(const key_type& k) {
            if (eraseHelper(_head.parent, k)) {
                return 1;
            } else {
                return 0;
            }
        }

        iterator erase(const_iterator first, const_iterator last) {
            while (first != last) {
                erase(first);
            }

            return last;
        }

        void swap(Map& x) {
            Map temp = std::move(*this);
            *this = std::move(x);
            x = std::move(temp);
        }

        // Empties the map
        void clear() {
            deleteHelper(_head.parent);
            _head.parent= nullptr;
            _head.left = &_head;
            _head.right = &_head;
            _size = 0;
        }

        // OBSERVER FUNCTIONS
        key_compare key_comp() const { return _comp; }

        // OPERATION FUNCTIONS
        iterator find(const key_type& k) {
            RB_Node* temp = findHelper(_head.parent, k);

            if (temp) {
                return iterator(temp);
            }

            return end();
        }

        const_iterator find(const key_type& k) const {
            RB_Node* temp = findHelper(_head.parent, k);

            if (temp) {
                return iterator(temp);
            }

            return end();
        }

        size_t count(const key_type& k) const {
            return (findHelper(_head.parent, k))? 1: 0;
        }

        iterator lower_bound(const key_type& k) {
            RB_Node* temp = boundHelper(_head.parent, k);

            if (temp) {
                if (_comp(temp->value.first, k)) {
                    return ++iterator(temp);
                } else {
                    return iterator(temp);
                }
            } else {
                return end();
            }
        }

        const_iterator lower_bound(const key_type& k) const {
            RB_Node* temp = boundHelper(_head.parent, k);

            if (temp) {
                if (_comp(temp->value.first, k)) {
                    return ++const_iterator(temp);
                } else {
                    return const_iterator(temp);
                }
            } else {
                return end();
            }
        }

        iterator upper_bound(const key_type& k) {
            RB_Node* temp = boundHelper(_head.parent, k);

            if (temp) {
                if (_comp(k, temp->value.first)) {
                    return --iterator(temp);
                } else {
                    return iterator(temp);
                }
            } else {
                return end();
            }
        }

        const_iterator upper_bound(const key_type& k) const {
            RB_Node* temp = boundHelper(_head.parent, k);

            if (temp) {
                if (_comp(k, temp->value.first)) {
                    return --const_iterator(temp);
                } else {
                    return const_iterator(temp);
                }
            } else {
                return end();
            }
        }

        std::pair<const_iterator, const_iterator> equal_range(const key_type& k) const {
            const RB_Node* temp = boundHelper(_head.parent, k);
            std::pair<const_iterator, const_iterator> p;

            if (temp) {
                if (_comp(temp->value.first, k)) {
                    p.first = ++const_iterator(temp);
                    p.second = p.first;
                } else if (_comp(k, temp->value.first)) {
                    p.first = const_iterator(temp);
                    p.second = const_iterator(temp);
                } else {
                    p.first = const_iterator(temp);
                    p.second = ++const_iterator(temp);
                }
            } else {
                p.first = cend();
                p.second = cend();
            }

            return p;
        }
};

#endif