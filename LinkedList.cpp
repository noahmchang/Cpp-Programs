#ifndef LINKED_LIST_CPP
#define LINKED_LIST_CPP

#include "LinkedList.hpp"

template <typename T>
LinkedList<T>::LinkedList() : _size(0), _head(nullptr), _tail(nullptr) {}

template <typename T>
LinkedList<T>::LinkedList(LinkedList<T> &&other) : _size(other._size),
                                                   _head(other._head),
                                                   _tail(other._tail)
{
    other._size = 0;
    other._head = nullptr;
    other._tail = nullptr;
}

// TODO: Implement all other methods defined in LinkedList.hpp here

/// @brief create a new empty list
// template <typename T>
// LinkedList<T>::LinkedList(){
//     _size = 0;
//     _head = nullptr;
//     _tail = nullptr;
// }

/// @brief copy constructor
/// @param other: the other list to be copied
/// @note the default copy constructor is deleted because it will only copy shallowly
/// and may result in two inter-dependent lists.
// template <typename T>
// LinkedList<T>::LinkedList(const LinkedList<T> &other) : delete{
//     _size = (*other)._size;
//     _head = (*other)._head;
//     _tail = (*other)._tail;
// }

/// @brief move constructor
/// @param other: the other list to be moved
// template <typename T>
// LinkedList<T>::LinkedList(LinkedList<T> &&other){
//     (**other)._size = _size;
//     (**other)._head = _head;
//     (**other)._tail = _tail;
// }

/// @brief create a new list from a vector
/// @param items: the vector whose values should be copied
template <typename T>
LinkedList<T>::LinkedList(const std::vector<T> &items){
    int n = items.size();
    _size = n;
    int i;
    if(n == 0){
        _head = nullptr;
        _tail =  nullptr;
        return;
    }
    LinkedListNode<T>* myNode = new LinkedListNode<T>(items[0]);
    _tail = myNode;
    _head = myNode;
    for(i=1;i<n;i++){
        //(*_tail).value = items[i];
        (*_tail)._next = new LinkedListNode<T>(items[i]);
        _tail = (*_tail)._next;
        // if(i != n-1){
        //     LinkedListNode<T>* nextNode = new LinkedListNode<T>(items[i]);
        //     (*_tail)._next = nextNode;
        //     if(i == 1){
        //         (*_head)._next = nextNode;
        //     }
        //     _tail = (*_tail)._next;
        //     //delete nextNode;
        // } else{
        //     LinkedListNode<T>* nextNode = new LinkedListNode<T>(items[i]);
        //     (*_tail)._next = nullptr;
        // }
    }
    (*_tail)._next = nullptr;
    //delete myNode;
}

/// @brief get the number of elements in the list
/// @return the number of elements in the list
template <typename T>
size_t LinkedList<T>::size() const{
    return _size;
}

/// @brief get the head node
/// @return the head node of the list if the list is not empty; nullptr otherwise
template <typename T>
LinkedListNode<T>* LinkedList<T>::head() const{
    if(_head != nullptr){
        return _head;
    } else{
        return nullptr;
    }
}

/// @brief get the tail node
/// @return the tail node of the list if the list is not empty; nullptr otherwise
template <typename T>
LinkedListNode<T>* LinkedList<T>::tail() const{
    if(_tail != nullptr){
        return _tail;
    } else{
        return nullptr;
    }
}

/// @brief find the first occurrence of the specified value in the list
/// @param value: the value we are trying to find
/// @return the node that contains the value specified if exists; nullptr otherwise
template <typename T>
LinkedListNode<T>* LinkedList<T>::find(T value) const{
    LinkedListNode<T>* current_pointer;
    current_pointer = _head;
    while(current_pointer != nullptr){
        if((*current_pointer).value == value){
            return current_pointer;
        } else{
            current_pointer = (*current_pointer)._next;
        }
    }
    return nullptr;
}

/// @brief add a new element to the beginning of the list
/// @param value: the value to be added
/// @return the new node created containing the specified value
template <typename T>
LinkedListNode<T>* LinkedList<T>::prepend(T value){
    //If empty list
    if(_head == nullptr){
        LinkedListNode<T>* head_node = new LinkedListNode<T>(value);
        _head = head_node;
        _tail = head_node;
        _size++;
        return head_node;
    }
    LinkedListNode<T>* head_node = new LinkedListNode<T>(value, _head);
    // (*head_node).value = value;
    // //point to original head node
    (*head_node)._next = _head;
    //change linked list head pointer to point to new head node
    _head = head_node;
    _size++;
    return head_node;
}

/// @brief add a new element to the end of the list
/// @param value: the value to be added
/// @return the new node created containing the specified value
template <typename T>
LinkedListNode<T>* LinkedList<T>::append(T value){
    //If empty list
    if(_head == nullptr){
        LinkedListNode<T>* tail_node = new LinkedListNode<T>(value);
        _head = tail_node;
        _tail = tail_node;
        _size++;
        return tail_node;
    }
    //create new tail node
    LinkedListNode<T>* tail_node = new LinkedListNode<T>(value);
    // tail_node.value = value;
    // //have the pointer be null
    // tail_node._next = nullptr;
    //connect the linked list tail pointer to the new tail node
    (*_tail)._next = tail_node;
    _tail = tail_node;
    _size++;
    return tail_node;
}

/// @brief insert a new element after the specified node
/// @param node: the node before the insertion position.
/// If nullptr, the new element will be added to the beginning of the list.
/// @param value: the value to be added
/// @return the new node created containing the specified value
template <typename T>
LinkedListNode<T>* LinkedList<T>::insertAfter(LinkedListNode<T> *node, T value){
    // LinkedListNode<T> new_node;
    // new_node.value = value;
    // LinkedListNode<T>* current_pointer = new LinkedListNode<T>;
    // current_pointer = _head;
    // do{
    //     if(node == nullptr){
    //         new_node._next = _head;
    //         //unsure if this will work
    //         _head = &new_node;
    //         _size++;
    //         break;
    //     } else if(current_pointer == node){
    //         new_node._next = (*current_pointer)._next;
    //         (*current_pointer)._next = &new_node;
    //         if(current_pointer == _tail){
    //             _tail = &new_node;
    //         }
    //         _size++;
    //         break;
    //     }
    //     current_pointer = (*current_pointer)._next;
    // }while(current_pointer != nullptr);
    // delete current_pointer;
    // return &new_node;

    //Empty cases
    // if(_head == nullptr && node == nullptr){
    //     LinkedListNode<T>* new_node = new LinkedListNode<T>(value);
    //     _head = new_node;
    //     _tail = new_node;
    //     _size++;
    //     return new_node;
    // } else if(node == nullptr){
    //     _size++;
    //     _tail = prepend(value);
    //     return _tail;
    // }
    // T val;
    // LinkedListNode<T>* current_ptr = new LinkedListNode<T>(val, nullptr);
    // current_ptr = _head;
    // if(_head == node){
    //     return prepend(value);
    // }
    // do{
    //     current_ptr = (current_ptr)._next;
    // }while((*current_ptr)._next != node);
    // if((*current_ptr)._next == node){
    //     LinkedListNode<T>* new_node = new LinkedListNode<T>(val, nullptr);
    //     (*new_node)._next = node;
    //     (*new_node).value = value;
    //     (*current_ptr)._next = new_node;
    //     if(node == nullptr){
    //         _tail = new_node;
    //     }
    //     _size++;
    //     return new_node;
    // }
    // return nullptr;

    //If list is empty or node is null
    if(_head == nullptr || node == nullptr){
        return prepend(value);
    }
    LinkedListNode<T>* new_node = new LinkedListNode<T>(value);
    (*new_node)._next = (*node)._next;
    (*node)._next = new_node;
    _size++;
    if(node == _tail){
        _tail = new_node;
    }
    return new_node;
}

/// @brief remove the first element from the list
/// @return the value of removed element if there was at least one element in the list; std::nullopt otherwise
template <typename T>
std::optional<T> LinkedList<T>::removeHead(){
    //THIS is if you are removing the last element.
    if(_head != nullptr){
        LinkedListNode<T>* previous_head;
        previous_head = _head;
        _head = (*_head)._next;
        T removed_value = (*previous_head).value;
        //if there's one element
        if(_size == 1){
            _tail = nullptr;
        }
        delete previous_head;
        _size--;
        return removed_value;
    } else{
        return std::nullopt;
    }

    // if(_tail != nullptr){
    //     LinkedListNode<T>* current_ptr;
    //     current_ptr = _head;
    //     //If there's one element
    //     if(_head == _tail){
    //         (_size)--;
    //         T top_value = (*_head).value;
    //         delete current_ptr;
    //         _head = nullptr;
    //         _tail = nullptr;
    //         return top_value;
    //     } else{
    //         do{
    //             current_ptr = (*current_ptr)._next;
    //         } while((*((*current_ptr)._next))._next != nullptr);
    //         (*current_ptr)._next = nullptr;
    //         T top_value = (*((*current_ptr)._next)).value;
    //         _tail = current_ptr;
    //         delete (*current_ptr)._next;
    //         (_size)--;
    //         return top_value;
    //     }
    // } else{
    //     return std::nullopt;
    // }
}

/// @brief removes the first occurrence of the given element if found
/// @param value: the value to be removed
/// @return true of the value is found and removed; false otherwise
template <typename T>
bool LinkedList<T>::remove(T value){
    if(_head == nullptr){
        return false;
    }
    //If there's one element
    if((*_head).value == value){
        if(removeHead() != std::nullopt){
            return true;
        } else{
            return false;
        }
    }

    LinkedListNode<T>* current_pointer;
    current_pointer = _head;
    while(((*current_pointer)._next != nullptr && (*((*current_pointer)._next)).value != value)){
        current_pointer = (*current_pointer)._next;
    }
    if((*current_pointer)._next != nullptr && (*((*current_pointer)._next)).value == value){
        LinkedListNode<T>* ptr_to_delete;
        ptr_to_delete = (*current_pointer)._next;
        (*current_pointer)._next = (*ptr_to_delete)._next;
        if(ptr_to_delete == _tail){
            _tail = current_pointer;
        }
        delete ptr_to_delete;
        _size--;
        return true;
    } else{
        return false;
    }
}

/// @brief remove all elements from the list
template <typename T>
void LinkedList<T>::clear(){
    if(_head == nullptr){
        return;
    }
    do{
        LinkedListNode<T>* old_ptr;
        old_ptr = _head;
        _head = (*_head)._next;
        delete old_ptr;
    }while(_head != nullptr);
    _size = 0;
    _head = nullptr;
    _tail = nullptr;
}

template <typename T>
LinkedList<T>::~LinkedList(){
    clear();
}

#endif
