#include <iostream>
#ifndef FILEOPS_H
#define FILEOPS_H
#include <list>
#include<stack>

using namespace std;

        struct Undo{
        int selection;
        int n;
        int m;
        string edit;
        };

class FileOps
{
    public:
        bool fileOpen = false;
        FileOps();
        virtual ~FileOps();

        list<string> list1;
        stack<Undo> s1;///stack of struct's to have neccessary info about prev. operations



/* open filename- IN:: (name of file to be opened) - RETURN:: none -- open file load contents
 into a linked list */
void open(const char*);

/* save filename - IN:: (name of file to be created and written to) - RETURN:: none --
create a new file with the name passed to function and write  all the contents
of the linked list to it */
void save(const char*);

/* insert n text */
void insertText(int&,const char*);

/* delete n */
void deleteN(int&);

/*move n m*/
void moveLine(int&,int&);

/*replace n, with 'text'*/
void replaceText(int&,const char*);




/*print everything, and print the page just edited*/
void printAll();
void currentPage(int&);

/* remove extra stack (saved info) to get to most recent edit*/
void removeExtra();
    protected:

    private:
};

#endif // FILEOPS_H
