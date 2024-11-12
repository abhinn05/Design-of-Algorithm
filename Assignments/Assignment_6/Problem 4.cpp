#include<bits/stdc++.h>
using namespace std;

int rodCutting(int ind,int N, vector<int>& price ,vector<vector<int>> &dp) {
    if(ind==0){
        return N*price[0];
    }
    if(dp[ind][N]!=-1){
        return dp[ind][N];
    }
    int notTake=0+rodCutting(ind-1,N,price,dp);
    int take=INT_MIN;
    int rodLength=ind+1;
    if(rodLength<=N){
        take=price[ind]+rodCutting(ind,N-rodLength,price,dp);
    }
    return dp[ind][N]=max(take,notTake);
}

int main() {
    int n;
    cout << "Enter the rod length: ";
    cin >> n;

    vector<int> price(n);
    cout << "Enter the prices for each length (1 to " << n << "):\n";
    for (int i = 0; i < n; i++) {
        cin >> price[i];
    }
    vector<vector<int>> dp(n,vector<int>(n+1,-1));
    int maxRevenue = rodCutting(n-1,n, price,dp);
    cout << "The maximum obtainable revenue is: " << maxRevenue << endl;

    return 0;
}