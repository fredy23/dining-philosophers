#include <iostream>
#include <thread>
#include <random>
#include <chrono>
#include <mutex>

#include "philosopher.hpp"

std::mutex Philosopher::m_streamMutex;

Philosopher::Philosopher(const std::string& p_name, Fork& p_leftFork, Fork& p_rightFork)
    : m_name{p_name},
      m_leftFork{p_leftFork},
      m_rightFork{p_rightFork},
      m_thread(&Philosopher::live, this)
{
    std::lock_guard<std::mutex> l_guard(m_streamMutex);
    std::cout << "Created philosopher with name " << m_name << '\n';
}

Philosopher::~Philosopher()
{
    if(m_thread.joinable())
    {
        m_thread.join();
    }
}

void Philosopher::live() const
{
    while(true)
    {
        think();

        {
            std::lock_guard<std::mutex> l_guard(m_streamMutex);
            std::cout << m_name << " is hungry...\n";
        }

        std::unique_lock<std::mutex> l_leftFork(m_leftFork, std::defer_lock);
        std::unique_lock<std::mutex> l_rightFork(m_rightFork, std::defer_lock);

        std::lock(l_leftFork, l_rightFork);

        eat();
    }
}

void Philosopher::eat() const
{
    ++m_totalEaten;

    {
        std::lock_guard<std::mutex> l_guard(m_streamMutex);
        std::cout << m_name << " is eating (" << m_totalEaten << " meals total)\n";
    }

    randomPause();
}

void Philosopher::think() const
{
    {
        std::lock_guard<std::mutex> l_guard(m_streamMutex);
        std::cout << m_name << " is thinking.\n";
    }

    randomPause();
}

void Philosopher::randomPause() const
{
    std::mt19937 l_rng(std::random_device{}());
    std::this_thread::sleep_for(std::chrono::milliseconds(l_rng() % 2000 + 500));
}
