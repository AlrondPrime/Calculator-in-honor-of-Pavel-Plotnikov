#include <iostream>
#include "ResSys.h"
#include "Poly.h"

int __cdecl main()
{
    Poly<ResSys> pol1(4, {1, 0, 0, 0, 2, 1});
    Poly<ResSys> pol2(4, { 1, 1, 1});
    Poly<ResSys> pol3 = pol1/pol2;
    pol1.print();
    pol2.print();
    pol3.print();
    (pol3.Remainder<ResSys>()).print();

    /*ResSys a(1, 5), b(2, 5), c(a-b);
    std::cout << c.GetVal();*/
}
