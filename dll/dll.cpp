#include <iostream>

template<typename T>
struct Node 
{
    T data;
    Node* prev, * next;
};

template <typename T>
void print(Node<T>* n)
{
    while (n != nullptr) {
        std::cout << n->data << " ";
        n = n->next;
    }
    std::cout << std::endl;
}

template <typename T>
void onlypositive(Node<T>* &start) 
{
    Node<T>* temp = start;
   
    while(temp)
    {
       
        if(temp->data<0) // ako e otricatelno.
        {
            if(!temp->prev) // edge case 1: da e v nachaloto
            {
           
                temp->next->prev = nullptr;
                temp = temp->next;
                start = temp;
          
                continue;
            }
            if(!temp->next)// kraq
            {
                if (temp->prev)
                {
                    temp->prev->next = nullptr;
                }
                delete temp;
                break;
            }
            else // obsht sluchai
            {
                temp->prev->next = temp->next;
                temp->next->prev = temp->prev;
           
                Node<T>* to_delete = temp;
                temp = temp->next;
                delete to_delete;
            
            }
        }
        else // ako e polojitelno.
        {
            temp = temp->next;
        }
    }

}

int add_10(int num)
{
    return num + 10;
}

int add_pred(int (* func)(int), int num)
{
    return func(num);
}

template <typename T>
void filter(Node<T>* &first, bool (* func)(T))
{
    Node<T>* temp = first;
    while(temp)
    {
        if(func(temp->data))
        {
            if(!temp->prev)
            {
                
                temp->next->prev = nullptr;
                temp = temp->next;   
                first = temp;
                continue;
            }

            if(!temp->next)
            {
                temp = temp->prev;
                delete temp->next;
                temp->next = nullptr;
                break;
            }
            else
            {
                temp->prev->next = temp->next;
                temp->next->prev = temp->prev;
                Node<T>* to_delete = temp;
                temp = temp->next;
                delete to_delete;
            }

        }
        else
        {
            temp = temp->next;
        }
    }
}

int add2(int n)
{
    return n * 2;
}
template <typename T>
void map(Node<T> *first,T (*func)(T))
{
    Node<T>* temp = first;
    while(temp)
    {
        temp->data = func(temp->data);
        temp = temp->next;  
    }
}

int sum(int n, int m)
{
    return n + m;
}

template <typename T>
T reduce(Node<T>* first, T(*func)(T,T))
{
    Node<T>* temp = first;
    T res = func(temp->data, temp->next->data);
    temp = temp->next->next;
    while (temp)
    {
        res = func(res,temp->data);
        temp = temp->next;
    }
    return res;
}

bool greater_5(int n)
{
    return n > 0;
}
int main() 
{
    Node<int>* a = new Node<int>{ -9,nullptr,nullptr };
    Node<int>* b = new Node<int>{ 8,a,nullptr };
    Node<int>* c = new Node<int>{ -7,b,nullptr };
    Node<int>* d = new Node<int>{ 6,c,nullptr };
    Node<int>* e = new Node<int>{ -10,d,nullptr };
    Node<int>* f = new Node<int>{ 10,e,nullptr };
    a->next = b;
    b->next = c;
    c->next = d;
    d->next = e;
    e->next = f;
    print(a);
    map(a, add2);
    print(a);
    filter(a, greater_5);
    print(a); 
    std::cout << reduce(a,sum);
}

