#include <iostream>
#include <vector>

using namespace std;



#define HT_LENGTH 256

struct HashTable {
    int keys[HT_LENGTH];
    int vals[HT_LENGTH];
    
    HashTable() { this->clear();}
    
    void clear() {
        keys[0] = 0; vals[0] = 1;
        for (int i = 1;i < HT_LENGTH;i++) keys[i] = -1;
    }
    
    int find(int key) {
        uint32_t ikey = (uint32_t)key % HT_LENGTH;
        for (int i = 0;i < HT_LENGTH;i++) {
            if (keys[ikey] == -1)  return 0;
            if (keys[ikey] == key) return vals[ikey];
            ikey = ++ikey == HT_LENGTH ? 0 : ikey;
        }
        return false;
    }
    
    void inc(int key) {
        uint32_t ikey = (uint32_t)key % HT_LENGTH;
        for (int i = 0;i < HT_LENGTH;i++) {
            if (keys[ikey] == -1) {
                keys[ikey] = key;
                vals[ikey] = 1;
                return;
            }
            if (keys[ikey] == key) {
                vals[ikey]++;
                return;
            }
            ikey = ++ikey == HT_LENGTH ? 0 : ikey;
        }
    }
};

class Solution {
private:
    HashTable ht;
public:
    int numSubmatrixSumTarget(vector<vector<int>>& matrix, int target) {
        int rprefix[100][101];
        int m = matrix.size(), n = matrix[0].size();
        int ret = 0;
        for (int i = 0;i < m;i++) {
            rprefix[i][0] = 0;
            for (int j = 1;j <= n;j ++) {
                rprefix[i][j] = rprefix[i][j - 1] + matrix[i][j - 1];
            }
        }
        
        for (int i = 1;i <= n;i++) {
            for (int j = i;j <= n;j++) {
                ht.clear();
                int cprefix = 0;
                for (int row = 0;row < m;row++) {
                    cprefix += rprefix[row][j] - rprefix[row][i - 1];
                    ret += ht.find(cprefix - target);
                    ht.inc(cprefix);
                }
            }
        }
        return ret;
    }
};





class allSubmatrixSums{
    private:
        int m = 3;
        int n = 3;
        vector<vector<vector<int>>> ones;
        int target;
        // vector<vector<vector<int>>> ones
        //     {
        //         {
        //             {},{},{}
        //         },
        //         {
        //             {},{},{}
        //         },
        //         {
        //             {}, {}, {}
        //         }
        //     };
        //vector<vector<vector<vector<int>>>> horiz{{{{}, {}, {}}, {{}, {}, {}}, {{}, {}, {}}}, {{{}, {}, {}}, {{}, {}, {}}, {{}, {}, {}}}, {{{}, {}, {}}, {{}, {}, {}}, {{}, {}, {}}}};

        vector<vector<int>> matrix;

        void calculate1LenHelper(int i, int j);
    public:
        allSubmatrixSums();
        allSubmatrixSums(int m, int n, int target);
        void calculate1Len(int i);
        void calculate2(int i, int j, int x, vector<vector<vector<vector<int>>>> horiz);
        void print();
        int sum = 0;
};
allSubmatrixSums::allSubmatrixSums(){
}
allSubmatrixSums::allSubmatrixSums(int m, int n, int target){
    this->m = m;
    this->n = n;
    this->target = target;
    for(int i = 0; i < m; i++){
        ones.push_back({});
    }
    for(int i = 0; i < m; i++){
        for(int j = 0; j < n; j++){
            ones[i].push_back({});
        }
    }
    matrix = 
    {
        {1, 2},
        {4, 5}, 
    };
}
void allSubmatrixSums::calculate1LenHelper(int i, int j){
    if(i == (m - 1)){
        if(ones[i][j].empty()){ 
            ones[i][j].push_back(matrix[i][j]);
        }
    }
    else{
        if(ones[i + 1][j].empty()){
            calculate1LenHelper(i + 1, j);
        }
        for(int x = 0; x < ones[i+1][j].size(); x++){
            ones[i][j].push_back(ones[i + 1][j].at(x) + matrix[i][j]);
        }
        ones[i][j].push_back(matrix[i][j]);
    }
    return;
}
void allSubmatrixSums::calculate2(int i, int j, int x, vector<vector<vector<vector<int>>>> horiz){
    if(j == (n - 1)){
        if(horiz[x][i][j].empty()){
            horiz[x][i][j].push_back(ones[i][j][x]);
        }
        
    }
    else{
        if(horiz[x][i][j+1].empty()){
            calculate2(i, j + 1, x, horiz);
        }
        for(int y : horiz[x][i][j+1]){
            horiz[x][i][j].push_back(y + ones[i][j][x]);
        }
        horiz[x][i][j].push_back(ones[i][j][x]);
    }
    for (int ans: horiz[x][i][j]){
        if (ans == target){
            sum++;
        }
    }
}
void allSubmatrixSums::calculate1Len(int i){
    for(int j = 0; j < n; j++){
        calculate1LenHelper(i, j);
    }

    vector<vector<vector<vector<int>>>> horiz;

    for(int x = 0; x < ones[0][0].size(); x++){
        horiz.push_back({});
    }
    for(int x = 0; x < ones[0][0].size(); x++){
        for(int i = 0; i < m; i++){
            horiz[x].push_back({});
        }
    }
    for(int x = 0; x < ones[0][0].size(); x++){
        for(int i = 0; i < m; i++){
            for(int j = 0; j < n; j++){
                horiz[x][i].push_back({});
            }
        }
    }

    

    //for each i
    for (i = 0; i < m; i++){
        //for each element in ones[i][j=0]
        for(int x = 0; x < ones[i][0].size(); x++){
        //recurrently go to ones[i][j+1] or be a base case (ones[i][j=n])
            int j = 0;
            calculate2(i, j, x, horiz);
        }
    }
}
void allSubmatrixSums::print(){
    for(int j = 0; j < n; j++){
        for(int i = 0; i < m; i++){
            for(int x: ones[i][j]){
                cout << x << " ";
            }
            cout << endl;
        }
    }
}

int main(){

    allSubmatrixSums a(2, 2, 4);
    a.calculate1Len(0);
    a.print();
    cout << "SUM: " << a.sum;

    return 0;
}