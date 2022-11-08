/*
 * Maze Generator:
 *   Made by Jaden Peterson in 2016
 */

 /*
  * This program is free software: you can redistribute it and/or modify
  * it under the terms of the GNU General Public License as published by
  * the Free Software Foundation, either version 3 of the License, or
  * (at your option) any later version.
  *
  * This program is distributed in the hope that it will be useful,
  * but WITHOUT ANY WARRANTY; without even the implied warranty of
  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  * GNU General Public License for more details.
  *
  * You should have received a copy of the GNU General Public License
  * along with this program.  If not, see <http://www.gnu.org/licenses/>.
  */

  /*
   * This program uses the Direct-First Search algorithm
   *   You can learn more about it at:
   *     https://en.wikipedia.org/wiki/Maze_generation_algorithm#Depth-first_search
   */

#ifndef MAZE_H
#define MAZE_H

#define UP    0
#define DOWN  1
#define LEFT  2
#define RIGHT 3


#include <cctype>
#include <cstring>
#include <iostream>
#include "vector.h"
#include <time.h>

class Maze
{
	int maze_size[2];

	int start_axis;
	int start_side;

	vector< vector< int > > dfs_path;

	/*
	 * Structure of the maze vector:
	 *                     |--> Filled in?
	 *   Row --> Column --|
	 *                     |--> Has been visited?
	 */
	vector< vector< vector< bool > > > maze;

	public:
	Maze(int height, int width) {
		srand(static_cast<int>(time(0)));
		maze_size[0] = height;
		maze_size[1] = width;

		// The width and height must be greater than or equal to 5 or it won't work
		// The width and height must be odd or else we will have extra walls
		for (int a = 0; a < 2; a++) {
			if (maze_size[a] < 5) {
				maze_size[a] = 5;
			}
			else if (maze_size[a] % 2 == 0) {
				maze_size[a]--;
			}
		}

		initializeMaze();
		randomPoint(false);
		randomPoint(true);
		generateMaze();

		//printMaze();
	}

	// Select a random direction based on our options, append it to the current path, and move there
	bool randomMove(bool first_move) {
		int random_neighbor;
		vector< vector< int > > unvisited_neighbors;

		for (int direction = 0; direction < 4; direction++) {
			int possible_pmd[2] = { 0, 0 };

			if (direction == UP) {
				possible_pmd[1] = -1;
			}
			else if (direction == DOWN) {
				possible_pmd[1] = 1;
			}
			else if (direction == LEFT) {
				possible_pmd[0] = -1;
			}
			else {
				possible_pmd[0] = 1;
			}

			if (dfs_path.back()[0] + possible_pmd[0] * 2 > 0 &&
				dfs_path.back()[0] + possible_pmd[0] * 2 < maze_size[0] - 1 &&
				dfs_path.back()[1] + possible_pmd[1] * 2 > 0 &&
				dfs_path.back()[1] + possible_pmd[1] * 2 < maze_size[1] - 1) {
				if (!maze[dfs_path.back()[1] + possible_pmd[1] * 2]
					[dfs_path.back()[0] + possible_pmd[0] * 2][1]) {
                    vector< int > possible_move_delta;
                    possible_move_delta.push_back(possible_pmd[0]);
                    possible_move_delta.push_back(possible_pmd[1]);

					unvisited_neighbors.push_back(possible_move_delta);
				}
			}
		}

		if (unvisited_neighbors.size() > 0) {
			random_neighbor = rand() % unvisited_neighbors.size();

			for (int a = 0; a < !first_move + 1; a++) {
				vector< int > new_location;

				new_location.push_back(dfs_path.back()[0] + unvisited_neighbors[random_neighbor][0]);
				new_location.push_back(dfs_path.back()[1] + unvisited_neighbors[random_neighbor][1]);

				dfs_path.push_back(new_location);

				maze[dfs_path.back()[1]][dfs_path.back()[0]][0] = false;
				maze[dfs_path.back()[1]][dfs_path.back()[0]][1] = true;
			}

			return true;
		}
		else {
			return false;
		}
	}

	bool validInteger(char* cstr) {
        std::string str(cstr);

		for (char& c : str) {
			if (!isdigit(c)) {
				return false;
			}
		}

		return true;
	}
	// The fun part ;)
	void generateMaze() {
		bool first_move = true;
		bool success = true;

		while ((int)dfs_path.size() > 1 - first_move) {
			if (!success) {
				dfs_path.pop_back();

				if (!first_move && dfs_path.size() > 2) {
					dfs_path.pop_back();
				}
				else {
					break;
				}

				success = true;
			}

			while (success) {
				success = randomMove(first_move);

				if (first_move) {
					first_move = false;
				}
			}
		}
	}

	// Initialize the maze vector with a completely-filled grid with the size the user specified
	void initializeMaze() {
		for (int a = 0; a < maze_size[1]; a++) {
			for (int b = 0; b < maze_size[0]; b++) {
				bool is_border;

				if (a == 0 || a == maze_size[1] - 1 ||
					b == 0 || b == maze_size[0] - 1) {
					is_border = true;
				}
				else {
					is_border = false;
				}

                vector< bool > new_cell;
                
                new_cell.push_back(true);
                new_cell.push_back(is_border);
                
                vector< vector<bool> > new_row;
                new_row.push_back(new_cell);


//				if ((unsigned int)a + 1 > maze.size()) {
//                    vector< vector<bool> > new_row;
//                    new_row.push_back(new_cell);
//
//					maze.push_back(new_row);
//				}
//				else {
//					maze[a].push_back(new_cell);
//				}
			}
		}
	}

	void parseArgs(int argc, char* argv[]) {
		bool width_found = false;
		bool height_found = false;
		int processing_number = -1;

		for (int arg = 1; arg < argc; arg++) {
			if (processing_number > -1) {
				if (validInteger(argv[arg])) {
					maze_size[processing_number] = atoi(argv[arg]);

					processing_number = -1;
				}
				else {
                    std::cerr << "'" << argv[arg] << "'" << " is not a valid integer." << std::endl;
					exit(1);
				}
			}
			else {
				if (!strcmp(argv[arg], "-w")) {
					processing_number = 0;
					width_found = true;
				}
				else if (!strcmp(argv[arg], "-h")) {
					processing_number = 1;
					height_found = true;
				}
				else {
                    std::cerr << "'" << argv[arg] << "'" << " is not a valid argument." << std::endl;
					exit(1);
				}
			}
		}

		if (!width_found || !height_found) {
            std::cerr << "You must specify the width and height with '-w' and '-h'" << std::endl;
			exit(1);
		}
	}

	void printMaze() {
		for (unsigned int a = 0; a < maze.size(); a++) {
			for (unsigned int b = 0; b < maze[a].size(); b++) {
				if (maze[a][b][0]) {
                    std::cout << "X";//(unsigned char)(219);
				}
				else {
                    std::cout << "  ";
				}
			}

            std::cout << std::endl;
		}
	}

	vector< vector< bool > > getMap() {
		long height = maze.size();
		long width = maze[0].size();
        vector<vector<bool>> map;
        map.resize(height);
		for (unsigned int a = 0; a < maze.size(); a++) {
            vector<bool> new_row;
            new_row.resize(width);
            map.push_back(new_row);
			for (unsigned int b = 0; b < maze[a].size(); b++) {
				map[a][b] = maze[a][b][0];
			}
		}
		return map;
	}
	
	vector< vector< int > > getStartEnd(){
        vector<int> start;
        start.push_back(0);
        start.push_back(0);
        vector<int> end;
        end.push_back(0);
        end.push_back(0);
		
		
		for (unsigned int a = 0; a < maze.size(); a++) {
			
			for (unsigned int b = 0; b < maze[a].size(); b++) {
				if((b != 0) && (b + 1 != maze[a].size()) && (a != 0) && (a + 1 != maze.size())){
					continue;
				}
				
				bool isBlack = !maze[a][b][0];
				if(isBlack){
					if(start[0] == 0 && start[1] == 0){
						start[0] = a;
						start[1] = b;
					}
					else{
						end[0] = a;
						end[1] = b;
					}
				}
			}
		}
        maze[start[0]][start[1]][0]=true;
        maze[end[0]][end[1]][0]=true;
        vector<vector<int>> toReturn;
        toReturn.push_back(start);
        toReturn.push_back(end);
		return toReturn;
	}

	// Set a random point (start or end)
	void randomPoint(bool part) {
		int axis = 0;
		int side = 0;

		if (!part) {
			axis = rand() % 2;
			side = rand() % 2;

			start_axis = axis;
			start_side = side;
		}
		else {
			bool done = false;

			while (!done) {
				axis = rand() % 2;
				side = rand() % 2;

				if (axis != start_axis ||
					side != start_side) {
					done = true;
				}
			}
		}

        vector< int > location;
        location.push_back(0);
        location.push_back(0);

		if (!side) {
			location[!axis] = 0;
		}
		else {
			location[!axis] = maze_size[!axis] - 1;
		}

		location[axis] = 2 * (rand() % ((maze_size[axis] + 1) / 2 - 2)) + 1;

		if (!part) {
			dfs_path.push_back(location);
		}

		maze[location[1]][location[0]][0] = false;
		maze[location[1]][location[0]][1] = true;
	}
};

#endif
