#ifndef QUEUE_CPP
#define QUEUE_CPP

#include "Queue.hpp"

template <typename T>
Queue<T>::Queue(LinkedList<T> &&llist) : _llist(std::move(llist)) {}

template <typename T>
Queue<T>::Queue() : Queue(LinkedList<T>()) {}

//vector
template <typename T>
Queue<T>::Queue(const std::vector<T> &items){
    for(int i=items.size()-1; i>=0; i--){
        _llist.prepend(items[i]);
    }
}

// TODO: Implement all other methods defined in Queue.hpp here
/// @brief Returns the number of elements in the queue.
/// @return The number of elements in the queue.
template <typename T>
size_t Queue<T>::size() const{
    return _llist.size();
}

/// @brief Adds an element to the queue.
/// @param value: the value to be added
template <typename T>
void Queue<T>::enqueue(T value){
    _llist.append(value);
}

/// @brief Removes the oldest element from the queue and returns that element.
/// @return The value of the dequeued element, or `std::nullopt` if the queue is empty.
template <typename T>
std::optional<T> Queue<T>::dequeue(){
    // LinkedListNode<T>* _head;
    // _head = _llist.head();
    // if(_head != nullptr){
    //     LinkedListNode<T>* previous_head;
    //     previous_head = _head;
    //     _head = (*_head)._next;
    //     T removed_value = (*previous_head).value;
    //     delete previous_head;
    //     delete _head;
    //     (_llist._size)--;
    //     return removed_value;
    // } else{
    //     return std::nullopt;
    // }
    return _llist.removeHead();
}

#endif