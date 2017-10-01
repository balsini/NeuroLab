#ifndef FUNCTION_H
#define FUNCTION_H

#include <map>
#include <vector>

class FunctionToFit {
    std::map<double, std::vector<double> > _data;
    std::vector<std::pair<long double, long double> > _constraints;
    unsigned int _variables;

  public:
    FunctionToFit();
    double evaluate(const double &x, const std::vector<long double> &p) const;
    long double x(unsigned int index) const;
    long double y(unsigned int index) const;
    unsigned int dataSize() const;
    unsigned int variables() const { return _variables; }
    const std::vector<std::pair<long double, long double> > getConstraints() const;
};

#endif
