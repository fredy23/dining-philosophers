#pragma once

#include <mutex>
#include <string>

class PhilosophersUtilities
{
public:
    static void randomPause();
    static void printMessage(const std::string& p_message);

private:
    static std::mutex m_streamMutex;
};
