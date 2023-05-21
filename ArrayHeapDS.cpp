#include<iostream>
#include<array>
using namespace std;
 
 class Array{
    private:
        int* m_Data;
        int sizeArray;
    
    public:
        Array(int sizeArray){
            this->sizeArray = sizeArray;
            m_Data = new int[sizeArray];
            for(int i =0;i<sizeArray;i++){
                m_Data[i] = 100*i;
            }
        }

        int size(){ return sizeArray;}

        const int& operator[](int index){
            return m_Data[index];
        }


 };
int main()
{
    Array arr(6);
    cout<<arr[5]<<endl;
    cout<<arr.size();
    return 0;
}