#include <stdio.h>
#include <algorithm>
#include <queue>
#include <vector>
#include <functional>
#define X first
#define Y second
#define PAIR pair<int, int>
using namespace std;
vector<PAIR> edge[20001];
int dist[20001];
 
int main(void){
    int st;
    int V, E;
    scanf("%d %d", &V, &E);
    for(int i = 1; i <= V; i++)
        dist[i] = 0x7ffff;
    scanf("%d", &st);
    while(E--){
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        edge[u].push_back(make_pair(v, w));
    }
    dist[st] = 0;
    priority_queue<PAIR, vector<PAIR >, greater<PAIR > > pq;
    pq.push(make_pair(0, st));
    while(!pq.empty()){
        int my_dist = pq.top().X;
        int current = pq.top().Y;
        pq.pop();
        if(dist[current] < my_dist)
            continue;
        for(int i = 0; i < edge[current].size(); i++){
            if(dist[edge[current][i].X] > my_dist + edge[current][i].Y){
                dist[edge[current][i].X] = my_dist + edge[current][i].Y;
                pq.push(make_pair(dist[edge[current][i].X], edge[current][i].X));
            }
        }
    }
    for(int i = 1; i <= V; i++){
        if(dist[i] == 0x7ffff)
            printf("INF\n");
        else
            printf("%d\n", dist[i]);
    }
}
