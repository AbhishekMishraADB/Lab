#include<type_traits>
#include<iostream>
#include<algorithm>
#include<numeric>
#include<memory>

using namespace std;

class A
{
    public:
    A()
    {

    }
};

class B : public A
{
    public:
     B(int val)
    {
       cout << "constructing B" << endl;
    }
};

struct B1
{
    public:
     B1(int val, double d)
    {
       cout << "constructing Struct B1" << val << d << endl;
    }
};

//-----------perfect forwarding .&& is universal reference.
template<typename T>
decltype(auto) create(T&& args)
{
    return B(forward<T>(args));
}

//-----------Template Declarations.
template<typename ...U>
void (*fn)(U&& ...args);

template<typename T, typename ... U>
void ExecuteTask( T(*f)(U...), U&& ...args)
{
    cout<<"Executing task with Generic callback" << endl;
    T ret = f(forward<U>(args)...);
    cout<<"Calling Generic Callback function: Result = " << ret << endl;
}

template<typename T, typename ... U>
T constructObject(U&& ...args)
{
   return T(forward<U>(args)...);
}

//-------------Client code;

int Function(int x, int y, int z)
{
    cout<< "Inside function " <<endl;
    return x + y + z;
}

void DemoPerfectForwarding()
{
    auto object = create<>(5);
    int a = 3;
    auto result = create<>(a);
}
int main()
{
   DemoPerfectForwarding();

   auto res = constructObject<B1>(2, 3.0);

   ExecuteTask<>(&Function, 1,2,3);

   return 0;
}