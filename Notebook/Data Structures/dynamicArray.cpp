#include <iostream> // Importing this part of the standard library to deal with input/output streams

template <typename T> // It indicates what type of object will be created with my class. In this case, T represents any type
class DynamicArray {
private:
    T* data; // data is a pointer to an object of type T 
    size_t size; // Size of the array (actual number of elements)
    size_t capacity; // Capacity of the array (maximum number of elements)

public:
    DynamicArray() : data(nullptr), size(0), capacity(0) {} // Constructor of the dynamic array

    ~DynamicArray() { // Delete the array from memory
        delete[] data;
    }

    void push_back(const T& value) { // const = I won't modify value ; & = I am passing value by reference; T = type of value
        if (size == capacity) {
            if (capacity == 0)
                capacity = 1;
            else
                capacity *= 2;

            T* new_data = new T[capacity];
            for (size_t i = 0; i < size; ++i) {
                new_data[i] = data[i];
            }
            delete[] data;
            data = new_data;
        }
        data[size] = value;
        size++;
    }

    T& operator[](size_t index) {
        if (index < size) {
            return data[index];
        } else {
            throw std::out_of_range("Index out of range");
        }
    }

    size_t getSize() const {
        return size;
    }
};

int main() {
    DynamicArray<int> dynamicArray;

    dynamicArray.push_back(10);
    dynamicArray.push_back(20);
    dynamicArray.push_back(30);

    for (size_t i = 0; i < dynamicArray.getSize(); ++i) {
        std::cout << dynamicArray[i] << " ";
    }
    
    return 0;
}
