#include <bits/stdc++.h>
using namespace std;

int lcs(string& s, string& t, int i, int j, vector<vector<int>>& dp) {
    if (i < 0 || j <0) {
        return 0;
    }
    if(dp[i][j]!=-1){
        return dp[i][j];
    }
    if (s[i] == t[j]) {
        return dp[i][j]=1 + lcs(s, t, i - 1, j - 1,dp);
    }

    return dp[i][j]=max(lcs(s, t, i - 1, j, dp), lcs(s, t, i, j - 1, dp));
}

int main() {
    string s, t;
    cout << "Enter the first string: ";
    cin >> s;
    cout << "Enter the second string: ";
    cin >> t;
    vector<vector<int>> dp(s.size(),vector<int>(t.size(),-1));
    int len = lcs(s, t, s.size() - 1, t.size() - 1,dp);
    cout << "The length of the longest common subsequence is: " << len << endl;

    return 0;
}
