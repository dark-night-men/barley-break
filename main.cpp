
//Initialization of large arrays
//Initialization of arrays as a member
//Default array initialization
//
//auto & ref in for
//inclass member initialization
//integer_sequence 

#include <iostream>
#include <array>
#include <functional>
#include <utility>
#include <vector>
#include <cassert>

using namespace std;


const int boardDimention = 2;
const int boardSize = boardDimention*boardDimention;

typedef pair<int, int> Location; //x,y

struct Cell
{
    //Cell( int id = DEFAULT_CELL_ID ) : id_( id ) {}

    void printCell() const;

    int id_ = DEFAULT_CELL_ID ;

    Location location_;

    typedef vector<Location> adjacentLocs_;
    static const int DEFAULT_CELL_ID = -1;
};

void Cell::printCell() const
{
    cout << "id " << id_ << "[" << location_.first << ":" << location_.second << "}" << endl ;
}

//template <typename T>
//void printCont( T& c )
//{
//    for ( const auto & x : c ) cout << x.get().id_ << endl;
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

typedef array< Cell, boardSize > BoardType;

void initAdjacentLocs( Cell & cell )
{
    assert( cell.id_ != Cell::DEFAULT_CELL_ID );

    for ( int i=0; i<2; ++i ) {
        for ( jnt j=0; j<2; ++j ) {
            if ( cell.id_ == 

        }
    }
}

void initBoard( BoardType & board )
{
    for ( int i=0; i<boardDimention; ++i )
        for ( int j=0; j<boardDimention; ++j ) {

            board[i*boardDimention + j].location_.first = i;
            board[i*boardDimention + j].location_.second = j;


            board[i*boardDimention + j].id_ = i*boardDimention + j;
        }
}

int main()
{
    //array <Cell, boardSize> cells = { Cell(1), Cell(2), Cell(4) };
    //array <Cell, boardSize> cells = {};
    BoardType cells = {};
    initBoard( cells );

    //array <reference_wrapper<Cell>, boardSize> cellsRefs
    array <reference_wrapper<Cell>, boardSize> cellsRefs
        = { cells[0], cells[1], cells[2], cells[3] };

    cout << "Hello " << endl;
    cout << "boardSize = " << boardSize << endl;

    //for ( cells : x ) cout << x.id_ << endl;
    //for ( x : cells ) cout << x.id_ << endl;
    printCont( cellsRefs );

    cellsRefs[2].get().id_ = 22;

    printCont( cells );
}
