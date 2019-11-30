//
// ANCHOR 
// 
// Subset sum problem
// 

#include <iostream>

using namespace std;

bool subsetSumRecursion(int input[],int size,int sum){

    if(sum == 0)
        return true;
    
    if(size<0 || sum <0)
        return false;

    bool include = subsetSumRecursion(input,size-1,sum-input[size]);

    bool exclude = subsetSumRecursion(input,size-1,sum);

    return include|exclude;

}

int main(){
    
    // Input: set of items and a sum
    int arr[] = { 7, 3, 2, 5, 8 };
    int sum = 14;
    // number of items
    int n = sizeof(arr) / sizeof(arr[0]);

    if (subsetSumRecursion(arr, n - 1, sum))
        cout << "Yes";
    else
        cout << "No";

    return 0;

}