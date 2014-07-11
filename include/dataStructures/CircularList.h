#ifndef _CircularList_h_
#define _CircularList_h_

#include <iterator>

#include <iostream>
#include <stdexcept>

namespace dataStructures {

template<typename T>
class CircularList {
    struct node {
        node(node* pred, node* succ, const T& item) :
                pred(pred), succ(succ), item(item) {
        }

        node* pred;
        node* succ;
        T item;
    };

    node* _sentinel;
    int count;

    template<typename U>
    class iterator_base {
    public:
        iterator_base(node* ptr = 0) :
                ptr(ptr) {
        }

        iterator_base& operator++() {
            ptr = ptr->succ;
            return *this;
        }

        iterator_base operator++(int) {
            iterator_base other(*this);
            ptr = ptr->succ;
            return other;
        }

        iterator_base& operator--() {
            ptr = ptr->pred;
            return *this;
        }

        iterator_base operator--(int) {
            iterator_base other(*this);
            ptr = ptr->pred;
            return other;
        }

        bool operator==(const iterator_base& other) const {
            return ptr == other.ptr;
        }

        bool operator!=(const iterator_base& other) const {
            return ptr != other.ptr;
        }

        U& operator*() const {
            return ptr->item;
        }

        U* operator->() const {
            return &(ptr->item);
        }

    private:
        node* ptr;
    };

public:
    CircularList () :
            _sentinel(new node(0, 0, T())), count(0) {
        _sentinel->succ = _sentinel->pred = _sentinel;
    }

    virtual ~CircularList() {
        while (_sentinel->succ != _sentinel) {
            this->_sentinel->succ = this->_sentinel->succ->succ;
            delete this->_sentinel->succ->pred;
        }
    }

    bool empty() const {
        return count == 0;
    }

    int size() const {
        return count;
    }

    T at(int position) const {
        if (position == 0) {
            return this->front();
        } else if (position == count - 1) {
            return this->back();
        } else if (position < 0 || position >= count) {
            throw std::out_of_range("Invalid position.");
        }

        node* p = _sentinel->succ;
        for (int i = 0; i < position; ++i)
            p = p->succ;
        return p->item;
    }

    T back() const {
        return _sentinel->pred->item;
    }

    T front() const {
        return _sentinel->succ->item;
    }

    void push(int position, const T& item) {
        if (position == 0) {
            push_front(item);
            return;
        } else if (position == count) {
            push_back(item);
            return;
        } else if (position < 0 || position > count) {
            throw std::out_of_range("Inserting out of bounds");
        }

        node* aux = _sentinel->succ;
        for (int i = 0; i < position; ++i) {
            aux = aux->succ;
        }

        aux->pred = aux->pred->succ = new node(aux->pred, aux, item);
        ++count;
    }

    void push_back(const T& item) {
        _sentinel->pred = _sentinel->pred->succ = new node(_sentinel->pred,
                _sentinel, item);
        ++this->count;
    }

    void push_front(const T& item) {
        _sentinel->succ = _sentinel->succ->pred = new node(_sentinel,
                _sentinel->succ, item);
        ++this->count;
    }

    T pop_back() {
        if (this->empty()) {
            throw std::out_of_range("Empty list.");
        }

        T removed = this->_sentinel->pred->item;
        this->_sentinel->pred = this->_sentinel->pred->pred;
        delete this->_sentinel->pred->succ;
        this->_sentinel->pred->succ = this->_sentinel;
        --this->count;
        return removed;
    }

    T pop(int position) {
        if (position == 0) {
            return this->pop_front();
        } else if (position == this->count - 1) {
            return this->pop_back();
        } else if (position < 0 || position >= this->count) {
            throw std::out_of_range("Invalid position.");
        }

        node* exNode = this->_sentinel->succ; // será o nó que estava na posição escolhida
        for (int i = 0; i < position; ++i) {
            exNode = exNode->succ;
        }
        T removed = exNode->item;
        exNode->pred->succ = exNode->succ;
        exNode->succ->pred = exNode->pred;
        delete exNode;
        --this->count;
        return removed;
    }

    T pop_front() {
        if (this->empty()) {
            throw std::out_of_range("Empty list.");
        }

        T removed = this->_sentinel->succ->item;
        this->_sentinel->succ = this->_sentinel->succ->succ;
        delete this->_sentinel->succ->pred;
        this->_sentinel->succ->pred = this->_sentinel;
        --this->count;
        return removed;
    }

    typedef iterator_base<T> iterator;
    typedef iterator_base<const T> const_iterator;

    iterator begin() {
        return iterator(_sentinel->succ);
    }

    iterator end() {
        return iterator(_sentinel);
    }

    iterator rbegin() {
        return iterator(_sentinel->pred);
    }

    iterator rend() {
        return iterator(_sentinel);
    }

    const_iterator begin() const {
        return const_iterator(_sentinel->succ);
    }

    const_iterator end() const {
        return const_iterator(_sentinel);
    }

    const_iterator rbegin() const {
        return const_iterator(_sentinel->pred);
    }

    const_iterator rend() const {
        return const_iterator(_sentinel);
    }
};

using std::begin;
using std::end;

}

#endif 