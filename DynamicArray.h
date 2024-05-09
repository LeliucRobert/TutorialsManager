//
// Created by Robi on 3/22/2024.
//

#ifndef OOP_A4_5_LELIUCROBERT_DYNAMICARRAY_H
#define OOP_A4_5_LELIUCROBERT_DYNAMICARRAY_H


#include "Domain.h"

template <typename T>
class DynamicArray {
    private:
        int arrSize;
        int capacity;
        T* elements;

        void resize(){
            this->capacity *= 2;
            T* copy = new T[this->capacity];
            for (int i = 0 ; i < this->arrSize ; i++){
                copy[i] = this->elements[i];
            }
            delete[] this->elements;
            this->elements = copy;
        }

    public:
        DynamicArray();
        ~DynamicArray();
        DynamicArray(const DynamicArray& arr);
        void add_element(Tutorial element);
        void update_element(std::string link , Tutorial element);
        void remove_element(std::string link);
        Tutorial& operator[](int index);
        int get_size();
        DynamicArray& operator=(const DynamicArray& other);
};

template <typename T>
DynamicArray<T>::DynamicArray() {
    this->capacity = 15;
    this->arrSize = 0;
    this->elements = new T[this->capacity];
}

template <typename T>
DynamicArray<T>::~DynamicArray() {
    delete[] this->elements;
}

template <typename T>
DynamicArray<T>::DynamicArray(const DynamicArray<T> &arr) {
    this->capacity = arr.capacity;
    this->arrSize = arr.arrSize;
    this->elements = new T[this->capacity];
    for (int i = 0 ; i < this->arrSize ; i++){
        this->elements[i] = arr.elements[i];
    }
}

template <typename T>
void DynamicArray<T>::add_element(Tutorial element) {
    int exists = 0;
    for (int i = 0 ; i < this->arrSize ; i++){
        if (this->elements[i].get_link() == element.get_link())
            exists = 1;
    }
    if (exists == 1)
        throw std::exception();
    else {
        this->elements[this->arrSize] = element;
        this->arrSize++;
    }
}

template <typename T>
void DynamicArray<T>::update_element(std::string link, Tutorial element) {
    int index = -1;
    for (int i = 0 ; i < this->arrSize ; i++)
        if (this->elements[i].get_link() == link){
            index = i;
            break;
        }
    if (index == -1)
        throw std::exception();
    else {
        this->elements[index].set_duration(element.get_duration());
        this->elements[index].set_likes(element.get_likes());
        this->elements[index].set_link(element.get_link());
        this->elements[index].set_presenter(element.get_presenter());
        this->elements[index].set_title(element.get_title());
    }
}

template <typename T>
void DynamicArray<T>::remove_element(std::string link) {
    int index = -1;
    for (int i = 0 ; i < this->arrSize ; i++)
        if (this->elements[i].get_link() == link){
            index = i;
            break;
        }
    if (index == -1)
        throw std::exception();
    else {
        this->elements[index] = this->elements[this->arrSize - 1];
        this->arrSize--;
    }
}

template <typename T>
Tutorial &DynamicArray<T>::operator[](int index) {
    return this->elements[index];
}

template <typename T>
DynamicArray<T> &DynamicArray<T>::operator=(const DynamicArray<T> &other) {
    if (this != &other) {
        Tutorial* newElements = new Tutorial[other.capacity];
        for (int i = 0; i < other.arrSize; ++i) {
            newElements[i] = other.elements[i];
        }

        delete[] this->elements;

        this->elements = newElements;
        this->arrSize = other.arrSize;
        this->capacity = other.capacity;
    }
    return *this;
}

template <typename T>
int DynamicArray<T>::get_size() {
    return this->arrSize;
}

#endif //OOP_A4_5_LELIUCROBERT_DYNAMICARRAY_H
