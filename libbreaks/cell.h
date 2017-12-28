#include <iostream>
#include <array>
#include <functional>
#include <utility>
#include <vector>
#include <cassert>
#include <memory>
#include <algorithm>

using namespace std;

using Location = pair<int, int>; //y,x row,column

using AdjacentLocs = vector<Location>;

enum class CellKind { Undefined, TopLeft, TopRight, BottomRight, BottomLeft
    , Left, Top, Right, Bottom, Common };

template <int T_BoardDimension >
class Board;

template <int T_BoardDimension = 2>
class Cell
{

public:
    Cell( Board<T_BoardDimension> * board = nullptr );

    void printCell() const;
    const Board<T_BoardDimension> & board() const;
    void setBoard( Board<T_BoardDimension> * board );
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

    Board< T_BoardDimension > * m_board = nullptr;
};

template <int T_BoardDimension = 2>
class Board
{

public:
    Board();

    int boardDimension() const { return m_boardDimension; }
    int boardSize() const { return m_boardSize; }

private:
    void initBoard();

    static const int m_boardDimension = T_BoardDimension;
    static const int m_boardSize = T_BoardDimension*T_BoardDimension;

    array<Cell<T_BoardDimension>, m_boardSize> m_cells;
};

string cellKind2String( CellKind cellKind );


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

template <int T_BoardDimension = 2>
void initAdjacentLocs( Cell<T_BoardDimension> & cell );

int testCatch();

template <int T_BoardDimension>
Board<T_BoardDimension>::Board()
{
    //debug
    for_each( m_cells.cbegin(), m_cells.cend(), []( const Cell<T_BoardDimension> & c ) { c.printCell(); } );

    initBoard();
    for_each( m_cells.cbegin(), m_cells.cend(), []( const Cell<T_BoardDimension> & c ) { c.printCell(); } );
}

template <int T_BoardDimension>
void Board<T_BoardDimension>::initBoard()
{

    for ( int i=0; i<m_boardDimension; ++i )
        for ( int j=0; j<m_boardDimension; ++j ) {

            int index = i*m_boardDimension + j;
            Cell<T_BoardDimension> & current = m_cells[index] ;

            current.setLocation( make_pair(i,j) );
            current.setId( index );
            current.setBoard( this );

            initAdjacentLocs( current );
       }
}

template <int T_BoardDimension>
Cell<T_BoardDimension>::Cell( Board<T_BoardDimension> * board )
    :m_board( board )
{
}

template <int T_BoardDimension>
const Board<T_BoardDimension> & Cell<T_BoardDimension>::board() const
{
    return *m_board;
}

template <int T_BoardDimension>
void Cell<T_BoardDimension>::printCell() const
{
    cout << "id " << m_id << "[" << m_location.first << ":" << m_location.second << "]" << endl ;
}

template <int T_BoardDimension>
int Cell<T_BoardDimension>::id() const
{
    return m_id;
}

template <int T_BoardDimension>
void Cell<T_BoardDimension>::setId( int id )
{
    m_id = id;
}

template <int T_BoardDimension>
CellKind Cell<T_BoardDimension>::cellKind() const
{
    return m_cellKind;
}

template <int T_BoardDimension>
void Cell<T_BoardDimension>::setCellKind( CellKind cellKind )
{
    m_cellKind = cellKind;
}

template <int T_BoardDimension>
Location Cell<T_BoardDimension>::location() const
{
    return m_location;
}

template <int T_BoardDimension>
void Cell<T_BoardDimension>::setLocation( const Location & location )
{
    m_location = location;
}
template <int T_BoardDimension>
void Cell<T_BoardDimension>::setBoard( Board<T_BoardDimension> * board )
{
    m_board = board;
}

template <int T_BoardDimension>
void initAdjacentLocs( Cell<T_BoardDimension> & cell )
{
    const int boardDimension = cell.board().boardDimension();
    cell.printCell();

    assert( cell.id() != Cell<T_BoardDimension>::DEFAULT_CELL_ID );
    assert( cell.cellKind() == CellKind::Undefined );

    if ( cell.location().first == 0 and cell.location().second == 0 ) {

        cell.setCellKind( CellKind::TopLeft );
    }
    else if ( cell.location().first == 0 and cell.location().second == boardDimension -1 ) {

        cell.setCellKind( CellKind::TopRight );
    }
    else if ( cell.location().first == boardDimension -1 and cell.location().second == 0 ) {

        cell.setCellKind( CellKind::BottomLeft );
    }
    else if ( cell.location().first == boardDimension -1 and cell.location().second == boardDimension -1 ) {

        cell.setCellKind( CellKind::BottomRight );
    }
    else if ( cell.location().first == 0 ) {

        cell.setCellKind( CellKind::Top );
    }
    else if ( cell.location().first == boardDimension -1 ) {

        cell.setCellKind( CellKind::Bottom );
    }
    else if ( cell.location().second  == 0 ) {

        cell.setCellKind( CellKind::Left );
    }
    if ( cell.location().second == boardDimension - 1 ) {

        cell.setCellKind( CellKind::Right );
    }
    else {
        cell.setCellKind( CellKind::Common );
    }

    cout << cellKind2String(cell.cellKind()) << " item" << endl;

}


