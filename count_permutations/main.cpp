#include <iostream>
#include <algorithm>
#include <vector>

template<class Iterator>
size_t count_permutations(Iterator p, Iterator q)
{
    if (p == q) return 1;
    std::vector<Iterator> vec;
    for(auto i = p; i != q; i++){
        vec.push_back(i);
    }
    auto less = [](Iterator i1, Iterator i2){return (*i1) < (*i2);};
    std::sort(vec.begin(), vec.end(), less);
    size_t s = 0;
    auto adj = std::adjacent_find(vec.begin(), vec.end(), [](Iterator i1, Iterator i2){return (*i1) == (*i2);});
    if(adj == vec.end())
        s++;
    while(std::next_permutation(vec.begin(), vec.end(), less)){
        auto adj = std::adjacent_find(vec.begin(), vec.end(), [](Iterator i1, Iterator i2){return (*i1) == (*i2);});
        if(adj == vec.end())
            s++;
    }
    return s;
}

using namespace std;

int main()
{
    vector<int> vec = {3, 1, 1};
    cout << count_permutations(vec.begin(), vec.end()) << " " << endl;
    return 0;
}
