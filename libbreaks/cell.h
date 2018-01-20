#include <iostream>
#include <array>
#include <functional>
#include <utility>
#include <vector>
#include <cassert>
#include <memory>
#include <algorithm>
#include <random>
#include <assert.h>

using namespace std;

using Location = pair<size_t, size_t>; //y,x row,column

template <typename T1, typename T2>
std::ostream& operator << (std::ostream& strm, const std::pair<T1,T2>& p)
{
    return strm << "[" << p.first << "," << p.second << "]";
}

template <typename T1, size_t T2>
std::ostream& operator << (std::ostream& strm, const std::array<T1,T2>& a)
{
    bool cs = false;
    for( const auto & v : a ) {
        if ( cs ) {
            strm << ", ";
        }

        strm << v ;
        cs = true;
    }

    return strm;
}


using AdjacentLocs = vector<Location>;


enum class CellKind { Undefined, TopLeft, TopRight, BottomRight, BottomLeft
    , Left, Top, Right, Bottom, Common };

template <size_t T_BoardDimension >
class Board;

template <size_t T_BoardDimension >
class Cell;

const size_t MAX_ADJACENT_CELLS_NUMBER = 4;
template <size_t T_BoardDimension = 2>
using AdjacentCells = array<Cell<T_BoardDimension>*, MAX_ADJACENT_CELLS_NUMBER> ;

template <size_t T_BoardDimension = 2>
using BoardCells = array<Cell<T_BoardDimension>, Board<T_BoardDimension>::boardSize() >;

template <size_t T_BoardDimension = 2>
using BoardValues = array<size_t, Board<T_BoardDimension>::boardSize() >;

template <size_t T_BoardDimension = 2>
class Cell
{

public:
    Cell( Board<T_BoardDimension> * board = nullptr );
    void init( size_t index, Board<T_BoardDimension> * board );

    void printCell() const;
    const Board<T_BoardDimension> & board() const;
    void setBoard( Board<T_BoardDimension> * board );
    size_t id() const;
    void setId( size_t );

    static const size_t DEFAULT_CELL_ID ;

    CellKind cellKind() const;
    void setCellKind( CellKind cellKind );

    Location location() const;
    void setLocation( const Location & location );

    const AdjacentLocs & adjLocs() const { return m_adjacentLocs; }
    const AdjacentCells<T_BoardDimension> & adjCells() const { return m_adjacentCells; }

    size_t value() const { return m_value; }
    void setValue( size_t v ) { m_value = v; }

private:
    void initAdjacentLocs();
    void initAdjacentCells();

    size_t m_id = DEFAULT_CELL_ID ;

    Location m_location;

    AdjacentLocs m_adjacentLocs;

    CellKind m_cellKind = CellKind::Undefined;

    Board< T_BoardDimension > * m_board = nullptr;

    AdjacentCells<T_BoardDimension> m_adjacentCells;

    size_t m_value = DEFAULT_CELL_ID;
};

template <size_t T_BoardDimension>
const size_t Cell<T_BoardDimension>::DEFAULT_CELL_ID = -1;

template <size_t T_BoardDimension = 2>
class Board
{
public:
    Board( size_t seed = 2, bool genNewSeed = false );

    static constexpr size_t boardDimension() { return m_boardDimension; }
    static constexpr size_t boardSize() { return m_boardSize; }

    Location index2Loc( size_t i ) const { return make_pair( i / m_boardDimension , i % m_boardDimension ); }
    size_t loc2Index( size_t i, size_t j ) const { return m_boardDimension * i  + j; }
    size_t loc2Index( const Location & loc ) const { return m_boardDimension * loc.first  + loc.second; }

    const Cell<T_BoardDimension> & cellAt( size_t i ) const { return m_cells.at( i ); }
    const Cell<T_BoardDimension> & cellAt( size_t i, size_t j ) const { return m_cells.at( loc2Index( i, j ) ); }

    const BoardValues<T_BoardDimension> & finalValues() const { return m_finalValues; }
    const BoardValues<T_BoardDimension> & startValues() const { return m_startValues; }

private:
    void initBoard();
    void genStartValues();
    void genFinalValues();

    friend class Cell<T_BoardDimension>;

    Cell<T_BoardDimension> * cell4Loc( const Location & loc ) { return &m_cells.data()[ loc2Index(loc) ]; }

    static const size_t m_boardDimension = T_BoardDimension;
    static constexpr const size_t m_boardSize = T_BoardDimension*T_BoardDimension;

    BoardCells<T_BoardDimension> m_cells;
    BoardValues<T_BoardDimension> m_startValues;
    BoardValues<T_BoardDimension> m_currentValues;
    BoardValues<T_BoardDimension> m_finalValues;

    size_t m_seed = 2;
    bool m_genNewSeed = false;

public:
    const BoardCells<T_BoardDimension> & cells() const { return m_cells; }
};

template <size_t T_BoardDimension = 2 >
class Turn
{
    array<size_t, Board<T_BoardDimension>::boardSize()> m_cellsState;
    const Board<T_BoardDimension> & m_board;
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

template <size_t T_BoardDimension>
Board<T_BoardDimension>::Board( size_t seed, bool genNewSeed )
    : m_seed( seed )
    , m_genNewSeed( genNewSeed )
{
    //debug
    //for_each( m_cells.cbegin(), m_cells.cend(), []( const auto & c ) { c.printCell(); } );

    initBoard();
    //for_each( m_cells.cbegin(), m_cells.cend(), []( const auto & c ) { c.printCell(); } );
}

template <size_t T_BoardDimension>
void Board<T_BoardDimension>::initBoard()
{
    size_t i = 0; //use iterator diff instead 
    //TODO change for -> for_each
    for( auto & cell : m_cells ) {
        cell.init( i, this );
        ++i;
    }

    genFinalValues();
    genStartValues();
}

template <size_t T_BoardDimension>
Cell<T_BoardDimension>::Cell( Board<T_BoardDimension> * board )
    :m_board( board )
{
}

template <size_t T_BoardDimension>
void Cell<T_BoardDimension>::init( size_t index, Board<T_BoardDimension> * board )
{
    setId( index );
    setBoard( board );
    setLocation( board->index2Loc( index ) );
    initAdjacentLocs();
    initAdjacentCells();
}

template <size_t T_BoardDimension>
const Board<T_BoardDimension> & Cell<T_BoardDimension>::board() const
{
    return *m_board;
}

template <size_t T_BoardDimension>
void Cell<T_BoardDimension>::printCell() const
{
    cout << "id " << m_id << " " << m_location << " " << cellKind2String( cellKind() ) << endl;
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
void Cell<T_BoardDimension>::initAdjacentCells()
{

    size_t i {0};
    for_each( m_adjacentLocs.cbegin(), m_adjacentLocs.cend()
            , [ this, &i ] (const Location & l) 
            {
                m_adjacentCells[ i++ ] = m_board->cell4Loc( l );
            }
    );
}

template <size_t T_BoardDimension>
void Cell<T_BoardDimension>::initAdjacentLocs()
{
    //printCell();

    assert( id() != Cell<T_BoardDimension>::DEFAULT_CELL_ID );
    assert( cellKind() == CellKind::Undefined );
    assert( m_board != nullptr );

    size_t boardDimension = m_board->boardDimension();

    if ( m_location.first == 0 and m_location.second == 0 ) {

        setCellKind( CellKind::TopLeft );
        m_adjacentLocs.push_back( make_pair( m_location.first, m_location.second + 1 ) );
        m_adjacentLocs.push_back( make_pair( m_location.first + 1, m_location.second ) );
    }
    else if ( m_location.first == 0 and m_location.second == boardDimension -1 ) {

        setCellKind( CellKind::TopRight );
        m_adjacentLocs.push_back( make_pair( m_location.first, m_location.second - 1 ) );
        m_adjacentLocs.push_back( make_pair( m_location.first + 1, m_location.second ) );
    }
    else if ( m_location.first == boardDimension -1 and m_location.second == 0 ) {

        setCellKind( CellKind::BottomLeft );
        m_adjacentLocs.push_back( make_pair( m_location.first - 1, m_location.second ) );
        m_adjacentLocs.push_back( make_pair( m_location.first , m_location.second + 1 ) );
    }
    else if ( m_location.first == boardDimension -1 and m_location.second == boardDimension -1 ) {

        setCellKind( CellKind::BottomRight );
        m_adjacentLocs.push_back( make_pair( m_location.first - 1, m_location.second ) );
        m_adjacentLocs.push_back( make_pair( m_location.first , m_location.second - 1 ) );
    }
    else if ( m_location.first == 0 ) {

        setCellKind( CellKind::Top );
        m_adjacentLocs.push_back( make_pair( m_location.first , m_location.second - 1 ) );
        m_adjacentLocs.push_back( make_pair( m_location.first , m_location.second + 1 ) );
        m_adjacentLocs.push_back( make_pair( m_location.first + 1, m_location.second ) );
    }
    else if ( m_location.first == boardDimension -1 ) {

        setCellKind( CellKind::Bottom );

        m_adjacentLocs.push_back( make_pair( m_location.first - 1 , m_location.second ) );
        m_adjacentLocs.push_back( make_pair( m_location.first , m_location.second - 1 ) );
        m_adjacentLocs.push_back( make_pair( m_location.first , m_location.second + 1 ) );
    }
    else if ( m_location.second  == 0 ) {

        setCellKind( CellKind::Left );

        m_adjacentLocs.push_back( make_pair( m_location.first - 1, m_location.second ) );
        m_adjacentLocs.push_back( make_pair( m_location.first , m_location.second + 1 ) );
        m_adjacentLocs.push_back( make_pair( m_location.first + 1, m_location.second ) );
    }
    else if ( m_location.second == boardDimension - 1 ) {

        setCellKind( CellKind::Right );

        m_adjacentLocs.push_back( make_pair( m_location.first - 1, m_location.second ) );
        m_adjacentLocs.push_back( make_pair( m_location.first , m_location.second - 1 ) );
        m_adjacentLocs.push_back( make_pair( m_location.first + 1, m_location.second ) );
    }
    else {
        setCellKind( CellKind::Common );

        m_adjacentLocs.push_back( make_pair( m_location.first - 1 , m_location.second ) );
        m_adjacentLocs.push_back( make_pair( m_location.first , m_location.second - 1 ) );
        m_adjacentLocs.push_back( make_pair( m_location.first , m_location.second + 1 ) );
        m_adjacentLocs.push_back( make_pair( m_location.first + 1, m_location.second ) );
    }
}


template <size_t T_BoardDimension>
void Board<T_BoardDimension>::genFinalValues()
{
    int c = 0;
    //TODO check more compact version
    generate_n ( m_finalValues.begin(), boardSize()
        , [&c]( )
        {
            return c++;
        }
    );      

    //cout << m_finalValues << endl;
}

template <size_t T_BoardDimension>
void Board<T_BoardDimension>::genStartValues()
{
    if ( m_genNewSeed ) {
        random_device seeder;
        m_seed = seeder.entropy() ? seeder() : time(nullptr);
    }

    default_random_engine generator(
            static_cast<default_random_engine::result_type>( m_seed ));
            //static_cast<default_random_engine::result_type>( m_seed ));

    m_startValues = m_finalValues;
    shuffle( m_startValues.begin(), m_startValues.end(), generator );
}
