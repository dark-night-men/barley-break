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

TEST_CASE( "Testing catch", "[catch test]" ) 
{
    REQUIRE( testCatch() == 1 );
}

TEST_CASE( "Cell adjacent locations init", "[cell]" )
{
    Board<> localBoard;
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

