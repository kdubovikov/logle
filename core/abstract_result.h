#ifndef ABSTRACT_RESULT_H
#define ABSTRACT_RESULT_H

#include <string>

class AbstractResult
{
protected:
    std::string logMessage;
public:
    virtual bool checkResults() = 0;
    std::string getLogMessage();
};

#endif // ABSTRACT_RESULT_H
