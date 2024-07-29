#include "Vector.h"
#include <iostream>

int main() {
    // Default constructor
    Vector<int> vec1;
    std::cout << "Default constructor: vec1.size() = " << vec1.size() << "\n";

    // Constructor with size
    Vector<int> vec2(5);
    std::cout << "Constructor with size: vec2.size() = " << vec2.size() << ", vec2.capacity() = " << vec2.capacity() << "\n";
    for (int i = 0; i < vec2.size(); ++i) {
        std::cout << vec2[i] << " ";
    }
    std::cout << "\n";

    // Constructor with size and value
    Vector<int> vec3(5, 10);
    std::cout << "Constructor with size and value: ";
    for (int i = 0; i < vec3.size(); ++i) {
        std::cout << vec3[i] << " ";
    }
    std::cout << "\n";

    // Copy constructor
    Vector<int> vec4(vec3);
    std::cout << "Copy constructor: ";
    for (int i = 0; i < vec4.size(); ++i) {
        std::cout << vec4[i] << " ";
    }
    std::cout << "\n";

    // Move constructor
    Vector<int> vec5(std::move(vec4));
    std::cout << "Move constructor: ";
    for (int i = 0; i < vec5.size(); ++i) {
        std::cout << vec5[i] << " ";
    }
    std::cout << "\n";

    // Initializer list constructor
    Vector<int> vec6{1, 2, 3, 4, 5};
    std::cout << "Initializer list constructor: ";
    for (int i = 0; i < vec6.size(); ++i) {
        std::cout << vec6[i] << " ";
    }
    std::cout << "\n";

    // Assignment operator
    vec1 = vec6;
    std::cout << "Assignment operator: ";
    for (int i = 0; i < vec1.size(); ++i) {
        std::cout << vec1[i] << " ";
    }
    std::cout << "\n";

    // Move assignment operator
    vec2 = std::move(vec1);
    std::cout << "Move assignment operator: ";
    for (int i = 0; i < vec2.size(); ++i) {
        std::cout << vec2[i] << " ";
    }
    std::cout << "\n";

    // Initializer list assignment operator
    vec3 = {10, 20, 30};
    std::cout << "Initializer list assignment operator: ";
    for (int i = 0; i < vec3.size(); ++i) {
        std::cout << vec3[i] << " ";
    }
    std::cout << "\n";

    // Element access
    std::cout << "Element access: vec3[1] = " << vec3[1] << ", vec3.at(2) = " << vec3.at(2) << "\n";
    std::cout << "Front element: " << vec3.front() << ", Back element: " << vec3.back() << "\n";

    // Data access
    int* data = vec3.data();
    std::cout << "Data access: ";
    for (int i = 0; i < vec3.size(); ++i) {
        std::cout << data[i] << " ";
    }
    std::cout << "\n";

    // Modifiers
    vec3.push_back(40);
    std::cout << "After push_back(40): ";
    for (int i = 0; i < vec3.size(); ++i) {
        std::cout << vec3[i] << " ";
    }
    std::cout << "\n";

    vec3.pop_back();
    std::cout << "After pop_back(): ";
    for (int i = 0; i < vec3.size(); ++i) {
        std::cout << vec3[i] << " ";
    }
    std::cout << "\n";

    // Insert elements
    vec3.insert(vec3.begin() + 1, 3, 15);
    std::cout << "After insert(begin() + 1, 3, 15): ";
    for (int i = 0; i < vec3.size(); ++i) {
        std::cout << vec3[i] << " ";
    }
    std::cout << "\n";

    // Erase elements
    vec3.erase(vec3.begin() + 1);
    std::cout << "After erase(begin() + 1): ";
    for (int i = 0; i < vec3.size(); ++i) {
        std::cout << vec3[i] << " ";
    }
    std::cout << "\n";

    // Capacity
    std::cout << "Capacity: size = " << vec3.size() << ", capacity = " << vec3.capacity() << "\n";
    vec3.reserve(20);
    std::cout << "After reserve(20): size = " << vec3.size() << ", capacity = " << vec3.capacity() << "\n";
    vec3.shrink_to_fit();
    std::cout << "After shrink_to_fit(): size = " << vec3.size() << ", capacity = " << vec3.capacity() << "\n";

    // Resize
    vec3.resize(10);
    std::cout << "After resize(10): ";
    for (int i = 0; i < vec3.size(); ++i) {
        std::cout << vec3[i] << " ";
    }
    std::cout << "\n";

    vec3.resize(5, 50);
    std::cout << "After resize(5, 50): ";
    for (int i = 0; i < vec3.size(); ++i) {
        std::cout << vec3[i] << " ";
    }
    std::cout << "\n";

    // Iterators
    std::cout << "Iterators: ";
    for (auto it = vec3.begin(); it != vec3.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << "\n";

    std::cout << "Reverse Iterators: ";
    for (auto it = vec3.rbegin(); it != vec3.rend(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << "\n";

    return 0;
}
