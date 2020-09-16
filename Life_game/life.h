#ifndef LIFE_H_INCLUDED
#define LIFE_H_INCLUDED

const int maxrow = 20, maxcol = 60;    //  grid dimensions

class Life {
public:
    void initialize();
    void print();
    void update();
    
    void patternLoaderPro();
    void patternSaverDeluxe();
    void userInput();
private:
    int maxrow = 20, maxcol = 60;
    int grid[20 + 2][60 + 2];  //  allows for two extra rows and columns
    //constant static error so declare as 
    int neighbor_count(int row, int col);
};



#endif 