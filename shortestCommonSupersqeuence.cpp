// ANCHOR 
// 
// Shortest common supersquence problem
// 
// 
#include <iostream>     
#include <string>
#include <unordered_map>

using namespace std;

//
// This function calculate length of shortest common supersequence between two string using recursion
// 
int SCSRecursion(string x,string y,int n,int m){
    if(n==0 || m==0)
        return m+n;
    
    if(x[n-1] == y[m-1]){
        return SCSRecursion(x,y,n-1,m-1)+1;
    }

    return min(SCSRecursion(x,y,n-1,m)+1,SCSRecursion(x,y,n,m-1)+1);
}

//
// This function calculate length of shortest common supersequence between two string using DP Memoized
//
int SCSMemoized(string x,string y,int n,int m, auto &lookup){
    if(n==0 || m==0)
        return m+n;

    // Preparing key for the look up table
    string key = to_string(n) + '|' + to_string(m);

    //If key is not found in look up
    if(lookup.find(key) == lookup.end()){
        if(x[n-1] == y[m-1])
            lookup[key] = SCSMemoized(x,y,n-1,m-1,lookup)+1;
        else 
            lookup[key] =  min(SCSMemoized(x,y,n-1,m,lookup)+1,SCSMemoized(x,y,n,m-1,lookup)+1);
        
    }
    
    // Else return lookup entry
    return lookup[key];
}

//
// This function calculate length of shortest common supersequence between two string using DP Tabulation
//
int SCSTabulation(string x,string y,int n,int m){

    //Creating DP table
    int t[n+1][m+1]={0};

    for(int i=1;i<=n;i++)
        t[i][0]=i;

    for(int j=1;j<=m;j++)
        t[0][j]=j;

    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){

            if(x[i-1] == y[j-1] )
            {
                t[i][j] = t[i-1][j-1]+1;
            }                
            else
            {
                t[i][j] = min(t[i-1][j]+1,t[i][j-1]+1);
            }
            
        }
    }

    //returing last subproblem solution
    return t[n][m];

}

int main()
{
    string X = "ABCBDAB", Y = "BDCABA";
    int m = X.length(), n = Y.length();
    
    unordered_map <string,int> lookup;

    cout << "\nThe minimum shortest common subsequence length using recursion is "<<SCSRecursion(X,Y,m,n);
    cout << "\nThe minimum shortest common subsequence length using DP Memoized is "<<SCSMemoized(X,Y,m,n,lookup);
    cout << "\nThe minimum shortest common subsequence length using DP Tabulation is "<<SCSTabulation(X,Y,m,n);
    return 0;
}
