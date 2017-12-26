#include "../tests/catch.hpp"
#include "cell.h"

#include <iostream>
#include <array>
#include <functional>
#include <utility>
#include <vector>
#include <cassert>

using namespace std;


//const int boardDimension = 2;
//const int boardSize = boardDimension*boardDimension;

void Cell::printCell() const
{
    cout << "id " << id_ << "[" << location_.first << ":" << location_.second << "}" << endl ;
}

void initAdjacentLocs( Cell & cell )
{
    cell.printCell();

    assert( cell.id_ != Cell::DEFAULT_CELL_ID );

    if ( cell.location_.first % ( boardDimension - 1 ) == 0 
            && cell.location_.second % ( boardDimension - 1 ) == 0 ) {

        cout << "Angle item" << endl;
    }
    else if ( cell.location_.first == 0 && cell.location_.second % ( boardDimension - 1 ) != 0 ) {

        cout << "Top Item" << endl;
    }
    else if ( cell.location_.first == ( boardDimension - 1 ) && cell.location_.second % ( boardDimension - 1 ) != 0 ) {

        cout << "Bottom Item" << endl;
    
    } else {
        cout << "Default " << endl;
    }

}

void initBoard( BoardType & board )
{
    for ( int i=0; i<boardDimension; ++i )
        for ( int j=0; j<boardDimension; ++j ) {

            board[i*boardDimension + j].location_.first = i;
            board[i*boardDimension + j].location_.second = j;

            board[i*boardDimension + j].id_ = i*boardDimension + j;
       }
}


int testCatch()
{
    return 33;
}
