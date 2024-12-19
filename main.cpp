#include <bits/stdc++.h>

// TIP To <b>Run</b> code, press <shortcut actionId="Run"/> or
// click the <icon src="AllIcons.Actions.Execute"/> icon in the gutter.
using namespace std;
mt19937_64 rnd;
struct engine {
    long long n, m, s;
    pair<int,int> current_pos;
    pair<int,int> apple_pos;
    engine() {
        //this->s = (rnd()%1000000)+1;
        this->n = (rnd()%1000000)+1;
        this->m = (rnd()%1)+1;

        this->current_pos = {rnd()%n, rnd()%m};
        this->apple_pos = {rnd()%n, rnd()%m};
    }
    engine(int n, int m, pair<int,int> current_pos, pair<int,int> apple_pos) {
        this->current_pos = current_pos;
        this->apple_pos = apple_pos;
        this->n = n;
        this->m = m;
    }
    void up() {
        this->current_pos.first -= 1;
        if (this->current_pos.first == -1) this->current_pos.first += n;
    }
    void down() {
        this->current_pos.first += 1;
        if (this->current_pos.first == n) this->current_pos.first -= n;
    }
    void left() {
        this->current_pos.second -= 1;
        if (this->current_pos.second == -1) this->current_pos.second += m;
    }
    void right() {
        this->current_pos.second += 1;
        if (this->current_pos.second == m) this->current_pos.second -= m;
    }
    bool check() {
        return current_pos == apple_pos;
    }
    void print_field() const {
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < m; j++) {
                pair<int,int> cur = {i,j};
                if (this->current_pos==cur && this->apple_pos==cur) cout<<'x'<<' ';
                else if (this->current_pos==cur) cout<<'*'<<' ';
                else if (this->apple_pos==cur) cout<<'0'<<' ';
                else cout<<'-'<<' ';
            }
            cout<<'\n';
        }
    }
};

void dumb_solve() {
    engine eng;
    int count = 0;
    pair<int,int> st = eng.current_pos;
    pair<int,int> fs = eng.apple_pos;
    int k = 1;
    bool flag = true;
    while(flag) {
        for(int i = 0; i < k; i++) {
            if (flag) eng.up(), count++;
            flag &= !eng.check();
        }
        if (flag) eng.right(), count++;
        flag &= !eng.check();
        for(int i = 0; i < k+1; i++) {
            if (flag) eng.down(), count++;
            flag &= !eng.check();
        }
        if (flag) eng.right(), count++;
        flag &= !eng.check();
        /*for(int i = 0; i < k; i++) {
            if (flag) eng.up(), count++;
            flag &= !eng.check();
        }
        for(int i = 0; i < k; i++) {
            if (flag) eng.left(), count++;
            flag &= !eng.check();
        }
        for(int i = 0; i < k+1; i++) {
            if (flag) eng.down(), count++;
            flag &= !eng.check();
        }
        for(int i = 0; i < k+1; i++) {
            if (flag) eng.right(), count++;
            flag &= !eng.check();
        }*/
        k+=2;
    }
}

int main() {
    rnd.seed(time(0));
    int t = 1000;
    long double old_t = t;
    long double e = 0;
    int bad = 0;
    while(t--) {
        engine eng;
        int count = 0;
        int count_apples = 0;
        vector<int> primes = {2,3,5,7,9,11,13,17,19};
        bool flag = true;
        //int s = 1;

        while(flag) {
            int mv = rnd() % 4;
            if (mv == 0) {
                eng.left(),count++;
                flag &= !eng.check();
            }
            if (mv == 1) {
                eng.right(),count++;
                flag &= !eng.check();
            } else if (mv == 2) {
                eng.up(),count++;
                flag &= !eng.check();
            } else {
                eng.down(),count++;
                flag &= !eng.check();
            }

        }

        if (count>35*eng.n*eng.m) {
            cout<<"oops"<<'\n';
            cout<<count<<' '<<(eng.n*eng.m)<<'\n';
            cout<<count/(eng.n*eng.m)<<'\n';
            bad++;
            //break;
        } else cout<<count/(eng.n*eng.m)<<'\n';
        e+=((long double)count/(long double)(eng.n*eng.m));
    }
    cout<<e/old_t<<'\n';
    cout<<bad<<'\n';
}

// TIP See CLion help at <a
// href="https://www.jetbrains.com/help/clion/">jetbrains.com/help/clion/</a>.
//  Also, you can try interactive lessons for CLion by selecting
//  'Help | Learn IDE Features' from the main menu.