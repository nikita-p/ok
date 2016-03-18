#include <iostream>

using namespace std;

ostream& operator<<(ostream& o, string& s)
{
    o << s.c_str();
    return o;
}

istream& operator>>(istream& i, string& s)
{
    char buf[256];
    i >> buf;
    string tmp(buf);
    s = tmp;

    return i;
}


template<typename T>
class AbstractList
{
protected:
    T _default;
public :
    virtual void sort(bool (*f) (T* first, T* second)) = 0;
    virtual T get(int index) = 0;
    virtual void set(int index, T data) = 0;
    virtual void insert(int index, T data) = 0;
    virtual T remove(int index) = 0;
    virtual int len() = 0;
    void push(T data)
    {
        insert(0, data);
    }
    virtual T pop()
    {
        if (empty())
            return _default;
        else
            return remove(0);
    }
    virtual bool empty()
    {
        return len() == 0;
    }
    virtual ostream& print(ostream& o)
    {
        for (int i = 0; i < len(); i ++)
        {
            o << get(i) << endl;
        }
        return o;
    }
    virtual istream& read(istream& in)
    {
        int count;
        in >> count;
        for (int i = 0 ; i < count ; i ++)
        {
            T tmp;
            in >> tmp;
            insert(len(), tmp);
        }
        return in;
    }
};

template <typename T>
class NewList : public AbstractList<T>
{
    int headNumber;
    T _data;
    NewList* next;
public:
    NewList(NewList* Next)
    {
        this->headNumber = 0;
        this->next = Next;
    }
    NewList(T Default) //init constructor with _default
    {
        this->headNumber = 0;
        this->_default = Default;
        this->next = new NewList(NULL); // end constructor
    }
    NewList() //init constructor without _default
    {
        this->headNumber = 0;
        this->next = new NewList(NULL); // end constructor
    }
    NewList(T Data, T Default, NewList* Next) //add constructor
    {
        this->headNumber = 0;
        this->_default = Default;
        this->_data = Data;
        this->next = Next;
    }
    NewList(const NewList& a) //copy constructor
    {
        this->headNumber = a.headNumber + 1;
        this->_data = a._data;
        this->_default = a._default;
        this->next = a.next;
    }
    NewList& operator = (NewList& a)
    {
        NewList* tmp = new NewList;
        tmp->_default = a._default;
        tmp->_data = a._data;
        tmp->next = a.next;
        tmp->headNumber = a.headNumber + 1;
        return *tmp;
    }
    virtual ~NewList() //destructor
    {
        if(this->headNumber != 0)
        {
            //cout << "haha";
            next == NULL;
        }
    }
    virtual T get(int index)
    {
        if(index>=len() || index < 0)
            return this->_default;
        if(index == 0)
            return next->_data;
        else
            return next->get(index-1);
    }
    int len(int c)
    {
        if(next == NULL)
            return c;
        else
            return next->len(c+1);
    }
    virtual int len()
    {
        return len(-1);
    }
    virtual void set(int index, T data)
    {
        if(next->next == NULL || index < 0)
            return;
        if(index == 0)
        {
            next->_data = data;
            return;
        }
        else
            return next->set(index-1, data);
    }
    virtual void insert(int index, T data)
    {
        if(next == NULL || index < 0)
            return;
        if(index == 0 || next->next == NULL)
        {
            next = new NewList(data, this->_default, next);
            return;
        }
        else
            return next->insert(index-1, data);
    }
    virtual T remove(int index)
    {
        if(next->next == NULL || index < 0)
            return this->_default;
        if(index == 0)
        {
            NewList* Del = next;
            next = next->next;
            Del->headNumber++;
            T s = Del->_data;
            delete Del;
            return s;
        }
        else
            return next->remove(index - 1);
    }
    virtual void sort(bool (*f) (T* first, T* second))
    {
        for(int i=0; i < len(); i++)
            swapper(f);
    }
    virtual void swapper(bool (*f) (T* first, T* second))
    {
        if(next->next->next == NULL)
            return;
        else
        {
            if(f(&(next->_data), &(next->next->_data)))
            {
                NewList* tmp = next->next;
                next->next = next->next->next;
                tmp->next = next;
                next = tmp;
            }
            return next->swapper(f);
        }
    }
};


template <typename T>
bool gr(T* first, T* second)
{
    if(*first > *second)
        return true;
    return false;
}

NewList<string>* get_init()
{
    NewList<string>* init = new NewList<string>("EMPTY!");
    return init;
}

