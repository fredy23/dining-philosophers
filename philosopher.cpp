#include <thread>
#include <mutex>

#include "philosopher.hpp"
#include "philosophers_utilities.hpp"

Philosopher::Philosopher(const std::string& p_name, Fork& p_leftFork, Fork& p_rightFork)
    : m_name{p_name},
      m_leftFork{p_leftFork},
      m_rightFork{p_rightFork},
      m_thread(&Philosopher::live, this)
{
    PhilosophersUtilities::printMessage("Created philosopher with name " + m_name);
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

        PhilosophersUtilities::printMessage(m_name + " is hungry...");

        std::unique_lock<std::mutex> l_leftFork(m_leftFork, std::defer_lock);
        std::unique_lock<std::mutex> l_rightFork(m_rightFork, std::defer_lock);

        std::lock(l_leftFork, l_rightFork);

        eat();
    }
}

void Philosopher::eat() const
{
    ++m_totalMeals;

    PhilosophersUtilities::printMessage(m_name + "is eating (" + std::to_string(m_totalMeals) + ")");
    PhilosophersUtilities::randomPause();
}

void Philosopher::think() const
{
    PhilosophersUtilities::printMessage(m_name + " is thinking.");
    PhilosophersUtilities::randomPause();
}
