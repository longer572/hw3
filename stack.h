#ifndef STACK_H
#define STACK_H

#include <vector>
#include <stdexcept>

// Use inheritance from std::vector (choose public/private) as appropriate
template <typename T>
class Stack: public std::vector<T> 
{
public:
    Stack();
    ~Stack();
    bool empty() const;
    size_t size() const;
    void push(const T& item);
    void pop();  // throws std::underflow_error if empty
    const T& top() const; // throws std::underflow_error if empty
    // Add other members only if necessary
private:
    std::vector<T>* data;
};

template<typename T>
Stack<T>::Stack()
{
    data = new typename std::vector<T>();
}

template<typename T>
Stack<T>::~Stack()
{
    delete data;
}

template<typename T>
bool Stack<T>::empty() const
{
    return data->empty();
}

template<typename T>
size_t Stack<T>::size() const
{
    return data->size();
}

template<typename T>
void Stack<T>::push(const T& item)
{
    data->push_back(item);
}

template<typename T>
void Stack<T>::pop()
{
    if (empty()){
        throw std::underflow_error("Stack is empty");
    } else {
        data->pop_back();
    }

}

template<typename T>
const T& Stack<T>::top() const
{
    if (empty()){
        throw std::underflow_error("Stack is empty");
    } else {
        return data->back();
    }
}

#endif