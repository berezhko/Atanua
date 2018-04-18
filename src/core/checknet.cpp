#include "checknet.h"
#include "atanua.h"

CheckNet::CheckNet() {
}

int CheckNet::add(Net *n)
{
    nets.push_back(n);
}

bool CheckNet::operator()()
{
    if (nets.empty())
        return invalid;

    for (auto e: nets) {
        if (e == NULL)
            return invalid;
    }

    for (auto e: nets) {
        if (e->mState == NETSTATE_INVALID)
            return invalid;
    }

    return valid;
}
