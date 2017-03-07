#include "maze.hh"
#include <assert.h>

int Location::getRow() const{
    return row;
}

int Location::getCol() const{
    return col;
}

// Constructor
// Initialize a new maze of size rows x cols
Maze::Maze(int rows, int cols){
    // The number of rows with cells in them
    numRows        = rows;

    // The number of columns with cells in them
    numCols        = cols;

    int insertRows = 2 * numRows + 1;
    int insertCols = 2 * numCols + 1;

    // The maze's "expanded representation"
    cells          = new MazeCell[insertRows * insertCols];

    // The start of the maze, in cell coordinates
    start          = Location(); // initializes the start location to 0, 0

    // The end of the maze, in cell coordinates
    end            = Location(); /* initializes the end location to 0, 0, 
                                   * we will set this later
                                   */
}
/* I am still not quite understanding exactly how the copy is supposed to work.
 * I thought that I followed the lecture slides pretty thouroughly, but
 * I am still getting a seg fault when testing the code.
 */
// Make a copy of an existing maze object
Maze::Maze(const Maze &m){
    numRows = m.numRows;
    numCols = m.numCols;
    start   = m.start;
    end     = m.end;
    int length = (2 * numRows + 1) * (2 * numCols + 1);
    cells = new MazeCell[length];
    for (int i = 0; i < length; i++)
    {
        cells[i] = m.cells[i];
    }
}

// Maze destructor
Maze::~Maze(){
    delete[] cells;
}

// Maze assignment operator
Maze & Maze::operator=(const Maze &m){
    if (this != &m)
    {
        delete[] cells;
        numRows = m.numRows;
        numCols = m.numCols;
        start   = m.start;
        end     = m.end;
        int length = (2 * numRows + 1) * (2 * numCols + 1);
        cells = new MazeCell[length];
        for (int i = 0; i < length; i++)
        {
            cells[i] = m.cells[i];
        }
    }
    return *this;
}

int Maze::getArrayIndex(const Location &loc) const{
    int row, col, index;
    row = loc.getRow();
    col = loc.getCol();
    index = (2 * row + 1) * (2 * getNumCols() + 1) + (2 * col + 1);
    return index;
}

Location Maze::getCellArrayCoord(int cellRow, int cellCol) const{
    int row = 2 * cellRow + 1;
    int col = 2 * cellCol + 1;
    return Location(row, col);
}

Location Maze::getWallArrayCoord(int cellRow, int cellCol,
                             Direction direction) const{
    int row = 2 * cellRow + 1;
    int col = 2 * cellCol + 1;
    switch (direction){
        case (Direction::NORTH):
            row--;
        case (Direction::SOUTH):
            row++;
        case (Direction::EAST):
            col++;
        case (Direction::WEST):
            col--;
    }
    return Location(row, col);
}



// Returns the number of rows in the maze
int Maze::getNumRows() const{
    return numRows;
}
    
// Returns the number of columns in the maze
int Maze::getNumCols() const{
    return numCols;
}

// Returns the starting point in the maze
Location Maze::getStart() const{
    return start;
}

// Sets the starting point in the maze
void Maze::setStart(int row, int col){
    start = Location(row,col);
}

// Returns the ending point in the maze 
Location Maze::getEnd() const{
    return end;
}

// Sets the ending point in the maze
void Maze::setEnd(int row, int col){
    end = Location(row,col);
}

// Sets all cells and walls to be empty, so that the maze is
// completely cleared
void Maze::clear(){
    int length = (2 * numRows + 1) * (2 * numCols + 1);
    for (int i = 0; i < length; i++)
    {
        cells[i] = MazeCell::EMPTY;
    }
}

/* So here, something is wrong with this function, but I'm not really sure
 * what exactly it is. Nearly all of my current problems have to do with the
 * walls; I'm not sure if that is a coincidence or not.
 */
// Places a wall at every location that can be a wall in the maze
void Maze::setAllWalls(){
    for (int i = 0; i < numRows; i++)
    {
        for (int j = 0; j < numCols; j++)
        {
            setWall(i, j, Direction::NORTH);
            setWall(i, j, Direction::SOUTH);
            setWall(i, j, Direction::EAST);
            setWall(i, j, Direction::WEST);
        }
    }
}

// Returns the value of the specified
MazeCell Maze::getCell(int cellRow, int cellCol) const{
    return cells[(2 * cellRow + 1) * (2 * numCols + 1) + (2 * cellCol + 1)];
}

void Maze::setCell(int cellRow, int cellCol, MazeCell val){
    cells[(2 * cellRow + 1) * (2 * numCols + 1) + (2 * cellCol + 1)] = val;
}

Location Maze::getNeighborCell(int cellRow, int cellCol,
                             Direction direction) const{
    Location loc;
    switch(direction){
        case Direction::NORTH:
            assert (cellRow >= 0);
            loc = Location(cellRow - 1, cellCol);
            break;
        case Direction::EAST:
            assert (cellCol < numCols + 1);
            loc = Location(cellRow, cellCol + 1);
            break;
        case Direction::SOUTH:
            assert (cellRow < numRows + 1);
            loc = Location(cellRow + 1, cellCol);
            break;
        case Direction::WEST:
            assert (cellCol >= 0);
            loc = Location(cellRow, cellCol - 1);
            break;
        default:
            cerr << "Invalid direction" << endl;
    }
    return loc;
}

/* Both this function and the following one are the ones giving me
 * the most trouble besides the constructor copy. I realize that this
 * is probably not the most elegant method of finding the expanded coordinates,
 * but it was the easiest for me to understand at first and I didnt deviate
 * after that.
 */
bool Maze::hasWall(int cellRow, int cellCol, Direction direction) const{
        int newRow;
        int newCol;
    switch(direction){
        case Direction::NORTH:
            assert (cellRow >= 0);
            newRow = 2 * cellRow + 1;
            newCol = 2 * cellCol + 1;
            if (cells[(newRow - 1) * (2 * numCols + 1) + newCol]
                == MazeCell::WALL){
                return true;
            }
            else return false;
            break;
        case Direction::EAST:
            assert (cellCol < numCols + 1);
            newRow = 2 * cellRow + 1;
            newCol = 2 * cellCol + 1;
            if (cells[newRow * (2 * numCols + 1) + (newCol + 1)]
                == MazeCell::WALL){
                return true;
            }
            else return false;
            break;
        case Direction::SOUTH:
            assert (cellRow < numRows + 1);
            newRow = 2 * cellRow + 1;
            newCol = 2 * cellCol + 1;
            if (cells[(newRow + 1) * (2 * numCols + 1) + newCol]
                == MazeCell::WALL){
                return true;
            }
            else return false;
            break;
        case Direction::WEST:
            assert (cellCol >= 0);
            newRow = 2 * cellRow + 1;
            newCol = 2 * cellCol + 1;
            if (cells[newRow * (2 * numCols + 1) + (newCol - 1)]
                == MazeCell::WALL){
                return true;
            }
            else return false;
            break;
        default:
            cerr << "Invalid direction" << endl;
            return false;
    }
}

void Maze::setWall(int cellRow, int cellCol, Direction direction){
    switch(direction){
        int newRow;
        int newCol;
        case Direction::NORTH:
            assert (cellRow >= 0);
            newRow = 2 * cellRow + 1;
            newCol = 2 * cellCol + 1;
            cells[(newRow - 1) * (2 * numCols + 1) + newCol] = MazeCell::WALL;
            break;
        case Direction::EAST:
            assert (cellCol < numCols + 1);
            newRow = 2 * cellRow + 1;
            newCol = 2 * cellCol + 1;
            cells[newRow * (2 * numCols + 1) + (newCol + 1)] = MazeCell::WALL;
            break;
        case Direction::SOUTH:
            assert (cellRow < numRows + 1);
            newRow = 2 * cellRow + 1;
            newCol = 2 * cellCol + 1;
            cells[(newRow + 1) * (2 * numCols + 1) + newCol] = MazeCell::WALL;
            break;
        case Direction::WEST:
            assert (cellCol >= 0);
            newRow = 2 * cellRow + 1;
            newCol = 2 * cellCol + 1;
            cells[newRow * (2 * numCols + 1) + (newCol - 1)] = MazeCell::WALL;
            break;
        default:
            cerr << "Invalid direction" << endl;
    }
}

void Maze::clearWall(int cellRow, int cellCol, Direction direction){
    switch(direction){
        int newRow;
        int newCol;
        case Direction::NORTH:
            assert (cellRow >= 0);
            newRow = 2 * cellRow + 1;
            newCol = 2 * cellCol + 1;
            cells[(newRow - 1) * (2 * numCols + 1) + newCol] = MazeCell::EMPTY;
            break;
        case Direction::EAST:
            newRow = 2 * cellRow + 1;
            newCol = 2 * cellCol + 1;
            assert (cellCol < 2 * numCols + 1);
            cells[newRow * (2 * numCols + 1) + newCol + 1] = MazeCell::EMPTY;
            break;
        case Direction::SOUTH:
            newRow = 2 * cellRow + 1;
            newCol = 2 * cellCol + 1;
            assert (cellRow < 2 * numRows + 1);
            cells[(newRow + 1) * (2 * numCols + 1) + newCol] = MazeCell::EMPTY;
            break;
        case Direction::WEST:
            newRow = 2 * cellRow + 1;
            newCol = 2 * cellCol + 1;
            assert (cellCol >= 0);
            cells[newRow * (2 * numCols + 1) + (newCol - 1)] = MazeCell::EMPTY;
            break;
        default:
            cerr << "Invalid direction" << endl;
    }
}

bool Maze::isVisited(int cellRow, int cellCol) const{
    return (cells[(2 * cellRow + 1) * (2 * numCols + 1) + (2 * cellCol + 1)] == MazeCell::VISITED);
}

// Changes the cell's value to VISITED
void Maze::setVisited(int cellRow, int cellCol){
    cells[(2 * cellRow + 1) * (2 * numCols + 1) + (2 * cellCol + 1)] = MazeCell::VISITED;
}

void Maze::print(ostream &os) const{
    os << numRows << " " << numCols << endl;
    os << "+";
    for (int k = 0; k < numCols; k++)
    {
        os << "---+";
    }
    os << endl;

    for (int l = 0; l < numRows; l++)
    {
        os << "|";
        for (int m = 0; m < numCols; m++)
        {
            Location loc = Location(l, m);
            if (loc == getStart())
                os << " S ";
            else if (loc == getEnd())
            {
                os << " E ";
            }
            else
            {
                os << "   ";
            }
            if (hasWall(l, m, Direction::EAST))
            {
                os << "|";
            }
            else {
                os << " ";
            }
        }
        os << endl;
        os << "+";
        for (int k = 0; k < numCols; k++)
        {
            if (hasWall(l, k, Direction::SOUTH))
            {
                os << "---+";
            }
            else{
                os << "   +";
            }
        }
        os << endl;
    }
}