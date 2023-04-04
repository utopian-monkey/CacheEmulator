#include <string>
#include<fstream>
#include <iostream>
using namespace std;

const int SIZE = 22;
int grades[SIZE];

void readData() {


    string inFileName = "grades.txt";
    ifstream inFile;
    inFile.open(inFileName.c_str());

    if (inFile.is_open())
    {
        for (int i = 0; i < SIZE; i++)
        {
            inFile >> grades[i];
            cout << i<<" "<<grades[i] << "\n ";
        }

        inFile.close(); // Close input file
    }
    else { //Error message
        cerr << "Can't find input file " << inFileName << endl;
    }
}

int main()
{
    readData();
    return 0;
}
