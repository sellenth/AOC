#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;

#if 1
char FILENAME[] = "./ex.txt";
#else
char FILENAME[] = "./input.txt";
#endif

#define F(i, a, b) for (int i = a; a < b; a++)

typedef long long i64;

enum TYPE
{
    REAL,
    SNAIL
};

class SN
{
public:
    SN *p;
    TYPE t;
    i64 v;
    SN *Lchild;
    SN *Rchild;

    SN()
    {
        p = NULL;
        t = SNAIL;
        Lchild = NULL;
        Rchild = NULL;
    }

    SN(SN *parent)
    {
        p = parent;
        t = SNAIL;
        Lchild = NULL;
        Rchild = NULL;
    }

    bool hasOpenNode(){
        if (t == SNAIL && Lchild == NULL){
            return true;
        }
        if (t == SNAIL && Rchild == NULL){
            return true;
        }
        return false;
    }

    void printNumber(){
        if (t == SNAIL){
            cout << '[';
        }
        if (Lchild != NULL){
            Lchild->printNumber();
        }
        if (Rchild != NULL){
            Rchild->printNumber();
        }

        else if (t == REAL && this == p->Lchild){
            cout << v << ',';
        } else if (t == REAL && this == p->Rchild) {
            cout << v << "],";
        }
    }
};

class Solution
{

public:
    SN *root;

    void parseSnailNumber(string &line)
    {
        SN* curr = root;
        int i = 0;
        while (i < line.size())
        {

            if (line[i] == '[')
            {
                if (curr->Lchild == NULL)
                {
                    curr->Lchild = new SN(curr);
                    curr = curr->Lchild;
                }
                else if (curr->Rchild == NULL)
                {
                    curr->Rchild = new SN(curr);
                    curr = curr->Rchild;
                }
                else
                {
                    cout << "Unreachable: " << i << endl;
                    exit(1);
                }
                i++;
            }
            else if (line[i] == ',' || line[i] == ']')
            {
                while (!curr->hasOpenNode())
                {
                    if (curr->p == NULL){ // number has finished parsing
                        return;
                    }
                    curr = curr->p;
                }

                if (curr->Lchild == NULL){
                    curr->Lchild = new SN(curr);
                    curr = curr->Lchild;
                } else {
                    curr->Rchild = new SN(curr);
                    curr = curr->Rchild;
                }
                i++;
            }
            else
            {
                curr->t = REAL;
                int nearestComma = line.find(',', i);
                int nearestClose = line.find(']', i);
                if (nearestComma < nearestClose)
                {
                    curr->v = stoi(line.substr(i, nearestComma));
                    i = nearestComma;
                }
                else if (nearestClose < nearestComma)
                {
                    curr->v = stoi(line.substr(i, nearestClose));
                    i = nearestClose;
                }
                curr = curr->p;
            }
        }
    }

    void parseInput()
    {
        ifstream in(FILENAME);

        string line;
        while (in.good())
        {
            getline(in, line);
            parseSnailNumber(line);
        }
    }

    void solvePart1()
    {
    }

    Solution()
    {
        root = new SN();
        parseInput();
        solvePart1();
        root->printNumber();
    }
};

int main()
{
    Solution *s = new Solution();
}