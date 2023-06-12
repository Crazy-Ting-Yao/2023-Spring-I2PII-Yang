#include <cmath>
#include <iostream>
#include <queue>
#include <set>
#include <utility>
#include <vector>
#define MAX 80
const int goal_row[16] = {-1, 0, 0, 0, 0, 1, 1, 1, 1, 2, 2, 2, 2, 3, 3, 3};
const int goal_col[16] = {-1, 0, 1, 2, 3, 0, 1, 2, 3, 0, 1, 2, 3, 0, 1, 2};

struct State{
    int puzzle[4][4];
    int steps;
    int h = 0;
    int zerox, zeroy;
    int prevx, prevy;
    void cal_h() {
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                if (!puzzle[i][j]) continue;
                h += abs(goal_row[puzzle[i][j]] - i) + abs(goal_col[puzzle[i][j]] - j);
            }
        }
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                if (!puzzle[i][j]) continue;
                if (!(goal_row[puzzle[i][j]] - i) && (goal_col[puzzle[i][j]] - j)) 
                    for (int k = j + 1; k < 4; k++)
                        if (goal_row[puzzle[i][k]] == i && puzzle[i][j] > puzzle[i][k])
                            h += 2;
                
                else if ((goal_row[puzzle[i][j]] - i) && !(goal_col[puzzle[i][j]] - j)) 
                    for (int k = i + 1; k < 4; k++)
                        if (goal_col[puzzle[k][j]] == j && puzzle[i][j] > puzzle[k][j])
                            h += 2;
            }
        }
    }
    State(int p[4][4], int steps, int px = -1, int py = -1)
        : steps(steps), prevx(px), prevy(py) {
        for (int i = 0; i < 4; i++) 
            for (int j = 0; j < 4; j++) {
                puzzle[i][j] = p[i][j];
                if (!puzzle[i][j]) 
                    zerox = i, zeroy = j;
            }
        cal_h();
    }
    bool operator>(const State& s) const { return steps + h > s.steps + s.h; }
};

struct cmp {
    bool operator()(const State& s1, const State& s2) {
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                if (s1.puzzle[i][j] - s2.puzzle[i][j])
                    return s1.puzzle[i][j] > s2.puzzle[i][j];
            }
        }
        return false;
    }
};

int main() {
    std::ios::sync_with_stdio(false);
    std::priority_queue<State, std::vector<State>, std::greater<State>> P;
    std::set<State, cmp> s;
    std::pair<std::set<State, cmp>::iterator, bool> it;
    int p[4][4];
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++) std::cin >> p[i][j];
    P.push({p, 0, -1, -1});
    s.insert({p, 0, -1, -1});
    while (P.size()) {
        if (!P.top().h) {
            std::cout << P.top().steps << std::endl;
            return 0;
        }
        if (P.top().steps >= MAX) {
            P.pop();
            continue;
        }
        int c[4][4];
        for (int i = 0; i < 4; i++)
            for (int j = 0; j < 4; j++) 
                c[i][j] = P.top().puzzle[i][j];
        int x = P.top().zerox;
        int y = P.top().zeroy;
        int prex = P.top().prevx;
        int prey = P.top().prevy;
        int steps = P.top().steps;
        P.pop();
        if (x && prex != x - 1) {
            std::swap(c[x - 1][y], c[x][y]);
            it = s.insert({c, steps + 1});
            if (it.second) P.push({c, steps + 1, x, y});
            else if (it.first->steps > steps + 1) {
                s.erase(it.first);
                s.insert({c, steps + 1});
                P.push({c, steps + 1, x, y});
            }
            std::swap(c[x - 1][y], c[x][y]);
        }
        if (y && prey != y - 1) {
            std::swap(c[x][y], c[x][y - 1]);
            it = s.insert({c, steps + 1});
            if (it.second) P.push({c, steps + 1, x, y});
            else if (it.first->steps > steps + 1) {
                s.erase(it.first);
                s.insert({c, steps + 1});
                P.push({c, steps + 1, x, y});
            }
            std::swap(c[x][y], c[x][y - 1]);
        }
        if (x < 3 && prex != x + 1) {
            std::swap(c[x + 1][y], c[x][y]);
            it = s.insert({c, steps + 1});
            if (it.second)
                P.push({c, steps + 1, x, y});
            else if (it.first->steps > steps + 1) {
                s.erase(it.first);
                s.insert({c, steps + 1});
                P.push({c, steps + 1, x, y});
            }
            std::swap(c[x + 1][y], c[x][y]);
        }
        if (y < 3 && prey != y + 1) {
            std::swap(c[x][y + 1], c[x][y]);
            it = s.insert({c, steps + 1});
            if (it.second) P.push({c, steps + 1, x, y});
            else if (it.first->steps > steps + 1) {
                s.erase(it.first);
                s.insert({c, steps + 1});
                P.push({c, steps + 1, x, y});
            }
            std::swap(c[x][y + 1], c[x][y]);
        }
    }
}
