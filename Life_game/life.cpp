#include "life.h"
#include "utility.h"    

#include <iostream>

using namespace std;

// Section 1.4:


int Life::neighbor_count(int row, int col)
/*
Pre:  The Life object contains a configuration, and the coordinates
      row and col define a cell inside its hedge.
Post: The number of living neighbors of the specified cell is returned.
*/

{
    int i, j;
    int count = 0;
    
    if (row == 1) {
        if (col == 1) { //top left corner
            for (i = row; i <= row + 1; i++)

                for (j = col; j <= col + 1; j++)
                    count += grid[i][j];  //  Increase the count if neighbor is alive.
            count -= grid[row][col]; //  Reduce count, since cell is not its own neighbor.
            return count;
        }
        else if (col = maxcol) { //top right corner
            for (i = row; i <= row + 1; i++)

                for (j = col - 1; j <= col + 1; j++)
                    count += grid[i][j];  //  Increase the count if neighbor is alive.
            count -= grid[row][col]; //  Reduce count, since cell is not its own neighbor.
            return count;
        }
        else { //top row
            for (i = row; i <= row + 1; i++)

                for (j = col - 1; j <= col + 1; j++)
                    count += grid[i][j];  //  Increase the count if neighbor is alive.
            count -= grid[row][col]; //  Reduce count, since cell is not its own neighbor.
            return count;
        }
    }
    else if (row == maxrow) {
        if (col == 1) {
            for (i = row - 1; i <= row; i++)

                for (j = col; j <= col + 1; j++)
                    count += grid[i][j];  //  Increase the count if neighbor is alive.
            count -= grid[row][col]; //  Reduce count, since cell is not its own neighbor.
            return count;
        }
        else if (col == maxcol) {
            for (i = row - 1; i <= row; i++)

                for (j = col - 1; j <= col; j++)
                    count += grid[i][j];  //  Increase the count if neighbor is alive.
            count -= grid[row][col]; //  Reduce count, since cell is not its own neighbor.
            return count;
        }
        else {
            for (i = row - 1; i <= row; i++)

                for (j = col - 1; j <= col + 1; j++)
                    count += grid[i][j];  //  Increase the count if neighbor is alive.
            count -= grid[row][col]; //  Reduce count, since cell is not its own neighbor.
            return count;
        }
    }
    else if (col == 1) {
        for (i = row - 1; i <= row + 1; i++)

            for (j = col; j <= col + 1; j++)
                count += grid[i][j];  //  Increase the count if neighbor is alive.
        count -= grid[row][col]; //  Reduce count, since cell is not its own neighbor.
        return count;
    }
    else if (col == maxcol) {
        for (i = row - 1; i <= row + 1; i++)

            for (j = col - 1; j <= col; j++)
                count += grid[i][j];  //  Increase the count if neighbor is alive.
        count -= grid[row][col]; //  Reduce count, since cell is not its own neighbor.
        return count;
    }
    else {
        for (i = row - 1; i <= row + 1; i++)

            for (j = col - 1; j <= col + 1; j++)
                count += grid[i][j];  //  Increase the count if neighbor is alive.
        count -= grid[row][col]; //  Reduce count, since cell is not its own neighbor.
        return count;
    }
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
    cout << "\nEdit grid size? ";
    if (user_says_yes()) {
        cout << "\nYou can choose the size of your grid. \nColumn 0-60, Row 0-20." << endl;
        do {
            cout << "Row: ";
            cin >> maxrow;
            cout << endl;
        } while (maxrow < 1 || maxrow >= 20);

        do {
            cout << "Hey guy, column: ";
            cin >> maxcol;
            cout << endl;
        } while (maxcol < 1 || maxcol >= 60);
    }
    else {
        maxcol = 60;
        maxrow = 20;
    }

    

    int row, col;
    for (row = 0; row <= maxrow + 1; row++)
        for (col = 0; col <= maxcol + 1; col++)
            grid[row][col] = 0;
    cout << "List the coordinates for living cells." << endl;
    cout << "Terminate the list with the special pair -1 -1" << endl;
    cin >> row >> col;

    while (row != -1 || col != -1) {
        if (row >= 1 && row <= maxrow)
            if (col >= 1 && col <= maxcol)
                grid[row][col] = 1;
            else
                cout << "Column " << col << " is out of range." << endl;
        else
            cout << "Row " << row << " is out of range." << endl;
        cin >> row >> col;
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


