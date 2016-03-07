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
class list : public AbstractList<T>
{
    T _data;
    list* next;
protected:
    T _default;
private:
    virtual void sort_line(bool (*f) (T*, T*))
    {
        if(next->next->next==NULL)
            return;
        if(f(&(next->_data), &(next->next->_data)))
        {
            list* tmp = next;
            next = next->next;
            tmp->next = next->next;
            next->next = tmp;
        }
        next->sort_line(f);
    }
public:
    list(T def)
    {
        _default = def;
        next = NULL;
    }
    list(T data, T def, list* nxt)
    {
        _data = data;
        _default = def;
        next = nxt;
    }
    virtual ~list()
    {
        next = NULL;
    }
    virtual void set(int index, T data)
    {
        if(next == NULL)
            return;
        if(index == 0)
        {
            _data = data;
            return;
        }
        next->set(index-1, data);
    }
    virtual void insert(int index, T data)
    {
        if(index == 0)
        {
            list* tmp = new list(_data, _default, next);
            _data = data;
            next = tmp;
            return;
        }
        if(next==NULL)
            return;
        if(index == 1 || next->next == NULL)
        {
            list* tmp = new list(data, _default, next);
            next = tmp;
            return;
        }
        next->insert(index-1,data);
    }
    virtual T get (int index)
    {
        if(index==0)
            return _data;
        return next->get(index-1);
    }
    virtual T remove(int index)
    {
        if(next == NULL)
        {
            return _default;
        }
        if(index==0)
        {
            _data = next->_data;
            list* del = next;
            next = next->next;
            T s = del->_data;
            delete del;
            return s;
        }
        if(index == 1)
        {
            list* del = next;
            next = next->next;
            T s = del->_data;
            delete del;
            return s;
        }
        return next->remove(index-1);
    }
    virtual int len(int i)
    {
        if(next == NULL)
            return i;
        return next->len(i+1);
    }
    virtual int len()
    {
        return len(0);
    }
    virtual void sort(bool (*f) (T*, T*))
    {
        insert(0, _default);
        for(int i=0;i<len(); i++)
            sort_line(f);
        remove(0);
    }
};

template <typename T>
bool gr(T* first, T* second)
{
    if(*first > *second)
        return true;
    return false;
}

AbstractList<string>* get_init()
{
    list<string>* s = new list<string>("EMPTY!");
    return s;
}


