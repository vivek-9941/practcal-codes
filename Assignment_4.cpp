#include <bits/stdc++.h>
using namespace std;

class HashTable
{
public:
    vector<long long> arr;
    int tablesize;
    HashTable(int size){
        tablesize = size;
        arr.resize(size,-1);
    }
    int hash(int val){
        int sum =0;
        while(val>0){
            sum+= val%10;
            val /=10;
        }
        return sum%tablesize;
    }

    void InsertWithoutReplacement(int num){
        int h  =hash(num);
        int comparison = 0;
        if(arr[h] == -1){
            arr[h] = num;
            return;

        }
        comparison++;
         int i = h+1;
         while(i%tablesize != h){
            comparison++;
            if(arr[i % tablesize]== -1){
                arr[i % tablesize] = num;
                return;
            }
            i++;
         }
         cout<<"comparisons :"<<comparison<<endl;
         cout<<"TABLE IS FULL"<<endl;
    }

    void insertWithReplacement(int num){
            int h = hash(num);
            int comparison = 0;
            if(arr[h] == -1){
                arr[h]  = num;
                return;

            }
            if(hash(arr[h]) != h){
                long long temp  = num;
                num  = arr[h];
                arr[h]  = temp;

            }
            comparison++;
            int i = h+ 1;
            while( i % tablesize != h){
                comparison++;
                if(arr[i%tablesize] == -1){
                    arr[i%tablesize]  = num;
                    return;
                }
                i++;
            }
            
            
        }
            bool searchintable(int num){
                int h  = hash(num);
                int comparison = 0;
                if(arr[h] == num){
                    cout<<"Found at"<<h<<endl;
                    return true;
                }
                comparison++;
                int i = h+1;
                while(i %tablesize != h){
                    comparison++;
                    if(arr[i%tablesize] == num){
                        cout<<"Found at"<<i%tablesize<<endl;
                        return true;
                    }
                    else if(arr[i%tablesize] == -1){
                        cout<<"NOT FOund "<<endl;
                        return false;

                    }
                    i++;
                }
                cout<<"NOT FOund "<<endl;
                return false;
            }
            void display() {
                for (int i = 0; i < tablesize; i++) {
                    if (arr[i] != -1) {
                        cout << "Index " << i << "-- " << arr[i] << endl;
                    }
                }
            }
};

int main() {
    long long  choice, size, number;
    cout << "Enter the size of the hash table: ";
    cin >> size;
    HashTable htWithoutReplace(size);
    HashTable htWithReplace(size);

    do {
        cout << "\nHash Table Menu:\n";
        cout << "1. insert\n";
        cout << "2. search\n";
        cout << "3. display\n";
        cout << "4. exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Enter the number to insert ";
            cin >> number;
            htWithoutReplace.InsertWithoutReplacement(number);
            htWithReplace.insertWithReplacement(number);
            // cout << "Comparisons in insert without replacement-" << htWithoutReplace.getComparisons() << endl;
            // cout << "Comparisons in insert with replacement- " << htWithReplace.getComparisons() << endl;
            break;

        case 2:
            cout << "Enter the number to search for: ";
            cin >> number;
          htWithoutReplace.searchintable(number);

            htWithReplace.searchintable(number);

            break;

        case 3:
            cout << "Hash Table without replacement:\n";
            htWithoutReplace.display();
            cout << "Hash Table with replacement:\n";
            htWithReplace.display();
            break;

        case 4:
            cout << "Exiting program." << endl;
            break;

        default:
            cout << "Invalid choice! Please try again." << endl;
        }
    } while (choice != 5);
}