#include <iostream>
#include <string>
#include "FileOps.h"

using namespace std;

int main()
{

    FileOps dofile;
    string nameOfFile;
    int x = -1;
    string y = " ";

    do{

       cin.clear();// for edge case
       fflush(stdin);// for edge case

        if( x == 1){//open filename::: open file and save to list
            cout << "Name of File::" << endl;
            cin >> nameOfFile;
            nameOfFile.append(".txt");

            dofile.open(nameOfFile.c_str());
        }


        if( x == 2 && dofile.fileOpen == true){//save filename::: save new file
            cout << "Name of new File::" << endl;
            cin >> nameOfFile;
            nameOfFile.append(".txt");

            dofile.save(nameOfFile.c_str());
        }


         if( x == 3 && dofile.fileOpen == true){//insert n text::: insert n text::
        int n=0;
        string text = " ";
        cout << "which line to insert(n)::" << endl;
        cin >> n;
        cout << "what text to insert(text)::" << endl;
        cin >> text;

        Undo me;
        me.selection = x;
        me.edit = text.c_str();
        me.m = -1;
        me.n = n;
        dofile.s1.push(me);

        dofile.insertText(n,text.c_str());
        dofile.currentPage(n);

        }


         if( x == 4 && dofile.fileOpen == true){//delete n:​:: delete node/line
            int n=0;
            cout << "which one to delete(n)::" << endl;
            cin >> n;

            list<string>::iterator itr1;
            itr1 = dofile.list1.begin();
            advance(itr1,n-1);

            Undo me;
            me.selection = x;
            me.edit = *itr1;
            me.m = -1;
            me.n = n;

            dofile.s1.push(me);
            dofile.deleteN(n);
            dofile.currentPage(n);

        }


        if( x == 5 && dofile.fileOpen == true){//move n m::: move the line at position ​n​ to position ​m​
        int n,m;
        cout << "which line to move(n)::" << endl;
        cin >> n;
        cout << "where to move it(m)::" << endl;
        cin >> m;

        list<string>::iterator itr1;
        itr1 = dofile.list1.begin();
        advance(itr1,n-1);
        // because i will delete later so its accounting for the shift
        ++m;
        Undo me;
        me.selection = x;
        me.edit = *itr1;
        me.m = m;
        me.n = n;
        dofile.s1.push(me);


        dofile.moveLine(n,m);
        dofile.deleteN(n);
        dofile.currentPage(n);
        }

         if( x == 6 && dofile.fileOpen == true){// replacentext::: replace the text inside line ​n with the string provided in `text`
        int n=0;
        string text = " ";
        cout << "which line to replace(n)::" << endl;
        cin >> n;
        cout << "what text to replace it with(text)::" << endl;
        cin >> text;

        list<string>::iterator itr1;
        itr1 = dofile.list1.begin();
        advance(itr1,n-1);

        Undo me;
        me.selection = x;
        me.edit = *itr1;
        me.m = -1;
        me.n = n;
        dofile.s1.push(me);

        dofile.replaceText(n,text.c_str());
        dofile.currentPage(n);
        }

         if( x == 7 && dofile.fileOpen == true){//next::: program should display the next page
        if(dofile.s1.top().n > 0){
        Undo me;
        me.selection = x;
        me.edit = " ";
        me.m = -1;

        int nextPage = dofile.s1.top().n + 10;
        me.n = nextPage;
        dofile.s1.push(me);
        dofile.currentPage(nextPage);//actually next page :)
        }

        }

         if( x == 8 && dofile.fileOpen == true){//prev::: program should display the previous page
        if(dofile.s1.top().n > 10){

        Undo me;
        me.selection = x;
        me.edit = " ";
        me.m = -1;

        int nextPage = dofile.s1.top().n - 10;
        me.n = nextPage;
        dofile.s1.push(me);
        dofile.currentPage(nextPage);//actually next page :)
        }

        }


          if( x == 9 && !dofile.s1.empty() && dofile.fileOpen == true){//undo::: Reverts the last taken action
////does not include previous save or undo actions. Once the user calls the open command, undo stack should be emptied

        Undo me;
        me.selection = x;
        me.edit = " ";
        me.m = -1;

        dofile.removeExtra(); // pops the undo prev and next operations


      if(dofile.s1.top().selection==3){//inserted new line
            ///DELETE
            dofile.deleteN(dofile.s1.top().n);
            me.n = dofile.s1.top().n;

         } else if(dofile.s1.top().selection==4){//deleted a line
            ///INSERT
            dofile.insertText(dofile.s1.top().n,dofile.s1.top().edit.c_str());
            me.n = dofile.s1.top().n;

         } else if(dofile.s1.top().selection==5){//moved line(n) to another line(m)
            ///REPLACE
            dofile.insertText(dofile.s1.top().n,dofile.s1.top().edit.c_str());
            dofile.deleteN(dofile.s1.top().m);
            me.n = dofile.s1.top().n;

         } else if(dofile.s1.top().selection==6){//replaced text at (n)
            ///MOVE
            dofile.replaceText(dofile.s1.top().n,dofile.s1.top().edit.c_str());
            me.n = dofile.s1.top().n;

         } else {cout<< "there seems to be nothing to undo" << endl;
         }

        dofile.currentPage(dofile.s1.top().n);
        dofile.s1.pop();

        dofile.s1.push(me);

    }




    cout << "make a selection::" << endl <<
    "1) open a file" << endl <<
    "2) save a file" << endl <<
    "3) insert new line at a line(n)" << endl <<
    "4) delete n" << endl <<
    "5) move line(n) to another line(m)" << endl <<
    "6) replace text at(n)" << endl <<
    "7) Next page" << endl <<
    "8) Prev page" << endl <<
    "9) Undo" << endl <<
    "0) exit " << endl;
    cin >> y;

    if (isdigit(y[0])) {
    x = (int)y[0] - 48;

    } else if(!isdigit(y[0])){
        for (int i=0; i<y.length(); i++){
        y[i]=tolower(y[i]);
        }

        if(y.find("open") != string::npos){
            x = 1;

        }
        if(y.find("save") != string::npos){
            x = 2;
        }
        if(y.find("insert") != string::npos){
            x = 3;
        }
        if(y.find("delete") != string::npos){
            x = 4;
        }
        if(y.find("move") != string::npos){
            x = 5;
        }
        if(y.find("replace") != string::npos){
            x = 6;
        }
        if(y.find("next") != string::npos){
            x = 7;
        }
        if(y.find("prev") != string::npos){
            x = 8;
        }
        if(y.find("undo") != string::npos){
            x = 9;
        }
        if(y.find("exit") != string::npos){
            x = 0;
        } else if (x == -1){ cout << "Unable to understand your input try again" << endl;}

    }
    y = " ";
    }while( x != 0);



    return 0;
}
