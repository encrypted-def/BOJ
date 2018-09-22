#include <bits/stdc++.h>
using namespace std;

///////////////////////////////////////////////////////////////////////
////// 1. Only odd-length palindrome //////////////////////////////////
////// 2. If even-length palindrome also needed, use pad function /////
///////////////////////////////////////////////////////////////////////
class Manacher{
public:
  string S;
  vector<int> A;
  int N;
  Manacher(string _S){
    S = _S;
    N = S.size();
    A.resize(N);
  }
  void calc(){
   int r=-1,p=-1;
    for(int i = 0; i < N; i++){
      if(i <= r) A[i] = min(A[2*p-i],r-i);
      else A[i] = 0;
      for(A[i]++; i-A[i] >= 0 and i+A[i] < N and S[i-A[i]]==S[i+A[i]]; A[i]++);
      A[i]--;
      if(r < i+A[i]) r = i+A[i],p=i;
    }
  }
  void pad(){
    S.resize(2*N+1);
    A.resize(2*N+1);
    S[2*N]='.';
    for(int i = N-1; i >= 0; i--){
      S[2*i+1]=S[i];
      S[2*i]='.';
    }
    N = 2*N+1;
  }
};
int main(){
	ios::sync_with_stdio(0);
  cin.tie(0);
  string S;
  cin >> S;
  Manacher MA(S);
  MA.pad();
  MA.calc();
  cout << *max_element(MA.A.begin(),MA.A.end()); 
}
