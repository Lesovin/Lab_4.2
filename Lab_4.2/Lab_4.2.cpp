#include <vector>
#include <iostream>

struct stats {
    size_t comparison_count = 0;
    size_t copy_count = 0;
};

stats Bubble_Sort(std::vector<int> &data)
{
    stats stat;
    for (size_t i = 0; i < data.size() - 1; i++)
    {
        for (size_t j = 0; j < data.size() - i - 1; j++)
        {
            stat.comparison_count++;
            if (data[j + 1] < data[j])
            {
                int temp = data[j+1];
                data[j + 1] = data[j];
                data[j] = temp;
                stat.copy_count++;
            }
        }
    }
    return stat;
}

stats Shell_Sort(std::vector<int>& data)
{
    stats stat;
    for (size_t d = data.size() / 2; d > 0; d /= 2) 
    {
        for (size_t i = d; i < data.size(); ++i) 
        {
            stat.comparison_count++;
            for (int j = i - d; j >= 0 && data[j] > data[j + d]; j -= d)
            {
                int temp = data[j];
                data[j] = data[j + d];
                data[j + d] = temp;
                stat.copy_count++;
            }
        }
    }
    return stat;
}

int main()
{
    stats stat;
    std::vector<int> v1 = { 3,1,7,9,6,4,2,5,10,8 };
    std::vector<int> v2 = { 3,1,7,9,6,4,2,5,10,8 };
    for (auto i = v1.begin(); i!=v1.end();++i)
    {
        std::cout << *i<<" ";
    }
    std::cout << "\n";
    stat=Bubble_Sort(v1);
    for (auto i = v1.begin(); i != v1.end(); ++i)
    {
        std::cout << *i<<" ";
    }
    std::cout << "\n";
    std::cout << "Number of comparisons:" << stat.comparison_count << std::endl;
    std::cout << "Number of copies:" << stat.copy_count << std::endl;
    for (auto i = v2.begin(); i != v2.end(); ++i)
    {
        std::cout << *i << " ";
    }
    std::cout << "\n";
    stat = Shell_Sort(v2);
    for (auto i = v2.begin(); i != v2.end(); ++i)
    {
        std::cout << *i << " ";
    }
    std::cout << "\n";
    std::cout << "Number of comparisons:" << stat.comparison_count << std::endl;
    std::cout << "Number of copies:" << stat.copy_count << std::endl;
    return 0;
}

