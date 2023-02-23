#ifndef HEAP_H
#define HEAP_H
#include <functional>
#include <stdexcept>
#include <vector>

template <typename T, typename PComparator = std::less<T> >
class Heap
{
public:
  /**
   * @brief Construct a new Heap object
   * 
   * @param m ary-ness of heap tree (default to 2)
   * @param c binary predicate function/functor that takes two items
   *          as an argument and returns a bool if the first argument has
   *          priority over the second.
   */
  Heap(int m=2, PComparator c = PComparator());

  /**
  * @brief Destroy the Heap object
  * 
  */
  ~Heap();

  /**
   * @brief Push an item to the heap
   * 
   * @param item item to heap
   */
  void push(const T& item);

  /**
   * @brief Returns the top (priority) item
   * 
   * @return T const& top priority item
   * @throw std::underflow_error if the heap is empty
   */
  T const & top() const;

  /**
   * @brief Remove the top priority item
   * 
   * @throw std::underflow_error if the heap is empty
   */
  void pop();

  /// returns true if the heap is empty

  /**
   * @brief Returns true if the heap is empty
   * 
   */
  bool empty() const;

    /**
   * @brief Returns size of the heap
   * 
   */
  size_t size() const;

private:
  /// Add whatever helper functions and data members you need below

  // Function that takes an index i and returns the index of the parent
  int parent(int i);

  // Function that takes an index i and a child n and returns the n-th child
  int child(int i, int n);

  // Recursive function to assist with popping items: takes an index i
  void trickleDown(int i);

  // Max number of children per item
  int d_;

  // Comparator functor
  PComparator c_;

  // Container vector
  std::vector<T> data;




};

/*

    END OF HEADER FILE: START OF IMPLEMENTATION

*/


// Add implementation of member functions here

template <typename T, typename PComparator>
Heap<T, PComparator>::Heap(int m, PComparator c)
{
  d_ = m;
  c_ = c;
}

template <typename T, typename PComparator>
Heap<T, PComparator>::~Heap()
{
}

template <typename T, typename PComparator>
void Heap<T, PComparator>::push(const T& item)
{
  data.push_back(item);
  std::size_t index = data.size() - 1;
  while (index != 0) {
    std::size_t parent_index = parent(index);
    T& current = data[index];
    T& parent = data[parent_index];
    if (c_(parent, current)) {
      break;
    }
    std::swap(parent, current);
    index = parent_index;
  }
}

// We will start top() for you to handle the case of 
// calling top on an empty heap
template <typename T, typename PComparator>
T const & Heap<T,PComparator>::top() const
{
  // Here we use exceptions to handle the case of trying
  // to access the top element of an empty heap
  if(empty()){
    // ================================
    // throw the appropriate exception
    // ================================
    throw std::underflow_error("Heap is empty");
  }
  // If we get here we know the heap has at least 1 item
  // Add code to return the top element

  return data[0];

}


// We will start pop() for you to handle the case of 
// calling top on an empty heap
template <typename T, typename PComparator>
void Heap<T,PComparator>::pop()
{
  if(empty()){
    // ================================
    // throw the appropriate exception
    // ================================
    throw std::underflow_error("Heap is empty");
  }
  data[0] = data.back();
  data.pop_back();
  if (data.size() > 0) {
    trickleDown(0);
  }


}

template <typename T, typename PComparator>
bool Heap<T, PComparator>::empty() const
{
  return (size() == 0);
}

template <typename T, typename PComparator>
size_t Heap<T, PComparator>::size() const
{
  return data.size();
}

// Function that takes an index i and returns the index of the parent
template<typename T, typename PComparator>
int Heap<T, PComparator>::parent(int i)
{
  return (i - 1) / d_;
}

// Function that takes an index i and a child n and returns the index of the n-th child
// n >= 1
template<typename T, typename PComparator>
int Heap<T, PComparator>::child(int i, int n)
{
  if (n < 1 || n > d_) {
    throw std::invalid_argument("n must be >= 1 and <= d");
  }
  if (i > (int) data.size() - 1 || i < 0) {
    throw std::invalid_argument("i must be >= size and < 0");
  }
  return i * d_ + n;
}

// Recursive function to assist with popping items: takes an index i
template<typename T, typename PComparator>
void Heap<T, PComparator>::trickleDown(int i)
{
  //Using a vector to store each of the children indices of a node
  std::vector<int> children;
  for (int k = 1; k <= d_; k++) {
    if (child(i, k) > (int) data.size() - 1) { // If child does not exist
      children.push_back(-1);
    } else { // If child does exist
      children.push_back(child(i, k));
    }
  }
  // Return if leaf node
  if (children[0] == -1) return;

  //Now find "best" child according to the functor PComparator
  int bestChildIndex = children[0];

  for (int k = 0; k < (int) children.size(); k++) {
    if (children[k] <= (int) data.size() - 1 && children[k] != -1) {
      if (bestChildIndex != children[k] && c_(data[children[k]], data[bestChildIndex])) {
        bestChildIndex = children[k];
      }
    }
  }
  //Compare with i and swap if needed: if swap required, then repeat process on next level of the tree
  if (c_(data[bestChildIndex], data[i])) {
    std::swap(data[bestChildIndex], data[i]);
    trickleDown(bestChildIndex);
  }
}




#endif

