/***************************************************************************
	SSbump Generator all code Copyright © 2008 - 2010 Colton Manville (Unless stated otherwise)
	(Contact: the_best_flash@hotmail.com)
 
    This file is part of SSbump Generator.

    SSbump Generator is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    SSbump Generator is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with SSbump Generator.  If not, see <http://www.gnu.org/licenses/gpl.txt>.
***************************************************************************/

#ifndef LINKEDLIST__H__
#define LINKEDLIST__H__

#ifndef NULL
#define NULL 0
#endif

template <class _NODE>
struct Node
{
    _NODE item;
    Node<_NODE>* next;
    Node<_NODE>* prev;
};

template <class _NODE>
class iterator_list
{
public:
    typedef Node<_NODE> node;

private:
    node* iter;

public:
    iterator_list<_NODE>()
    {
        iter = NULL;
    }

    iterator_list<_NODE>(node* &n)
    {
        iter = n;
    }

    iterator_list<_NODE>(const iterator_list<_NODE>& it)
    {
        iter = it.iter;
    }

    ~iterator_list<_NODE>(){/*Do Nothing*/}

    iterator_list<_NODE> Next(int n = 1)
    {
        for( int i = 0; i < n; i++ )
        {
            if(iter != NULL && iter->next != NULL)
                iter = iter->next;
        }

        return *this;
    }

    iterator_list<_NODE> Prev(int n = 1)
    {
        for( int i = 0; i < n; i++ )
        {
            if(iter != NULL && iter->prev != NULL)
                iter = iter->prev;
        }

        return *this;
    }

    _NODE* GetPtr()
    {
        if( iter != NULL )
            return &iter->item;

        return NULL;
    }

    _NODE Get()
    {
        return iter->item;
    }

    void  Set(_NODE item)
    {
        if( iter != NULL )
            iter->item = item;
    }

    iterator_list<_NODE> operator ++()
    {
        if(iter != NULL && iter->next != NULL)
            iter = iter->next;

        return *this;
    }

    iterator_list<_NODE> operator --()
    {
        if(iter != NULL && iter->prev != NULL)
            iter = iter->prev;

        return *this;
    }

    iterator_list<_NODE> operator ++(int)
    {
        iterator_list<_NODE> old = *this;

        if(iter != NULL && iter->next != NULL)
            iter = iter->next;

        return old;
    }

    iterator_list<_NODE> operator --(int)
    {
        iterator_list<_NODE> old = *this;

        if(iter != NULL && iter->prev != NULL)
            iter = iter->prev;

        return old;
    }

    iterator_list<_NODE> operator +(int n)
    {
        for( int i = 0; i < n; i++ )
        {
            if(iter != NULL && iter->next != NULL)
                iter = iter->next;
        }

        return *this;
    }

    iterator_list<_NODE> operator -(int n)
    {
        for( int i = 0; i < n; i++ )
        {
            if(iter != NULL)
                iter = iter->prev;
        }

        return *this;
    }

    bool operator ==(const iterator_list<_NODE>& it)
    {
        return (iter == it.iter);
    }

    bool operator !=(const iterator_list<_NODE>& it)
    {
        return (iter != it.iter);
    }

    _NODE operator *()
    {
        return iter->item;
    }

    iterator_list<_NODE>& operator=(iterator_list<_NODE> it)
    {
        iter = it.iter;
    }
};

template <class _NODE>
class LinkedList
{

public:
    typedef iterator_list<_NODE> iterator;
    typedef Node<_NODE> node;

    LinkedList<_NODE>();
    LinkedList<_NODE>(LinkedList<_NODE> &list);
    ~LinkedList<_NODE>();
    _NODE pop_front();
    _NODE pop_back();
    bool push_front(_NODE item);
    bool push_back(_NODE item);
    bool insert(int pos, _NODE item);
    _NODE remove(int pos);
    _NODE front() const;
    _NODE* front_ptr();
    _NODE* back_ptr();
    _NODE* get_ptr( int pos );
    _NODE back()  const;
    _NODE get(int pos);
    int count();
    int Size(){return size;}
    void clear();

    _NODE operator []( int pos );
    LinkedList<_NODE>& operator =( LinkedList<_NODE> &list );

    iterator begin()
    {
        iterator it(headptr->next);

        return it;
    }

    iterator end()
    {
        iterator it(tailptr);

        return it;
    }

    iterator at(int i)
    {
        node* cur = headptr->next;
        int pos = 0;

        while( cur != tailptr && pos < i)
        {
            cur = cur->next;
            pos++;
        }

        iterator it(cur);

        return it;
    }

private:
    node* headptr;
    node* tailptr;
    int size;

};

template <class _NODE>
LinkedList<_NODE>::LinkedList()
{
    headptr = new node;
    tailptr = new node;

    headptr->prev = NULL;
    headptr->next = tailptr;
    tailptr->next = NULL;
    tailptr->prev = headptr;
    size = 0;
}

template <class _NODE>
LinkedList<_NODE>::LinkedList(LinkedList<_NODE> &list)
{
    headptr = new node;
    tailptr = new node;

    headptr->prev = NULL;
    headptr->next = tailptr;
    tailptr->next = NULL;
    tailptr->prev = headptr;

    size = 0;

    for( int i = 0; i < list.count(); i++ )
        this->push_back(list.get(i));
}

template <class _NODE>
LinkedList<_NODE>::~LinkedList()
{
    clear();

    delete headptr;
    delete tailptr;
}

template <class _NODE>
void LinkedList<_NODE>::clear()
{
    while( size != 0 )
        this->pop_front();
}

template <class _NODE>
int LinkedList<_NODE>::count()
{
    return size;
}

template <class _NODE>
_NODE LinkedList<_NODE>::get(int pos)
{   
    int i = 0;
    node* cur = headptr->next;

    //find where the node is
    while( cur != tailptr && i < pos )
    {
        cur = cur->next;
        i++;
    }

    return cur->item;
}

template <class _NODE>
_NODE LinkedList<_NODE>::pop_front()
{
    if( size != 0 )
    {
        node* cur;
        _NODE temp;

        cur = headptr->next;
        headptr->next = cur->next;

        temp = cur->item;
        delete cur;
        --size;

        return temp;
    }

    return headptr->item;
}

template <class _NODE>
_NODE LinkedList<_NODE>::pop_back()
{
    if( size != 0 )
    {
        node* cur;
        _NODE temp;

        cur = tailptr->prev;
        tailptr->prev = cur->prev;

        temp = cur->item;
        delete cur;
        size--;

        return temp;
    }

    return headptr->item;
}

template <class _NODE>
bool LinkedList<_NODE>::push_front(_NODE item)
{
    node* temp = NULL; //Node that is being added

    //create node to be inserted
    temp = new node;

    if( temp == NULL )
        return false;

    temp->item = item;
    temp->prev = NULL;
    temp->next = NULL;

    temp->next = headptr->next;
    temp->prev = headptr;
    temp->next->prev = temp;
    temp->prev = NULL;
    headptr->next = temp;
    size++;
    return true;
}

template <class _NODE>
bool LinkedList<_NODE>::push_back(_NODE item)
{
    node* temp = NULL; //Node that is being added

    //create node to be inserted
    temp = new node;

    if( temp == NULL )
        return false;

    temp->item = item;
    temp->prev = NULL;
    temp->next = NULL;

    temp->next = tailptr;
    temp->prev = tailptr->prev;
    temp->prev->next = temp;
    tailptr->prev = temp;
    size++;
    return true;
}

template <class _NODE>
bool LinkedList<_NODE>::insert(int pos, _NODE item)
{
    node* cur;  //Current node being checked
    node* prev; //Previously checked node
    node* temp = NULL; //Node that is being added
    int i;

    //create node to be inserted
    temp = new node;

    if( temp == NULL )
        return false;

    temp->next = NULL;
    temp->prev = NULL;
    temp->item = item;

    cur = headptr->next; //First item in the list

    i = 0;
    //find where the number needs to be inserted
    while( cur != tailptr && i < pos )
    {
        cur = cur->next;
        i++;
    }

    prev = cur->prev;

    //Insert at middle of list
    prev->next = temp;
    temp->next = cur;
    cur->prev = temp;
    temp->prev = prev;
    size++;

    return true;
}

template <class _NODE>
_NODE LinkedList<_NODE>::remove(int pos)
{
    node* cur;  //Node that is currently being checked
    node* prev; //Node that was previously checked
    _NODE temp;
    int i;

    //Remove from empty list
    if( headptr->next == tailptr )
        return tailptr->item;

    cur = headptr->next;
    prev = headptr;

    i = 0;
    //Try to find number in the list
    while( cur != tailptr && i < pos )
    {
        cur = cur->next;
        i++;
    }

    if( cur == tailptr )
    {
        cur = cur->prev;
    }

    prev = cur->prev;

    //Remove from the Middle/End
    prev->next = cur->next;
    cur->next->prev = prev;
    temp = cur->item;
    delete cur;
    size--;

    return temp;
}

template <class _NODE>
_NODE LinkedList<_NODE>::front() const
{
    return headptr->next->item;
}

template <class _NODE>
_NODE* LinkedList<_NODE>::front_ptr()
{
    return &headptr->next->item;
}

template <class _NODE>
_NODE LinkedList<_NODE>::back() const
{
    return tailptr->prev->item;
}

template <class _NODE>
_NODE* LinkedList<_NODE>::back_ptr()
{
    return &tailptr->prev->item;
}

template <class _NODE>
_NODE* LinkedList<_NODE>::get_ptr( int pos )
{
    int i = 0;
    node* cur = headptr->next;

    //find where the node is
    while( cur != tailptr && i < pos )
    {
        cur = cur->next;
        i++;
    }

    if( cur == tailptr )
        return NULL;

    return &cur->item;
}

template <class _NODE>
_NODE LinkedList<_NODE>::operator []( int pos )
{
    int i = 0;
    node* cur = headptr->next;

    //find where the node is
    while( cur != tailptr && i < pos )
    {
        cur = cur->next;
        i++;
    }

    return cur->item;
}

template <class _NODE>
LinkedList<_NODE>& LinkedList<_NODE>::operator =( LinkedList<_NODE> &list )
{
    this->clear();

    for( int i = 0; i < list.count(); i++ )
        this->push_back(list.get(i));

    return list;
}

#endif
