//
// ANCHOR 
// 
// Rod cut problem
// 
#include <iostream>
#include <string>
#include <unordered_map>

using namespace  std;

//
// This function return maximum value that can be achieved by cutting rod using recursion method
// 
int rodCutRecursion(int profit[],int maximumRodLength){

    if(maximumRodLength == 0)
        return 0;
    
    int maxValue = INT8_MIN;

    for(int i=1;i<=maximumRodLength;i++){

        int cost = profit[i-1]+rodCutRecursion(profit,maximumRodLength-i);

        if(cost>maxValue)
            maxValue = cost;
        
    }

    return maxValue;

}


//
// This function return maximum value that can be achieved by cutting rod using DP Memoized
// 
int rodCutMemoized(int profit[],int maximumRodLength, auto &lookup){

    if(maximumRodLength == 0)
        return 0;

    string key = to_string(maximumRodLength);
    

    if(lookup.find(key) == lookup.end()){
        int maxValue = INT8_MIN;

        for(int i=1;i<=maximumRodLength;i++){

            int cost = profit[i-1]+rodCutMemoized(profit,maximumRodLength-i,lookup);

            if(cost>maxValue)
                maxValue = cost;
            
        }

        lookup[key] = maxValue;

    }
    
    return lookup[key];

}

//
// This function return maximum value that can be achieved by cutting rod using DP Tabulation
// 
int rodCutTabulation(int profit[],int maximumRodLength){

    int t[maximumRodLength+1]={0};

    int maxValue = INT8_MIN;

    for(int i=1;i<=maximumRodLength;i++){
        for(int j=1;j<=i;j++){
            t[i] = max(t[i], profit[j-1]+t[i-j]);
            
        }
        
    }        
    
    return t[maximumRodLength];

}

int main(){

    int length[]={1,2,3,4,5,6,7,8};
    int price[]= { 1, 5, 8, 9, 10, 17, 17, 20 };

    int rodLength = 4;

    unordered_map<string,int> lookup;

    cout << "\nMaximum profit that can be achieved by cutting rod is  " << rodCutRecursion(price,rodLength); 
    cout << "\nMaximum profit that can be achieved by cutting rod is  " << rodCutMemoized(price,rodLength,lookup); 
    cout << "\nMaximum profit that can be achieved by cutting rod is  " << rodCutTabulation(price,rodLength); 
    return 0;
}