#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

/*Prueba
4
3
2
5
1
9
12
7
6
11
10
8
13
*/

vector<int> suffixArray(string S) {
  int n = S.length();
  vector<string> sa;
  vector<int> A(n);
  for (int i = 0; i < n; i++)
    sa.push_back(S.substr(n - i - 1, i + 1));
  sort(sa.begin(), sa.end());
  for (int i = 0; i < n; i++)
    A[i] = n - sa[i].size() + 1;
  return A;
}

int main() { 
  string S = "TEC Monterrey";  
  for (int i = 0;i<S.length();i++){
    cout << suffixArray(S)[i] << endl;
  }
}
