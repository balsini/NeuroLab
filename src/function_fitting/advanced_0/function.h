#ifndef FUNCTION_H
#define FUNCTION_H

#include <map>
#include <vector>

class FunctionToFit {
    std::map<unsigned int, std::vector<double>> data;

  public:
    FunctionToFit();
    double evaluate(double CPU_freq, double params[]);
};

#endif
