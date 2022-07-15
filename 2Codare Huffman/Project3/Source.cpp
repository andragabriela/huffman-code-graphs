#include <fstream>
#include <sstream>
#include <queue>
#include <algorithm>
#include <tuple>
#include <map>
//huffman
using namespace std;

const int NMAX = 1e4 + 10;
int st[NMAX], dr[NMAX];
int fr[NMAX], root;
char let[NMAX], minCode[NMAX];

const int LMAX = 500;
int frec[LMAX];

map < char, string >  mp;

void dfs(int node, string cod) {
    //g << node << " " << cod << "\n";
    if (st[node] == -1 && dr[node] == -1) {
        mp[let[node]] = cod;
        return;
    }
    if (st[node] != -1) {
        dfs(st[node], cod + "0");
    }
    if (dr[node] != -1) {
        dfs(dr[node], cod + "1");
    }
}

int main(int argc, char** argv) {

    ifstream f(argv[1]);
    ofstream g(argv[2]);

    //ifstream f("date.in");
    //ofstream g("date.out");

    string s;
    getline(f, s);
    for (auto it : s)
        frec[it]++;

    for (int i = 0; i < NMAX; i++)
        st[i] = dr[i] = -1;

    vector < pair < char, int > > aux;
    for (auto it : s) {
        if (!frec[it]) continue;
        aux.push_back({ it, frec[it] });
        frec[it] = 0;
    }

    sort(aux.begin(), aux.end());
    int first_available = aux.size() + 1;
    int root = 0 ;
    int node = 0;
    priority_queue < tuple < int, char, int > > q;
    g << aux.size() << "\n";
    for (auto it : aux) {
        node++;
        g << it.first << " " << it.second << "\n";
        q.push({ -it.second, -it.first, node });
        let[node] = it.first;
        minCode[node] = it.first;
    }

    while (q.size() > 1) {
        int f1 = -get<0>(q.top());
        char c1 = -get<1>(q.top());
        int node1 = get<2>(q.top());
        q.pop();

        int f2 = -get<0>(q.top());
        char c2 = -get<1>(q.top());
        int node2 = get<2>(q.top());
        q.pop();

        st[first_available] = node1;
        dr[first_available] = node2;
        let[first_available] = 0;
        fr[first_available] = f1 + f2;
        minCode[first_available] = min(c1, c2);

        q.push({ -fr[first_available], -minCode[first_available], first_available });
        root = first_available;
        first_available++;

    }

    dfs(root, "");

    for (auto it : s)
        g << mp[it];


    return 0;
}
