// 11th Day.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <functional>

using namespace std;

class Monkey {
public:
    std::function<void()> m_function;

    Monkey(std::function<void()> getm_function) {
        m_function = getm_function;
    }

};

int invoke(int x, int y,
    function<int(int, int)> func)
{
    return func(x, y);
}

/*
Monkey 0:
    Starting items : 79, 98
    Operation : new = old * 19
    Test : divisible by 23
    If true : throw to monkey 2
    If false : throw to monkey 3

Monkey 1 :
    Starting items : 54, 65, 75, 74
    Operation : new = old + 6
    Test : divisible by 19
    If true : throw to monkey 2
    If false : throw to monkey 0

    Monkey 2 :
    Starting items : 79, 60, 97
    Operation : new = old * old
    Test : divisible by 13
    If true : throw to monkey 1
    If false : throw to monkey 3

    Monkey 3 :
    Starting items : 74
    Operation : new = old + 3
    Test : divisible by 17
    If true : throw to monkey 0
    If false : throw to monkey 1
*/



int main()
{
    std::function<void()> m_function = [this]() { std::cout << "test\n";   };
    Monkey test(m_function);



        cout << "Addition of 20 and 10 is ";
        int k = invoke(20, 10,
            [](int x,
                int y) -> int {
                    return x + y;
            });

        cout << k << '\n';


}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
