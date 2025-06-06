//! Copyright [year] <Jessllena>
namespace structures {

template<typename T>
class DoublyLinkedList {
 public:
    DoublyLinkedList();
    ~DoublyLinkedList();
    void clear();

    void push_back(const T& data);  // insere no fim
    void push_front(const T& data);  // insere no início
    void insert(const T& data, std::size_t index);  // insere na posição
    void insert_sorted(const T& data);  // insere em ordem

    T pop(std::size_t index);  // retira da posição
    T pop_back();  // retira do fim
    T pop_front();  // retira do início
    void remove(const T& data);  // retira específico

    bool empty() const;  // lista vazia
    bool contains(const T& data) const;  // contém

    T& at(std::size_t index);  // acesso a um elemento (checando limites)
    const T& at(std::size_t index) const;  // getter constante a um elemento

    std::size_t find(const T& data) const;  // posição de um dado
    std::size_t size() const;  // tamanho

 private:
    class Node {  // implementar cada um dos métodos de Node
     public:
        explicit Node(const T& data):
            data_{data}
        {}
        Node(const T& data, Node* next):
            data_{data},
            next_{next}
        {}
        Node(const T& data, Node* prev, Node* next):
            data_{data},
            next_{next},
            prev_{prev}
        {}

        T& data() {   // getter: dado
            return data_;
        }

        const T& data() const {  // getter const: dado
            return data_;
        }

         Node* next() {  // getter: próximo
            return next_;
        }

        const Node* next() const {  // getter const: próximo
            return next_;
        }

        void next(Node* node) {  // setter: próximo
            next_ = node;
        }

        Node* prev() {
            return prev_;
        }
        const Node* prev() const {
            return prev_;
        }
        void prev(Node* node) {
            prev_ = node;
        }

     private:
        T data_;
        Node* prev_;
        Node* next_;
    };

    Node* end() {  // último nodo da lista
        auto it = head;
        for (auto i = 1u; i < size(); ++i) {
            it = it->next();
        }
        return it;
    }

    Node* head{nullptr};  // primeiro da lista
    Node* tail{nullptr};  // ultimo da lista
    std::size_t size_;
};

}  // namespace structures

template<typename T>
structures::DoublyLinkedList<T>::DoublyLinkedList() {
    head = nullptr;
    size_ = 0;
}

template<typename T>
structures::DoublyLinkedList<T>::~DoublyLinkedList() {
    clear();
}

template<typename T>
void structures::DoublyLinkedList<T>::clear() {
    while (!empty()) {
        pop_front();
    }
}

template<typename T>
void structures::DoublyLinkedList<T>::push_back(const T& data) {
    if (empty()) {
        return push_front(data);
    } else {
        Node *p;
        p = head;

        while (p->next() != nullptr) {
            p = p->next();
        }
        Node *novo = new Node(data);
        novo->next(nullptr);
        p->next(novo);
        size_++;
    }
}

template<typename T>
void structures::DoublyLinkedList<T>::push_front(const T& data) {
    Node *novo = new Node(data);
    novo->next(head);
    head = novo;
    size_++;
}


template<typename T>
void structures::DoublyLinkedList<T>::insert(const T& data, std::size_t index) {
    if (index > size_ || index < 0) {
        throw std::out_of_range("fora de alcance");
    } else if (index == 0) {
        return push_front(data);
    } else if (index == size_-1) {
        return push_back(data);
    } else {
        Node *p;
        p = head;
        for (int i = 1; (std::size_t)i < index; i++) {
            p = p->next();
        }
        Node *novo = new Node(data);
        novo->next(p->next());
        p->next(novo);

        size_++;
    }
}

template<typename T>
void structures::DoublyLinkedList<T>::insert_sorted(const T& data) {
    if (empty()) {
        return push_front(data);
    }

    Node *p;
    p = head;

    Node* q;
    q = nullptr;

    while (p != nullptr && data > p->data()) {
        q = p;
        p = p->next();
    }
    if (q != nullptr) {
        Node *novo = new Node(data);
        novo->next(p);
        q->next(novo);
    } else {
        return push_front(data);
    }
    size_++;
}

template<typename T>
T& structures::DoublyLinkedList<T>::at(std::size_t index) {
    if (empty() || index > size_-1) {
        throw std::out_of_range("erro");
    }

    Node *p;
    p = head;

    for (int i = 0; (std::size_t)i < index; i++) {
        p = p->next();
    }
    return p->data();
}

template<typename T>
T structures::DoublyLinkedList<T>::pop(std::size_t index) {
    if (empty())
        throw std::out_of_range("lista vazia");

    if (index > size_-1 || index < 0)
        throw std::out_of_range("fora de alcance");

    if (size_ == 1 || index == 0) {
        return pop_front();
    }
    if (index == size_-1) {
        return pop_back();
    }

    Node *p;
    p = head;

    for (int i = 1; (std::size_t)i < index; i++) {
        p = p->next();
    }

    Node *aux;
    aux = p->next();
    p->next(aux->next());

    T saida = aux->data();

    delete aux;

    size_--;

    return saida;
}

template<typename T>
T structures::DoublyLinkedList<T>::pop_back() {
    if (empty())
        throw std::out_of_range("lista vazia");

    if (size_ == 1)
        return pop_front();

    Node *p;
    p = head;

    for (int i = 1; (std::size_t)i < size_-1; i++) {
        p = p->next();
    }

    T saida = p->next()->data();

    delete p->next();
    p->next(nullptr);

    size_--;

    return saida;
}

template<typename T>
T structures::DoublyLinkedList<T>::pop_front() {
    if (empty())
        throw std::out_of_range("lista vazia");

    Node *p;
    p = head;

    head = p->next();

    T saida = p->data();
    delete p;

    size_--;

    return saida;
}

template<typename T>
void  structures::DoublyLinkedList<T>::remove(const T& data) {
    if (empty())
        throw std::out_of_range("lista vazia");

    Node *p;
    p = head;

    for (int i = 0; (std::size_t)i < size_; i++) {
        if (p->data() == data) {
            pop(i);
            return;
        }
        p = p->next();
    }
}

template<typename T>
bool structures::DoublyLinkedList<T>::empty() const {
    return (size_ == 0);
}

template<typename T>
bool structures::DoublyLinkedList<T>::contains(const T& data) const {
    if (empty())
        throw std::out_of_range("lista vazia");

    Node *p;
    p = head;

    for (int i = 0; (std::size_t)i < size_; i++) {
        if (p->data() == data) {
            return true;
        }
        p = p->next();
    }
    return false;
}

template<typename T>
std::size_t structures::DoublyLinkedList<T>::find(const T& data) const {
    if (empty())
        throw std::out_of_range("lista vazia");

    Node *p;
    p = head;

    for (int i = 0; (std::size_t)i < size_; i++) {
        if (p->data() == data) {
            return (std::size_t)i;
        }
        p = p->next();
    }
    return size_;
}

template<typename T>
std::size_t structures::DoublyLinkedList<T>::size() const {
     return size_;
}
