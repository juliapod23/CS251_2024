#include "canvaslist.h"

#include <iostream>

using namespace std;

CanvasList::CanvasList() {
    list_size = 0;
    list_front = nullptr;
}

CanvasList::CanvasList(const CanvasList& other) {
    list_size = 0;
    list_front = nullptr;

    if (other.list_front != nullptr) { // if list isn't empty, start copying elements over
        ShapeNode* curOther = other.list_front;
        ShapeNode* lastNode = nullptr;
        while (curOther != nullptr) { // link elements to list and build list one by one
            ShapeNode* copyShape = new ShapeNode();
            copyShape->value = curOther->value->copy();
            copyShape->next = nullptr;

            if (list_front == nullptr) {
                list_front = copyShape;
            } else {
                lastNode->next = copyShape;
            }
            lastNode = copyShape;
            curOther = curOther->next;
            list_size++;
        }
    }
}

CanvasList& CanvasList::operator=(const CanvasList& other) {
    if (this == &other) {
        return *this;
    }

    clear();
    // creates a pointer to the CanvasList object and pointer array for the shapes inside the CanvasList object
    if (other.list_front != nullptr) {
        ShapeNode* curOther = other.list_front;
        ShapeNode* lastNode = nullptr;

        while (curOther != nullptr) {
            ShapeNode* copyShape = new ShapeNode();
            copyShape->value = curOther->value->copy();
            copyShape->next = nullptr;

            if (list_front == nullptr) {
                list_front = copyShape;
            } else {
                lastNode->next = copyShape;
            }

            lastNode = copyShape;
            curOther = curOther->next;
            list_size++;
        }
    }
    return *this;
}

CanvasList::~CanvasList() {
    clear();
}

void CanvasList::clear() {
    ShapeNode* cur = list_front;

    while (cur != nullptr) {
        ShapeNode* next = cur->next;
        delete cur->value;
        delete cur;
        cur = next;  // Update the current pointer to the next node
    }

    list_front = nullptr;
    list_size = 0;
}

void CanvasList::insert_after(int index, Shape* s) {
    if (index < 0 || index >= list_size) {
        return;
    }

    ShapeNode* insertNode = new ShapeNode;
    insertNode->value = s;
    insertNode->next = nullptr;

    if (list_front == nullptr) {
        list_front = insertNode;
    } else {
        ShapeNode* cur = list_front;

        // iterates through until node at position index is found
        for (int i = 0; i < index && cur != nullptr; i++) {
            if (cur->next == nullptr || i == index) {
                break;
            }
            cur = cur->next;
        }
        insertNode->next = cur->next;
        cur->next = insertNode;
    }
    list_size++;
}

void CanvasList::push_front(Shape* s) {
    // links a node to the front of CanvasList
    ShapeNode* insertNode = new ShapeNode;
    insertNode->value = s;

    insertNode->next = list_front;
    list_front = insertNode;

    list_size++;
}

void CanvasList::push_back(Shape* s) {
    // iterates through entire CanvasList and links a node to the end
    ShapeNode* insertNode = new ShapeNode;
    insertNode->value = s;
    insertNode->next = nullptr;

    if (list_front == nullptr) {
        list_front = insertNode;
    } else {
        ShapeNode* cur = list_front;
        while (cur->next != nullptr) {
            cur = cur->next;
        }
        cur->next = insertNode;
    }
    list_size++;
}

void CanvasList::remove_at(int index) {
    if (index < 0 || index >= list_size) {
        return;
    }
    // if index = 0, just unlink first node
    if (index == 0) {
        ShapeNode* temp = list_front;
        list_front = list_front->next;

        delete temp->value;
        delete temp;
    } else { // else, iterate to index and unlink the node
        ShapeNode* cur = list_front;
        for (int i = 0; i < index - 1; i++) {
            cur = cur->next;
        }

        ShapeNode* temp = cur->next;
        cur->next = temp->next;

        delete temp->value;
        delete temp;
    }
    list_size--;
}

void CanvasList::remove_every_other() {
    if (!list_front || !list_front->next) {
        return;
    }

    ShapeNode* prev = list_front;
    ShapeNode* cur = prev->next;

    while (cur) {
        prev->next = cur->next;
        delete cur->value;
        delete cur;

        if (prev->next) {
            prev = prev->next;
            cur = prev->next;
        } else {
            cur = nullptr;
        }
        list_size--;
    }
}

Shape* CanvasList::pop_front() {
    // unlink the front node and return it
    if (list_front == nullptr) {
        return nullptr;
    }
    ShapeNode* temp = list_front;
    list_front = list_front->next;
    Shape* result = temp->value;
    delete temp;
    list_size--;
    return result;
}

Shape* CanvasList::pop_back() {
    // unlink the back node and return it
    if (list_front == nullptr) {
        return nullptr;
    }

    if (list_front->next == nullptr) {
        Shape* back = list_front->value;
        delete list_front;
        list_front = nullptr;
        list_size--;
        return back;
    }
    ShapeNode* cur = list_front;
    ShapeNode* prev = nullptr;

    // Traverse to the last node
    while (cur->next != nullptr) {
        prev = cur;
        cur = cur->next;
    }

    // cur is now the last node
    if (prev != nullptr) {
        prev->next = nullptr;
    }

    Shape* back = cur->value;
    delete cur;
    list_size--;

    return back;
}

ShapeNode* CanvasList::front() const {
    return list_front;
}

bool CanvasList::empty() const {
    return (list_size == 0);
}

int CanvasList::size() const {
    return list_size;
}

int CanvasList::find(int x, int y) const {
    ShapeNode* cur = list_front;
    int i = 0;

    while (cur != nullptr) {
        if (cur->value->getX() == x && cur->value->getY() == y) {
            // Found a matching Shape, return its index
            return i;
        }

        cur = cur->next;
        i++;
    }

    // No matching Shape found
    return -1;
}

Shape* CanvasList::shape_at(int index) const {
    if (index < 0 || index >= list_size) {
        return nullptr;
    }

    // iterates through linked list until node is found
    ShapeNode* cur = list_front;
    for (int i = 0; i < index; i++) {
        cur = cur->next;
    }

    return cur->value;
}

void CanvasList::draw() const {
    ShapeNode* cur = list_front;

    while (cur != nullptr) {
        // Use the as_string method to get the string representation of each Shape
        std::cout << cur->value->as_string() << std::endl;
        cur = cur->next;
    }
}

void CanvasList::print_addresses() const {
    ShapeNode* cur = list_front;

    while (cur != nullptr) {
        // Print the address of the node and the address of the Shape
        std::cout << "Node Address: " << cur << "\tShape Address: " << cur->value << std::endl;
        cur = cur->next;
    }
}