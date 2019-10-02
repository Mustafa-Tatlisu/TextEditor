#include<iostream>
#include<fstream>
#include <list>
#include<cmath>
#include<stack>
#include "FileOps.h"

using namespace std;

FileOps::FileOps()
{
    //ctor
}

FileOps::~FileOps()
{
    //dtor
}


void FileOps::open(const char* nameFile)
{
    string line;
    fstream openFile;
    openFile.open(nameFile);

    if(openFile.is_open()){
        while(getline(openFile, line)){

        list1.push_back(line);
        }
        fileOpen = true;
        cout << fileOpen << "----" << endl;
    } else {
        cout << endl << "!!!!!!file was unopened you will be redirected to start!!!!!!" << endl << endl;

    }


}


void FileOps::save(const char* nameFile)
{
    ofstream outfile(nameFile);

        for (auto v : list1)///what is auto? why does this work?
        outfile << v << endl;



}


void FileOps::deleteN(int& n)
{   list<string>::iterator itr1;
    itr1 = list1.begin();
    advance(itr1,n-1);
    list1.erase(itr1);

}


void FileOps::moveLine(int& n,int& m)// move the line at position ​n​ to position ​m​
{
    string moving = " ";
    int counter = 1;

    list<string>::iterator itr1;
    itr1 = list1.begin();

    for (auto v : list1){
        if(counter == n){
                moving = v;
        }
        counter++;
    }
     advance(itr1,m-1);
    list1.insert(itr1,moving);

}


void FileOps::insertText(int& n, const char* text)
{
    int counter = 0;
    if( n > list1.size()){//throws warning but not relevant, b/c n can never be negative
         counter = n - list1.size();
    }

    while ( counter-1 > 0 ){
        list1.push_back(" ");
        --counter;
    }
    list<string>::iterator itr1;
    itr1 = list1.begin();
    advance(itr1,n-1);
    list1.insert(itr1,text);

}


void FileOps::replaceText(int& n, const char* text)
{
    list<string>::iterator itr1;
    itr1 = list1.begin();
    advance(itr1,n-1);
    list1.insert(itr1,text);

    list1.erase(itr1);
}



///*//////////////////////////////////PRINT FUNCTIONS////////////////////////////////


void FileOps::printAll()
{


int counter = 0;
int tmp = 0;
cout << endl;
     for (auto v : list1){
        counter++;

    cout  << counter << ") " << v << endl;
     if (counter%10 == 0){
        tmp = counter/10;
        cout << endl << "--- page " << tmp << " ---"<< "\n" << endl;

     }
    }
cout << endl << "--- page " << ++tmp << " ---" << "\n" <<endl;
}

void FileOps::currentPage(int& n)
{

int counter = n;
if(n%10==0){
    counter--;
}

counter = (counter)/10;
int tmp = counter;
//because its an integer the division will truncate

list<string>::iterator itr1;
itr1 = list1.begin();
counter = counter * 10;//get it back to the pages line #
advance(itr1,counter++);

cout << endl;
for(int i = 1; i <=10 && counter <= list1.size() ; i++){//throws warning but not relevant, b/c counter can never be negative
    cout  << counter << ") " << *itr1 << endl;
    ++counter;
    ++itr1;
}


cout << endl << "--- page " << ++tmp << " ---" << "\n" <<endl;
}


///*///////operation to remove the next prev and undo operations from stack until the next undo/////////

void FileOps::removeExtra(){

    while((s1.top().selection== 7 || s1.top().selection== 8 || s1.top().selection== 9) && s1.size() > 1) {
            s1.pop();
           }

}
