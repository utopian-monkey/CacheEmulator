#include <iostream>
#include <fstream>
using namespace std;

int main() {

	ifstream fileHandler("filename.txt");

	while (!fileHandler.eof())
        {
        string  x;
        fileHandler >> x;
        cout << x << endl;
        
        }
       fileHandler.close();
}
