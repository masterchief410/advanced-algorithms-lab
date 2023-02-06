#include <bits/stdc++.h>
using namespace std;

bool findAugPath(int v, vector<int> &P, vector<vector<int>> &G, set<int> &X, set<int> &Y, set<int> &matched) {
    if (Y.count(v) && !matched.count(v)) {
        P.push_back(v);
        return true;
    }

    for (auto to : G[v]) {
        if (findAugPath(to, P, G, X, Y, matched)) {
            P.push_back(v);
            return true;
        }
    }

    return false;
}

set<pair<int, int>> findMaxMatching(vector<pair<int, int>> &edges, set<int> &X, set<int> &Y) {
    set<pair<int, int>> matching;
    while (true) {
        set<int> matched;
        for (auto &[x, y] : matching) {
            matched.insert(x);
            matched.insert(y);
        }

        // Creating a directed graph
        vector<vector<int>> digraph(X.size() + Y.size() + 1);
        for (auto u : X)  // adding edges from source
            if (!matched.count(u))
                digraph[0].push_back(u);

        for (auto &[from, to] : edges)  // adding directed edges
            if (matching.count({from, to}))
                digraph[to].push_back(from);
            else
                digraph[from].push_back(to);

        vector<int> augmentingPath;
        findAugPath(0, augmentingPath, digraph, X, Y, matched);
        set<pair<int, int>> augmentingPathSet;
        if (augmentingPath.empty())
            break;
        for (int i = 0; i < augmentingPath.size() - 2; i++) {
            if (i % 2 == 0)
                augmentingPathSet.insert({augmentingPath[i + 1], augmentingPath[i]});
            else
                augmentingPathSet.insert({augmentingPath[i], augmentingPath[i + 1]});
        }

        if (augmentingPathSet.size() == 0)
            break;  // we are breaking the loop if there is no augmenting path
        set<pair<int, int>> newMatching;
        set_symmetric_difference(matching.begin(), matching.end(), augmentingPathSet.begin(), augmentingPathSet.end(), inserter(newMatching, newMatching.begin()));  // we are finding the symmetric diff of M and P
        matching = newMatching;
    }
    return matching;
}

int main() {
    int numVertices, numEdges, numX, numY;

    numVertices = 9;
    numEdges = 10;
    numX = 4;
    numY = 5;

    vector<pair<int, int>> edges = {{1, 5}, {2, 5}, {1, 6}, {2, 7}, {3, 7}, {3, 8}, {3, 9}, {3, 6}, {4, 7}, {4, 9}};

    set<int> X = {1, 2, 3, 4};
    set<int> Y = {5, 6, 7, 8, 9};

    set<pair<int, int>> maxMatching = findMaxMatching(edges, X, Y);
    for (auto &[x, y] : maxMatching) {
        cout << x << " " << y << endl;
    }
    return 0;
}