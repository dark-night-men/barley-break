
//Initialization of large arrays
//Initialization of arrays as a member
//Default array initialization
//
//auto & ref in for
//inclass member initialization
//integer_sequence 

#include "../tests/catch.hpp"
#include "../libbreaks/cell.h"

#include <iostream>
#include <array>
#include <functional>
#include <utility>
#include <vector>
#include <cassert>

using namespace std;

int main()
{
    //array <Cell, boardSize> cells = { Cell(1), Cell(2), Cell(4) };
    //array <Cell, boardSize> cells = {};
    BoardType cells = {};
    initBoard( cells );

    //array <reference_wrapper<Cell>, boardSize> cellsRefs
    array <reference_wrapper<Cell>, boardSize> cellsRefs
        = { cells[0], cells[1], cells[2], cells[3] };

    cout << "Hello " << endl;
    cout << "boardSize = " << boardSize << endl;

    //for ( cells : x ) cout << x.m_id << endl;
    //for ( x : cells ) cout << x.m_id << endl;
    printCont( cellsRefs );

    cellsRefs[2].get().m_id = 22;

    printCont( cells );
}
