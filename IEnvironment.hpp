#ifndef IENVIRONMENT_HPP
#define IENVIRONMENT_HPP

class IEnvironment {
public:
    virtual ~IEnvironment() {}
    virtual void print(bool printDimensions = true) const = 0;
};

#endif // IENVIRONMENT_HPP
