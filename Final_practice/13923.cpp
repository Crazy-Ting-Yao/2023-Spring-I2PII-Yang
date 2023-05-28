#include<iostream>
#include<queue>
#include<string>

typedef struct{
    int x;
    int y;
}Point;

int main(){
    int n, m;
    int steps = -1;
    std::cin>>n>>m;
    std::string map[n];
    for(int i=0;i<n;i++){
        std::cin>>map[i];
    }
    Point startpos;
    bool found = false;
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            if(map[i][j]=='P'){
                startpos.x = i;
                startpos.y = j;
                map[i][j] = '#';
                found = true;
                break;
            }
        }
        if(found) break;
    }
    std::queue<std::pair<Point,int>> q;
    q.push(std::make_pair(startpos,0));
    while(!q.empty()){
        Point cur = q.front().first;
        int curstep = q.front().second+1;
        q.pop();
        if(cur.x){
            if(map[cur.x-1][cur.y]=='@'){
                steps = curstep;
                break;
            }
            else if(map[cur.x-1][cur.y]!='#') {
                cur.x--;
                map[cur.x][cur.y] = '#';
                q.push(std::make_pair(cur,curstep));
                cur.x++;    
            }
        }
        if(cur.y){
            if(map[cur.x][cur.y-1]=='@'){
                steps = curstep;
                break;
            }
            else if(map[cur.x][cur.y-1]!='#') {
                cur.y--;
                map[cur.x][cur.y] = '#';
                q.push(std::make_pair(cur,curstep));
                cur.y++;
            }
        }
        if(cur.x+1<n){
            if(map[cur.x+1][cur.y]=='@'){
                steps = curstep;
                break;
            }
            else if(map[cur.x+1][cur.y]!='#'){
                cur.x++;
                map[cur.x][cur.y] = '#';
                q.push(std::make_pair(cur,curstep));
                cur.x--;
            }
        }
        if(cur.y+1<m){
            if(map[cur.x][cur.y+1]=='@'){
                steps = curstep;
                break;
            }
            else if(map[cur.x][cur.y+1]!='#') {
                cur.y++;
                map[cur.x][cur.y] = '#';
                q.push(std::make_pair(cur,curstep));
                cur.y--;
            }   
        }
    }
    std::cout<<steps<<std::endl;
}