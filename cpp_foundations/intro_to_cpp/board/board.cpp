#include <iostream>
#include <vector>
using std::cout;
using std::vector;

void PrintBoard(vector<vector<int>> board){
	for(int i = 0; i < board.size(); i++){
    	for (int j = 0; j < board[0].size(); j++) {
        	cout << board[i][j] << " ";
        }
        cout << "\n";
    }
}

int main(){
    vector<vector<int>> board 
    {{0, 1, 0, 0, 0, 0},
    {0, 1, 0, 0, 0, 0},
    {0, 1, 0, 0, 0, 0},
    {0, 1, 0, 0, 0, 0},
    {0, 0, 0, 0, 1, 0}};
    PrintBoard(board);
 }
