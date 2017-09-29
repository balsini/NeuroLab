#ifndef FUNCTION_H
#define FUNCTION_H

#include <map>
#include <vector>

class FunctionToFit {
    std::map<double, std::vector<double>> data;
    unsigned int variables;
  public:
    FunctionToFit();
    double evaluate(const double x, const std::vector<long double> &p) const;
    long double x(unsigned int index) const;
    long double y(unsigned int index) const;
    unsigned int dataSize() const;
    unsigned int dimension() const { return variables; }
};

#endif
