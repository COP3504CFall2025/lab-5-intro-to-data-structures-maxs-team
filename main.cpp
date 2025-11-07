#ifdef MAIN

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
    ABS<int>* one = new ABS<int>();
    std::cout << one -> getMaxCapacity()<<std::endl;
    std::cout << one -> getSize()<<std::endl;
    one -> push(1);
    std::cout << one -> getMaxCapacity()<<std::endl;
    one -> push(2);
    std::cout << one -> getMaxCapacity()<<std::endl;
    one -> push(3);
    std::cout << one -> getMaxCapacity()<<std::endl;
    ABS<int>* two = new ABS<int>(*one);
    one -> PrintForward();
    two -> pop();
    two -> PrintForward();
    std::cout << "peek: " << two -> peek() << std::endl;
    std::cout << two -> getMaxCapacity()<<std::endl;

    delete one;
    one = nullptr;
    return 0;
}


#endif