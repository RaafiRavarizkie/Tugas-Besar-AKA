#include <iostream>
#include <vector>
#include <climits>
#include <chrono>
using namespace std;
using namespace chrono;
int tspIteratif(const vector<vector<int>>& graph, int n) {
    vector<vector<int>> dp(1 << n, vector<int>(n, INT_MAX));
    dp[1][0] = 0;
    for (int mask = 1; mask < (1 << n); ++mask) {
        for (int curr = 0; curr < n; ++curr) {
            if (!(mask & (1 << curr))) continue;
            for (int next = 0; next < n; ++next) {
                if (mask & (1 << next)) continue;
                int newMask = mask | (1 << next);
                if (dp[mask][curr] != INT_MAX && graph[curr][next] != INT_MAX) {
                    dp[newMask][next] = min(dp[newMask][next], dp[mask][curr] + graph[curr][next]);
                }
            }
        }
    }
    int minCost = INT_MAX;
    int finalMask = (1 << n) - 1;
    for (int i = 1; i < n; ++i) {
        if (dp[finalMask][i] != INT_MAX && graph[i][0] != INT_MAX) {
            minCost = min(minCost, dp[finalMask][i] + graph[i][0]);
        }
    }

    return minCost;
}
int main() {
    int n;
    cout << "Masukkan jumlah kota: ";
    cin >> n;
    vector<vector<int>> graph(n, vector<int>(n));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (i != j) {
                graph[i][j] = (i + j);
            } else {
                graph[i][j] = 0;
            }
        }
    }
    auto start = steady_clock::now();
    tspIteratif(graph, n);
    auto stop = steady_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout << "Jarak terpendek: " << tspIteratif(graph, n) << endl;
    cout << "Waktu eksekusi: " << duration.count() << " mikrodetik" << endl;
    return 0;
}
