#include <iostream>
#include <random>
#include <chrono>
#include <thread>

#include "philosophers_utilities.hpp"

std::mutex PhilosophersUtilities::m_streamMutex;

void PhilosophersUtilities::randomPause()
{
    std::mt19937 l_rng(std::random_device{}());
    std::this_thread::sleep_for(std::chrono::milliseconds(l_rng() % 2000 + 500));
}

void PhilosophersUtilities::printMessage(const std::string& p_message)
{
    std::lock_guard<std::mutex> l_guard(m_streamMutex);
    std::cout << p_message << '\n';
}
