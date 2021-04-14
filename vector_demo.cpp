#include <vector>
#include <iostream>
#include <algorithm>
#include <ranges>

#include <boost/iterator/transform_iterator.hpp>

constexpr int multiplyByTwo(int i)
{
    return i*2;
}

const std::vector<int> foo { 1,2,3,4,5,6,7 };

void Solution1()
{
    const auto fooTimesTwo = []{
        std::vector<int> tmp{};
        tmp.reserve(foo.size());
        std::transform(foo.begin(), foo.end(), std::back_inserter(tmp), &multiplyByTwo);
        return tmp;
    }();
}

void Solution2()
{
    const std::vector<int> fooTimesTwo { 
        boost::make_transform_iterator(foo.begin(), &multiplyByTwo),
        boost::make_transform_iterator(foo.end(), &multiplyByTwo) };
}

int main()
{
    auto range = foo | std::ranges::views::transform(&multiplyByTwo);
    
    const std::vector<int> fooTimesTwo {
        std::ranges::begin(range),
        std::ranges::end(range)
    };

    for (const auto& el : fooTimesTwo)
    {
        std::cout << el << ", ";
    }
}
