#include<iostream>
using namespace std;


class Vector{
    private:
        int* m_data;
        int cap;
        int currsize;
    public:
        class Iterator;
        Vector(){
            m_data = new int[5];
            cap = 5;
            currsize = 0;
        }
        void push(int data){
            if(currsize==cap){
                //double the size
                int newcap = cap*2;
                int* new_m_data = new int[newcap];
                for(int i =0;i<cap;i++){
                    new_m_data[i] = m_data[i];
                }
                delete []m_data;
                m_data = new_m_data;
                cap = newcap;
            }
            m_data[currsize++] = data;
            
        }

        int pop(){
            if(currsize==0) return -1;
            return m_data[currsize--];
        }
        int size(){
            return currsize;
        }
        int& get(int index){
            return m_data[index];
        }
        int& operator[](int index) {return m_data[index];}

        Iterator begin();
        Iterator end();
};
class Vector::Iterator{
    private:
        int m_pos;
        Vector& m_vect;
    public:
        
        Iterator(int pos,Vector& vec):m_pos(pos),m_vect(vec){}

        Iterator operator++(int){
            Iterator tmp = *this;
            m_pos++;
            return tmp;
        }

        Iterator& operator++(){
            m_pos++;
            return *this;
        }  
        int & operator*(){
            return m_vect.get(m_pos);
        } 
        bool operator!=(const Iterator& other) const{
            return m_pos != other.m_pos;
        } 
        bool operator==(const Iterator& other) const{
            return m_pos == other.m_pos;
        } 
};

Vector::Iterator Vector::begin(){
    return Iterator(0,*this);
}

Vector::Iterator Vector::end(){
    return Iterator(currsize,*this);
}

int main()
{
    Vector v;
    v.push(1);
    v.push(2);
    v.push(3);
    v.push(4);
    v.push(5);
    v.push(6);
    v.push(7);
    v.pop();   
    v.push(5);
    v.push(6);
    v.push(7);
    cout<< "not using Iterator"<<endl;
    for(int i =0;i<v.size();i++){
        cout<<v[i]<<" ";
    }
    cout<<endl;
    cout<< "Using Iterator"<<endl;
    for(Vector::Iterator it = v.begin();it!=v.end();it++){
        cout<<*it<<" ";
    }
    return 0;
}