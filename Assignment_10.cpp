// Implement the Heap sort algorithm demonstrating heap data structure
// with modularity of programming language
#include <bits/stdc++.h>
using namespace std;
class Heap
{
public:
    void heapify(vector<int> &arr, int n, int i)
    {
        int l = 2 * i + 1;
        int r = 2 * i + 2;
        int largest = i;
        if (l < n && arr[largest] < arr[l])
        {
            largest = l;
        }
        if (r < n && arr[largest] < arr[r])
        {
            largest = r;
        }
        if (largest != i)
        {
            swap(arr[largest], arr[i]);
            heapify(arr, n, largest);
        }
    }
    void heapsort(vector<int> &arr)
    {
        int n = arr.size();
        for (int i = n / 2 - 1; i >= 0; i--)
        {
            heapify(arr, n, i);
        }

        for (int i = n - 1; i > 0; i--)
        {
            swap(arr[0], arr[i]);
            heapify(arr, i, 0);
        }
    }
    void printarr(vector<int> arr)
    {

        for (auto x : arr)
            cout << x << " ";
    }
};
int main()
{
    vector<int> arr = {
        1, 5, 2, 3, 678, 33, -1};
    Heap h;
    h.printarr(arr);
    cout << endl;
    h.heapsort(arr);
    h.printarr(arr);
}