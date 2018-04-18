#ifndef CHECKNET_H
#define CHECKNET_H

#include <vector>

class Net;

class CheckNet
{
public:
    CheckNet();
    int add(Net *n);
    bool operator()();

    static const bool valid = 0;
    static const bool invalid = 1;

private:
    std::vector<Net*> nets;
};

#endif
