#pragma once
#include <string>

class AbstractResult
{
protected:
    std::string logMessage;
public:
    virtual bool checkResults() = 0;
    std::string getLogMessage();
};