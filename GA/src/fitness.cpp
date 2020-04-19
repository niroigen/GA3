#include "GA/fitness.hpp"

#define DEBUG_MODE 1

#if DEBUG_MODE
#define DEBUG(x) std::cout << x << std::endl;
#define WAIT std::cin.get();
#else
#define DEBUG(x)
#define WAIT
#endif

void evalPartial(Individual* individual, unsigned int start_idx, unsigned int end_idx, unsigned long* counter) {
    for (int i = start_idx; i < end_idx; i++)
    {
        if (individual->currentState[i] != individual->goalState[i])
        {
            (*counter)++;
        }
    }
}

void defaultFitnessFunction(Individual* individual)
{
    const int num_threads = 2;
    unsigned long* fitness1 = new unsigned long(0);
    unsigned long* fitness2 = new unsigned long(0);
    unsigned long* fitness3 = new unsigned long(0);
    unsigned long* fitness4 = new unsigned long(0);

    std::thread t1(evalPartial, individual, 0, 16383, fitness1);
    std::thread t2(evalPartial, individual, 16384, 32767, fitness2);
    std::thread t3(evalPartial, individual, 32768, 49151, fitness3);
    std::thread t4(evalPartial, individual, 49152, 65535, fitness4);

    t1.join();
    t2.join();
    t3.join();
    t4.join();

    individual->fitness = *fitness1 + *fitness2 + *fitness3 + *fitness4;

    delete fitness1;
    delete fitness2;
    delete fitness3;
    delete fitness4;
}