#include "maze.hh"
#include <cstdlib>   // needed for srand() and rand() functions
#include <ctime>     // needed for time() function

using namespace std;

void addDirectionOption(const Maze &maze, const Location &current,
                        Direction dir, vector<Direction> &v){
    Location loc = maze.getNeighborCell(current.getRow(), current.getCol(), dir);
    if (maze.getCell(loc.getRow(), loc.getCol()) != MazeCell::VISITED)
    {
        v.push_back(dir);
    }
}

void usage(string error){
    cerr << error << endl;
}

int main(int argc, char** argv){
    if (argc > 3) {
        usage("Too many arguments");
        return 1; // Indicate there was an issue
    }

    int rows = (int) atoi(argv[1]);
    int cols = (int) atoi(argv[2]);
    if (rows < 0 || cols < 0) {
        usage("One or more of the arguments to tsp-ga was an invalid value");
        return 1; // Indicate there was an issue
    }
    Maze maze = Maze(rows, cols);
    vector<Location> path;

    srand(time(NULL));

    maze.clear();
    maze.setAllWalls();
    maze.setStart(0, 0);
    maze.setEnd(maze.getNumRows() - 1, maze.getNumCols() - 1);
    maze.setVisited(0, 0);
    path.push_back(maze.getStart());

    vector<Direction> options;

    while(path.empty() != true){
        Location current = path.back();

        // If the cell we are looking at is the end of the maze, skip the
        // cell so that the current path will not go through the end-point.
        if (current == maze.getEnd())
        {
            path.pop_back();
            continue;
        }

        options.clear();

        if (current.row > 0){  // I can move up a row
            addDirectionOption(maze, current, Direction::NORTH, options);
        }
        if (current.col < maze.getNumCols() - 1){  // I can move East
            addDirectionOption(maze, current, Direction::EAST, options);
        }
        if (current.row < maze.getNumRows() - 1){ // I can move down a row
            addDirectionOption(maze, current, Direction::SOUTH, options);
        }
        if (current.col > 0){ // I can move West
            addDirectionOption(maze, current, Direction::WEST, options);
        }
        if (options.empty())
        {
            path.pop_back();
            continue;
        }

        int index = rand() % options.size();

        Direction dir = options[index];

        maze.clearWall(current.getRow(), current.getCol(), dir);

        Location next = maze.getNeighborCell(current.getRow(), current.getCol(), dir);

        maze.setVisited(next.getRow(), next.getCol());

        path.push_back(next);
    }

    maze.print(cout);
    
    return 0;
}