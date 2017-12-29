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

Location make_location( size_t i, size_t j ) { return make_pair( i, j ); }

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
