//
// Created by Ethan Horowitz on 10/30/23.
//

#include "LinkedList.h"


//template <class T>
//LinkedList<T>::LinkedList() {
//    length = 0;
//    index = -1;
//    head = nullptr;
//    tail = nullptr;
//    curr = nullptr;
//}
//
//template <class T>
//LinkedList<T>::LinkedList(const LinkedList<T> & list) {
//    length = 0;
//    index = 0;
//    head = nullptr;
//    tail = nullptr;
//    curr = nullptr;
//
//    ListNode<T> * temp = list.head;
//
//    while(temp != nullptr)
//    {
//        append(temp->element);
//        temp = temp->next;
//    }
//}
//
//template <class T>
//LinkedList<T> & LinkedList<T>::operator=(const LinkedList<T> & list)
//{
//    clear();
//
//    ListNode<T> * temp = list.head;
//
//    while(temp != nullptr)
//    {
//        append(temp->element);
//        temp = temp->next;
//    }
//
//    return *this;
//}
//
//template <class T>
//LinkedList<T>::~LinkedList() {
//    clear();
//}
//
//template<class T>
//T& LinkedList<T>::current()
//{
//    return curr->element;
//}
//
//template<class T>
//T &LinkedList<T>::get(int ind) {
//    if(index < 0 || index >= length)
//        return nullptr;
//
//    while (index != ind){
//        if (ind > index)
//            next();
//        else
//            prev();
//    }
//    return curr->element;
//}
//
//
//template<class T>
//T& LinkedList<T>::first() const
//{
//    return head->element;
//}
//
//template<class T>
//T& LinkedList<T>::last() const
//{
//    return tail->element;
//}
//
//template<class T>
//int LinkedList<T>::getLength()
//{
//    return length;
//}
//
//template <class T>
//void LinkedList<T>::append(T element)
//{
//    ListNode<T> * node = new ListNode<T>(element, tail, nullptr);
//
//    if(length == 0) {
//        curr = tail = head = node;
//        index = 0;
//    }
//    else {
//        tail->next = node;
//        tail = node;
//    }
//
//    length++;
//
//}
//
//template <class T>
//void LinkedList<T>::DeleteLast()
//{
//    if(length == 0)
//        return;
//    curr = tail;
//    deleteCurrent();
//}
//
//template <class T>
//void LinkedList<T>::DeleteFirst()
//{
//    if(length == 0)
//        return;
//    curr = head;
//    deleteCurrent();
//}
//
//template <class T>
//bool LinkedList<T>::next()
//{
//    if(length == 0)
//        return false;
//
//    if(curr->next == nullptr)
//        return false;
//
//    curr = curr->next;
//    index++;
//    return true;
//}
//
//template <class T>
//bool LinkedList<T>::moveToStart()
//{
//    curr = head;
//    index = 0;
//    return length != 0;
//}
//
//template<class T>
//bool LinkedList<T>::prev()
//{
//    if(length == 0)
//        return false;
//
//    if(curr->prev != nullptr)
//        return false;
//
//    index--;
//    curr = curr->prev;
//    return true;
//}
//
//template <class T>
//void LinkedList<T>::Delete(T & elem)
//{
//    if(search(elem))
//        deleteCurrent();
//}
//
//template <class T>
//void LinkedList<T>::deleteCurrent()
//{
//    if(length == 0)
//        return;
//    length--;
//    ListNode<T> * temp = curr;
//
//    if(temp->prev != nullptr)
//        temp->prev->next = temp->next;
//    if(temp->next != nullptr)
//        temp->next->prev = temp->prev;
//
//    if(length == 0) {
//        head = curr = tail = nullptr;
//        index = -1;
//    }
//    else if(curr == head) {
//        curr = head = head->next;
//        index = 0;
//    }
//    else if(curr == tail) {
//        curr = tail = tail->prev;
//        index = length - 1;
//    }
//    else {
//        curr = curr->prev;
//        index--;
//    }
//
//    delete temp;
//}
//
//template <class T>
//bool LinkedList<T>::search(T elem)
//{
//    if(length == 0)
//        return false;
//    if(moveToStart())
//        do {
//            if(curr->element == elem)
//                return true;
//        } while (next());
//    return false;
//}
//
//template <class T>
//void LinkedList<T>::update(T elem)
//{
//    if(search(elem))
//        curr->element = elem;
//}
//
//template <class T>
//void LinkedList<T>::clear()
//{
//    if(length == 0) {
//        return;
//    }
//    ListNode<T> * temp = head;
//
//    while(temp != nullptr)
//    {
//        head = head->next;
//        delete temp;
//        temp = head;
//    }
//
//    head = curr = tail = nullptr;
//
//    length = 0;
//    index = -1;
//}
