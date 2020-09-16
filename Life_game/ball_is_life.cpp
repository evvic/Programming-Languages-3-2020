/* Program extracts from Chapter 1 of
   "Data Structures and Program Design in C++"
   by Robert L. Kruse and Alexander J. Ryba
   Copyright (C) 1999 by Prentice-Hall, Inc.  All rights reserved.
   Extracts from this file may be used in the construction of other programs,
   but this code will not compile or execute as given here. */


   // Section 1.2:

#include "utility.h"
#include "life.h"

#include <windows.h>

void instructions();
char MenuOptions();

int main()  //  Program to play Conway's game of Life.
/*
Pre:  The user supplies an initial configuration of living cells.
Post: The program prints a sequence of pictures showing the changes in
      the configuration of living cells according to the rules for
      the game of Life.
Uses: The class Life and its methods initialize(), print(), and update().
      The functions  instructions(),  user_says_yes().
*/

{
    Life configuration;
    instructions();
    configuration.initialize();
    configuration.print();

   
    
    char option = 'a';

    while (option != 'Q') {

        option = MenuOptions();

        switch (option) {
        case 'A':
            int realspeed, genZ;

            cout << "\nEnter speed of generations (ms): ";
            cin >> realspeed;
            while (realspeed < 0 || realspeed > 10000) {
                cout << "\nThat ain't some real speed smh..\n";
                cout << "\nEnter speed of generations (ms): ";
                cin >> realspeed;
            }

            cout << "\nEnter the amount of generations. 0 is for infinte.\n\t";
            cin >> genZ;
            while (genZ < 0 || genZ > 1000) {
                cout << "\nThe gens must be between 0-1000 brotha. Unless infintity go zoom\n";
                cout << "\nEnter the amount of generations: ";
                cin >> genZ;
            }

            if (genZ == 0) {
                while (true) {
                    configuration.update();
                    configuration.print();
                    Sleep(realspeed);
                    cout << "\n\tPress Ctrl + C to quit.";
                }
            }
            else {
                for (int i = 0; i < genZ; i++) {
                    configuration.update();
                    configuration.print();
                    Sleep(realspeed);
                }
            }
            break;
        case 'N':
            configuration.update();
            configuration.print();
            break;
        default:
            cout << "Goodnight!";
        }

    }
    
    cout << "\nSave progress";
    if (user_says_yes()) { configuration.patternSaverDeluxe(); }
    
}


char MenuOptions() {
    char trash;
    do {
        cout << "\n\t -'n' view next life generation.";
        cout << "\n\t -'a' animate the Life generations.";
        cout << "\n\t -'q' quit Life.";
        cout << "\n\t\t> ";
        cin >> trash;
        trash = toupper(trash);
    } while (trash != 'N' && trash != 'A' && trash != 'Q');

    return trash;
}


void instructions()
/*
Pre:  None.
Post: Instructions for using the Life program have been printed.
*/

{
    cout << "Welcome to Conway's game of Life." << endl;
    cout << "This game uses a grid of size " << maxrow << " by " << maxcol << " in which" << endl;
    cout << "each cell can either be occupied by an organism or not." << endl;
    cout << "The occupied cells change from generation to generation" << endl;
    cout << "according to the number of neighboring cells which are alive."
        << endl;
}
