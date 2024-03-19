#pragma once

#include <iostream>  // For debugging
#include <sstream>   // For as_string

using namespace std;

template <typename T>
class prqueue {
   private:
    struct NODE {
        int priority;
        T value;
        NODE* parent;
        NODE* left;
        NODE* right;
        NODE* link;  // Link to duplicates -- Part 2 only
    };

    NODE* root;
    size_t sz;

    // Utility pointers for begin and next.
    NODE* curr;
    NODE* temp;  // Optional

    // TODO_STUDENT: add private helper function definitions here

   public:
    /// Creates an empty `prqueue`.
    ///
    /// Runs in O(1).
    prqueue() {
        this->root = nullptr;
        this->sz = 0;
        this->curr = nullptr;
        this->temp = nullptr;
    }

    /// Copy constructor.
    ///
    /// Copies the value-priority pairs from the provided `prqueue`.
    /// The internal tree structure must be copied exactly.
    ///
    /// Runs in O(N), where N is the number of values in `other`.
    prqueue(const prqueue& other) {
        this->root = other->root;
        this->sz = other->sz;
        this->curr = other->curr;
        this->temp = other->temp;
    }

    /// Assignment operator; `operator=`.
    ///
    /// Clears `this` tree, and copies the value-priority pairs from the
    /// provided `prqueue`. The internal tree structure must be copied exactly.
    ///
    /// Runs in O(N + O), where N is the number of values in `this`, and O is
    /// the number of values in `other`.
    prqueue& operator=(const prqueue& other) {
    }

    /// Empties the `prqueue`, freeing all memory it controls.
    ///
    /// Runs in O(N), where N is the number of values.
    void clear() {
        clearAll(root);
        root = nullptr;
        sz = 0;
    }

    /// Destructor, cleans up all memory associated with `prqueue`.
    ///
    /// Runs in O(N), where N is the number of values.
    ~prqueue() {
        clear();
    }

    /// Adds `value` to the `prqueue` with the given `priority`.
    ///
    /// Uses the priority to determine the location in the underlying tree.
    ///
    /// Runs in O(H + M), where H is the height of the tree, and M is
    /// the number of duplicate priorities.
    void enqueue(T value, int priority) {
        NODE* key = new NODE();
        key->value = value;
        key->priority = priority;

        if(root == nullptr){  // if tree empty, make the key the root
            root = key;
        } else{  // else, find new position
            NODE* prev = nullptr;
            NODE* curr = root;
            while(curr != nullptr){
                prev = curr;
                if(curr->priority > priority){
                    curr = curr->left;
                } else if(curr->priority < priority){
                    curr = curr->right;
                } else{
                    curr = curr->right;
                }
            }
            if(prev->priority > priority){
                prev->left = key;
            } else{
                prev->right = key;
            }
            key->parent = prev;
        }
        sz++; // increase prqueue size
    }

    /// Returns the value with the smallest priority in the `prqueue`, but does
    /// not modify the `prqueue`.
    ///
    /// If the `prqueue` is empty, returns the default value for `T`.
    ///
    /// Runs in O(H + M), where H is the height of the tree, and M is
    /// the number of duplicate priorities.
    T peek() const {
        if(root == nullptr){
            return T{};
        }
        NODE* tempNode = findMinPriority(root);
        return tempNode->value;
    }

    /// Returns the value with the smallest priority in the `prqueue` and
    /// removes it from the `prqueue`.
    ///
    /// If the `prqueue` is empty, returns the default value for `T`.
    ///
    /// Runs in O(H + M), where H is the height of the tree, and M is
    /// the number of duplicate priorities.
    T dequeue() {
        if (root == nullptr) {
        return T();
    }

    NODE* current = root;
    while (current->left != nullptr) {
        current = current->left;
    }

    T value = current->value;

    if (current->parent == nullptr) {
        if (current->right != nullptr) {
            root = current->right;
            root->parent = nullptr;
        } else {
            root = nullptr;
        }
    } else {
        if (current->right != nullptr) {
            current->parent->left = current->right;
            current->right->parent = current->parent;
        } else {
            current->parent->left = nullptr;
        }
    }

    delete current;

    sz--;

    return value;
    }

    /// Returns the number of elements in the `prqueue`.
    ///
    /// Runs in O(1).
    size_t size() const {
        return sz;
    }

    /// Resets internal state for an iterative inorder traversal.
    ///
    /// See `next` for usage details.
    ///
    /// O(H), where H is the maximum height of the tree.
    void begin() {
        // TODO_STUDENT
    }

    /// Uses the internal state to return the next in-order value and priority
    /// by reference, and advances the internal state. Returns true if the
    /// reference parameters were set, and false otherwise.
    ///
    /// Example usage:
    ///
    /// ```c++
    /// pq.begin();
    /// T value;
    /// int priority;
    /// while (pq.next(value, priority)) {
    ///   cout << priority << " value: " << value << endl;
    /// }
    /// ```
    ///
    /// Runs in worst-case O(H + M) or O(H), depending on implementation, where
    /// H is the height of the tree, and M is the number of duplicate
    /// priorities.
    bool next(T& value, int& priority) {
        // TODO_STUDENT
    }

    /// Converts the `prqueue` to a string representation, with the values
    /// in-order by priority.
    ///
    /// Example:
    ///
    /// ```c++
    /// prqueue<string> names;
    /// names.enqueue("Gwen", 3);
    /// names.enqueue("Jen", 2);
    /// names.enqueue("Ben", 1);
    /// names.enqueue("Sven", 2);
    /// ```
    ///
    /// Calling `names.as_string()` would return the following multi-line
    /// string:
    ///
    /// ```text
    /// 1 value: Ben
    /// 2 value: Jen
    /// 2 value: Sven
    /// 3 value: Gwen
    /// ```
    ///
    /// Runs in O(N), where N is the number of values.
    string as_string() const {
        return as_stringHelp(root);
    }

    /// Checks if the contents of `this` and `other` are equivalent.
    ///
    /// Two `prqueues` are equivalent if they have the same priorities and
    /// values, as well as the same internal tree structure.
    ///
    /// These two `prqueue`s would be considered equivalent, because
    /// they have the same internal tree structure:
    ///
    /// ```c++
    /// prqueue<string> a;
    /// a.enqueue("2", 2);
    /// a.enqueue("1", 1);
    /// a.enqueue("3", 3);
    /// ```
    ///
    /// and
    ///
    /// ```c++
    /// prqueue<string> b;
    /// a.enqueue("2", 2);
    /// a.enqueue("3", 3);
    /// a.enqueue("1", 1);
    /// ```
    ///
    /// While this `prqueue`, despite containing the same priority-value pairs,
    /// would not be considered equivalent, because the internal tree structure
    /// is different.
    ///
    /// ```c++
    /// prqueue<string> c;
    /// a.enqueue("1", 1);
    /// a.enqueue("2", 2);
    /// a.enqueue("3", 3);
    /// ```
    ///
    /// Runs in O(N) time, where N is the maximum number of nodes in
    /// either `prqueue`.
    ///
    bool operator==(const prqueue& other) const {
        // TODO_STUDENT
    }

    /// Returns a pointer to the root node of the BST.
    ///
    /// Used for testing the internal structure of the BST. Do not edit or
    /// change.
    ///
    /// Runs in O(1).
    void* getRoot() {
        return root;
    }

    // clear() function helper
    void clearAll(NODE* node){
        if(node == nullptr){
            return;
        }

        clearAll(node->left);
        clearAll(node->right);
        delete node;
    }

    
    NODE* findMinPriority(NODE* tempNode) const {
        while(tempNode && tempNode->left != nullptr){
            tempNode = tempNode->left;
        }
        return tempNode;
    }

    // as_string() helper function
    std::string as_stringHelp(NODE* node) const{
        if(node == nullptr){
            return "";
        }

        std::stringstream ss;
        ss << as_stringHelp(node->left);
        ss << node->priority << " value: " << node->value << std::endl;
        ss << as_stringHelp(node->right);
        return ss.str();
    }
};
