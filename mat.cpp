#include <iostream>
#include <string>
#include <vector>
#include <algorithm>


using namespace std;

#include "mat.hpp"

namespace ariel
{
    string mat(int cols, int rows, char ch1, char ch2)
    {
        if (cols % 2 == 0 || rows % 2 == 0)//checks that the mat size is odd.
        {
            throw invalid_argument("Mat size is always odd");
        }
        if (cols < 0 || rows < 0)// checks that mat size is positive.
        {
            throw invalid_argument("Mat size is always positive");
        }
        char const lowest = 33;
        char const highest = 126;
        if (ch1 < lowest || ch1 > highest || ch2 < lowest || ch2 > highest)//checks that the chars are printable.
        {
            throw invalid_argument("char is not printable");
        }
        //At first we will create 2D vector that will be the mat.
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

        //next we will create new 2D vector that will be the reverse of the original table. 
        
        vector<vector<int>> rev_table( rows , vector<int> (cols));
        for(int i = 0; i < rows; i++)
        {
            for(int j = 0; j < cols; j++)
            {
                rev_table[i][j] = table[rows-1-i][cols-1-j];
            }
        }

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

        //now we will go over the table and use the mod2 function on each enterance.
        
        for(int i = 0; i < rows; i++)
        {
            for(int j = 0; j < cols; j++)
            {
                table[i][j] = table[i][j]%2 ;
            }
        }

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
        string ans;

        for(int i = 0; i < rows; i++)
        {
            for(int j = 0; j < cols; j++)
            {
                ans += ch_table[i][j];
            }
        ans += "\n";
        }       

        return ans;
        
    }
}
