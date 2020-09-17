//   CODE FOR OPERATIONS ON STACK AND QUEUE
//   OPERATIONS ARE DONE USING ARRAY REPRESENTATION


#include<bits/stdc++.h>
#define MAX 10
using namespace std;

void push(int* tp, int n, int* arr){
    (*tp)++;
    arr[*tp] = n;
    cout << "Element Pushed!\n";
}

void pop(int *tp, int *arr){
    cout << "Popped Element is: " << arr[*tp] << endl;
    (*tp)--;
}

void disp(int tp, int arr[]){
    cout << "Stack Status: ";
    while(tp != -1){
        cout << arr[tp] << " ";
        tp--;
    }
}

void stk(){
    cout << "\n\tSTACK OPERATIONS";
    int top = -1, stak[MAX], ch, n;
    do{
        cout << "\n1. Push\n2. Pop\n3. Display\n4. Exit\nEnter your choice: ";
        cin >> ch;
        if(ch == 1){
            if(top == MAX-1){
                cout << "Stack Overflow!\n";
                continue;
            }
            cout << "Enter value to be pushed: ";
            cin >> n;
            push(&top, n, stak);
        }
        else if(ch == 2){
            if(top == -1){
                cout << "Stack Underflow!\n";
                continue;
            }
            pop(&top, stak);
        }
        else if(ch == 3){
            if(top == -1){
                cout << "Stack Underflow!\n";
                continue;
            }
            disp(top, stak);
        }
        else if(ch == 4)
            break;
        else
            cout << "Invalid Choice!\n";
    }while(ch != 4);
}

void ins(int* tl, int* arr, int n){
    *tl = ((*tl)+1) % MAX;
    arr[*tl] = n;
}

void del(int* hd, int* arr){
    cout << "Element Deleted is: " << arr[*hd] << endl;
    (*hd) = ((*hd)+1) % MAX;
}

void display(int hd, int tl, int arr[]){
    cout << "Queue Status: ";
    while(hd != tl){
        cout << arr[hd] << " ";
        hd = (hd+1) % MAX;
    }
    cout << arr[hd];
}

void que(){
    cout << "\n\tQUEUE OPERATIONS";
    int head = -1, tail = -1, _que[MAX], ch, n;
    do{
        cout << "\n1. Insert\n2. Serve\n3. Display\n4. Exit\nEnter your choice: ";
        cin >> ch;
        if(ch == 1){
            if((tail+1) % MAX == head){
                cout << "Queue Overflow!\n";
                continue;
            }
            cout << "Enter value to insert: ";
            cin >> n;
            if(head == -1){
                head++;
            }
            ins(&tail, _que, n);
        }
        else if(ch == 2){
            if(head == -1){
                cout << "Queue Underflow!\n";
                continue;
            }
            if(head == tail){
                cout << "Element Deleted is: " << _que[head] << endl;
                head = tail = -1;
            }
            else
                del(&head, _que);
        }
        else if(ch == 3){
            if(head == -1){
                cout << "Queue Underflow!\n";
                continue;
            }
            display(head, tail, _que);
        }
        else if(ch == 4)
            break;
        else
            cout << "Invalid choice!\n";
    }while(ch != 4);
}

int main(){
    int ch;
    do{
        cout << "\n\tMAIN MENU\n1. Stack\n2. Queue\n3. Exit\nEnter your choice: ";
        cin >> ch;
        if(ch == 1)
            stk();
        else if(ch == 2)
            que();
        else if(ch == 3)
            break;
        else
            cout << "Invalid choice!\n";
    }while(ch != 3);
    return 0;
}
