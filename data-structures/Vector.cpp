#include <iostream>
using namespace std;

class Vector
{
private:
    int *arr = nullptr;
    int size = 0;
    int capacity = 0;

public:
    Vector(int size)
    {
        if (size < 0)
            size = 1;
        this->size = size;
        capacity = size + 10;
        arr = new int[capacity]{};
    }
    ~Vector()
    {
        delete[] arr;
        arr = nullptr;
    }

    int get(int index)
    {
        if (0 <= index && index < size)
        {
            return arr[index];
        }
        return -1;
    }
    void set(int index, int val)
    {
        if (0 <= index && index < size)
        {
            arr[index] = val;
        }
    }

    void print()
    {
        for (int i = 0; i < size; i++)
        {
            cout << arr[i] << ' ';
        }
        cout << '\n';
    }
    int find(int val)
    {
        for (int i = 0; i < size; i++)
        {
            if (arr[i] == val)
            {
                return val;
            }
        }
        return -1;
    }

    int get_front()
    {
        return arr[0];
    }
    int get_back()
    {
        return arr[size - 1];
    }
    void expand_capacity()
    {
        capacity *= 2;
        int *arr2 = new int[capacity]{};
        for (int i = 0; i < size; i++)
            arr2[i] = arr[i];
        swap(arr2, arr);
        delete[] arr2;
    }
    void push_back(int val)
    {
        if (size == capacity)
            expand_capacity();
        arr[size++] = val;
    }
};

int main()
{
    return 0;
}