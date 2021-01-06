#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

/*
QUESTION:
Given an array of integers nums and an integer target, return indices of the two numbers such that they add up to target.

You may assume that each input would have exactly one solution, and you may not use the same element twice.

You can return the answer in any order.
*/

//Returns: pointer to an array with two indices. Params: vect is the vector being checked, target: the sum they should add up to
int* twoSum(const vector<int>& vect, int target){
    //map of values in vect to their index in vect.(contains the last index)
    unordered_map<int, int> valuesContained;
    for(unsigned int i = 0; i < vect.size(); i++){
        if (pos )
        valuesContained[vect.at(i)] = i;
    }
    for (unsigned int i = 0; i < vect.size(); i++){
        int neededValue = target - vect.at(i);
        // if the value is found (before valuesContained.end()) and is not itself
        unordered_map<int, int>::iterator pos = valuesContained.find(neededValue);
        if (pos != valuesContained.end() && i != valuesContained.at(neededValue)){
            int *ans = new int[2];
            ans[0] = i;
            ans[1] = valuesContained.at(neededValue);
            return ans;
        }
    }
    return new int[2];
}
/*
SOLUTION:
A posible solution would be to go through each element of the array, and for that element, checking all of the other elements to see if its pair
is in the array. This would be O(n^2) time.

Another possible solution is to go through each element then checking if its pair is in the array in linear time. It is possible to do that by
using an unordered structure that has a search in liner time, which a map satisfies. 

runtime ends up being the worst runtime of all subsections, so if we can create many subsections in O(n) time, the runtime will be better than O(n^2)
and the second possibility does that. Adding the elements to the map is O(n) time and running through the array to find if the pair is contained in the
map is also O(n) time, so the algorithm runs O(n) time.
*/

int main(){
    vector<int> nums = {1, 5, 6, 7};
    int target = 7;
    int *a = twoSum(nums, target);
    cout << a[0] << " " << a[1] << endl;
}