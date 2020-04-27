#include <queue>
#include <iostream>
#include <vector>
#include <functional>

using namespace std;

template<typename T> void print_queue(T& q) {
    while(!q.empty()) {
        std::cout << q.top() << " ";
        q.pop();
    }
    std::cout << '\n';
}
 
int main(){
  function<bool(int,int)> great = [](const int& a,const int& b){return a>b;};
  priority_queue<int, vector<int>, decltype(great)> pq(great);
  cout << pq.empty() << endl;
  pq.push(3);
  pq.push(8);
  pq.push(4);
  print_queue(pq);
  cout << endl;
  return 0;
}
