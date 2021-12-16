#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <set>
#include <unordered_map>
#include <algorithm>

using namespace std;

#if 0
char FILENAME[] = "./ex.txt";
#else
char FILENAME[] = "./input.txt";
#endif

#define F(i, a, b) for(int i = a; i < b; i++)
class Solution {

public:
    set<pair<int, int>> sptSet;
    vector<vector<int>> costs;
    vector<vector<int>> distances;

    void parseInput(){
        ifstream in(FILENAME);

        string line;
        int i = 0;
        while (in.good()){
            costs.push_back({});
            getline(in, line);

            stringstream s_stream(line);
            while(s_stream.good()){
                string substr;
                costs[i].push_back(s_stream.get() - 48);
            }
            costs[i].pop_back();

            i++;
        }
    }

    void part2(){
        int xSize = costs.size();
        int ySize = costs[0].size();
        F(i, 0, xSize){
            F(j, ySize, 5*ySize){
                int newCost = costs[i][j - ySize] + 1;
                if (newCost > 9){
                    costs[i].push_back(1);
                } else {
                    costs[i].push_back(newCost);
                }
            }

        }

        F(i, xSize, 5 * xSize){
            costs.push_back(vector<int>(costs[0].size(), 0));
            F(j, 0, costs[0].size()){
                int newCost = costs[i - xSize][j] + 1;
                if (newCost > 9){
                    costs[i][j] = 1;
                } else {
                    costs[i][j] = newCost;
                }
            }
        }
    }

    bool validCoord(int x, int y){
        return x >= 0 && x < costs.size() && y >= 0 && y < costs[0].size();
    }

    void printArr(vector<vector<int>> &arr){
        F(i,0, arr.size()){
            F(j,0, arr[0].size()){
                cout << arr[i][j] << ' ';
            }
            cout << endl;
        }
    }

    void solvePart1(){
        distances = {};
        F(i,0, costs.size())
            distances.push_back(vector<int>(costs.size(), INT_MAX));
        
        distances[0][0] = 0;

        int dx[] = {-1, 0, 0, 1};
        int dy[] = {0, -1, 1, 0};

        sptSet.insert(make_pair(0, 0));
        while (!sptSet.empty()){
            pair<int, int> curr = *sptSet.begin();
            int cx = curr.first;
            int cy = curr.second;
            sptSet.erase(sptSet.begin());

            F(i, 0, 4){
                int nx = cx + dx[i];
                int ny = cy + dy[i];
                if (validCoord(nx, ny)){
                    if (costs[nx][ny] + distances[cx][cy] < distances[nx][ny]){
                        if (distances[nx][ny] != INT_MAX){
                            if (sptSet.find(make_pair(nx, ny)) != sptSet.end()){
                                sptSet.erase(sptSet.find(make_pair(nx, ny)));
                            }
                        }
                        distances[nx][ny] = costs[nx][ny] + distances[cx][cy];
                        sptSet.insert(make_pair(nx, ny));
                    }
                }
            }
        }

        cout << "Distance to the bottom right is: " << distances[distances.size() - 1][distances[0].size() - 1] << endl;
    }

    Solution() {
        parseInput();
        solvePart1();

        part2();
        solvePart1();
    }
};

int main() {
    Solution* s = new Solution();
}