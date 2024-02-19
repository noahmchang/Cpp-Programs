#ifndef STACK_CPP
#define STACK_CPP

#include "Stack.hpp"

template <typename T>
Stack<T>::Stack() {}

// TODO: Implement all other methods defined in Stack.hpp here
/// @brief push the items into the stack sequentially, where end of items is the top
template <typename T>
Stack<T>::Stack(const std::vector<T> &items){
    for(int i=items.size()-1; i>=0; i--){
        _llist.append(items[i]);
    }
}

/// @brief Returns the number of elements in the stack.
/// @return The number of elements in the stack.
template <typename T>
size_t Stack<T>::size() const{
    return _llist.size();
}

/// @brief Returns the top element of the stack.
/// @return The value of the top element, or `std::nullopt` if the stack is empty.
template <typename T>
std::optional<T> Stack<T>::top() const{
    if(_llist.head() != nullptr){
        return (*(_llist.head())).value;
    } else{
        return std::nullopt;
    }
}

/// @brief Adds an element to the top of the stack.
/// @param value: the value to be added
template <typename T>
void Stack<T>::push(T value){
    _llist.prepend(value);
}

/// @brief Removes the top element from the stack and returns that element.
/// @return The value of the popped element, or `std::nullopt` if the stack is empty.
template <typename T>
std::optional<T> Stack<T>::pop(){

    return _llist.removeHead();

    // T val;
    // LinkedListNode<T>* _head = new LinkedListNode<T>(val, nullptr);
    // _head = _llist.head();
    // if(_head != nullptr){
    //     LinkedListNode<T>* previous_head = new LinkedListNode<T>(val, nullptr);
    //     previous_head = _head;
    //     _head = (*_head)._next;
    //     T removed_value = (*previous_head).value;
    //     delete previous_head;
    //     delete _head;
    //     (_llist._size)--;
    //     return removed_value;
    // } else{
    //     delete _head;
    //     return std::nullopt;
    // }
}

#endif
