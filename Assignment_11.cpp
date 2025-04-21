#include <bits/stdc++.h>
#include<fstream>
#include <cstdio>

using namespace std;
class student
{
    int roll, div;
    string name, address;

    student()
    {
        roll = div = 0;
        name = address = "";
    }
    void display()
    {
        cout << name << " " << roll << " " << div << " " << address << endl;
    }
    void getinfo()
    {
        cout << "Enter name: ";
        cin >> name;
        cout << "Enter roll no: ";
        cin >> roll;
        cout << "Enter div: ";
        cin >> div;
        cout << "Enter address: ";
        cin >> address;
    }
    friend class Myfile;
};
class Myfile
{
    string filename;
    fstream file;
    student s;

public:
    Myfile()
    {
        cout << "Enter file name" << endl;
        cin >> filename;
        file.open(filename, ios::out);
        if (!file)
        {
            cout << "Error opening file" << endl;
        }
        else
        {
            cout << "File opened " << endl;
        }
        file.close();
    }
    void addrecord()
    {
        file.open(filename, ios::app);
        s.getinfo();
        file.write(reinterpret_cast<char *>(&s), sizeof(s));
        file.close();
    }
    void displayfile()
    {
        file.open(filename, ios::in);
        file.read(reinterpret_cast<char *>(&s), sizeof(s));
        while (!file.eof())
        {
            s.display();
            file.read(reinterpret_cast<char *>(&s), sizeof(s));
        }
        file.close();
    }
    void deleterecord(int roll){
        file.open(filename, ios::in);
        fstream temp;
        temp.open("temp" , ios:: out);
        bool found = 0;
        file.read(reinterpret_cast<char*>(&s) , sizeof(s));
        while(!file.eof()){
            if(roll == s.roll){
                cout<<"Deleted"<<endl;
                found = true;
                s.display();

            }
            else{
                temp.write(reinterpret_cast<char*>(&s) , sizeof(s));

            }
            file.read(reinterpret_cast<char*>(&s) , sizeof(s));
        }
        if(!found){
            cout<<"No record found"<<endl;

        }
        file.close();
        temp.close();
        remove(filename.c_str());
        rename("temp" , filename.c_str());
    }
};
int main() {
    Myfile File;
    int Choice;
    int R;
    do {
        cout<<"\n1: Add a record\n2: Display Database\n3: Delete a record\nEnter your choice: ";
        cin>>Choice;

        switch( Choice ) {
            case 1:
                File.addrecord();
                break;
                    
            case 2:
                File.displayfile();
                break;
                    
            case 3:
                cout<<"Enter the record you want to delete: ";
                cin>>R;
                File.deleterecord(R);
                break;
        }
    }
    while(Choice<6);
    cout<<endl;
    return 0;
}