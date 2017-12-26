#include <iostream>
#include <array>
#include <functional>
#include <utility>
#include <vector>
#include <cassert>

using namespace std;


const int boardDimension = 2;
const int boardSize = boardDimension*boardDimension;

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

void initAdjacentLocs( Cell & cell );
void initBoard( BoardType & board );

int testCatch();
