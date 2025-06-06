// Copyright [2018] <Jessllena>
#ifndef STRUCTURES_ARRAY_QUEUE_H
#define STRUCTURES_ARRAY_QUEUE_H

#include <cstdint>  // std::size_t
#include <stdexcept>  // C++ Exceptions

namespace structures {

template<typename T>
//! classe ArrayQueue
class ArrayQueue {
 public:
    //! construtor padrao
    ArrayQueue();
    //! construtor com parametro
    explicit ArrayQueue(std::size_t max);
    //! destrutor padrao
    ~ArrayQueue();
    //! metodo enfileirar
    void enqueue(const T& data);
    //! metodo desenfileirar
    T dequeue();
    //! metodo retorna o ultimo
    T& back();
    //! metodo limpa a fila
    void clear();
    //! metodo retorna tamanho atual
    std::size_t size();
    //! metodo retorna tamanho maximo
    std::size_t max_size();
    //! metodo verifica se vazio
    bool empty();
    //! metodo verifica se esta cheio
    bool full();

 private:
    T* contents;
    std::size_t size_;
    std::size_t max_size_;
    int begin_;  // indice do inicio (para fila circular)
    int end_;  // indice do fim (para fila circular)
    static const auto DEFAULT_SIZE = 10u;
};

}  // namespace structures

#endif

template<typename T>
structures::ArrayQueue<T>::ArrayQueue() {
    max_size_ = DEFAULT_SIZE;
    contents = new T[DEFAULT_SIZE];
    end_ = -1;
    begin_ = 0;
}

template<typename T>
structures::ArrayQueue<T>::ArrayQueue(std::size_t max) {
    max_size_ = max;
    contents = new T[max_size_];
    end_ = -1;
    begin_ = 0;
    size_ = 0;
}

template<typename T>
structures::ArrayQueue<T>::~ArrayQueue() {
    delete [] contents;
}

template<typename T>
void structures::ArrayQueue<T>::enqueue(const T& data) {
    if (full())
        throw std::out_of_range("fila cheia");
    // top_++;
    size_++;
    end_ = (end_ + 1) % max_size_;
    contents[end_] = data;
}

template<typename T>
T structures::ArrayQueue<T>::dequeue() {
    if (empty())
        throw std::out_of_range("fila vazia");
    T aux;
    size_--;
    aux = contents[begin_];
    begin_ = (begin_ + 1) % max_size_;
    // end_--;
    return aux;
}

template<typename T>
T& structures::ArrayQueue<T>::back() {
    if (empty())
        throw std::out_of_range("fila vazia");
    return contents[end_];
}

template<typename T>
void structures::ArrayQueue<T>::clear() {
    end_ = -1;
    begin_ = 0;
    size_ = 0;
}

template<typename T>
std::size_t structures::ArrayQueue<T>::size() {
    return size_;
}

template<typename T>
std::size_t structures::ArrayQueue<T>::max_size() {
    return max_size_;
}

template<typename T>
bool structures::ArrayQueue<T>::empty() {
    return (size_ == 0);
}

template<typename T>
bool structures::ArrayQueue<T>::full() {
    // return (top_ == static_cast<int>(max_size()-1));
    return size() == max_size();
}
