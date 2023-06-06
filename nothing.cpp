#include<bits/stdc++.h>
using namespace std;

void add(vector<int> t){
    t.push_back(1);
}

int main(void){
    vector<int> a = {};
    std::cout << a.size() << endl;
    add(a);
    std::cout << a.size() << endl;
}