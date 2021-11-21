#include <iostream>
#include <algorithm>

		
using namespace std;
#define ll long long int
#define ull unsigned long long int
#define li long int
#define ui unsigned int

// class Vector {
  // public:
    // Vector(int s) :elem{new double[s]}, sz{s} {} //constructor
    // double& operator[] (int i) { return elem[i];} //subscript
    // int size(){ return sz; }
  // private:
    // double* elem;
    // int sz;
// };


class Vector {
public:
  Vector(int s);
  double& operator[](int i);
  int size();
private:
  double* elem;
  int sz;
};

Vector::Vector(int s)
  :elem{ new double[s]}, sz{s}{}

double& Vector::operator[](int i)
{
  return elem[i];
}

double read_and_sum(int s){
  
  Vector v(s);
  for(int i=0; i < s; ++i)
    cin >> v[i];

  double sum = 0;
  for(int i=0; i<v.size(); i++)
    sum+=v[i];
  return sum;
}

int main(){

 Vector v(6); 

 cout << v.size() << '\n';

 cout << read_and_sum(6) << '\n';


}

