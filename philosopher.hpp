#pragma once

#include <thread>
#include <mutex>
#include <string>

using Fork = std::mutex;

class Philosopher
{
public:
    Philosopher(const std::string& p_name, Fork& p_leftFork, Fork& p_rightFork);
    ~Philosopher();

    Philosopher(Philosopher&&) = default;
    Philosopher& operator=(Philosopher&&) = default;

private:
    void live() const;
    void eat() const;
    void think() const;

    std::string m_name;
    Fork& m_leftFork;
    Fork& m_rightFork;
    mutable int m_totalMeals {0};

    std::thread m_thread;
};
