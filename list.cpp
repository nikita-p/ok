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
class MyList: public AbstractList<T>
{
    T _data;
    MyList* next;
    virtual int len(int n)
    {
        if(next == NULL)
            return n-1;
        else
            return next->len(n+1);
    }

public:
    MyList(T def) //init empty end
    {
        this->next = NULL;
        this->_default = def;
    }
    MyList(T def, MyList* s) //init empty head
    {
        this->next = s;
        this->_default = def;
    }
    MyList(T data, T def, MyList* s) //insert
    {
        this->next = s;
        this->_default = def;
        this->_data = data;
    }
    virtual ~MyList()
    {
        next = NULL;
    }
    virtual void swapper(bool (*f) (T* first, T* second))
    {
        if(next->next->next == NULL)
            return;
        else
        {
            if(f(&(next->_data), &(next->next->_data)))
            {
                MyList* tmp = next->next;
                next->next = next->next->next;
                tmp->next = next;
                next = tmp;
            }
            return next->swapper(f);
        }
    }

    virtual void sort(bool (*f) (T* first, T* second))
    {
        for(int i=0; i < len(); i++)
            swapper(f);
    }
    virtual T get(int index)
    {
        if(next->next == NULL || index < 0)
            return this->_default;
        if(index == 0)
            return next->_data;
        else
            return next->get(index-1);
    }
    virtual void set(int index, T data)
    {
        if(next->next == NULL || index < 0)
            return;
        if(index == 0)
            next->_data = data;
        else
            next->set(index-1, data);
    }
    virtual void insert(int index, T data)
    {
        if(next == NULL || index < 0)
            return;
        if(index == 0 || next->next == NULL)
        {
            next = new MyList(data, this->_default, next);
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
            MyList* Del = this->next;
            this->next = this->next->next;
            T s = Del->_data;
            delete Del;
            return s;
        }
        else
            return next->remove(index-1);
    }
    virtual int len()
    {
        return len(0);
    }
};

template <typename T>
bool gr(T* first, T* second)
{
    if(*first > *second)
        return true;
    return false;
}

MyList<string>* get_init()
{
    MyList<string>* end = new MyList<string>("EMPTY!");
    MyList<string>* head = new MyList<string>("EMPTY!", end);
    return head;
}

/*
int main()
{
    MyList<string>* s = get_init();
    for(;;)
    {
        s->push("s");
        s->pop();
    }
    return 0;
}*/
