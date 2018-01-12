#include "catch.hpp"
#include "../libbreaks/cell.h"

using namespace std;

//unsigned int Factorial( unsigned int number ) 
//{
//    return number <= 1 ? number : Factorial(number-1)*number;
//}
//
//TEST_CASE( "Factorials are computed", "[factorial]" ) 
//{
//    REQUIRE( Factorial(1) == 1 );
//    REQUIRE( Factorial(2) == 2 );
//    REQUIRE( Factorial(3) == 6 );
//    REQUIRE( Factorial(10) == 3628800 );
//}

TEST_CASE( "loc2Index index2Loc", "[cell]" ) 
{
    Board<> b;

    REQUIRE( b.index2Loc( 0 ) == pair<size_t,size_t>( 0, 0 ) );
    REQUIRE( b.loc2Index( 0, 0 ) == 0 );

    REQUIRE( b.index2Loc( 1 ) == pair<size_t,size_t>( 0, 1 ) );
    REQUIRE( b.loc2Index( 0, 1 ) == 1 );

    REQUIRE( b.index2Loc( 2 ) == pair<size_t,size_t>( 1, 0 ) );
    REQUIRE( b.loc2Index( 1, 0 ) == 2 );

    REQUIRE( b.index2Loc( 3 ) == pair<size_t,size_t>( 1, 1 ) );
    REQUIRE( b.loc2Index( 1, 1 ) == 3 );
}

TEST_CASE( "cellAt", "[cell]" )
{
    Board<> board;

    REQUIRE( board.cellAt(0,0).cellKind() == CellKind::TopLeft ) ;
    REQUIRE( board.cellAt(0,0).id() == board.cellAt(0).id() ) ;
    REQUIRE( 0 == board.cellAt(0).id() ) ;

    REQUIRE( board.cellAt(1,1).cellKind() == CellKind::BottomRight ) ;
    REQUIRE( board.cellAt(1,1).id() == board.cellAt(3).id() ) ;
    REQUIRE( 3 == board.cellAt(3).id() ) ;
}

TEST_CASE( "Cell adjacent locations init", "[cell]" )
{
    Cell<> cell;

    REQUIRE( cell.cellKind() == CellKind::Undefined );

    Board<> board;
    const Cell<> & cellRef = board.cells().at(0);
    REQUIRE( cellRef.cellKind() == CellKind::TopLeft );

    REQUIRE( cellRef.adjLocs().at(0).first == 0 );
    REQUIRE( cellRef.adjLocs().at(0).second == 1 );

    REQUIRE( cellRef.adjLocs().at(1).first == 1 );
    REQUIRE( cellRef.adjLocs().at(1).second == 0 );
}

TEST_CASE( "Cell adjacent locations init item 1", "[cell]" )
{

    Board<> board;
    const Cell<> & cellRef = board.cells().at(1);
    REQUIRE( cellRef.cellKind() == CellKind::TopRight );

    REQUIRE( cellRef.adjLocs().at(0).first == 0 );
    REQUIRE( cellRef.adjLocs().at(0).second == 0 );

    REQUIRE( cellRef.adjLocs().at(1).first == 1 );
    REQUIRE( cellRef.adjLocs().at(1).second == 1 );
}

TEST_CASE( "Cell adjacent locations init item 2", "[cell]" )
{

    Board<> board;
    const Cell<> & cellRef = board.cells().at(2);
    REQUIRE( cellRef.cellKind() == CellKind::BottomLeft );

    REQUIRE( cellRef.adjLocs().at(1).first == board.boardDimension() - 1 );
    REQUIRE( cellRef.adjLocs().at(1).second == 1 );

    REQUIRE( cellRef.adjLocs().at(0).first == board.boardDimension() - 2 );
    REQUIRE( cellRef.adjLocs().at(0).second == 0 );
}

TEST_CASE( "Cell adjacent locations init item 3", "[cell]" )
{

    Board<> board;
    const Cell<> & cellRef = board.cells().at(3);
    REQUIRE( cellRef.cellKind() == CellKind::BottomRight );

    REQUIRE( cellRef.adjLocs().at(1).first == board.boardDimension() - 1 );
    REQUIRE( cellRef.adjLocs().at(1).second == board.boardDimension() - 2 );

    REQUIRE( cellRef.adjLocs().at(0).first == board.boardDimension() - 2 );
    REQUIRE( cellRef.adjLocs().at(0).second == board.boardDimension() - 1 );
}

TEST_CASE( "Cell adjacent locations init dim 3 item 1", "[cell]" )
{

    Board<3> board;

    const Cell<3> & cellRef = board.cells().at(1);
    REQUIRE( cellRef.cellKind() == CellKind::Top);

    REQUIRE( cellRef.adjLocs().size() == 3 );

    REQUIRE( cellRef.adjLocs().at(0).first == 0 );
    REQUIRE( cellRef.adjLocs().at(0).second == 0 );

    REQUIRE( cellRef.adjLocs().at(1).first == 0 );
    REQUIRE( cellRef.adjLocs().at(1).second == 2 );

    REQUIRE( cellRef.adjLocs().at(2).first == 1 );
    REQUIRE( cellRef.adjLocs().at(2).second == 1 );
}

TEST_CASE( "Cell adjacent locations init dim 3 item 3", "[cell]" )
{

    Board<3> board;

    const Cell<3> & cellRef = board.cells().at(3);
    REQUIRE( cellRef.cellKind() == CellKind::Left);

    REQUIRE( cellRef.adjLocs().size() == 3 );

    REQUIRE( cellRef.adjLocs().at(0).first == 0 );
    REQUIRE( cellRef.adjLocs().at(0).second == 0 );

    REQUIRE( cellRef.adjLocs().at(1).first == 1 );
    REQUIRE( cellRef.adjLocs().at(1).second == 1 );

    REQUIRE( cellRef.adjLocs().at(2).first == 2 );
    REQUIRE( cellRef.adjLocs().at(2).second == 0 );
}

TEST_CASE( "Cell adjacent locations init dim 3 item 5", "[cell]" )
{

    Board<3> board;

    const Cell<3> & cellRef = board.cells().at(5);
    REQUIRE( cellRef.cellKind() == CellKind::Right);

    REQUIRE( cellRef.adjLocs().size() == 3 );

    REQUIRE( cellRef.adjLocs().at(0).first == 0 );
    REQUIRE( cellRef.adjLocs().at(0).second == 2 );

    REQUIRE( cellRef.adjLocs().at(1).first == 1 );
    REQUIRE( cellRef.adjLocs().at(1).second == 1 );

    REQUIRE( cellRef.adjLocs().at(2).first == 2 );
    REQUIRE( cellRef.adjLocs().at(2).second == 2 );
}

TEST_CASE( "Cell adjacent locations init dim 3 item 7", "[cell]" )
{

    Board<3> board;

    const Cell<3> & cellRef = board.cells().at(7);
    REQUIRE( cellRef.cellKind() == CellKind::Bottom);

    REQUIRE( cellRef.adjLocs().size() == 3 );

    REQUIRE( cellRef.adjLocs().at(0).first == 1 );
    REQUIRE( cellRef.adjLocs().at(0).second == 1 );

    REQUIRE( cellRef.adjLocs().at(1).first == 2 );
    REQUIRE( cellRef.adjLocs().at(1).second == 0 );

    REQUIRE( cellRef.adjLocs().at(2).first == 2 );
    REQUIRE( cellRef.adjLocs().at(2).second == 2 );
}

TEST_CASE( "Cell adjacent locations init dim 3 item 4", "[cell]" )
{

    Board<3> board;

    const Cell<3> & cellRef = board.cells().at(4);
    REQUIRE( cellRef.cellKind() == CellKind::Common);

    REQUIRE( cellRef.adjLocs().size() == 4 );

    REQUIRE( cellRef.adjLocs().at(0).first == 0 );
    REQUIRE( cellRef.adjLocs().at(0).second == 1 );

    REQUIRE( cellRef.adjLocs().at(1).first == 1 );
    REQUIRE( cellRef.adjLocs().at(1).second == 0 );

    REQUIRE( cellRef.adjLocs().at(2).first == 1 );
    REQUIRE( cellRef.adjLocs().at(2).second == 2 );

    REQUIRE( cellRef.adjLocs().at(3).first == 2 );
    REQUIRE( cellRef.adjLocs().at(3).second == 1 );
}


TEST_CASE( "Adjacent cells topology ", "[cell]" )
{
    Board<> board;

    {
        const Cell<> & cellRef = board.cells().at(0);

        const AdjacentCells<> & cells = cellRef.adjCells();
        REQUIRE( cells.at(0)->id() == 1 );
        REQUIRE( cells.at(1)->id() == 2 );
    }

    {
        const Cell<> & cellRef = board.cells().at(1);

        const AdjacentCells<> & cells = cellRef.adjCells();
        REQUIRE( cells.at(0)->id() == 0 );
        REQUIRE( cells.at(1)->id() == 3 );
    }

    {
        const Cell<> & cellRef = board.cells().at(2);

        const AdjacentCells<> & cells = cellRef.adjCells();
        REQUIRE( cells.at(0)->id() == 0 );
        REQUIRE( cells.at(1)->id() == 3 );
    }

    {
        const Cell<> & cellRef = board.cells().at(3);

        const AdjacentCells<> & cells = cellRef.adjCells();
        REQUIRE( cells.at(0)->id() == 1 );
        REQUIRE( cells.at(1)->id() == 2 );
    }
}

TEST_CASE( "Adjacent cells topology dim 3", "[cell]" )
{
    Board<3> board;

    {
        const Cell<3> & cellRef = board.cells().at(0);

        const AdjacentCells<3> & cells = cellRef.adjCells();
        REQUIRE( cells.at(0)->id() == 1 );
        REQUIRE( cells.at(1)->id() == 3 );
    }

    {
        const Cell<3> & cellRef = board.cells().at(1);

        const AdjacentCells<3> & cells = cellRef.adjCells();
        REQUIRE( cells.at(0)->id() == 0 );
        REQUIRE( cells.at(1)->id() == 2 );
        REQUIRE( cells.at(2)->id() == 4 );
    }

    {
        const Cell<3> & cellRef = board.cells().at(2);

        const AdjacentCells<3> & cells = cellRef.adjCells();
        REQUIRE( cells.at(0)->id() == 1 );
        REQUIRE( cells.at(1)->id() == 5 );
    }

    {
        const Cell<3> & cellRef = board.cells().at(3);

        const AdjacentCells<3> & cells = cellRef.adjCells();
        REQUIRE( cells.at(0)->id() == 0 );
        REQUIRE( cells.at(1)->id() == 4 );
        REQUIRE( cells.at(2)->id() == 6 );
    }

    {
        const Cell<3> & cellRef = board.cells().at(4);

        const AdjacentCells<3> & cells = cellRef.adjCells();
        REQUIRE( cells.at(0)->id() == 1 );
        REQUIRE( cells.at(1)->id() == 3 );
        REQUIRE( cells.at(2)->id() == 5 );
        REQUIRE( cells.at(3)->id() == 7 );
    }

    {
        const Cell<3> & cellRef = board.cells().at(5);

        const AdjacentCells<3> & cells = cellRef.adjCells();
        REQUIRE( cells.at(0)->id() == 2 );
        REQUIRE( cells.at(1)->id() == 4 );
        REQUIRE( cells.at(2)->id() == 8 );
    }

    {
        const Cell<3> & cellRef = board.cells().at(6);

        const AdjacentCells<3> & cells = cellRef.adjCells();
        REQUIRE( cells.at(0)->id() == 3 );
        REQUIRE( cells.at(1)->id() == 7 );
    }

    {
        const Cell<3> & cellRef = board.cells().at(7);

        const AdjacentCells<3> & cells = cellRef.adjCells();
        REQUIRE( cells.at(0)->id() == 4 );
        REQUIRE( cells.at(1)->id() == 6 );
        REQUIRE( cells.at(2)->id() == 8 );
    }

    {
        const Cell<3> & cellRef = board.cells().at(8);

        const AdjacentCells<3> & cells = cellRef.adjCells();
        REQUIRE( cells.at(0)->id() == 5 );
        REQUIRE( cells.at(1)->id() == 7 );
    }
}
