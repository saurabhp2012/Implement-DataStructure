#include<iostream>
using namespace std;
 
 template<typename T,size_t S>
 class Array{
    private:
        T m_Data[S];
    public:

        int size() const { return S;}
        T& operator[](size_t index){ 
            if(!(index<S)){
               // _debugbreak();
            }
            return m_Data[index];
            }
        const T& operator[] (size_t index) const{ return m_Data[index];}

        T* Data(){return m_Data;}
        const T* Data() const {return m_Data;}
 };
int main()
{
    Array<int,5> a;
    const auto& refArray = a;
    memset (&a[0], 0, a.size() * sizeof (int)) ;
    a[1] = 5;
    a[4] = 8;
    for(int i=0;i<a.size();i++){
        std::cout<<a[i]<<endl;
    }
     
    std::cout<<a.size();
    return 0;
}