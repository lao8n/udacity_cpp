#include <algorithm>  // for sort
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
using std::cout;
using std::ifstream;
using std::istringstream;
using std::sort;
using std::string;
using std::vector;
using std::abs;

// TODO: Add kStart and kFinish enumerators to the State enum.
enum class State {kEmpty, kObstacle, kClosed, kPath, kStart, kFinish};

// directional deltas
const int delta[4][2]{{-1, 0}, {0, -1}, {1, 0}, {0, 1}};

vector<State> ParseLine(string line) {
    istringstream sline(line);
    int n;
    char c;
    vector<State> row;
    while (sline >> n >> c && c == ',') {
      if (n == 0) {
        row.push_back(State::kEmpty);
      } else {
        row.push_back(State::kObstacle);
      }
    }
    return row;
}


vector<vector<State>> ReadBoardFile(string path) {
  ifstream myfile (path);
  vector<vector<State>> board{};
  if (myfile) {
    string line;
    while (getline(myfile, line)) {
      vector<State> row = ParseLine(line);
      board.push_back(row);
    }
  }
  return board;
}

// TODO: Write function to compare the f-value of two nodes here
bool Compare(vector<int> node1, vector<int> node2){
  int f1 = node1[2] + node1[3];
  int f2 = node2[2] + node2[3];
  return f1 > f2;
}

/**
 * Sort the two-dimensional vector of ints in descending order.
 */
void CellSort(vector<vector<int>> *v) {
  sort(v->begin(), v->end(), Compare);
}

// Calculate the manhattan distance
int Heuristic(int x1, int y1, int x2, int y2) {
  return abs(x2 - x1) + abs(y2 - y1);
}

// TODO: Write CheckValidCell here. Check that the 
// cell is on the grid and not an obstacle (i.e. equals kEmpty).
bool CheckValidCell(int x, int y, vector<vector<State>> &grid){
	if(x >= 0 && x < grid.size() && y >= 0 && y < grid[0].size() ) {
    	if (grid[x][y] == State::kEmpty) {
        	return true;
      }
    }
 	return false;
}

// TODO: Write the AddToOpen function here.
void AddToOpen(int x, int y, int g, int h, vector<vector<int>> &open_nodes, vector<vector<State>> &grid){
  vector<int> node{x, y, g, h};
  open_nodes.push_back(node);
  grid[x][y] = State::kClosed;
}

/** 
 * Expand current nodes's neighbors and add them to the open list.
 */
// TODO: ExpandNeighbors(arguments) {
void ExpandNeighbors(vector<int> &current, int goal[2], vector<vector<int>> &open_nodes, vector<vector<State>> &grid){
  // TODO: Get current node's data.
	int x = current[0], y = current[1], g = current[2];
  // TODO: Loop through current node's potential neighbors.
	for (const auto& d : delta){
    	int px = x + d[0], py = y + d[1];
      	// TODO: Check that the potential neighbor's x2 and y2 values are on the grid and not closed.
      	if(CheckValidCell(px, py, grid)){
        	// TODO: Increment g value, compute h value, and add neighbor to open list.
			AddToOpen(px, py, g + 1, Heuristic(px, py, goal[0], goal[1]), open_nodes, grid);
        }
    }
// } TODO: End the function
}

/** 
 * Implementation of A* search algorithm
 */
vector<vector<State>> Search(vector<vector<State>> grid, int init[2], int goal[2]) {
  // Create the vector of open nodes.
  vector<vector<int>> open {};
  
  // TODO: Initialize the starting node. 
  int ix = init[0], iy = init[1];
  int gx = goal[0], gy = goal[1];
  int g = 0;
  int h = Heuristic(ix, iy, gx, gy);  

  // TODO: Use AddToOpen to add the starting node to the open vector.
  AddToOpen(ix, iy, g, h, open, grid);

  // TODO: while open vector is non empty {
  while (open.size() > 0) {
    // TODO: Sort the open list using CellSort, and get the current node.
	  CellSort(&open); // decreasing order
    
    // TODO: Get the x and y values from the current node,
    // and set grid[x][y] to kPath.
    vector<int> node = open.back();
    open.pop_back(); // doesn't return removed element
	  int x = node[0], y = node[1];
    grid[x][y] = State::kPath;
    
    // TODO: Check if you've reached the goal. If so, return grid.
    if(x == goal[0] && y == goal[1]){
      // TODO: Set the init grid cell to kStart, and 
      grid[ix][iy] = State::kStart;
      // set the goal grid cell to kFinish before returning the grid. 
      grid[gx][gy] = State::kFinish;

    	return grid;
    }

    // If we're not done, expand search to current node's neighbors.
    ExpandNeighbors(node, goal, open, grid);
  }
    
  cout << "No path found!" << "\n";
  return std::vector<vector<State>>{};
}


string CellString(State cell) {
  switch(cell) {
    case State::kObstacle: return "⛰️   ";
    case State::kPath: return "🚗   ";
    // TODO: Add cases to return "🚦   " for kStart
    case State::kStart: return "🚦 ";
    // and "🏁   " for kFinish.
    case State::kFinish: return "🏁 ";
    default: return "0   "; 
  }
}


void PrintBoard(const vector<vector<State>> board) {
  for (int i = 0; i < board.size(); i++) {
    for (int j = 0; j < board[i].size(); j++) {
      cout << CellString(board[i][j]);
    }
    cout << "\n";
  }
}

#include "test.cpp"

int main() {
  int init[2]{0, 0};
  int goal[2]{4, 5};
  auto board = ReadBoardFile("1.board");
  auto solution = Search(board, init, goal);
  PrintBoard(solution);
  // Tests
  TestHeuristic();
  TestAddToOpen();
  TestCompare();
  TestSearch();
  TestCheckValidCell();
  TestExpandNeighbors();
}