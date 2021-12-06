#include <iostream>
#include <string>
#include <fstream>

using namespace std;

int main()
{
    //char filename[] = "./ex.txt";
    char filename[] = "./input.txt";
    FILE *startPointer;
    FILE *endPointer;
    char firstNum[100];
    char secondNum[100];

    int iters = 0;
    int count = 0;

    startPointer = fopen(filename, "r");
    endPointer = fopen(filename, "r");
    if (startPointer == NULL)
        perror("Error opening file");
    else
    {
        while (!feof(endPointer))
        {
            if (fgets(secondNum, 100, endPointer) == NULL)
                break;
            iters++;
            if (iters >= 4){
                cout << secondNum << endl;
                if (fgets(firstNum, 100, startPointer) == NULL)
                break;

                int one = stoi(firstNum);
                int four = stoi(secondNum);
                if (four > one)
                {
                    count++;
                }
            }
        }
        fclose(endPointer);
    }

    cout << count << endl;
    return 0;
}