#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

/*
The idea for this solution is given in:
https://codegolf.stackexchange.com/questions/241219/mat-printing-matrix
*/

int printMat(vector<vector<int>> table, int rows, int cols)
{
   for(int i = 0; i < rows; i++)
    {
        for(int j = 0; j < cols; j++)
        {
            cout << table[i][j];
        }
        cout << '\n';
    }
    cout << '\n';
    return 0;
}

int main(){
    int const rows = 5; 
    int const cols = 7; 
    char const ch1 = '@';
    char const ch2 = '-';
    vector<vector<int>> table( rows , vector<int> (cols));   

    /*next we will fill the table such that each enterance vec[i][j] will get the minimum between i and j.
    for example the enterance located in the third row (i=2), and the second column (j=1) will get the value 1
    (vec[2][1] = 1).
    */ 
    for(int i = 0; i < rows; i++)
    {
        for(int j = 0; j < cols; j++)
        {
            table[i][j] = min(i,j);
        }
    }

    cout << "step 1 - fill table with minimum between i and j:" << endl;
    printMat(table, rows,cols);
    /*
    should print: 
    0000000
    0111111
    0122222
    0123333
    0123444
    */




    //next we will create new 2D vector that will be the reverse of the original table. 
    
    vector<vector<int>> rev_table( rows , vector<int> (cols));
    for(int i = 0; i < rows; i++)
    {
        for(int j = 0; j < cols; j++)
        {
            rev_table[i][j] = table[rows-1-i][cols-1-j];
        }
    }

    cout << "step 2 - create reversed table:" << endl;
    printMat(rev_table, rows,cols);
     /*
    should print: 
    4443210
    3333210
    2222210
    1111110
    0000000
    */

    /*next we will go over the original table and to each enterance we will give the minimum value between the current value
    and the value in the same entarence in the reversed table. 
    for example if table[2][6]==2 and rev_table[2][6]==1 then we will change the value of table[2][6] to 1.
    */
    for(int i = 0; i < rows; i++)
    {
        for(int j = 0; j < cols; j++)
        {
            table[i][j] = min(table[i][j],rev_table[i][j]);
        }
    }

    cout << "step 3 - create a \"minimum table\" out of the 2 tables above:" << endl;
    printMat(table, rows,cols);
    /*
    should print: 
    0000000
    0111110
    0122210
    0111110
    0000000
    */


    //now we will go over the table and use the mod2 function on each enterance.
    
    for(int i = 0; i < rows; i++)
    {
        for(int j = 0; j < cols; j++)
        {
            table[i][j] = table[i][j]%2 ;
        }
    }

    cout << "step 4 - use the mod 2 function on the given table:" << endl;
    printMat(table, rows,cols);
    /*
    should print: 
    0000000
    0111110
    0100010
    0111110
    0000000
    */

    /* At the end we will create a char table in the same size and fill it such that in each enterance that the value
    is 0 in the original table, we will put the first char(ch1) and the second char(ch2) otherwise.
    */

    vector<vector<char>> ch_table( rows , vector<char> (cols)); 

    for(int i = 0; i < rows; i++)
    {
        for(int j = 0; j < cols; j++)
        {
            if(table[i][j] == 0)
            {
                ch_table[i][j] = ch1 ;
            }
            else
            {
                ch_table[i][j] = ch2 ;
            }
        }
    }
    
    // the last thing we need to do is to create a string out of the chars table and return it.
    cout << "step 5 - replace 0 with first char and 1 with second char:" << endl;

    string ans;

    for(int i = 0; i < rows; i++)
    {
        for(int j = 0; j < cols; j++)
        {
            ans += ch_table[i][j];
        }
    ans += "\n";
    }       
    cout << ans;
    /*
    should print: 
    @@@@@@@
    @-----@
    @-@@@-@
    @-----@
    @@@@@@@
    */
    return 0;
}