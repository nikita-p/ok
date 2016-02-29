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
    virtual void set(int index, T data, int c)
    {
        if(index == c)
            _data = data;
        if(next == NULL)
            return;
        else
            next->set(index,data,c+1);
    }
    virtual void insert(T data)
    {
        list* b = new list(_data, _default, next);
        _data = data;
        next = b;
    }
    virtual void insert(T data, int pos, int c)
    {
        if(next==NULL)
        {
            list* b = new list(data, _default, NULL);
            next = b;
            return;
        }
        if(c == (pos-1))
        {
            list* b = new list(data, _default, next);
            next = b;
        }
        else
            next->insert(data,pos,c+1);
    }
    virtual T _get(int index)
    {
        if(index == 0)
            return _data;
        if(next== NULL)
            return _default;
        else
            return next->get(index-1);
    }
    virtual T remove(int pos, int i)
    {
        if(pos==i+1)
        {
            list* b = next->next;
            T s = next->_data;
            delete next;
            next = b;
            return s;
        }
        else
            next->remove(pos, i+1);
    }
    virtual int len(int c)
    {
        if(next == NULL)
            return (c+1);
        else
            return next->len(c+1);
    }
    virtual void sort_line(bool (*f) (T*, T*))
    {
        if(next->next==NULL)
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
    list()
    {
        _data=0;
        next=NULL;
    }
    list(T data, T def)
    {
        _data = data;
        _default = def;
        next = NULL;
    }
    list(T data, T def, list* nxt)
    {
        _data = data;
        _default = def;
        next = nxt;
    }
    virtual void set(int index, T data)
    {
        set(index, data, 0);
    }
    virtual void insert(int index, T data)
    {
        if(index==0)
            insert(data);
        else
            insert(data, index, 0);
    }
    virtual T get (int index)
    {
        return _get(index);
    }
    virtual T remove(int index)
    {
        if(next == NULL)
            return _default;
        if(index==0)
        {
            list* b = next;
            T s = _data;
            _data = next->_data;
            next = next->next;
            delete b;
            return s;
        }
        return remove(index, 0);
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
    string e("EMPTY!");
    string d("Hello world!");
    list<string>* s = new list<string>(e, d);
    string test("test");
    s->set(0, test);
    return s;
}


int main()
{
    AbstractList<string>* al = get_init();
    al->read(cin);
    al->print(cout);
   /*     al->insert(4,"dda");
        al->insert(4,"ddf");
        al->insert(4,"dsd");
        al->insert(4,"edd");
        al->print(cout);
        al->sort(gr);
        al->print(cout);*/
    return 0;
}
