/*
*	Name: Devin Smaldore
*	Date: 12-12-16
*	Class: CSC-2710
*	Location: ~/csc2710/p8/nQueens.cpp
*  General Comments: Suppose a NxN chess board has been established
      with a supply of N queens.  Write a a program that outputs the 
      first solution found in the N Queens problem.   Normally this 
      would be a simple task, but some of the squares of the 
      chessboard have been marked as unusable and hence cannot have
      a queen placed on them.  In a slight twist, a queen can hide 
      behind a barrier unless the multiple queens appear in the same 
      row.  This means that two queens can occupy the same column or 
      diagonal as long as there is a least one barrier between.  
      However, a barrier cannot protect a queen in a row.
 
 * Format of Input:
      -t, number of cycles to run
      -n, dimensions of the board
      - the next n lines contain the chessboard
      2
      4
      ....
      ....
      ....
      ....
      4
      ..#.
      #..#
      ##..
      ...#
 * Format of Output:
     .Q..
     ...Q
     Q...
     ..Q.
     
     ..#Q
     #Q.#
     ##.Q
     Q..#
 
 * To Compile:
     g++ -Wall nQueens.cpp
  
 * To Execute: 
     -./a.out < test.txt < results.txt
 
 * To see the output:
     -either vi into results.txt
     -cat results.txt
 
*/

#include <iostream>
#include <stdlib.h>


using namespace std;

//prototypes
void nQueens(int i, int n, int col[], char** board, bool& found);
bool checkQueen(int col[], int i, int index, char **board, int n);
void print(int col[], int n, char **board);



int main(void)
{
   int t = 0;
   cin >> t; //number of test cases to run
   for(int x = 0; x<t; x++){
      int n = 0; //denotes the deminsions of the board
      cin >> n; //dimensions of the board
      int col[n];
      char **board;
      bool found = false;
      board = new char* [n];
      //initialize and cin board[][]
      for(int i = 0; i<n; i++)
         board[i] = new char[n];
      for(int j = 0; j<n; j++)
         for(int k = 0; k<n; k++)
            cin >> board[j][k];
      nQueens(0, n, col, board, found);
      if(!found)
         cout << "No Solution" << endl << endl;
   
      //delete 2D array to free up space
      for(int y = 0; y<n; y++)
         delete board[y];

      delete [] board;
   }
}
   
/* PreCondition:
      i initially comes in as 0, n is the dimensions, col array
      is empty, board is loaded with our board, and found comes 
      in as false initially
   PostCondition:
      col array is loaded with the correct values, board doesn't 
      change, and if we find a solution, found is turned to true
*/
void nQueens(int i, int n, int col[], char **board, bool& found){
   
   //found initially comes in as false, and is only turned true
   //if we find a possible board
   if(!found){ 
      if (i == n){
         //out one possible queen arrangement
         print(col, n, board);
         found = true; 
      } else {
         //consider putting the queen in each column position of the 
         //ith row then recurse to the next row
         for(int k = 0; k<n; k++){
            //make sure we are not looking at a #
            if(board[i][k] != '#'){
               col[i] = k;
               if(checkQueen(col, i, k, board, n)){
                  nQueens(i+1, n, col, board, found);
               }
            }
         }
      }
   }
}

/* PreCondition:
      takes in the col array, i, which initially comes in as 0,
      index, which is our k value in nqueens that gets incremented,
      the size of the board, and the board itself
   PostCondition: 
      A queen is either able to be added to the board (returns true),
      or not (returns false)
*/
bool checkQueen(int col[], int i, int index, char **board, int n){
   int k = i-1;
   bool promised = true;
   bool dLeft = true;
   bool dRight = true;
   bool vert = true;
   int left = index;
   int right = index;


   //promised is our flag that states whether the queen can be put in a certain
   // spot
   while(k >= 0 && promised){
      //vertical # check
      if(board[k][index] == '#'){
         vert = false;
      }

      //diagonal Left # check
      if(left > 0){
         left--;
         if(board[k][left] == '#'){
            dLeft = false;
         }
      }
   
      //diagonal Right # check
      if(right < n-1){
         right++;
         // if the current position is a pound, we could possibly put a queen 
         //at the position
         if(board[k][right] == '#'){
           dRight = false;
        }
      }
      
      //checks the overall diagonal if there is a queen
      if(abs(col[i] - col[k]) == i-k){
         //this sees if we are looking at the left diagonal
         if(left < index && dLeft){
            promised = false;
         }
         //this sees if we are looking at the right diagonal
         else if(right > index && dRight){
            promised = false;
         }
         //this is if there are no # left or right... i.e. no barriers in the
         // board
         else if(dLeft && dRight){
            promised = false;
         }
         //otherwise, we can still possibly place a queen at this position
         else 
            promised = true;
      }
      
      //checks to see if there is no queen and no # above
      if(index == col[k] && vert)
         promised = false;

      k--;
   }
   
   return promised; 
}


//takes in the col array, the size, and the 2D array
//and prints the board with Queens
void print(int col[], int n, char **board){
   for(int i = 0; i<n; i++){
      for(int j = 0; j<n; j++){
         if(col[i] == j)
            cout << "Q";
         else
            cout << board[i][j];
      }
      cout << endl;
   }
   cout << endl;
}
