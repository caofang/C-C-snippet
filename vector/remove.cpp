// Use g++ -std=c++11 or clang++ -std=c++11 to compile.
// g++ -std=c++11 -o remove remove.cpp

#include <vector> // the general-purpose vector container
#include <iostream>
#include <algorithm> // remove and remove_if

using namespace std; 
bool is_odd(int i)
{
    return (i % 2) != 0;  
}

void print(const vector<int> &vec)
{
    for (const auto& i: vec) 
        cout << i << ' '; 
    cout << endl;
}
 
int main()
{
    // initialises a vector that holds the numbers from 0-9.
    vector<int> v = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    print(v);

    // removes all elements with the value 5
    v.erase( remove( v.begin(), v.end(), 5 ), v.end() ); 
    print(v); 

    // removes all odd numbers
    v.erase( remove_if(v.begin(), v.end(), is_odd), v.end() );
    print(v);

    return 0;  
}