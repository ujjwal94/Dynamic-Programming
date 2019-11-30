//ANCHOR 
// 
// Levenshtein distance problem(Edit distance)
// 
// 
#include <iostream>
#include <string>
#include <unordered_map>

using namespace std;

//
// This function calculate edit distance using recursion
// 
int editDistanceRecursion(string x, string y,int n,int m){

    // case 1
    if(m == 0 || n ==0)
        return m+n;
    
    int editCost = 1;

    // case 2
    if(x[n-1] == y[m-1])
        editCost=0;
    
    return min(
        min(
            editDistanceRecursion(x,y,n,m-1)+1,         //insert case 3a
            editDistanceRecursion(x,y,n-1,m)+1          //delete case 3b
        ),                                      
        editDistanceRecursion(x,y,n-1,m-1)+editCost     //Replace case 2 & case 3c
    );
}


//
// This function calculate edit distance using DP Memoized
// 
int editDistanceMemoized(string x, string y,int n,int m,auto &lookup){

    if(m == 0 || n ==0)
        return m+n;
    
    //Formation of key for look up table
    string key = to_string(n)+'|'+to_string(m);

    //If unable to find in look up table
    if(lookup.find(key) == lookup.end()){
        int editCost = 1;
    
        if(x[n-1] == y[m-1])
            editCost=0;
        
        return min(
            min(
                editDistanceRecursion(x,y,n,m-1)+1,  //insert
                editDistanceRecursion(x,y,n-1,m)+1   //delete
            ),                                      
            editDistanceRecursion(x,y,n-1,m-1)+editCost     //Replace
        );
    }

    return lookup[key];
    
}

//
// This function calculate edit distance using DP Tabulation
// 
int editDistanceTabulation(string x, string y,int n,int m){

    // DP table
    int t[n+1][m+1]={0};
    
    // Case 1
    for(int i=1;i<=n;i++)
        t[i][0]=i;

    for(int j=1;j<=m;j++)
        t[0][j]=j;
    
    int editcost = 1;

    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            
            if(x[i-1] == y[j-1])
               editcost = 0;
            else 
               editcost = 1;
            
            t[i][j] =
                        min(
                            min(
                                t[i][j-1]+1,     //Insert
                                t[i-1][j]+1      //Delete
                            ),
                            t[i-1][j-1]+editcost //Replace
                        );
        }
    }

    //Return last subproblem solution
    return t[n][m];
}


int main(){

    string X = "kitten", Y = "sitting";

    unordered_map <string,int> lookup;

    cout << "\nRecursion Method     : The levenshtein distance (Edit distance) is " << editDistanceRecursion(X,Y,X.length(),Y.length()) ;
    cout << "\nDP Memoized Method   : The levenshtein distance (Edit distance) is " << editDistanceMemoized(X,Y,X.length(),Y.length(),lookup) ;
    cout << "\nDP Tabulation Method : The levenshtein distance (Edit distance) is " << editDistanceTabulation(X,Y,X.length(),Y.length()) ;

}