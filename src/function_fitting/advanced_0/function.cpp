#include "function.h"

#include <cmath>

FunctionToFit::FunctionToFit()
{
  _variables = 3;

  _data[200000] = {1.220887347, 8319726.652061044};
  _data[300000] = {0.90306089, 11235108.410020946};
  _data[400000] = {0.751605932, 13488865.066594498};
  _data[500000] = {0.661970632, 15296736.003841331};
  _data[600000] = {0.609807254, 16599648.386603154};
  _data[700000] = {0.585602534, 17291892.387883693};
  _data[800000] = {0.55984071, 18070277.52590554};
  _data[900000] = {0.54964296, 18425941.451155856};
  _data[1000000] = {0.544051834, 18597579.06817386};
  _data[1100000] = {0.534063586, 18949204.299429618};
  _data[1200000] = {0.52912982, 19127445.888421107};
  _data[1300000] = {0.517684422, 19540244.152836416};
  _data[1400000] = {0.519390035, 19474844.179480646};
  _data[1500000] = {0.515397643, 19634437.87033384};
  _data[1600000] = {0.51706104, 19585579.296401832};
  _data[1700000] = {0.512361435, 19742773.965804044};
  _data[1800000] = {0.521394118, 19408763.2572794};
  _data[1900000] = {0.515753466, 19628058.107902274};
  _data[2000000] = {0.52580657, 19246522.537746154};

  _constraints.push_back(std::make_pair(0, 2));
  _constraints.push_back(std::make_pair(0, 1000000000));
  _constraints.push_back(std::make_pair(0, 2));
}

double FunctionToFit::evaluate(const double &x, const std::vector<long double> &p) const
{
#if 1
  double TOTAL_INSTR = p[1];
  double CPU_instr = TOTAL_INSTR * p[2];
  double IPC = 1.6;
  double MPC = 1.0 / 150.0;
  double RAM_freq = 933.0;

  double MEM_instr = TOTAL_INSTR - CPU_instr;
  double T_CPU = CPU_instr * IPC / x;

  double T_CACHE_OP = IPC / x;
  double T_MEM_OP = MPC / RAM_freq;

  double v = _data.at(x)[1];

  double CACHE_OPS = p[0] * v;

  double T_MEM = MEM_instr * (CACHE_OPS * T_CACHE_OP + (1.0 - CACHE_OPS) * T_MEM_OP);

  return T_CPU + T_MEM;
#else
  auto a = p[0];
  auto b = p[1];
  auto c = p[2];
  auto d = p[3];
  auto e = p[4];

  return a + b / x + c * exp(- d * x + e);
#endif
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
