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
    cout << "id " << m_id << "[" << m_location.first << ":" << m_location.second << "}" << endl ;
}

void initAdjacentLocs( Cell & cell )
{
    cell.printCell();

    assert( cell.m_id != Cell::DEFAULT_CELL_ID );

    if ( cell.m_location.first % ( boardDimension - 1 ) == 0 
            && cell.m_location.second % ( boardDimension - 1 ) == 0 ) {

        cout << "Angle item" << endl;
    }
    else if ( cell.m_location.first == 0 && cell.m_location.second % ( boardDimension - 1 ) != 0 ) {

        cout << "Top Item" << endl;
    }
    else if ( cell.m_location.first == ( boardDimension - 1 ) && cell.m_location.second % ( boardDimension - 1 ) != 0 ) {

        cout << "Bottom Item" << endl;
    
    } else {
        cout << "Default " << endl;
    }

}

void initBoard( BoardType & board )
{
    for ( int i=0; i<boardDimension; ++i )
        for ( int j=0; j<boardDimension; ++j ) {

            board[i*boardDimension + j].m_location.first = i;
            board[i*boardDimension + j].m_location.second = j;

            board[i*boardDimension + j].m_id = i*boardDimension + j;
       }
}


int testCatch()
{
    return 33;
}
