// Type your code here, or load an example.

#include<type_traits>
#include<iostream>
#include<algorithm>
#include<numeric>
using namespace std;

template<class T> 
constexpr T absolute(T arg)
{
   return arg < 0? -arg : arg;
}


// using enable_if
template<class T>
constexpr enable_if_t<is_floating_point<T>::value, bool> close_enough(T a, T b)
{
    return absolute( a - b) < static_cast<T>(0.0000001);
}

template<class T>

constexpr enable_if_t<!is_floating_point<T>::value, bool> ValidTemperature(T a, T b)
{
    return a == b;
}

// using c++20

template<class T>
requires is_floating_point_v<T> 
constexpr bool ValidTemperature(T a, T b)
{
    return absolute(a - b) < static_cast<T>(0.0000001);
}
// using if constexpr... else.

/*template<class T>
constexpr bool ValidTemperature(T a, T b)
{
    if constexpr (is_floating_point<T>::value)
        return absolute(a-b) <  static_cast<T>(0.0000001);
    else
        return a == b;
}*/



// Concepts, requires

template<class T>
requires is_floating_point_v<T> || is_floating_point_v<T>
constexpr double Average(const std::vector<T>& vec) {
    const double sum = std::accumulate(vec.begin(), vec.end(), 0.0);        
    return sum / static_cast<double>(vec.size());
}

template<class T>
concept needed = is_floating_point_v<T> || is_floating_point_v<T>;

template<class T>
requires needed<T>
constexpr double AverageX(const std::vector<T>& vec) {
    const double sum = std::accumulate(vec.begin(), vec.end(), 0.0);        
    return sum / static_cast<double>(vec.size());
}

template<class T>
constexpr
enable_if_t<is_floating_point_v<T> || is_integral_v<T>, double>
AverageY(const std::vector<T>& vec) {
    const double sum = std::accumulate(vec.begin(), vec.end(), 0.0);        
    return sum / static_cast<double>(vec.size());
}


int main()
{
   float a = 20.000004;
   float b = 20.000004;

   auto result = ValidTemperature(a, b);

   cout<< "Result is"<< result << endl;

   return 0;
}