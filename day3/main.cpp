#include <iostream>
#include <bitset>
#include <string>
#include <vector>
#include <string.h>
#include <fstream>

using namespace std;

int part1()
{
    //char filename[] = "./ex.txt";
    char filename[] = "./input.txt";
    FILE *fp;
    char rawLine[100];
    int numLines = 0;
    vector<int> record;

    fp = fopen(filename, "r");
    if (fp == NULL)
        perror("Error opening file");
    else
    {
        while (!feof(fp))
        {
            if (fgets(rawLine, 100, fp) == NULL)
                break;

            for (int i = 0; i < 100; i++)
            {
                char c = rawLine[i];
                if (c == '\n' || c == '\0')
                {
                    numLines++;
                    break;
                }
                else
                {
                    if (numLines == 0)
                    {
                        record.push_back(c - 48);
                    }
                    else
                    {
                        record[i] += c - 48;
                    }
                }
            }
        }
        fclose(fp);
    }

    uint64_t gamma = 0;
    uint64_t epsilon = 0;

    for (int i = 0; i < record.size(); i++)
    {
        if (record[record.size() - 1 - i] > numLines / 2.0)
        {
            gamma |= 1UL << i;
        }
        else
        {
            epsilon |= 1UL << i;
        }
    }

    cout << "Gamma: " << bitset<8>(gamma) << endl;
    cout << "Epsilon: " << bitset<8>(epsilon) << endl;

    cout << "Answer: " << gamma * epsilon << endl;
    return 1;
}

enum MOST_COMMON
{
    ZERO,
    ONE,
    BOTH
};

MOST_COMMON mostCommon(const vector<string> &vec, int idx)
{
    int sum = 0;
    for (auto &s : vec)
    {
        s[idx] == '1' ? sum++ : sum--;
    }
    if (sum == 0)
    {
        return BOTH;
    }
    if (sum > 0)
    {
        return ONE;
    }
    return ZERO;
}

enum FILTER_TYPE
{
    OXY,
    CO2
};

void filterVectors(vector<string> &vec, FILTER_TYPE ft)
{
    int inputLength = vec[0].length();
    for (int i = 1; i < inputLength; i++)
    {
        MOST_COMMON common = mostCommon(vec, i);
        auto it = vec.begin();

        while (it != vec.end())
        {
            if (vec.size() <= 1)
            {
                return;
            }

            if (common == BOTH)
            {
                if ((*it)[i] == '0' && ft == OXY)
                {
                    it = vec.erase(it);
                }
                else if ((*it)[i] == '1' && ft == CO2)
                {
                    it = vec.erase(it);
                }
                else
                {
                    it++;
                }
            }
            else if (common == ONE)
            {
                if ((*it)[i] == '0' && ft == OXY)
                {
                    it = vec.erase(it);
                }
                else if ((*it)[i] == '1' && ft == CO2)
                {
                    it = vec.erase(it);
                }
                else
                {
                    it++;
                }
            }
            else if (common == ZERO)
            {
                if ((*it)[i] == '1' && ft == OXY)
                {
                    it = vec.erase(it);
                }
                else if ((*it)[i] == '0' && ft == CO2)
                {
                    it = vec.erase(it);
                }
                else
                {
                    it++;
                }
            }
        }
    }
    return;
}

int part2()
{
    //char filename[] = "./ex.txt";
    char filename[] = "./input.txt";
    ifstream in(filename);
    vector<string> all;
    vector<string> oxygen;
    vector<string> co2;

    string line;
    while (getline(in, line))
    {
        if (line.size() > 0)
        {
            all.push_back(line);
        }
    }

    MOST_COMMON common = mostCommon(all, 0);

    for (auto &s : all)
    {
        if (common == BOTH)
        {
            if (s[0] == '1')
            {
                oxygen.push_back(s);
            }
            else
            {
                co2.push_back(s);
            }
        }
        else if (common == ONE)
        {
            if (s[0] == '1')
            {
                oxygen.push_back(s);
            }
            else
            {
                co2.push_back(s);
            }
        }
        else if (common == ZERO)
        {
            if (s[0] == '0')
            {
                oxygen.push_back(s);
            }
            else
            {
                co2.push_back(s);
            }
        }
    }

    filterVectors(oxygen, OXY);
    filterVectors(co2, CO2);

    cout << "Oxygen: " << oxygen[0] << "\tCO2: " << co2[0] << endl;
    uint64_t o2num = 0;
    uint64_t co2num = 0;

    for (int i = 0; i < oxygen[0].length(); i++)
    {
        if (oxygen[0][oxygen[0].length() - i - 1] == '1')
        {
            o2num |= 1UL << i;
        }
        if (co2[0][oxygen[0].length() - i - 1] == '1')
        {
            co2num |= 1UL << i;
        }
    }

    cout << o2num * co2num << endl;

    return 0;
}

int main()
{
    //part1();
    part2();
}