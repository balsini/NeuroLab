#include "../functionfitting.h"

#include <cmath>

FunctionToFit::FunctionToFit()
{
//#define EXEC_BZIP2
//#define EXEC_CACHEKILLER
//#define EXEC_DES3_ENCRYPT
#define POW_IDLE_BIG
//#define POW_IDLE_LITTLE
#ifdef EXEC_BZIP2
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
#elif defined(EXEC_CACHEKILLER)
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
#elif defined(DES3_ENCRYPT)
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
#elif defined(EXEC_DES3_ENCRYPT)
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
#elif defined(POW_IDLE_BIG)
    /* frequency -> power */
    _data[ 200000 ] = { 0.11384 };
    _data[ 300000 ] = { 0.128787 };
    _data[ 400000 ] = { 0.131175 };
    _data[ 500000 ] = { 0.137935 };
    _data[ 600000 ] = { 0.148588 };
    _data[ 700000 ] = { 0.162303 };
    _data[ 800000 ] = { 0.182609 };
    _data[ 900000 ] = { 0.212562 };
    _data[ 1000000 ] = { 0.250501 };
    _data[ 1100000 ] = { 0.290595 };
    _data[ 1200000 ] = { 0.329039 };
    _data[ 1300000 ] = { 0.377707 };
    _data[ 1400000 ] = { 0.410597 };
    _data[ 1500000 ] = { 0.462267 };
    _data[ 1600000 ] = { 0.53053 };
    _data[ 1700000 ] = { 0.610619 };
    _data[ 1800000 ] = { 0.700314 };
    _data[ 1900000 ] = { 0.821853 };
    _data[ 2000000 ] = { 1.03724 };

    /* frequency -> voltage */
    _data2[ 200000 ] = { 0.916414 };
    _data2[ 300000 ] = { 0.916623 };
    _data2[ 400000 ] = { 0.916334 };
    _data2[ 500000 ] = { 0.916392 };
    _data2[ 600000 ] = { 0.916442 };
    _data2[ 700000 ] = { 0.916399 };
    _data2[ 800000 ] = { 0.928542 };
    _data2[ 900000 ] = { 0.952775 };
    _data2[ 1000000 ] = { 0.977758 };
    _data2[ 1100000 ] = { 1.00225 };
    _data2[ 1200000 ] = { 1.02737 };
    _data2[ 1300000 ] = { 1.05228 };
    _data2[ 1400000 ] = { 1.06432 };
    _data2[ 1500000 ] = { 1.08505 };
    _data2[ 1600000 ] = { 1.11552 };
    _data2[ 1700000 ] = { 1.15317 };
    _data2[ 1800000 ] = { 1.19105 };
    _data2[ 1900000 ] = { 1.24186 };
    _data2[ 2000000 ] = { 1.31784 };
#elif defined(POW_IDLE_LITTLE)
    _data[ 200000 ] = {0.014286022527 };
    _data[ 300000 ] = {0.0176564630017 };
    _data[ 400000 ] = {0.0206775010414 };
    _data[ 500000 ] = {0.0233931600552 };
    _data[ 600000 ] = {0.0289896589283 };
    _data[ 700000 ] = {0.0353970341141 };
    _data[ 800000 ] = {0.0419518965156 };
    _data[ 900000 ] = {0.0649049267157 };
    _data[ 1000000 ] = {0.07700485942 };
    _data[ 1100000 ] = {0.0911104786687 };
    _data[ 1200000 ] = {0.107736782445 };
    _data[ 1300000 ] = {0.132103339988 };
    _data[ 1400000 ] = {0.162989048706 };
#endif
#if 1
  /*
  _constraints.push_back(std::make_pair(0, 1));
  _constraints.push_back(std::make_pair(0, 1000000000));
  _constraints.push_back(std::make_pair(0, 1));
  */
#ifdef XXX
  _constraints.push_back(std::make_pair(-10, 10));
  _constraints.push_back(std::make_pair(-1000000000, 1000000000));
  //_constraints.push_back(std::make_pair(10000, 100000000));
#elif defined(POW_IDLE_BIG)
  _constraints.push_back(std::make_pair(0, 1000));
  _constraints.push_back(std::make_pair(0, 1));
  _constraints.push_back(std::make_pair(0, 10));
#endif
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
  // cachekiller_perf.sh: 0.486207 52252.2 1.69011 156644
  // bzip2: 0.995107 7.6922e+6 6.69154 135190
  // des3_encrypt: 1.36817e-17 1.50382e+6 2.12979 126684
  long double res;
#ifdef XXX
  res = p[0] + p[1] / x + 1.69 * exp(- x / 156644)
#elif defined(POW_IDLE_BIG)
  auto f = x;
  auto v = _data2.at(f).front();
  auto K_0 = p[1];
  auto gamma = p[0];
  auto displacement = p[2];

  res = displacement + (1 + gamma * v) * K_0 * f * v * v;
#endif

  return res;
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
