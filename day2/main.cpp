#include <iostream>
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
    char rawCommand[100];
    vector<string> parsedCommand;

    int yVal = 0;
    int xVal = 0;

    fp = fopen(filename, "r");
    if (fp == NULL)
        perror("Error opening file");
    else
    {
        while (!feof(fp))
        {
            if (fgets(rawCommand, 100, fp) == NULL)
                break;
            
            parsedCommand.push_back(string(strtok(rawCommand, " ")));
            parsedCommand.push_back(string(strtok(NULL, " ")));

            string& command = parsedCommand[0];
            string& scale = parsedCommand[1];

            if (command == "forward"){
                xVal += stoi(scale);
            }
            else if (command == "up"){
                yVal -= stoi(scale);
            }
            else if (command == "down"){
                yVal += stoi(scale);
            }

            parsedCommand = {};
        }
        fclose(fp);
    }

    cout << yVal * xVal << endl;

    return 0;
}

int part2()
{
    //char filename[] = "./ex.txt";
    char filename[] = "./input.txt";
    FILE *fp;
    char rawCommand[100];
    vector<string> parsedCommand;

    int yVal = 0;
    int xVal = 0;
    int aim = 0;

    fp = fopen(filename, "r");
    if (fp == NULL)
        perror("Error opening file");
    else
    {
        while (!feof(fp))
        {
            if (fgets(rawCommand, 100, fp) == NULL)
                break;
            
            parsedCommand.push_back(string(strtok(rawCommand, " ")));
            parsedCommand.push_back(string(strtok(NULL, " ")));

            string& command = parsedCommand[0];
            string& scale = parsedCommand[1];

            if (command == "forward"){
                xVal += stoi(scale);
                yVal += aim * stoi(scale);
            }
            else if (command == "up"){
                aim -= stoi(scale);
            }
            else if (command == "down"){
                aim += stoi(scale);
            }

            parsedCommand = {};
        }
        fclose(fp);
    }

    cout << yVal * xVal << endl;

    return 0;
}

int main(){
    //part1();
    part2();
}