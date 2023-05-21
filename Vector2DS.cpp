    #include<iostream>
    using namespace std;

    struct Vector3{
        int x=0;
        int y =0;
        int z=0;

            Vector3(){
                //cout<<"Default vector3"<<endl;
            }
            Vector3(int x, int y,int z):x(x),y(y),z(z){
                
            }
            Vector3(const Vector3& other):x(other.x),y(other.y),z(other.z){
                cout<<"Copy"<<endl;
            }
            Vector3(const Vector3&& other):x(other.x),y(other.y),z(other.z){
                cout<<"Move"<<endl;
            }
            Vector3& operator= (const Vector3& other)
            {
                std::cout << "Copy vector3\n"<<endl;
                x = other.x;
                y = other.y;
                z = other. z;
                return *this;
            }
            Vector3& operator= (const Vector3&& other)
            {
                std::cout << "Move vector3\n"<<endl;
                //std::cout <<" x: "<<other.x<<" y: "<<other.y<<" z: "<<other.z<<endl;
                x = other.x;
                y = other.y;
                z = other. z;
                return *this;
            }        
            ~Vector3(){
                cout<<"Destroy"<<endl;
            }

    };


    template<typename Vector>
    class VectorIterator{
        public:
            using ValueType = typename Vector::ValueType;
            using PointerType = ValueType*;
            using ReferenceType = ValueType&;    
        private:
            PointerType m_Ptr;

        public:

            VectorIterator(PointerType ptr):m_Ptr(ptr){}

            VectorIterator& operator++(){
                m_Ptr++;
                return *this;
            }
            VectorIterator operator++(int){
                VectorIterator iterator = *this;
                ++(*this);
                return iterator;
            }
            VectorIterator& operator--(){
                m_Ptr--;
                return *this;
            }
            VectorIterator operator--(int){
                VectorIterator iterator = *this;
                --(*this);
                return iterator;
            }
            ReferenceType operator[](int index){
                return *(m_Ptr+index);
            }
            PointerType operator->(){
                return m_Ptr;
            }
            ReferenceType operator*(){
                return *m_Ptr;
            }
            bool operator==(const VectorIterator& other) const
            {
                return m_Ptr == other.m_Ptr;
            }
            bool operator!=(const VectorIterator& other) const
            {
                return !(*this==other);
            } 
    };

    template<typename T>
    class Vector{
        private:
            T* m_Data;
            size_t m_Size;
            size_t m_Capacity;

            void ReAlloc(size_t newCapacity){
                // 1. allocate a new block of memory
                // 2. copy/move old elements into new block
                // 3. delete

                T* newBlock = new T[newCapacity];

                if (newCapacity < m_Size)
                    m_Size = newCapacity;

                for(size_t i = 0;i<m_Size;i++){
                    newBlock[i] = std::move(m_Data[i]);
                }
                //delete[] m_Data;
                m_Data = newBlock;
                newBlock = nullptr;
                m_Capacity = newCapacity;
            }

        public:

            using ValueType = T;
            using Iterator = VectorIterator<Vector<T>>;

            Vector(){
                //allocate 2 element initially
                m_Data = new T[2];
                m_Size = 0;
                m_Capacity = 2;

            }

            void PushBack(const T& value){

                if(m_Size>=m_Capacity)
                    ReAlloc(m_Capacity+m_Capacity/2);
                m_Data[m_Size++] = value;
            }
            
            void PushBack(T&& value){

                if(m_Size>=m_Capacity)
                    ReAlloc(m_Capacity+m_Capacity/2);
                m_Data[m_Size++] = std::move(value);
            }
            
            void PopBack()      
            {   
                if (m_Size > 0)
                {
                    m_Size--;
                    m_Data[m_Size].~T() ;
                }
            }

            const T& operator[](int index) const{
                if(m_Size>=m_Capacity){
                    //assert
                }
                return m_Data[index];
            }

            T& operator[](int index) {
                return m_Data[index];
            }

            const size_t Size()const{ return m_Size;}
        
            Iterator begin(){
                return Iterator(m_Data);
            }

            Iterator end(){
                return Iterator(m_Data+m_Size);
            }


    };

    void PrintVector(const Vector<Vector3>& vector)
    {
        for (size_t i = 0; i <vector.Size(); i++)
        std::cout << vector[i].x << " " << vector[i].y << " " << vector[i].z << std::endl;

    }
    int main()
    {
        cout<<"*************-----------------------------------------------------------**************"<<endl;
        // Vector<Vector3> vector;
        // cout<<"----------------------------------------------------------"<<endl;
        // vector.PushBack(Vector3(1,2,3));
        // cout<<"----------------------------------------------------------"<<endl;
        // vector.PushBack(Vector3(4,5,6));
        // cout<<"-----------------------------------------------------------"<<endl;
        // PrintVector(vector);
        // cout<<"----------------"<<endl;
        // vector.PopBack();
        // cout<<"-----------------------------------------------------------"<<endl;
        // PrintVector(vector);
        // cout<<"-----------------------------------------------------------"<<endl;
        Vector<int> values;
        values.PushBack(1);
        values.PushBack(2);
        values.PushBack(3);
        values.PushBack(4);

        cout<<"Not using Iterator"<<endl;
        for(int i =0;i<values.Size();i++){
            cout<<values[i]<<" ";
        }
        cout<<endl;
        
        cout<<"Using Iterator"<<endl;
        for(Vector<int>::Iterator it = values.begin();it!=values.end();it++){
            cout<<*it<<" ";
        }
        cout<<endl;
        cout<<"Range based for loop"<<endl;
        for(int value:values){
            cout<<value<<" ";
        }
        

        return 0;
    }