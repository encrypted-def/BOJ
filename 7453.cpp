#include <bits/stdc++.h>
using namespace std;
int A[4001], B[4001], C[4001], D[4001];
int mid1[16000001], mid2[16000001];
int main(void) {

  int T, TT;
  scanf("%d", &T);
  TT = T*T;
  for (int i = 0; i < T; i++)
    scanf("%d %d %d %d", &A[i], &B[i], &C[i], &D[i]);
  for (int i = 0; i < T; i++) 
    for (int j = 0; j < T; j++) 
      mid1[i*T + j] = -(A[i] + B[j]);
    
  for (int i = 0; i < T; i++)
    for (int j = 0; j < T; j++)
      mid2[i*T + j] = C[i] + D[j];

  sort(mid1, mid1 + TT);
  sort(mid2, mid2 + TT);
  mid1[TT] = mid2[TT] = 0x7f7f7f7f;
  long long cnt = 0;
  int idx1 = 0, idx2 = 0;
  while(idx1 < TT && idx2 < TT){
    int cnt1 = 0, cnt2 = 0;
    if(mid1[idx1] != mid2[idx2]){
      if(mid1[idx1] < mid2[idx2]) idx1++;
      else idx2++;
      continue;
    }
    idx1++; cnt1++; idx2++; cnt2++;
    while(mid1[idx1] == mid1[idx1-1]){
      idx1++;
      cnt1++;
    }
    while(mid2[idx2] == mid2[idx2-1]){
      idx2++;
      cnt2++;
    }
    cnt += 1ll * cnt1*cnt2;
  }

  printf("%lld", cnt);
}
