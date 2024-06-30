//
// Created by PUMA on 26/06/2024.
//

#ifndef CPP_ICLEANER_HPP
#define CPP_ICLEANER_HPP
class ICleaner {
public:
    virtual ~ICleaner() {}

    virtual void clean() = 0;
};

#endif //CPP_ICLEANER_HPP
