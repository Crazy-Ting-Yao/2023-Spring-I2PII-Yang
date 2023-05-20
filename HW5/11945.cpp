#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;

// G[i] is the neighbor towns of town i
vector<int> diamondTowns;
vector<int> G[100005];
int Dist[100005];

struct node {
    int id;
    int dist;
    node(int id, int l) {
        this->id = id;
        this->dist = l;
    }
};

int main() {
    int N, M, K;
    cin >> N >> M >> K;
    for (int i = 0; i < M; i++) {
        int a, b;
        cin >> a >> b;
        G[a].push_back(b);
        G[b].push_back(a);
    }
    for (int i = 0; i < K; i++) {
        int x;
        cin >> x;
        diamondTowns.push_back(x);
    }
    fill(Dist, Dist + 100005, -1);

    queue<node> Q;
    // [TODO] complete the task!

    for(int i=0;i<diamondTowns.size();i++) Dist[diamondTowns[i]] = 0;
    for (int i = 0; i < diamondTowns.size(); i++){
        node start(diamondTowns[i],0);
        Q.push(start);
        while(Q.size()){
            node t = Q.front();
            Q.pop();
            for(int i=0;i<G[t.id].size();i++){
                if(Dist[G[t.id][i]]==-1||Dist[G[t.id][i]]>t.dist){
                    Dist[G[t.id][i]]=t.dist+1;
                    node p(G[t.id][i],Dist[G[t.id][i]]);
                    Q.push(p);
                }
            }
        }
    }
    // Output
    for (int i = 1; i <= N; i++) {
        cout << Dist[i] << '\n';
    }
    return 0;
}