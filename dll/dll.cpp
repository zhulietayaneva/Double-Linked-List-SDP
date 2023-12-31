#include <iostream>
#include <functional>

template<typename T>
struct Node 
{
    T data;
    Node* prev, * next = nullptr;

    Node() {
       
        prev = nullptr;
        next = nullptr;
    }

    Node(T val)
    {
        data = val;
        this->prev = nullptr;
        this->next = nullptr;
    }

    Node(T val,Node* prev,Node* next)
    {
        data = val;
        this->prev = prev;
        this->next = next;
    }
};



// ------------- jorj -------------

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
        if(!func(temp->data))
        {
            Node<T>* to_delete = temp;
            if(!temp->prev)
            {
                temp->next->prev = nullptr;
                temp = temp->next;   
                first = temp;
                delete to_delete;
                continue;
            }

            if(!temp->next)
            {
                temp = temp->prev;
                temp->next = nullptr;
                delete to_delete;
                break;
            }
            else
            {
                temp->prev->next = temp->next;
                temp->next->prev = temp->prev;
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

bool filter_condition(int n)
{
    return n > 0;
}

Node<int>* range(int x, int y)
{
    if(x>y)
    {
        int temp = x;
        x = y;
        y = temp;
    }
    Node<int>* result = new Node<int>(x);
    Node<int>* temp = result;
    for(int i = x+1; i<y+1;i++)
    {
        Node<int>* to_add = new Node<int>(i);
        to_add->prev = temp;
        temp->next = to_add;
        temp = temp->next;
    }
    return result;
}


template <typename T>
void reverse(Node<T>* &first)
{
   Node<T>* temp = first;
   Node<T>* start = first;
   Node<T>* end = nullptr;
   int cnt = 0;
   while(temp)
   {
       Node<T>* next = temp->next;
       temp->next = temp->prev;
       temp->prev = next;
      
       if(!temp->prev&&cnt!= 0)
       {
         end = temp;
       }
       temp = next;
       cnt++;
   }
   first = end;
}

template <typename T>
void append(Node<T>* &l1,Node<T>* l2)
{
    Node<T>* temp_1 = l1;
    Node<T>* temp_2 = l2;
    while(temp_1->next)
    {
        temp_1 = temp_1->next;
    }

    while(temp_2)
    {
        Node<T>* new_node = new Node<T>(temp_2->data);
        new_node->prev = temp_1;
        temp_1->next = new_node;
        temp_1 = temp_1->next;
        temp_2 = temp_2->next;
    }
}

template <typename T>
Node<T>* concat(Node<T>* l1, Node<T>* l2)
{
    Node<T>* temp_1 = l1;
    Node<T>* temp_2 = l2;
    Node<T>* result = new Node<T>(temp_1->data);
    Node<T>* temp = result;
    temp_1 = temp_1->next;
    while(temp_1)
    {                                   //data  , temp,  
        Node<T>* new_node = new Node<T>(temp_1->data);
        new_node->prev = temp;
        temp->next = new_node;
        temp = temp->next;


        temp_1 = temp_1->next;
    }

    while (temp_2)
    {
        Node<T>* new_node = new Node<T>(temp_2->data);
        new_node->prev = temp;
        temp->next = new_node;
        temp = temp->next;
        temp_2 = temp_2->next;
    }
    return result;
}




Node<int>* fill_gaps(Node<int>* first)
{
    Node<int>* temp = first;

    while (temp->next)
    {
        //std::cout << temp->data<<", "<<temp->next->data<<std::endl;
        if (temp->data > 2 * temp->next->data) {
            while (temp->data > 2 * temp->next->data)
            {
                Node<int>* new_node = new Node<int>(temp->data / 2);
                new_node->next = temp->next;
                temp->next = new_node;
                temp = temp->next;
            }
        }
        else
        {
            temp = temp->next;
        }
    }

    return first;
}


void keep_product(Node<int>* first)
{
    if (!first->next && !first->next->next)
    {
        return;
    }

    Node<int>* curr_1 = first;
    Node<int>* curr_2 = curr_1->next;
    Node<int>* temp = curr_2->next;
    while (temp)
    {

        if (temp->data % curr_1->data != 0 || temp->data % curr_2->data != 0)
        {
            Node<int>* to_delete = temp;
            temp = temp->next;
            curr_2->next = temp;
            delete to_delete;

        }
        else
        {
            temp = temp->next;
            curr_2 = curr_2->next;
            curr_1 = curr_1->next;
        }
    }


}


Node<int>* mirror(Node<int>* first)
{
    Node<int>* result = new Node<int>(first->data);
    Node<int>* curr = result;
    Node<int>* temp = first->next;
    while (temp)
    {
        Node<int>* new_node = new Node<int>(temp->data);
        curr->next = new_node;
        curr = curr->next;
        temp = temp->next;
    }

    Node<int>* temp_2 = first;
    Node<int>* prev_node = NULL, * next_node = NULL;
    print(temp_2);
    while (temp_2)
    {
        next_node = temp_2->next;

        temp_2->next = prev_node;

        prev_node = temp_2;
        temp_2 = next_node;
    }


    Node<int>* temp_3 = prev_node;
    while (temp_3)
    {
        Node<int>* new_node = new Node<int>(temp_3->data);
        curr->next = new_node;
        curr = curr->next;
        temp_3 = temp_3->next;
    }


    return result;
}


//------------------hulieta-----------------


template <typename T>
void filter_j(Node<T>* &first, std::function<bool(T)> kur)
{
    Node<T>* temp = first;

    while (temp)
    {
        
        if (kur(temp->data))
        {
            Node<T>* toDelete = temp;
            if (temp->prev==nullptr)
            {
                temp = temp->next;
                temp->prev = nullptr;
                first = temp;
                delete toDelete;                
            }
            else if(temp->next == nullptr)
            {
                temp->prev->next = nullptr;
                temp = temp->prev;
                delete toDelete;
                break;
            }
            else
            {
                temp->next->prev = temp->prev;
                temp->prev->next = temp->next;
                temp = temp->next;
                delete toDelete;
            }            
        }
        else 
        {
             temp = temp->next;
        }
    }
}

template <typename T>
Node<T>* range_j(T a, T b) {

    if (a>b)
    {
        T temp;
        temp=b;
        b = a;
        a = temp;
    }

    Node<T>* first = new Node<T>(a,nullptr,new Node<T>());
    Node<T>* temp = first;
    for (int i = a+1; i <= b; i++)
    {
        Node<T>* oldTemp = temp;
        if(i==b)
        {
            temp = new Node<T>(i, oldTemp, nullptr);            
        }
        else
        {
            temp = new Node<T>(i,oldTemp,new Node<T>());                  
        }
        oldTemp->next = temp;
    }
    return first;

}

template <typename T>
Node<T>* reverse_j(Node<T>* &first, Node<T>* &last) {

    Node<T>* temp = first;
    while (temp)
    {
        std::swap(temp->next, temp->prev);
        temp = temp->prev;
    }
    std::swap(first, last);
    return first;
}
template <typename T>
void append_j(Node<T>* &l1_last, Node<T>* &l2) {

    Node<T>* temp = l2;
    temp->prev = l1_last;
    l1_last->next = temp;
    while (temp) {
        Node<T>* newNode = new Node<T>(temp->data, temp->prev, temp->next);
        temp = temp->next;
    }

    return;

}

template <typename T>
Node<T>* concat_j(Node<T>* &l1, Node<T>* &l2) {

    Node<T>* iter = l1;
    Node<T>* iter_l1 = new Node<T>(l1->data);
    Node<T>* iter_l2 = new Node<T>(l2->data);
    Node<T>* res = iter_l1;
    iter = l1->next;
    while (iter) {

        Node<T>* newNode = new Node<T>(iter->data, iter_l1, nullptr);       
        iter_l1->next = newNode;

        iter_l1 = newNode;

        iter = iter->next;
    }   
  
    iter_l1->next = iter_l2;
    iter = l2->next;
  
    while (iter) {

        Node<T>* newNode = new Node<T>(iter->data, iter_l2, nullptr);
        iter_l2->next = newNode;

        iter_l2 = newNode;

        iter = iter->next;
    }

 


    return res;

}



int main() 
{
    Node<int>* a = new Node<int>{ 1,nullptr,nullptr };
    Node<int>* b = new Node<int>{ -2,a,nullptr };
    Node<int>* c = new Node<int>{ 3,b,nullptr };
    Node<int>* d = new Node<int>{- 4,c,nullptr };
    Node<int>* e = new Node<int>{ 5,d,nullptr };
    Node<int>* f = new Node<int>{ -6,e,nullptr };
    a->next = b;
    b->next = c;
    c->next = d;
    d->next = e;
    e->next = f;

    Node<int>* g = new Node<int>{ 7,f,nullptr };
    Node<int>* h = new Node<int>{ -8,g,nullptr };
    Node<int>* i = new Node<int>{ 9,h,nullptr };
    g->next = h;
    h->next = i;

    print(a);
    print(concat_j(a, g));

    
}

