#include <iostream>
using namespace std;

int main()
{
    int column = 5, row = 5;
    int **arr = new int *[column];
    for (int i = 0; i < column; i++)
    {
        arr[i] = new int[row];
    }

    for (int i = 0; i < column; i++)
    {
        delete[] arr[i];
    }
    delete[] arr;

    return 0;
}