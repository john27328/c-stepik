#include <iostream>
#include <algorithm>
#include <vector>

template<class Iterator>
size_t count_permutations(Iterator p, Iterator q)
{
    std::vector<Iterator> vec;
    for(auto i = p; i != q; i++){
        vec.push_back(i);
    }
    auto less = [](Iterator i1, Iterator i2){return (*i1) < (*i2);};
    std::sort(vec.begin(), vec.end(), less);
    size_t s = 1;
    while(std::next_permutation(vec.begin(), vec.end(), less)){
        s++;
        for(auto i: vec){
            std::cout << *i << " ";
        }
        std::cout << std::endl;
    }
    return s;
}

using namespace std;

int main()
{
    vector<int> vec = {4, 3, 2};
    cout << count_permutations(vec.begin(), vec.end()) << " " << endl;
    return 0;
}
