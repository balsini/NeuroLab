#include "function.h"

#include <cmath>

FunctionToFit::FunctionToFit()
{
#if 0
  // bzip2_perf.sh
  _data[200000] = {41.000305156, 1915360.036985184};
  _data[300000] = {27.294285376, 2853658.7760780067};
  _data[400000] = {20.596632646, 3769935.9081922425};
  _data[500000] = {16.599864691, 4670655.119377924};
  _data[600000] = {13.946207868, 5548381.232546247};
  _data[700000] = {12.005747716, 6483955.42213974};
  _data[800000] = {10.567865948, 7313536.941167112};
  _data[900000] = {9.5533941, 8077099.635196668};
  _data[1000000] = {8.703649316, 8879973.69769028};
  _data[1100000] = {7.976247804, 9657917.593955435};
  _data[1200000] = {7.298408795, 10551161.789232168};
  _data[1300000] = {6.872768475, 11229885.639352925};
  _data[1400000] = {6.521464305, 11874838.591177415};
  _data[1500000] = {6.132806424, 12545236.989531303};
  _data[1600000] = {5.949125595, 12974902.40664519};
  _data[1700000] = {5.464577641, 14096866.960408514};
  _data[1800000] = {5.28200159, 14519628.912114734};
  _data[1900000] = {5.016087584, 15341446.637706874};
  _data[2000000] = {4.864610088, 15812357.539147545};
#elif 1
  // cachekiller_perf.sh
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
#else
  // des3_encrypt_perf.sh
  _data[200000] = {7.960844594, 170886.8932104668};
  _data[300000] = {5.203507918, 226898.66501707898};
  _data[400000] = {3.852668671, 316186.0268881658};
  _data[500000] = {3.056318095, 346492.7298413289};
  _data[600000] = {2.531410355, 393007.3992290357};
  _data[700000] = {2.150385425, 505381.0295426458};
  _data[800000] = {1.893171146, 582425.4200840223};
  _data[900000] = {1.67191051, 633549.4595341709};
  _data[1000000] = {1.496425646, 726087.5292429999};
  _data[1100000] = {1.370600728, 861850.5563788085};
  _data[1200000] = {1.247152069, 765503.280418324};
  _data[1300000] = {1.151533717, 854384.0145325072};
  _data[1400000] = {1.071037274, 912194.2099654694};
  _data[1500000] = {0.998932489, 939679.1177947161};
  _data[1600000] = {0.938699582, 1016938.7717912076};
  _data[1700000] = {0.885167121, 1116428.7246498393};
  _data[1800000] = {0.836543487, 1113669.539572902};
  _data[1900000] = {0.790822247, 1246644.241155244};
  _data[2000000] = {0.754319393, 1445045.706255626};
#endif
#if 1
  /*
  _constraints.push_back(std::make_pair(0, 1));
  _constraints.push_back(std::make_pair(0, 1000000000));
  _constraints.push_back(std::make_pair(0, 1));
  */
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

long double IPC = 1.6;

/*
 * CPU time
 *
 * The time spent by the program in running the CPU instructions (ALU and FPU)
 *
 * @param I_C Total number of CPU instructions
 * @param f_C CPU frequency
 */
static inline
long double T_CPU(long unsigned int I_C, long unsigned int f_C)
{
  return static_cast<long double>(I_C) / static_cast<long double>(IPC) / f_C;
}

unsigned long int RAM_freq = 933000;
double CIPC = 1.0 / 21.0; // Cache instructions per cycle
unsigned long int L2_miss_penality_cycles = 30;
unsigned long int cache_size = 2000000;

/*
 * Memory time
 *
 * The time spent by the program in running the memory instructions (memory and
 * caches)
 *
 * @param I_M Total number of memory instructions
 * @param f_C CPU frequency
 */
static inline
long double T_memory(long unsigned int I_M, long unsigned int f_C, long double CP)
{
  //long double T_CACHE_OP = 1 / CIPC / f_C;
  long double T_MEM_OP = 1 / CIPC / f_C + 110.0 / 1000.0 / 1000.0 / 1000.0;

  return I_M * T_MEM_OP;

  //double CACHE_OPS = p[0] * v;
  //return I_M * (CACHE_OPS * T_CACHE_OP + (1.0 - CACHE_OPS) * T_MEM_OP);
}

long double FunctionToFit::evaluate(const long double &x,
                                    const std::vector<long double> &p) const
{
#if 0
  long unsigned int TOTAL_INSTR = p[0];
  long unsigned int CPU_instr = TOTAL_INSTR * p[1];
  long unsigned int MEM_instr = TOTAL_INSTR - CPU_instr;

  //double v = _data.at(CPU_freq)[1];

  return T_CPU(CPU_instr, CPU_freq) + T_memory(MEM_instr, CPU_freq, p[2]);
#else
  return p[0] + p[1] / x + 1.85419 * exp(- x / 161021);
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
