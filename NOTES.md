## things that need to be considered

### Itrator Invalidation
occurs when an iterator to an element in a data structure such as an array, list, or map is no longer valid or reliable due to a change in the data structure (removal of an element or addition in the array, list, or map).

Example in C++
```cpp
#include <iostream>
#include <vector>

int main() {
    std::vector<int> numbers = {1, 2, 3, 4, 5};

    // Iterator pointing to the second element
    std::vector<int>::iterator it = numbers.begin() + 1;

    // Add an element to the vector, invalidating the iterator
    numbers.push_back(6);

    // Accessing the iterator after the modification is undefined behavior
    std::cout << *it << std::endl; // This can lead to unpredictable results

    return 0;
}
```
