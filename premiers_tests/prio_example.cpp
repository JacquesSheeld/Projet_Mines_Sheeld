#include <queue>
#include <iostream>
#include <vector>
#include <functional>

using namespace std;

template<typename T> void print_queue(T& q) {
    while(!q.empty()) {
        std::cout << q.top() << ", ";
        q.pop();
    }
    std::cout << '\n';
}

struct mystruct{
  int a;
  int b;
  mystruct(int a, int b): a(a), b(b){};
};
ostream& operator<< (ostream& os, const mystruct& x) {
    os << x.a << ' ' << x.b;
    return os;
  }
  
int main(){
  mystruct a (1,2);
  mystruct b (2,1);
  function<bool(mystruct, mystruct)> great = [](const mystruct& a,const mystruct& b){return a.b>b.b;};
  priority_queue<mystruct, vector<mystruct>, decltype(great)> pq(great);
  cout << pq.empty() << endl;
  pq.push(a);
  pq.push(b);
  print_queue(pq);
  cout << endl;
  return 0;
}
