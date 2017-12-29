#include "catch.hpp"
#include "../libbreaks/cell.h"

unsigned int Factorial( unsigned int number ) 
{
    return number <= 1 ? number : Factorial(number-1)*number;
}

TEST_CASE( "Factorials are computed", "[factorial]" ) 
{
    REQUIRE( Factorial(1) == 1 );
    REQUIRE( Factorial(2) == 2 );
    REQUIRE( Factorial(3) == 6 );
    REQUIRE( Factorial(10) == 3628800 );
}

TEST_CASE( "loc2Index index2Loc", "[cell]" ) 
{
    Board<> b;

    REQUIRE( b.index2Loc( 0 ) == make_location( 0, 0 ) );
    REQUIRE( b.loc2Index( 0, 0 ) == 0 );

    REQUIRE( b.index2Loc( 1 ) == make_location( 0, 1 ) );
    REQUIRE( b.loc2Index( 0, 1 ) == 1 );

    REQUIRE( b.index2Loc( 2 ) == make_location( 1, 0 ) );
    REQUIRE( b.loc2Index( 1, 0 ) == 2 );

    REQUIRE( b.index2Loc( 3 ) == make_location( 1, 1 ) );
    REQUIRE( b.loc2Index( 1, 1 ) == 3 );
}

TEST_CASE( "cellAt", "[cell]" )
{
    Board<> board;

    REQUIRE( board.cellAt(0,0).cellKind() == CellKind::TopLeft ) ;
    REQUIRE( board.cellAt(0,0).id() == board.cellAt(0).id() ) ;
    REQUIRE( 0 == board.cellAt(0).id() ) ;
}

TEST_CASE( "Cell adjacent locations init", "[cell]" )
{
    Board<> board;
    Cell<> cell;

    REQUIRE( cell.cellKind() == CellKind::Undefined );
}

//TEST_CASE( "Translate CellKind enum to string", "[cell]" )
//{
//    CellKind cellKind;
//
//    REQUIRE( cellKind2String( cellKind ) == "Undefined" );
//
//    cellKind = CellKind::Angle;
//    REQUIRE( cellKind2String( cellKind ) == "Angle" );
//
//    cellKind = CellKind::Border;
//    REQUIRE( cellKind2String( cellKind ) == "Border" );
//    
//    cellKind = CellKind::Common;
//    REQUIRE( cellKind2String( cellKind ) == "Common" );
//}

