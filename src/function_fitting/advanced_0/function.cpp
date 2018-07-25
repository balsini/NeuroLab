#include "../functionfitting.h"

#include <cmath>

FunctionToFit::FunctionToFit()
{
//#define EXEC_BZIP2
//#define EXEC_CACHEKILLER
//#define EXEC_DES3_ENCRYPT


//#define POW_IDLE_LITTLE
//#define POW_IDLE_BIG

//#define POW_BIG_CACHE
//#define POW_BIG_GZIP2
//#define POW_BIG_ENCRY
//#define POW_BIG_DECRY
//#define POW_BIG_HASH

//#define POW_LITTLE_CACHE
//#define POW_LITTLE_GZIP2
//#define POW_LITTLE_ENCRY
//#define POW_LITTLE_DECRY
#define POW_LITTLE_HASH

#define POW_BIG_WL (defined(POW_BIG_CACHE)|| defined(POW_BIG_GZIP2) || \
    defined(POW_BIG_DECRY) || defined(POW_BIG_ENCRY) || defined(POW_BIG_HASH))

#define POW_BIG_ANY (defined(POW_IDLE_BIG) || POW_BIG_WL)

#define POW_LITTLE_WL (defined(POW_LITTLE_CACHE) || defined(POW_LITTLE_GZIP2) || \
    defined(POW_LITTLE_DECRY) || defined(POW_LITTLE_ENCRY) || defined(POW_LITTLE_HASH))

#define POW_LITTLE_ANY (defined(POW_IDLE_LITTLE) || POW_LITTLE_WL)



    /* FREQUENCIES */
#if POW_BIG_ANY
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

#elif POW_LITTLE_ANY
    /* frequency -> voltage */
    _data2[200000] = {0.92002};
    _data2[300000] = {0.92};
    _data2[400000] = {0.91998};
    _data2[500000] = {0.919941};
    _data2[600000] = {0.9575};
    _data2[700000] = {0.993809};
    _data2[800000] = {1.03133};
    _data2[900000] = {1.06923};
    _data2[1000000] = {1.10625};
    _data2[1100000] = {1.14375};
    _data2[1200000] = {1.18125};
    _data2[1300000] = {1.23098};
    _data2[1400000] = {1.28002};
#endif


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

#elif defined(POW_BIG_GZIP2)
    /* frequency -> power WL */
    _data[200000] = {0.1861451190184049};
    _data[300000] = {0.22988578332145404};
    _data[400000] = {0.2648607993527508};
    _data[500000] = {0.3068098377153219};
    _data[600000] = {0.35707005811623244};
    _data[700000] = {0.40583876754385956};
    _data[800000] = {0.47465079739336496};
    _data[900000] = {0.5579458443877551};
    _data[1000000] = {0.6467968408163265};
    _data[1100000] = {0.7593615820029027};
    _data[1200000] = {0.8774849261538461};
    _data[1300000] = {0.9961042922077922};
    _data[1400000] = {1.101980340101523};
    _data[1500000] = {1.245568896797153};
    _data[1600000] = {1.4098878425925925};
    _data[1700000] = {1.6156188204633204};
    _data[1800000] = {1.8361952725450903};
    _data[1900000] = {2.1413340228690227};
    _data[2000000] = {2.655111776344086};

#elif (defined(POW_BIG_CACHE))
    /* frequency -> power WL */
    _data[200000] = {0.1957103023255814};
    _data[300000] = {0.25202243902439025};
    _data[400000] = {0.28045775609756096};
    _data[500000] = {0.3061555365853659};
    _data[600000] = {0.3477611749999999};
    _data[700000] = {0.375106375};
    _data[800000] = {0.4267720243902438};
    _data[900000] = {0.49453175609756106};
    _data[1000000] = {0.5556705};
    _data[1100000] = {0.6295907857142857};
    _data[1200000] = {0.7188698333333333};
    _data[1300000] = {0.8129962142857142};
    _data[1400000] = {0.9021049534883722};
    _data[1500000] = {0.9836573953488371};
    _data[1600000] = {1.1562032790697674};
    _data[1700000] = {1.3039993636363638};
    _data[1800000] = {1.4482111333333332};
    _data[1900000] = {1.761199711111111};
    _data[2000000] = {2.0912775869565214};

#elif (defined(POW_BIG_DECRY))
    /* frequency -> power WL */
    _data[200000] = {0.1876455046728972};
    _data[300000] = {0.23244958241758243};
    _data[400000] = {0.26691172995780593};
    _data[500000] = {0.31712217224880385};
    _data[600000] = {0.3706149144385027};
    _data[700000] = {0.42691486390532546};
    _data[800000] = {0.5000816129032258};
    _data[900000] = {0.5864980839160839};
    _data[1000000] = {0.6921192196969697};
    _data[1100000] = {0.8064680975609755};
    _data[1200000] = {0.9312492173913046};
    _data[1300000] = {1.116338824074074};
    _data[1400000] = {1.163971892156863};
    _data[1500000] = {1.3210939896907217};
    _data[1600000] = {1.5142504347826091};
    _data[1700000] = {1.731474137931034};
    _data[1800000] = {1.9803091927710847};
    _data[1900000] = {2.3205384};
    _data[2000000] = {2.8390857368421054};

#elif (defined(POW_BIG_ENCRY))
    /* frequency -> power WL */
    _data[200000] = {0.18793199056603774};
    _data[300000] = {0.2312484851851852};
    _data[400000] = {0.27173786324786325};
    _data[500000] = {0.31935720289855074};
    _data[600000] = {0.37155071351351354};
    _data[700000] = {0.4268156547619048};
    _data[800000] = {0.49535299999999993};
    _data[900000] = {0.5868741843971632};
    _data[1000000] = {0.6896210916030534};
    _data[1100000] = {0.8029869836065573};
    _data[1200000] = {0.9346935087719298};
    _data[1300000] = {1.0892538504672897};
    _data[1400000] = {1.1687302277227722};
    _data[1500000] = {1.3208295729166666};
    _data[1600000] = {1.52409754945055};
    _data[1700000] = {1.731036126436782};
    _data[1800000] = {1.9821802073170733};
    _data[1900000] = {2.315865151898734};
    _data[2000000] = {2.881170855263158};

#elif defined(POW_BIG_HASH)
    /* frequency -> power WL */
    _data[200000] = {0.19091071375464683};
    _data[300000] = {0.2360958552631579};
    _data[400000] = {0.27919296464646465};
    _data[500000] = {0.32462464};
    _data[600000] = {0.3770300318471338};
    _data[700000] = {0.43088936363636365};
    _data[800000] = {0.5061868923076922};
    _data[900000] = {0.60152485};
    _data[1000000] = {0.7053859375};
    _data[1100000] = {0.8073583557692309};
    _data[1200000] = {0.9363818163265306};
    _data[1300000] = {1.0628671195652175};
    _data[1400000] = {1.1463073678160922};
    _data[1500000] = {1.322471626506024};
    _data[1600000] = {1.5172279615384614};
    _data[1700000] = {1.743204346666667};
    _data[1800000] = {1.9781730416666663};
    _data[1900000] = {2.3228605362318837};
    _data[2000000] = {2.9286380909090908};


#elif (defined(POW_LITTLE_ENCRY))
    /* frequency -> power WL */
    _data[200000] = {0.03189463676341249};
    _data[300000] = {0.042660783817951964};
    _data[400000] = {0.053534729684908786};
    _data[500000] = {0.06294876024590164};
    _data[600000] = {0.08019401466992665};
    _data[700000] = {0.09944637499999999};
    _data[800000] = {0.12078815161290322};
    _data[900000] = {0.16761104710144928};
    _data[1000000] = {0.20099565060240962};
    _data[1100000] = {0.23161173127753304};
    _data[1200000] = {0.2654722307692308};
    _data[1300000] = {0.32200709375};
    _data[1400000] = {0.38823849720670395};

#elif (defined(POW_LITTLE_CACHE))
    /* frequency -> power WL */
    _data[200000] = {0.03328071153846154};
    _data[300000] = {0.04252608};
    _data[400000] = {0.050281944954128445};
    _data[500000] = {0.057745153061224484};
    _data[600000] = {0.0704466989247312};
    _data[700000] = {0.08407355681818182};
    _data[800000] = {0.0994760476190476};
    _data[900000] = {0.14171467499999998};
    _data[1000000] = {0.1648539240506329};
    _data[1100000] = {0.18585242857142856};
    _data[1200000] = {0.22001740789473687};
    _data[1300000] = {0.24970190666666672};
    _data[1400000] = {0.29371365789473686};


#elif (defined(POW_LITTLE_DECRY))
    /* frequency -> power WL */
    _data[200000] = {0.031901012216404886};
    _data[300000] = {0.04259887468671679};
    _data[400000] = {0.05369509523809524};
    _data[500000] = {0.06311228455284552};
    _data[600000] = {0.08009744660194174};
    _data[700000] = {0.09956813239436621};
    _data[800000] = {0.12095963461538464};
    _data[900000] = {0.16885689208633095};
    _data[1000000] = {0.20206093227091632};
    _data[1100000] = {0.2327283903508772};
    _data[1200000] = {0.26747556666666666};
    _data[1300000] = {0.3170286237113403};
    _data[1400000] = {0.3807648222222222};

#elif defined(POW_LITTLE_GZIP2)
    /* frequency -> power WL */
    _data[200000] = {0.031198151705276702};
    _data[300000] = {0.04128960207300585};
    _data[400000] = {0.05082910140360928};
    _data[500000] = {0.05951877071158473};
    _data[600000] = {0.07456368851807708};
    _data[700000] = {0.09136622296994168};
    _data[800000] = {0.10924603126550868};
    _data[900000] = {0.15446138515709643};
    _data[1000000] = {0.1824229076563413};
    _data[1100000] = {0.2101917215269086};
    _data[1200000] = {0.23938437009966776};
    _data[1300000] = {0.28496157252978277};
    _data[1400000] = {0.33251512472647704};

#elif defined(POW_LITTLE_HASH)
    /* frequency -> power WL */
    _data[200000] = {0.03023931526104418};
    _data[300000] = {0.04009171181556196};
    _data[400000] = {0.049722730188679246};
    _data[500000] = {0.05870487906976745};
    _data[600000] = {0.07439841551246537};
    _data[700000] = {0.09192945833333334};
    _data[800000] = {0.10979396727272726};
    _data[900000] = {0.15437981300813008};
    _data[1000000] = {0.1845078116591928};
    _data[1100000] = {0.2149518916256158};
    _data[1200000] = {0.24672793048128341};
    _data[1300000] = {0.2899144046242775};
    _data[1400000] = {0.3325641614906832};


#elif defined(POW_IDLE_BIG)
    /* frequency -> power */
    _data[200000] = {0.11753618415};
    _data[300000] = {0.124703106195};
    _data[400000] = {0.125327878446};
    _data[500000] = {0.134832690447};
    _data[600000] = {0.150089416338};
    _data[700000] = {0.169601106499};
    _data[800000] = {0.19585144422};
    _data[900000] = {0.231446941998};
    _data[1000000] = {0.273615714344};
    _data[1100000] = {0.318171347641};
    _data[1200000] = {0.365590132943};
    _data[1300000] = {0.42342218299};
    _data[1400000] = {0.465458459238};
    _data[1500000] = {0.517404849145};
    _data[1600000] = {0.589372067423};
    _data[1700000] = {0.672044867398};
    _data[1800000] = {0.78247376533};
    _data[1900000] = {0.921020426427};
    _data[2000000] = {1.14932193089};


#elif defined(POW_IDLE_LITTLE)
    /* frequency -> power */
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
#elif (POW_IDLE_BIG || POW_IDLE_LITTLE)
  _constraints.push_back(std::make_pair(0, 0.8));
  _constraints.push_back(std::make_pair(0, 100));
  _constraints.push_back(std::make_pair(0, 150));
  _constraints.push_back(std::make_pair(1e-9, 9.9e-9));
#elif (POW_BIG_WL || POW_LITTLE_WL)
    _constraints.push_back(std::make_pair(0, 0.8));
    _constraints.push_back(std::make_pair(0, 200));
    _constraints.push_back(std::make_pair(0, 200));
    _constraints.push_back(std::make_pair(1e-10, 1e-9));
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
#elif (defined(POW_IDLE_BIG) || defined(POW_IDLE_LITTLE))
  // Solution IDLE_BIG
  // <disp, eta, gamma, K0>
  // 0.0615501, 0.181869, 70.899, 3.25146e-9

  // Solution IDLE_LITTLE
  // <disp, eta, gamma, K0>
  // 0.000383117 0.00884979 64.8351 8.15464e-10

  auto f = x;
  auto v = _data2.at(f).front();

  auto displacement = p[0];
  auto eta = p[1];
  auto gamma = p[2];
  auto K_0 = p[3];

  res = displacement + (1 + eta + gamma * v) * K_0 * f * v * v;

#elif (POW_BIG_WL)
  std::vector<double> idle_sol_big = {0.0637727, 0.0223477, 28.099, 7.28082e-9};
  // Solution GZIP2
  //<dist, eta, gamma, Kw>
  // 0.00829219 87.1105 53.1254 2.92188e-9
  //
  // Solution Cachekiller
  // <dist, eta, gamma, Kw>
  // 0.0561092 42.5547 58.1872 2.48896e-9
  //
  // Solution Encryption
  // <dist, eta, gamma, Kw>
  // 0.000358041 66.7515 48.4517 4.0149e-9
  //
  // Solution Decryption
  // <dist, eta, gamma, Kw>
  // 0.000532978 38.0653 12.3592 9.34218e-9

  // Solution Hash
  // 0.0348713 35.4281 129.969 2.55853e-9

  double Pidle;
  auto f = x;
  auto v = _data2.at(f).front();

  auto displacement = p[0];
  auto eta = p[1];
  auto gamma = p[2];
  auto K_w = p[3];

   Pidle = idle_sol_big[0] + (1 + idle_sol_big[1] + idle_sol_big[2] * v) * idle_sol_big[3] * f * v * v;
  res = Pidle + displacement + (1 + eta + gamma * v) * K_w * f * v * v;

#elif (POW_LITTLE_WL)
  std::vector<double> idle_sol_little = {0.000383117, 0.00884979, 64.8351, 8.15464e-10};


  // Solution GZIP2
  // 0.00532092 99.0716 1.4549 7.65224e-10
  //
  // Solution Cachekiller
  // 0.0130081 57.5485 1.78526 9.53085e-10
  //
  // Solution Encryption
  // 1.55226e-5 91.5498 33.1454 7.57548e-10
  //
  // Solution Decryption
  // 3.00809e-7 122.153 15.9118 6.95939e-10

  // Solution Hash
  // 0.00681312 142.931 4.71582 5.18158e-10

  double Pidle;
  auto f = x;
  auto v = _data2.at(f).front();

  auto displacement = p[0];
  auto eta = p[1];
  auto gamma = p[2];
  auto K_w = p[3];

   Pidle = idle_sol_little[0] + (1 + idle_sol_little[1] + idle_sol_little[2] * v) * idle_sol_little[3] * f * v * v;
  res = Pidle + displacement + (1 + eta + gamma * v) * K_w * f * v * v;

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
