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
    //Cell( int id = DEFAULT_CELL_ID ) : m_id( id ) {}

    void printCell() const;

    int m_id = DEFAULT_CELL_ID ;

    Location m_location;

    typedef vector<Location> m_adjacentLocs;
    static const int DEFAULT_CELL_ID = -1;

    enum class CellKind { Undefined, Angle, Border, Common };
    CellKind m_cellKind = CellKind::Undefined;

};

string cellKind2String( Cell::CellKind cellKind );


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

typedef array< Cell, boardSize > BoardType;

void initAdjacentLocs( Cell & cell );
void initBoard( BoardType & board );

int testCatch();
