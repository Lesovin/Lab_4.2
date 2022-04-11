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
    std::vector<int> res(data.size());
    size_t resl = 0;
    size_t resr = res.size() - 1;
    size_t podsize=2;
    while (true)
    {
        size_t resl = 0; // Левая граница неотсортированной последовательности в res
        size_t resr = res.size() - 1; // Правая граница неотсортированной последовательности в res
        bool left = true;
        size_t vecl = 0; // Индекс левой границы неотсортированной последовательности в data
        size_t vecr = data.size() - 1; // Индекс правой границы неотсортированной последовательности в data
        while (vecl < vecr)
        {
            size_t i = vecl;
            size_t j = vecr;
            while (vecl <= vecr && data[vecl] <= data[vecl + 1])
            {
                stat.comparison_count++;
                vecl++;
                podsize++;
                if (vecl == res.size() - 1) return stat;
            }
            while (vecl <= vecr && data[vecr] <= data[vecr - 1])
            {
                stat.comparison_count++;
                vecr--;
                podsize++;
            }
            if (left) 
            {
                for (size_t p = 0; p < podsize; ++p) 
                {
                    if (i <= vecl)
                    {
                        if (j < vecr) // Если вся правая подпоследовательность уже перебрана, то поочередно записываем левую последовательность
                        { 
                            res[resl] = data[i];
                            stat.copy_count++;
                            resl++;
                            i++; 
                            continue;
                        }
                        else if (data[i] < data[j]) //Если правая подпоследовательность не целиком рассмотрена, то нужно сравнивать
                        { 
                            stat.comparison_count++;
                            res[resl] = data[i];
                            stat.copy_count++;
                            resl++;
                            i++; 
                            continue;
                        }
                        else if (i == j)
                        {
                            res[resl] = data[i];
                            stat.copy_count++;
                            break;
                        }
                    }
                    if (j >= vecr) 
                    {
                        if (i > vecl) // Вся левая подпоследовательность рассмотрена
                        { 
                            res[resl] = data[j];
                            stat.copy_count++;
                            resl++;
                            j--; 
                            continue;
                        }
                        else if (data[j] < data[i]) //Если левая подпоследовательность не целиком рассмотрена, то нужно сравнивать
                        { 
                            stat.comparison_count++;
                            res[resl] = data[j];
                            stat.copy_count++;
                            resl++;
                            j--; 
                            continue;
                        }
                        else if (i == j)
                        {
                            res[resl] = data[i];
                            stat.copy_count++;
                            break;
                        }
                    }
                }
                left = !left;
            }
            else {
                for (size_t p = 0; p < podsize; ++p) 
                {
                    if (i <= vecl) 
                    {
                        if (j < vecr) // Если вся правая подпоследовательность уже перебрана, то поочередно записываем левую последовательность
                        { 
                            res[resr] = data[i];
                            stat.copy_count++;
                            resr--;
                            i++; 
                            continue;
                        }
                        else if (data[i] < data[j]) //Если правая подпоследовательность не целиком рассмотрена, то нужно сравнивать
                        { 
                            stat.comparison_count++;
                            res[resr] = data[i];
                            stat.copy_count++;
                            resr--;
                            i++; 
                            continue;
                        }
                        else if (i == j)
                        {
                            res[resl] = data[i];
                            stat.copy_count++;
                            break;
                        }
                    }
                    if (j >= vecr && data[j] < data[i]) 
                    {
                        stat.comparison_count++;
                        if (i > vecl) // Вся левая подпоследовательность рассмотрена
                        { 
                            res[resr] = data[j];
                            stat.copy_count++;
                            resr--;
                            j--; 
                            continue;
                        }
                        else if (data[j] < data[i]) //Если левая подпоследовательность не целиком рассмотрена, то нужно сравнивать
                        { 
                            stat.comparison_count++;
                            res[resr] = data[j];
                            stat.copy_count++;
                            resr--;
                            j--; 
                            continue;
                        }
                        else if (i == j)
                        {
                            res[resl] = data[i];
                            stat.copy_count++;
                            break;
                        }
                    }
                }
                left = !left;
            }
            vecl++;
            vecr--;
        }
        data = res;
        for (size_t k = 0; k < res.size(); k++) res[k] = 0;
    }
    return stat;
}

int main()
{
    stats stat;
    std::vector<int> v1 = { 3,1,7,9,6,4,2,5,10,8 };
    std::vector<int> v2 = { 3,1,7,9,6,4,2,2,10,8 };
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
    stat=Two_Way_Merge_Sort(v2);
    for (auto i = v2.begin(); i != v2.end(); ++i)
    {
        std::cout << *i << " ";
    }
    std::cout << "\n";
    std::cout << "Number of comparisons:" << stat.comparison_count << std::endl;
    std::cout << "Number of copies:" << stat.copy_count << std::endl;
    return 0;
}

