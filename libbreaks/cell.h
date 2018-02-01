#ifndef CELL_H_HEADER
#define CELL_H_HEADER

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
#include <map>
#include <memory>
#include <queue>
#include <sstream>

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

template <typename T1, size_t T2>
string array2string( const std::array<T1,T2>& a)
{
    ostringstream strstream;
    strstream << a;

    return strstream.str();
}

template <typename T1, size_t T2>
void fillArrayPtr( std::array<T1*,T2>& a)
{
    fill(a.begin(), a.end(), nullptr );
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
    friend class Board<T_BoardDimension>;

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

template <size_t T_BoardDimension >
class Turn;

template <size_t T_BoardDimension >
using TurnSPtr = shared_ptr< Turn<T_BoardDimension> >;

template <size_t T_BoardDimension = 2 >
using BoardTurns = map<string, TurnSPtr<T_BoardDimension> >;

template <size_t T_BoardDimension = 2 >
using ChildrenTurns = array<TurnSPtr<T_BoardDimension>, MAX_ADJACENT_CELLS_NUMBER>;

template <size_t T_BoardDimension = 2 >
class Turn
{
public:
    Turn( Board<T_BoardDimension> & board
        , const BoardValues<T_BoardDimension> & values = BoardValues<T_BoardDimension>()
        , const ChildrenTurns<T_BoardDimension> & childrenTurns = ChildrenTurns<T_BoardDimension>()
        , TurnSPtr<T_BoardDimension> parent = nullptr);

    Turn( Board<T_BoardDimension> & board
        , BoardValues<T_BoardDimension> && values
        , ChildrenTurns<T_BoardDimension> && childrenTurns = ChildrenTurns<T_BoardDimension>()
        , TurnSPtr<T_BoardDimension> parent = nullptr);

    void setChildrenTurns( const ChildrenTurns<T_BoardDimension> & childrenTurns )
        { m_children = childrenTurns; }

    void setChildrenTurns( const ChildrenTurns<T_BoardDimension> && childrenTurns )
        { move(m_children, childrenTurns); }

    void setChildrenValues( const BoardValues<T_BoardDimension> & boardValues )
        { m_instantValues = boardValues; }

    void setChildrenValues( BoardValues<T_BoardDimension> && boardValues )
        { move( m_instantValues, boardValues); }

    void setParent( const TurnSPtr<T_BoardDimension> & parent )
        { m_parent = parent; }

    void getParent( TurnSPtr<T_BoardDimension> & parent ) const
        { parent = m_parent; }

    bool hasParent() const
        { return m_parent.operator bool(); }

    bool visited() const { return m_visited; }
    void setVisited() { m_visited = true; }

    const BoardValues<T_BoardDimension> & values() const
        { return m_instantValues; }

    size_t id() const
        { return m_turnId; }

private:
    Board<T_BoardDimension> & m_board;
    BoardValues<T_BoardDimension> m_instantValues;

    TurnSPtr<T_BoardDimension> m_parent = nullptr;
    ChildrenTurns<T_BoardDimension> m_children;
    size_t m_turnId;
    static size_t m_counter;

    bool m_visited = false;
};

template <size_t T_BoardDimension >
size_t Turn<T_BoardDimension>::m_counter = 0;

template <size_t T_BoardDimension >
Turn<T_BoardDimension>::Turn( Board<T_BoardDimension> & board 
        , const BoardValues<T_BoardDimension> & values
        , const ChildrenTurns<T_BoardDimension> & childrenTurns
        , TurnSPtr<T_BoardDimension> parent )

    : m_board( board )
    , m_instantValues( values )
    , m_parent( parent )
    , m_children( childrenTurns )
    , m_turnId( m_counter++ )
{
}

//template <size_t T_BoardDimension >
//Turn<T_BoardDimension>::Turn( const Board<T_BoardDimension> & board , const BoardValues<T_BoardDimension> && values, Turn * parent );
//    : m_board( board )
//    , m_instantValues( values )
//    , m_parent( parent )
//    , m_turnId( ++m_counter )
//{
//}

template <size_t T_BoardDimension >
Turn<T_BoardDimension>::Turn( Board<T_BoardDimension> & board 
        , BoardValues<T_BoardDimension> && values
        , ChildrenTurns<T_BoardDimension> && childrenTurns
        , TurnSPtr<T_BoardDimension> parent )

    : Turn( board, values, childrenTurns, parent )
{
}

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
    const BoardValues<T_BoardDimension> & currentValues() const { return m_currentValues; }

    void setTurnsParent( const TurnSPtr<T_BoardDimension> & parent, ChildrenTurns<T_BoardDimension> & childrenTurns );

private:
    void initBoard();
    void genStartValues();
    void genFinalValues();
    void genChildrenValues( const BoardValues<T_BoardDimension> & values
        , vector<BoardValues<T_BoardDimension>> & childrenValues );
    void genChildrenTurns( const vector<BoardValues<T_BoardDimension>> & childrenValues
        , ChildrenTurns<T_BoardDimension> & childrenTurns );

    typename AdjacentCells<T_BoardDimension>::iterator m_currentAdjacentCell;
    typename BoardCells<T_BoardDimension>::iterator m_currentCell;

    bool currentAdjacentCellIsValid();

    void assignValues( const BoardValues<T_BoardDimension> & values );
    void resetCells( const BoardValues<T_BoardDimension> & values );
    void nextValuesOfBoard( BoardValues<T_BoardDimension> & values );
    void updateCurrentValues();

    void genTurnsTree();

    friend class Cell<T_BoardDimension>;
    friend class Turn<T_BoardDimension>;

    Cell<T_BoardDimension> * cell4Loc( const Location & loc ) { return &m_cells.data()[ loc2Index(loc) ]; }

    static const size_t m_boardDimension = T_BoardDimension;
    static constexpr const size_t m_boardSize = T_BoardDimension*T_BoardDimension;

    BoardCells<T_BoardDimension> m_cells;
    BoardValues<T_BoardDimension> m_startValues;
    BoardValues<T_BoardDimension> m_currentValues;
    BoardValues<T_BoardDimension> m_finalValues;

    size_t m_seed = 2;
    bool m_genNewSeed = false;

    BoardTurns<T_BoardDimension> m_turns;
    queue< pair<TurnSPtr<T_BoardDimension>, BoardValues<T_BoardDimension> > > m_turnsGenQueue;

public:
    const BoardCells<T_BoardDimension> & cells() const { return m_cells; }
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
    genTurnsTree();
    
}

template <size_t T_BoardDimension>
void Board<T_BoardDimension>::setTurnsParent( const TurnSPtr<T_BoardDimension> & parent
        , ChildrenTurns<T_BoardDimension> & childrenTurns  )
{

    for( auto & turn : childrenTurns ) {
        if ( not turn ) break;

        if ( not turn->hasParent() )
            turn->setParent( parent );
    }
}

template <size_t T_BoardDimension>
Cell<T_BoardDimension>::Cell( Board<T_BoardDimension> * board )
    :m_board( board )
{
    fillArrayPtr( m_adjacentCells );
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

template <size_t T_BoardDimension >
void Board<T_BoardDimension>::assignValues( const BoardValues<T_BoardDimension> & values )
{
    typename BoardCells<T_BoardDimension>::iterator iter = m_cells.begin();

    for( const auto & v : values ) {
        assert( iter != m_cells.end() );

        iter->setValue( v );
        ++iter;
    }

}

template <size_t T_BoardDimension >
void Board<T_BoardDimension>::resetCells( const BoardValues<T_BoardDimension> & values )
{
    assignValues( values );
    m_currentCell = find_if( m_cells.begin(), m_cells.end()
            , []( const auto & c)
        {
           return c.m_value == 0; 
        }
    );

    assert( m_currentCell != m_cells.end() );

    m_currentAdjacentCell = m_currentCell->m_adjacentCells.begin();

    //debug
    //while( (*m_currentAdjacentCell) != nullptr and m_currentAdjacentCell != m_currentCell->m_adjacentCells.end() ) {

    //    assert( (*m_currentAdjacentCell) != nullptr );
    //    cout << "resetCells id : " << (*m_currentAdjacentCell)->m_id << "  val : " << (*m_currentAdjacentCell)->m_value << endl;
    //    ++m_currentAdjacentCell;
    //}

    m_currentAdjacentCell = m_currentCell->m_adjacentCells.begin();

    assert( currentAdjacentCellIsValid() );
}

template <size_t T_BoardDimension >
bool Board<T_BoardDimension>::currentAdjacentCellIsValid()
{
    return (*m_currentAdjacentCell) != nullptr && m_currentAdjacentCell != m_currentCell->m_adjacentCells.end();
}

template <size_t T_BoardDimension >
void Board<T_BoardDimension>::nextValuesOfBoard( BoardValues<T_BoardDimension> & values )
{
    assert( m_currentCell != m_cells.end() );
    assert( currentAdjacentCellIsValid() );

    //cout << m_currentCell->m_value << endl;
    //cout << endl << "id : " << m_currentCell->m_id << " val : " << m_currentCell->m_value << endl;
    //cout << "adjCell id : " << (*m_currentAdjacentCell)->m_id << " val : " << (*m_currentAdjacentCell)->m_value << endl;

    Cell<T_BoardDimension> * currentAdjacentCell = *m_currentAdjacentCell;
    swap( m_currentCell->m_value, currentAdjacentCell->m_value ); //SEGFAULT

    updateCurrentValues();

    values = m_currentValues;

    //updateCurrentValues();

    swap( m_currentCell->m_value, currentAdjacentCell->m_value );

    ++m_currentAdjacentCell;

}

template <size_t T_BoardDimension >
void Board<T_BoardDimension>::updateCurrentValues()
{
    std::transform( m_cells.cbegin(), m_cells.cend(), m_currentValues.begin()
        , [] ( const auto & c )
        {
            return c.m_value;
        }
    );
}

template <size_t T_BoardDimension >
void Board<T_BoardDimension>::genTurnsTree()
{
    cout << endl << "genTurnsTree started" << endl;
    //TurnSPtr<T_BoardDimension> turn1( new Turn<T_BoardDimension>( *this, m_startValues ) );

    cout << "finalValues : " << m_finalValues << endl;

    auto pairIt = m_turns.insert( make_pair( array2string( m_startValues )
        , make_shared<Turn<T_BoardDimension>>( *this, m_startValues ) ) );

    assert( pairIt.second );

    m_turnsGenQueue.emplace( pairIt.first->second, m_startValues );

    while( not m_turnsGenQueue.empty() ) {

        if ( m_turnsGenQueue.front().second != m_finalValues
                and not m_turnsGenQueue.front().first->visited() ) {

            vector<BoardValues<T_BoardDimension>> childrenValues;


            genChildrenValues( m_turnsGenQueue.front().second, childrenValues );

            ChildrenTurns<T_BoardDimension> childrenTurns;
            genChildrenTurns( childrenValues, childrenTurns );


            auto frontTurn = m_turnsGenQueue.front().first;
            frontTurn->setVisited();
            frontTurn->setChildrenTurns( childrenTurns );

            setTurnsParent( frontTurn, childrenTurns );

            //m_turnsGenQueue.pop();

            auto vIter = childrenValues.begin();
            for( auto & ct : childrenTurns ) {

                if ( not ct ) break;

                //cout << "queue emplace : " << *vIter << endl;
                m_turnsGenQueue.emplace( ct, *vIter );
                vIter = next( vIter );
            }
        } //if
        else {
            cout << "final or visited :  id : "
                << m_turnsGenQueue.front().first->id()
                << "  , values : "
                << m_turnsGenQueue.front().first->values() << endl;
        } //if

        cout << "queue size : " << m_turnsGenQueue.size() << endl;
        m_turnsGenQueue.pop();

    } //while

    cout << "genTurnsTree stoped" << endl;
}

template <size_t T_BoardDimension >
void Board<T_BoardDimension>::genChildrenValues( const BoardValues<T_BoardDimension> & values
        , vector<BoardValues<T_BoardDimension>> & childrenValues )
{
    //cout << endl <<  "genChildrenValues started" << endl;

    assert( childrenValues.empty() );
    resetCells( values );

    cout << endl << endl  << values << endl << endl;

    BoardValues<T_BoardDimension> nextValues;

    while( currentAdjacentCellIsValid() ) {
        nextValuesOfBoard( nextValues );
        cout << nextValues << endl;

        childrenValues.push_back( nextValues );
    }

    //cout << "genChildrenValues stoped" << endl;
}

template <size_t T_BoardDimension >
void Board<T_BoardDimension>::genChildrenTurns( const vector<BoardValues<T_BoardDimension>> & childrenValues
        , ChildrenTurns<T_BoardDimension> & childrenTurns )
{
    //cout << endl << "genChildrenTurns started  childrenValues.size :" << childrenValues.size() << endl;

    //Turn T0( m_startValues );
    //ChildrenValues cv = genChildrenValues( T0 );
    //ChildrenTurns ct = genChildrenTurns( cv );


    //TurnSPtr<T_BoardDimension> turn1( new Turn<T_BoardDimension>( *this, m_startValues ) );

    typename ChildrenTurns<T_BoardDimension>::iterator iter = childrenTurns.begin();
    for( const auto & cv : childrenValues ) {

        //cout << "distance : " << distance( childrenTurns.begin(), iter ) << endl;
        assert( distance( childrenTurns.begin(), iter ) <= childrenValues.size() ); //remove excessive ?

        //if ( *iter ) {
        //    cout << "ptr is initialled : use count " << iter->use_count() << endl;
        //} else {
        //    cout << "ptr is NOT initialized " << iter->use_count() << endl;
        //}

        auto cvItem = m_turns.find( array2string( cv ) );
        if(  cvItem == m_turns.end() ) {

            auto pairIt = m_turns.insert( make_pair( array2string( cv )
                        , make_shared<Turn<T_BoardDimension>>( *this, cv ) ) );
            assert( pairIt.second );

            ( *iter ) = ( pairIt.first->second );

        } else {
            ( *iter ) = ( cvItem->second );
        }

        //if ( *iter ) {
        //    cout << "ptr is initialled : use count " << iter->use_count() << endl;
        //} else {
        //    cout << "ptr is NOT initialized " << iter->use_count() << endl;
        //}
        //cout << endl;


        ++iter;
    }

    //cout << "genChildrenTurns stoped" << endl;
}

#endif //CELL_H_HEADER
