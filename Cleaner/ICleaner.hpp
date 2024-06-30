

#ifndef CPP_ICLEANER_HPP
#define CPP_ICLEANER_HPP
#include "../IEnvironment.hpp"

class ICleaner : public IEnvironment {
public:
    virtual ~ICleaner() {}

    virtual void clean() = 0;
};

#endif //CPP_ICLEANER_HPP
