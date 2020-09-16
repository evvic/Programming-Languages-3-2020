#include "life.h"
#include "utility.h"    

#include <iostream>
#include <stdio.h>
#include <conio.h> //_getch()
#include <iomanip> //cout spacing
#include <fstream> //file read & write
#include <string>

using namespace std;
// Section 1.4:

void Life::patternSaverDeluxe() {
    string description;
    string fileName;

    cout << endl << endl;
    cout << "\nSaving a pattern for Life...";

    cout << "\n\nEnter the file name with .txt: ";
    cin >> fileName;

    ofstream outFS;
    outFS.open(fileName); //this will corrupt a previous file if it had the same .txt name

    cout << "\nEnter a short description.";
    cout << "\n\t>";
    cin.ignore(); //needed after cin for name
    getline(cin, description);

    outFS << description << endl;

    for (int row = 0; row < maxrow; row++) {
        for (int col = 0; col < maxcol; col++) {
            if (grid[row][col] == 1) {
                outFS << 'X';
            }
            else {
                outFS << '_';
            }
        }

        outFS << endl;
    }

    outFS.close();
}

void Life::patternLoaderPro() {

    string fileName;
    string fileTxt;
    
    ifstream inFS;

    do {
        cout << "\nEnter the file name: ";
        cin >> fileName;

        inFS.open(fileName);

        if (inFS.fail()) {
            cout << "\n\tcould not open file";
        }
        else {
            cout << "\tsuccessfuly opened...\n";
        }
    } while (inFS.fail());

    getline(inFS, fileTxt);
    //inFS.ignore();

    cout << "\nDescription: " << fileTxt << endl;

    for (int i = 0; inFS >> fileTxt; i++) {

        for (int j = 0; j < 60; j++) { //looping through the 60 column and disecting


            switch (fileTxt.at(j)) {
            case '_':
                grid[i][j] = 0;
                break;
            case 'x':
                grid[i][j] = 1;
                break;
            case 'X':
                grid[i][j] = 1;
                break;
            default:
                cout << "XD";
                break;
            }
        }
    }

    inFS.close();
}

void Life::userInput() {
    char c;

    cout << "Only press 'x' or '(space)' or else error." << endl;
    for (int row = 0; row < maxrow; row++) {
        cout << setw(3) << left << row + 1 << '.';
        for (int col = 0; col < maxcol; col++) {
            do {
                c = _getch();
                cout << c;
                c = toupper(c);
            } while (!checkFax(c));

            if (c == 'X') {
                grid[row][col] = 1;
            }
            else {
                grid[row][col] = 0;
            }

        }
        cout << "[next row]" << endl;

    }
}

int Life::neighbor_count(int row, int col)
/*
Pre:  The Life object contains a configuration, and the coordinates
      row and col define a cell inside its hedge.
Post: The number of living neighbors of the specified cell is returned.
*/
{
    int i, j;
    int count = 0;
    for (i = row - 1; i <= row + 1; i++)
        for (j = col - 1; j <= col + 1; j++)
            count += grid[i][j];  //  Increase the count if neighbor is alive.
    count -= grid[row][col]; //  Reduce count, since cell is not its own neighbor.
    return count;
}
void Life::update()
/*
Pre:  The Life object contains a configuration.
Post: The Life object contains the next generation of configuration.
*/

{
    int row, col;
    int new_grid[20 + 2][60 + 2]; //oof
    /*
    TBH this is very bad, but the compiler is arguing with me that it HAS to be a constant, which doesn't really
    make sense. Just being real though, this MAY add bugs but it is still constrained with the maxcol and maxrow
    so I ain't gonna complain XD
    */

    for (row = 1; row <= maxrow; row++)
        for (col = 1; col <= maxcol; col++)
            switch (neighbor_count(row, col)) {
            case 2:
                new_grid[row][col] = grid[row][col];  //  Status stays the same.
                break;
            case 3:
                new_grid[row][col] = 1;                //  Cell is now alive.
                break;
            default:
                new_grid[row][col] = 0;                //  Cell is now dead.
            }
    for (row = 1; row <= maxrow; row++)
        for (col = 1; col <= maxcol; col++)
            grid[row][col] = new_grid[row][col];
}
void Life::initialize()
/*
Pre:  None.
Post: The Life object contains a configuration specified by the user.
*/

{
    char f;

    do {
        cout << "\nEnter how you would like to play:";
        cout << "\n\t -'o' to play original state.";
        cout << "\n\t -'e' to edit grid size.";
        cout << "\n\t -'p' to load custom pattern.";
        cout << "\n\t> ";
        f = _getch();
        cin.clear();
        cout << f << endl;

        f = toupper(f);

    } while (f != 'O' && f != 'E' && f != 'P');
    
    switch (f) {
    case 'O':
        maxcol = 60;
        maxrow = 20;

        userInput(); //get the Life board filled

        cout << "\n\nSave this pattern ";
        if (user_says_yes()) {
            patternSaverDeluxe();
        }
        break;

    case 'E':
        cout << "\nYou can choose the size of your grid. \nColumn 0-60, Row 0-20." << endl;
        do {
            cout << "Row: ";
            cin >> maxrow;
            cout << endl;
        } while (maxrow < 1 || maxrow > 20);

        do {
            cout << "Hey guy, column: ";
            cin >> maxcol;
            cout << endl;
        } while (maxcol < 1 || maxcol > 60);

        userInput(); //get the Life board filled
        cout << "\n\nSave this pattern ";
        if (user_says_yes()) {
            patternSaverDeluxe();
        }
        break;
    case 'P':
        //LOAD PATTERN
        patternLoaderPro(); //fill Life board with pattern
        break;
    default:
        cout << right << "Aye you broke the switch statement LMAO";
        break;
    }

}
void Life::print()
/*
Pre:  The Life object contains a configuration.
Post: The configuration is written for the user.
*/
{
    int row, col;
    cout << "\nThe current Life configuration is:" << endl;
    for (row = 1; row <= maxrow; row++) {
        for (col = 1; col <= maxcol; col++)
            if (grid[row][col] == 1) cout << '*';
            else cout << ' ';
        cout << endl;
    }
    cout << endl;
}