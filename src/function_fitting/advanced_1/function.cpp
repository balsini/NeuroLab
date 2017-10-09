#include "../functionfitting.h"

#include <cmath>

FunctionToFit::FunctionToFit()
{
#if 1
  // T = 16
  _data[600000] = {0.32848};
  _data[700000] = {0.34627};
  _data[800000] = {0.37874};
  _data[900000] = {0.42381};
  _data[1000000] = {0.47206};
  _data[1100000] = {0.52776};
  _data[1200000] = {0.5901};
  _data[1300000] = {0.65176};
  _data[1400000] = {0.70843};
  _data[1500000] = {0.76326};
  _data[1600000] = {0.87954};
  _data[1700000] = {0.97761};
  _data[1800000] = {1.1195};
  _data[1900000] = {1.2882};
  _data[2000000] = {1.5985};
#elif 0
  // T = 16
  _data[600000] = {0.32848};
  _data[700000] = {0.34627};
  _data[800000] = {0.37874};
  _data[900000] = {0.42381};
  _data[1000000] = {0.47206};
  _data[1100000] = {0.52776};
  _data[1200000] = {0.5901};
  _data[1300000] = {0.65176};
  _data[1400000] = {0.70843};
  _data[1500000] = {0.76326};
  _data[1600000] = {0.87954};
  _data[1700000] = {0.97761};
  _data[1800000] = {1.1195};
  _data[1900000] = {1.2882};
  _data[2000000] = {1.5985};
#else
  // T = 100
  _data[200000] = {0.1517};
  _data[300000] = {0.17171};
  _data[400000] = {0.17165};
  _data[500000] = {0.17796};
  _data[600000] = {0.18778};
  _data[700000] = {0.20141};
  _data[800000] = {0.22678};
  _data[900000] = {0.26538};
  _data[1000000] = {0.30516};
  _data[1100000] = {0.34945};
  _data[1200000] = {0.40208};
  _data[1300000] = {0.45138};
  _data[1400000] = {0.49933};
  _data[1500000] = {0.55794};
  _data[1600000] = {0.6438};
  _data[1700000] = {0.72082};
  _data[1800000] = {0.8421};
  _data[1900000] = {0.97793};
  _data[2000000] = {1.2379};
#endif
#if 1
  /*
  _constraints.push_back(std::make_pair(0, 1));
  _constraints.push_back(std::make_pair(0, 1000000000));
  _constraints.push_back(std::make_pair(0, 1));
  */
  _constraints.push_back(std::make_pair(-1000000000, 1000000000));
  _constraints.push_back(std::make_pair(-1000000000, 1000000000));
  _constraints.push_back(std::make_pair(-1000000000, 1000000000));
  _constraints.push_back(std::make_pair(-1000000000, 1000000000));
  _constraints.push_back(std::make_pair(-1000000000, 1000000000));
  //_constraints.push_back(std::make_pair(-1000000000, 1000000000));
  //_constraints.push_back(std::make_pair(161020, 161021));
#else
  _constraints.push_back(std::make_pair(-1000000000, 1000000000));
  _constraints.push_back(std::make_pair(-1000000000, 1000000000));
  _constraints.push_back(std::make_pair(-1000000000, 1000000000));
  _constraints.push_back(std::make_pair(-1000000000, 1000000000));
  _constraints.push_back(std::make_pair(-1000000000, 1000000000));
#endif

  _variables = _constraints.size();
}

long double FunctionToFit::evaluate(const long double &x,
                                    const std::vector<long double> &p) const
{
  return p[0] + p[1] * x + p[2] * x * x + p[3] * exp(x * p[4]);
}

long double FunctionToFit::x(unsigned int index) const
{
  auto v = _data.cbegin();

  std::advance(v, index);

  return (*v).first;
}

long double FunctionToFit::y(unsigned int index) const
{
  auto v = _data.cbegin();

  std::advance(v, index);

  return (*v).second[0];
}

unsigned int FunctionToFit::dataSize() const
{
  return _data.size();
}

const std::vector<std::pair<long double, long double> > FunctionToFit::getConstraints() const
{
  const std::vector<std::pair<long double, long double> > r = _constraints;

  return r;
}
