#include "../tests/catch.hpp"
#include "cell.h"

#include <iostream>
#include <array>
#include <functional>
#include <utility>
#include <vector>
#include <cassert>
#include <algorithm>

using namespace std;


//const int boardDimension = 2;
//const int boardSize = boardDimension*boardDimension;
//template <int T_BoardDimnsion>
//Board::Board()
//    : Board( m_boardDimension )
//{
//}
//
//template <int T_BoardDimnsion>
//Board::Board( int dimension )
//    : m_boardDimension( dimension )
//    , m_boardSize( m_boardDimension*m_boardDimension )
//{
//    initBoard();
//}

template <int T_BoardDimnsion>
void Board<T_BoardDimnsion>::initBoard()
{

    //fill_n( m_cells.begin(), boardSize(), Cell( *this ));

    //for ( int i=0; i<m_boardDimension; ++i )
    //    for ( int j=0; j<m_boardDimension; ++j ) {

    //        m_cells[i*m_boardDimension + j].setLocation( make_pair(i,j) );
    //        m_cells[i*m_boardDimension + j].setId( i*m_boardDimension + j );
    //   }
}

//Cell::Cell( Board & board )
//    :m_board( board )
//{
//}

template <int T_BoardDimnsion>
const Board<T_BoardDimnsion> & Cell<T_BoardDimnsion>::board() const
{
    return m_board;
}

template <int T_BoardDimnsion>
void Cell<T_BoardDimnsion>::printCell() const
{
    cout << "id " << m_id << "[" << m_location.first << ":" << m_location.second << "}" << endl ;
}

template <int T_BoardDimnsion>
int Cell<T_BoardDimnsion>::id() const
{
    return m_id;
}

template <int T_BoardDimnsion>
void Cell<T_BoardDimnsion>::setId( int id )
{
    m_id = id;
}

template <int T_BoardDimnsion>
CellKind Cell<T_BoardDimnsion>::cellKind() const
{
    return m_cellKind;
}

template <int T_BoardDimnsion>
void Cell<T_BoardDimnsion>::setCellKind( CellKind cellKind )
{
    m_cellKind = cellKind;
}

template <int T_BoardDimnsion>
Location Cell<T_BoardDimnsion>::location() const
{
    return m_location;
}

template <int T_BoardDimnsion>
void Cell<T_BoardDimnsion>::setLocation( const Location & location )
{
    m_location = location;
}

template <int T_BoardDimnsion>
void initAdjacentLocs( Cell<T_BoardDimnsion> & cell )
{
    const int boardDimension = cell.board().boardDimension();
    cell.printCell();

    assert( cell.id() != Cell<T_BoardDimnsion>::DEFAULT_CELL_ID );
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

int testCatch()
{
    return 33;
}

string cellKind2String( CellKind cellKind )
{
    string result;

    switch ( cellKind )
    {
        case CellKind::Undefined : result = "Undefined" ;
             break;
        case CellKind::TopLeft : result = "TopLeft" ;
             break;
        case CellKind::TopRight : result = "TopRight" ;
             break;
        case CellKind::BottomLeft : result = "BottomLeft" ;
             break;
        case CellKind::BottomRight : result = "BottomRight" ;
             break;
        case CellKind::Left : result = "Left" ;
             break;
        case CellKind::Top : result = "Top" ;
             break;
        case CellKind::Bottom : result = "Bottom" ;
             break;
        case CellKind::Right : result = "Right" ;
             break;
        case CellKind::Common : result = "Common" ;
             break;
        default :
            assert( 0 );
    }

    return result;
}
