#include <iostream>
#include <array>
#include <functional>

struct Cell
{
    Cell( int id = -1 ) : id_( id ) {}

    int id_ ;
    int x_;
    int y_;
};

using namespace std;

//Initialization of large arrays
//Initialization of arrays as a member
//Default array initialization
//
//auto & ref in for

const int boardDimention = 2;
const int boardSize = boardDimention*boardDimention;

//template <typename T>
//void printCont( T& c )
//{
//    for ( const auto & x : c ) cout << x.get().id_ << endl;
//    cout << "..." << endl;
//}

template <typename T,long unsigned int N>
void printCont( array<T,N>& c )
{
    for ( const auto & x : c ) {
        cout << x.id_ << "[" << x.x_ << ":" << x.y_ << "]" << endl;
    }
    cout << "..." << endl;
}

template <typename T,long unsigned int N>
void printCont( array<reference_wrapper<T>,N>& c )
{
    for ( const auto & x : c ) cout << x.get().id_ << endl;
    cout << "..." << endl;
}

typedef array< Cell, boardSize > BoardType;

void initBoard( BoardType & board )
{
    for ( int i=0; i<boardDimention; ++i )
        for ( int j=0; j<boardDimention; ++j ) {

            board[i*boardDimention + j].x_ = i;
            board[i*boardDimention + j].y_ = j;
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
