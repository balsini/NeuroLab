#include "function.h"

FunctionToFit::FunctionToFit()
{
  data[200000] = {1.220887347, 8319726.652061044};
  data[300000] = {0.90306089, 11235108.410020946};
  data[400000] = {0.751605932, 13488865.066594498};
  data[500000] = {0.661970632, 15296736.003841331};
  data[600000] = {0.609807254, 16599648.386603154};
  data[700000] = {0.585602534, 17291892.387883693};
  data[800000] = {0.55984071, 18070277.52590554};
  data[900000] = {0.54964296, 18425941.451155856};
  data[1000000] = {0.544051834, 18597579.06817386};
  data[1100000] = {0.534063586, 18949204.299429618};
  data[1200000] = {0.52912982, 19127445.888421107};
  data[1300000] = {0.517684422, 19540244.152836416};
  data[1400000] = {0.519390035, 19474844.179480646};
  data[1500000] = {0.515397643, 19634437.87033384};
  data[1600000] = {0.51706104, 19585579.296401832};
  data[1700000] = {0.512361435, 19742773.965804044};
  data[1800000] = {0.521394118, 19408763.2572794};
  data[1900000] = {0.515753466, 19628058.107902274};
  data[2000000] = {0.52580657, 19246522.537746154};
}

double FunctionToFit::evaluate(double CPU_freq, double params[])
{
  double TOTAL_INSTR = params[1];
  double CPU_instr = TOTAL_INSTR * params[2];
  double IPC = 1.6;
  double MPC = 1.0 / 150.0;
  double RAM_freq = 933.0;

  double MEM_instr = TOTAL_INSTR - CPU_instr;
  double T_CPU = CPU_instr * IPC / CPU_freq;

  double T_CACHE_OP = IPC / CPU_freq;
  double T_MEM_OP = MPC / RAM_freq;

  double CACHE_OPS = data[CPU_freq][1] * params[0];

  double T_MEM = MEM_instr * (CACHE_OPS * T_CACHE_OP + (1.0 - CACHE_OPS) * T_MEM_OP);

  return T_CPU + T_MEM;
}
