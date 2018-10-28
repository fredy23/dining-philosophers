#include <iostream>
#include <cstdio>
#include <array>
#include <thread>
#include <csignal>

#include "philosopher.hpp"

int main()
{
    constexpr std::size_t PHILOSOPHERS_NUM = 5;
    
    Fork l_forks[PHILOSOPHERS_NUM];

    std::array<Philosopher, PHILOSOPHERS_NUM> l_philosophers =
    {{
        {"Socrates", l_forks[0], l_forks[1]},
        {"Plato", l_forks[1], l_forks[2]},
        {"Aristotle", l_forks[2], l_forks[3]},
        {"Pythagoras", l_forks[3], l_forks[4]},
        {"Democritus", l_forks[4], l_forks[0]},
    }};

    std::signal(SIGINT, [](int p_sigNum)
    {
        std::cout << "\nDinner is over!\n";
        std::exit(p_sigNum);
    });

    std::getchar();
}
