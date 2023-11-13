//
// Created by Ethan Horowitz on 10/30/23.
//

#ifndef SIMLED_LINKEDLIST_H
#define SIMLED_LINKEDLIST_H

template <class T>
class ListNode {
public:
    T element;
    ListNode* next;
    ListNode* prev;

    ListNode(T element, ListNode* prev, ListNode* next) : element(element)
    {
        this->next = next;
        this->prev = prev;
    };
};

template <class T>
class LinkedList  {
private:
    int length;
    int index;
    ListNode<T>* head;
    ListNode<T>* tail;
    ListNode<T>* curr;
public:
    LinkedList();
    LinkedList(const LinkedList<T>&);
    ~LinkedList();
    T& current();
    T& first() const;
    T& last() const;
    T get(int ind);
    int getLength();
    void append(T);
    void deleteCurrent();
    bool next();
    bool moveToStart();
    bool prev();
    bool search(T);
    void clear();
    void update(T elem);
    LinkedList& operator = (const LinkedList<T>&);
};


template <class T>
LinkedList<T>::LinkedList() {
    length = 0;
    index = -1;
    head = nullptr;
    tail = nullptr;
    curr = nullptr;
}

template <class T>
LinkedList<T>::LinkedList(const LinkedList<T> & list) {
    length = 0;
    index = 0;
    head = nullptr;
    tail = nullptr;
    curr = nullptr;

    ListNode<T> * temp = list.head;

    while(temp != nullptr)
    {
        append(temp->element);
        temp = temp->next;
    }
}

template <class T>
LinkedList<T> & LinkedList<T>::operator=(const LinkedList<T> & list)
{
    if (this == &list)
        return *this;
    clear();

    ListNode<T> * temp = list.head;

    while(temp != nullptr)
    {
        append(temp->element);
        temp = temp->next;
    }

    return *this;
}

template <class T>
LinkedList<T>::~LinkedList() {
    clear();
}

template<class T>
T& LinkedList<T>::current()
{
    return curr->element;
}

template<class T>
T LinkedList<T>::get(int ind) {
    if(index < 0 || index >= length) {
        return 0;
    }

    while (index != ind){
        if (index < ind) {
            this->next();
        }
        else {
            this->prev();
        }
    }
    return curr->element;
}

template<class T>
T& LinkedList<T>::first() const
{
    return head->element;
}

template<class T>
T& LinkedList<T>::last() const
{
    return tail->element;
}

template<class T>
int LinkedList<T>::getLength()
{
    return length;
}

template <class T>
void LinkedList<T>::append(T element)
{
    auto* node = new ListNode<T>(element, tail, nullptr);

    if(length == 0) {
        curr = tail = head = node;
        index = 0;
    }
    else {
        tail->next = node;
        tail = node;
    }

    length++;
}

template <class T>
bool LinkedList<T>::next()
{
    if(length == 0)
        return false;

    if(curr->next == nullptr)
        return false;

    curr = curr->next;
    index++;
    return true;
}

template <class T>
bool LinkedList<T>::moveToStart()
{
    curr = head;
    index = 0;
    return length != 0;
}

template<class T>
bool LinkedList<T>::prev()
{
    if(length == 0) {
        return false;
    }

    if(curr->prev == nullptr) {
        return false;
    }

    index--;
    curr = curr->prev;
    return true;
}

template <class T>
void LinkedList<T>::deleteCurrent()
{
    if(length == 0)
        return;
    length--;
    ListNode<T> * temp = curr;

    if(temp->prev != nullptr)
        temp->prev->next = temp->next;
    if(temp->next != nullptr)
        temp->next->prev = temp->prev;

    if(length == 0) {
        head = curr = tail = nullptr;
        index = -1;
    }
    else if(curr == head) {
        curr = head = head->next;
        index = 0;
    }
    else if(curr == tail) {
        curr = tail = tail->prev;
        index = length - 1;
    }
    else {
        curr = curr->prev;
        index--;
    }

    delete temp;
}

template <class T>
bool LinkedList<T>::search(T elem)
{
    if(length == 0)
        return false;
    if(moveToStart())
        do {
            if(curr->element == elem)
                return true;
        } while (next());
    return false;
}

template <class T>
void LinkedList<T>::update(T elem)
{
    curr->element = elem;
}

template <class T>
void LinkedList<T>::clear()
{
    if(length == 0) {
        return;
    }
    ListNode<T> * temp = head;

    while(temp != nullptr)
    {
        head = head->next;
        delete temp;
        temp = head;
    }

    head = curr = tail = nullptr;

    length = 0;
    index = -1;
}


#endif //SIMLED_LINKEDLIST_H
