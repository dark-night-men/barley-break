#include <iostream>
#include <array>
#include <functional>
#include <utility>
#include <vector>
#include <cassert>

using namespace std;


//const int boardDimension = 2;
//const int boardSize = boardDimension*boardDimension;

//typedef pair<int, int> Location; //y,x row,column
using Location = pair<int, int>; //y,x row,column

using AdjacentLocs = vector<Location>;

enum class CellKind { Undefined, TopLeft, TopRight, BottomRight, BottomLeft
    , Left, Top, Right, Bottom, Common };

class Board;
class Cell
{

public:
    Cell( Board & board );

    void printCell() const;
    const Board & board() const;
    int id() const;
    void setId( int );

    static const int DEFAULT_CELL_ID = -1;

    CellKind cellKind() const;
    void setCellKind( CellKind cellKind );

    Location location() const;
    void setLocation( const Location & location );

private:

    int m_id = DEFAULT_CELL_ID ;

    Location m_location;

    AdjacentLocs m_adjacentLocs;

    CellKind m_cellKind = CellKind::Undefined;

    reference_wrapper<Board> m_board;
};

class Board
{

public:
    Board();
    Board( int dimension );

    int boardDimension() const { return m_boardDimension; }
    int boardSize() const { return m_boardSize; }

private:
    void initBoard();

    int m_boardDimension = 2;
    int m_boardSize = -1;

    vector<Cell> m_cells;
};

string cellKind2String( CellKind cellKind );


//template <typename T>
//void printCont( T& c )
//{
//    for ( const auto & x : c ) cout << x.get().m_id << endl;
//    cout << "..." << endl;
//}

template <typename T,long unsigned int N>
void printCont( array<T,N>& c )
{
    for ( const auto & x : c ) x.printCell();
    cout << "..." << endl;
}

template <typename T,long unsigned int N>
void printCont( array<reference_wrapper<T>,N>& c )
{
    for ( const auto & x : c ) x.get().printCell() ;
    cout << "..." << endl;
}

void initAdjacentLocs( Cell & cell );

int testCatch();
