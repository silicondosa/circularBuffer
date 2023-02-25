// circularBuffer.cpp : This file contains the 'main' function of the example. Program execution begins and ends there.
//

#include <iostream>
#include "../../circularBuffer.h"

using namespace std;
int main()
{
    std::cout << "Hello World!\n";

    circularBuffer<int> b(5, CBUF_OVERWRITE);

    std::cout << "Buffer Capacity: " << b.getCapacity() << endl;

    cout << "Is buffer empty? " << b.isEmpty() << endl;

    int a = 1;
    b.insertData(&a);

    a = 2;
    b.insertData(&a);

    a = 3;
    b.insertData(&a);

    int i, c;
    cout << "Print all data points.\n";
    do {
        i = b.readData(&c);
        cout << c << "\t" << i << endl;
    } while (i == 1);

    a = 4;
    b.insertData(&a);

    a = 5;
    b.insertData(&a);

    a = 6;
    b.insertData(&a);

    cout << "Print all data points.\n";
    do {
        i = b.readData(&c);
        cout << c << "\t" << i << endl;
    } while (i == 1);

    cout << "Print first two data points only.\n";
    for (int j = 0; j < 2; j++) {
        i = b.readData(&c);
        cout << c << "\t" << i << endl;
    }

    cout << "Resetting reads before continuing...\n";
    b.resetRead();

    cout << "Print and remove all data points.\n";
    do {
        i = b.readRemoveData(&c);
        cout << c << "\t" << i << endl;
    } while (b.getLength() > 0);

    cout << "Is buffer empty? " << b.isEmpty() << endl;

    return 0;
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
