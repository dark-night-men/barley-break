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
    Cell cell;

    REQUIRE( cell.m_cellKind == Cell::CellKind::Undefined );
}

TEST_CASE( "Translate CellKind enum to string", "[cell]" )
{
    Cell::CellKind cellKind;

    REQUIRE( cellKind2String( cellKind ) == "Undefined" );

    cellKind = Cell::CellKind::Angle;
    REQUIRE( cellKind2String( cellKind ) == "Angle" );

    cellKind = Cell::CellKind::Border;
    REQUIRE( cellKind2String( cellKind ) == "Border" );
    
    cellKind = Cell::CellKind::Common;
    REQUIRE( cellKind2String( cellKind ) == "Common" );
}

