//#ifdef MAIN

#include "ABDQ.hpp"
#include "ABQ.hpp"
#include "ABS.hpp"
#include "Interfaces.hpp"
#include "LinkedList.hpp"
#include "LLDQ.hpp"
#include "LLQ.hpp"
#include "LLS.hpp"
#include <iostream>

/*
    - LEAVE THE IFDEF GUARDS TO KEEP YOUR MAIN WITHOUT CONFLICTING WITH GRADESCOPE!
    - Test your code in this main and run locally with the RunMain configuration in CLion, or
    through your own command line compilation. Make sure to add flag "-DMAIN" to your compilation so this
    main function can compile.

*/

int main() {
    ABDQ<int>* one = new ABDQ<int>();

    one -> pushFront(2);
    one -> pushBack(3);
    one -> pushFront(1);
    one -> pushBack(4);
    one -> pushBack(5);
    one -> pushBack(6);
    one -> popBack();
    one -> popFront();

    ABDQ<int>* two = new ABDQ<int>(*one);
    ABDQ<int>* three = std::move(two);

    std::cout << one -> front() << one -> getSize();
    delete one;
    delete three;
    one = nullptr;
    two = nullptr;
    three = nullptr;
    return 0;
}


//#endif