// CODE FOR MENU DRIVEN SORTING METHODS
// INCLUDES SELECTION, BUBBLE, INSERTION AND QUICK SORTING METHODS

#include <bits/stdc++.h>
using namespace std;

void sel_sort(vector<int> &v, int n){
    for(int i = 0; i < n-1; i++){
        int min_indx = i;
        for(int j = i; j < n; j++)
            if(v[min_indx] > v[j])
                min_indx = j;
        swap(v[i], v[min_indx]);
    }
}

void bub_sort(vector<int> &v, int n){
    for(int i = 0; i < n-1; i++){
        bool flag = false;
        for(int j = 0; j < n-1-i; j++)
            if(v[j] > v[j+1]){
                swap(v[j], v[j+1]);
                flag = true;
            }
        if(!flag)
            break;
    }
}

void ins_sort(vector<int> &v, int n){
    for(int i = 1; i < n; i++){
        int key = v[i];
        int j = i - 1;
        while(j > -1 && v[j] > key){
            v[j+1] = v[j];
            j--;
        }
        v[j+1] = key;
    }
}


void swap_Elements(int* a, int* b)
{
    int t = *a;
    *a = *b;
    *b = t;
}

int pviot_Fun(vector<int> &v, int min, int max)
{
    int pivot = v[max];
    int i = (min - 1);

    for (int j = min; j <= max - 1; j++)
    {

        if (v[j] < pivot)
        {
            i++;
            swap_Elements(&v[i], &v[j]);
        }
    }
    swap_Elements(&v[i + 1], &v[max]);
    return (i + 1);
}

void quick_Sort(vector<int> &v, int min, int max)
{
    if (min < max)
    {
        int pi = pviot_Fun(v, min, max);
        quick_Sort(v, min, pi - 1);
        quick_Sort(v, pi + 1, max);
    }
}
void display_Array(vector<int> &v ,int n)
{
     cout << "After Sorting: ";
        for(int i=0;i<n;i++){
            cout << v[i] << " ";
        }
}

int main(){
    int n, ch, x;
    vector<int> v(n);
    do{
        cout << "\n\tMENU\n1. Selection Sort\n2. Bubble Sort\n3. Insertion Sort\n4. Quick Sort\n5. Exit\nEnter your choice: ";
        cin >> ch;
        if(ch != 5){
            cout << "Enter number of elements: ";
            cin >> n;
            cout << "Enter Elements: ";
            for(int i=0;i<n;i++){
                cin >> x;
                v.push_back(x);
            }
        }
        if(ch == 1)
            {
                sel_sort(v, n);
                display_Array(v,n);
            }
        else if(ch == 2)
            {
                bub_sort(v, n);
                display_Array(v,n);
            }
        else if(ch == 3)
        {
            ins_sort(v, n);
            display_Array(v,n);
        }
        else if(ch == 4)
            {
                quick_Sort(v, 0, n - 1);
                display_Array(v,n);
            }
        else if(ch == 5)
            break;
        else
            {
                cout<<"Invalid Choice\n";
            }
        cout << "\n";
    } while(ch != 5);
    return 0;
}
