#include <iostream>
#include <array>
#include <functional>
#include <utility>
#include <vector>
#include <cassert>
#include <memory>
#include <algorithm>

using namespace std;

using Location = pair<size_t, size_t>; //y,x row,column
Location make_location( size_t i, size_t j );

using AdjacentLocs = vector<Location>;

enum class CellKind { Undefined, TopLeft, TopRight, BottomRight, BottomLeft
    , Left, Top, Right, Bottom, Common };

class TestsTool
{
};

template <size_t T_BoardDimension >
class Board;

template <size_t T_BoardDimension = 2>
class Cell
{

public:
    Cell( Board<T_BoardDimension> * board = nullptr );

    void printCell() const;
    const Board<T_BoardDimension> & board() const;
    void setBoard( Board<T_BoardDimension> * board );
    size_t id() const;
    void setId( size_t );

    static const size_t DEFAULT_CELL_ID = -1;

    CellKind cellKind() const;
    void setCellKind( CellKind cellKind );

    Location location() const;
    void setLocation( const Location & location );

private:

    size_t m_id = DEFAULT_CELL_ID ;

    Location m_location;

    AdjacentLocs m_adjacentLocs;

    CellKind m_cellKind = CellKind::Undefined;

    Board< T_BoardDimension > * m_board = nullptr;

    friend class TestsTool;
};

template <size_t T_BoardDimension = 2>
class Board
{

public:
    Board();

    size_t boardDimension() const { return m_boardDimension; }
    size_t boardSize() const { return m_boardSize; }

    Location index2Loc( size_t i ) const { return make_location( i / m_boardDimension , i % m_boardDimension ); }
    size_t loc2Index( size_t i, size_t j ) const { return m_boardDimension * i  + j; }

    const Cell<T_BoardDimension> & cellAt( size_t i ) const { return m_cells.at( i ); }
    const Cell<T_BoardDimension> & cellAt( size_t i, size_t j ) const { return m_cells.at( loc2Index( i, j ) ); }

private:
    void initBoard();

    static const size_t m_boardDimension = T_BoardDimension;
    static const size_t m_boardSize = T_BoardDimension*T_BoardDimension;

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

template <size_t T_BoardDimension = 2>
void initAdjacentLocs( Cell<T_BoardDimension> & cell );

template <size_t T_BoardDimension>
Board<T_BoardDimension>::Board()
{
    //debug
    for_each( m_cells.cbegin(), m_cells.cend(), []( const Cell<T_BoardDimension> & c ) { c.printCell(); } );

    initBoard();
    for_each( m_cells.cbegin(), m_cells.cend(), []( const Cell<T_BoardDimension> & c ) { c.printCell(); } );
}

template <size_t T_BoardDimension>
void Board<T_BoardDimension>::initBoard()
{

    for ( size_t i=0; i<m_boardDimension; ++i )
        for ( size_t j=0; j<m_boardDimension; ++j ) {

            size_t index = i*m_boardDimension + j;
            Cell<T_BoardDimension> & current = m_cells[index] ;

            current.setLocation( make_pair(i,j) );
            current.setId( index );
            current.setBoard( this );

            initAdjacentLocs( current );
       }
}

template <size_t T_BoardDimension>
Cell<T_BoardDimension>::Cell( Board<T_BoardDimension> * board )
    :m_board( board )
{
}

template <size_t T_BoardDimension>
const Board<T_BoardDimension> & Cell<T_BoardDimension>::board() const
{
    return *m_board;
}

template <size_t T_BoardDimension>
void Cell<T_BoardDimension>::printCell() const
{
    cout << "id " << m_id << "[" << m_location.first << ":" << m_location.second << "] "
        << cellKind2String( cellKind() ) << endl;
}

template <size_t T_BoardDimension>
size_t Cell<T_BoardDimension>::id() const
{
    return m_id;
}

template <size_t T_BoardDimension>
void Cell<T_BoardDimension>::setId( size_t id )
{
    m_id = id;
}

template <size_t T_BoardDimension>
CellKind Cell<T_BoardDimension>::cellKind() const
{
    return m_cellKind;
}

template <size_t T_BoardDimension>
void Cell<T_BoardDimension>::setCellKind( CellKind cellKind )
{
    m_cellKind = cellKind;
}

template <size_t T_BoardDimension>
Location Cell<T_BoardDimension>::location() const
{
    return m_location;
}

template <size_t T_BoardDimension>
void Cell<T_BoardDimension>::setLocation( const Location & location )
{
    m_location = location;
}
template <size_t T_BoardDimension>
void Cell<T_BoardDimension>::setBoard( Board<T_BoardDimension> * board )
{
    m_board = board;
}

template <size_t T_BoardDimension>
void initAdjacentLocs( Cell<T_BoardDimension> & cell )
{
    const size_t boardDimension = cell.board().boardDimension();
    cell.printCell();

    assert( cell.id() != Cell<T_BoardDimension>::DEFAULT_CELL_ID );
    assert( cell.cellKind() == CellKind::Undefined );

    Location location = cell.location();

    if ( location.first == 0 and location.second == 0 ) {

        cell.setCellKind( CellKind::TopLeft );
    }
    else if ( location.first == 0 and location.second == boardDimension -1 ) {

        cell.setCellKind( CellKind::TopRight );
    }
    else if ( location.first == boardDimension -1 and location.second == 0 ) {

        cell.setCellKind( CellKind::BottomLeft );
    }
    else if ( location.first == boardDimension -1 and location.second == boardDimension -1 ) {

        cell.setCellKind( CellKind::BottomRight );
    }
    else if ( location.first == 0 ) {

        cell.setCellKind( CellKind::Top );
    }
    else if ( location.first == boardDimension -1 ) {

        cell.setCellKind( CellKind::Bottom );
    }
    else if ( location.second  == 0 ) {

        cell.setCellKind( CellKind::Left );
    }
    else if ( location.second == boardDimension - 1 ) {

        cell.setCellKind( CellKind::Right );
    }
    else {
        cell.setCellKind( CellKind::Common );
    }

}


