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

stats Two_Way_Merge_Sort(std::vector<int>& data)
{
    stats stat;
    std::vector<int> temp(2*data.size());
    for (size_t i = 0; i < data.size(); i++)
    {
        temp[i] = data[i];
        temp[i + data.size()] = data[i];
    }
    int s=1;
    int i;
    int j;
    int k;
    int g;
    bool flag = false;
    while (flag==false)
    {
        s = 1 - s;
        int d = 1;
        flag = true;
        if (s == 0)
        {
            i = 1;
            j = data.size();
            k = j + 1;
            g = 2 * data.size();
        }
        else {
            i = data.size() + 1;
            j = data.size() * 2;
            k = 1;
            g = data.size();
        }
        while (i != j)
        {
            if (temp[i] > temp[j])
            {
                temp[k] = temp[j];
                k = k + d;
                j = j - 1;
                if (temp[j + 1] > temp[j])
                {
                    while (temp[i - 1] < temp[i])
                    {
                        temp[k] = temp[i];
                        k = k + d;
                        i = i + 1;
                    }
                    flag = false;
                    d = -d;
                    int p = k;
                    k = g;
                    g = p;
                }
            }
            else
            {
                temp[k] = temp[i];
                k = k + d;
                j = i + 1;
                if (temp[i - 1] > temp[i])
                {
                    while (temp[j + 1] < temp[j])
                    {
                        temp[k] = temp[j];
                        k = k + d;
                        j = j - 1;
                    }
                    flag = false;
                    d = -d;
                    int p = k;
                    k = g;
                    g = p;
                }
            }
        }
        temp[k] = temp[i];
    }
    if (s == 0)
    {
        for (size_t i = 0; i < data.size(); i++) data[i] = temp[i+data.size()];
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
    stat = Two_Way_Merge_Sort(v2);
    for (auto i = v2.begin(); i != v2.end(); ++i)
    {
        std::cout << *i << " ";
    }
    std::cout << "\n";
    std::cout << "Number of comparisons:" << stat.comparison_count << std::endl;
    std::cout << "Number of copies:" << stat.copy_count << std::endl;
    return 0;
}

