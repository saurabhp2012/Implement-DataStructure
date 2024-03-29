#include<iostream>

class String{

    private:
        char* m_Buffer;
        unsigned int m_Size;
    public:
        String(const char* string){
            m_Size = strlen(string);
            m_Buffer = new char[m_Size+1];
            memcpy(m_Buffer,string,m_Size);
            m_Buffer[m_Size] = 0;
        }

        String(const String& other):m_Size(other.m_Size){
            m_Buffer = new char[m_Size+1];
            memcpy(m_Buffer,other.m_Buffer,m_Size+1);

        }
        char& operator[](unsigned int index){
            return m_Buffer[index];
        }
    friend std::ostream& operator<<(std::ostream& stream, String& string);

    ~String(){
        delete []m_Buffer;
    }
};

std::ostream& operator<<(std::ostream& stream, String& string)
{
    
    stream<< string.m_Buffer;
    return stream;
}
int main()
{
    String string = "Cherno";
    String s2 = string;
    s2[2] = 'a';
    std::cout<<string<<std::endl;
    std::cout<<s2<<std::endl;

    
}