/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: predictAndUpdateState.c
 *
 * MATLAB Coder version            : 23.2
 * C/C++ source code generated on  : 25-Jun-2025 17:47:33
 */

/* Include Files */
#include "predictAndUpdateState.h"
#include "socEstimator_internal_types.h"
#include <math.h>
#include <string.h>

/* Function Declarations */
static int div_s32_floor(int numerator, int denominator);

static void macroKernel1(int M, int K, int N, const float *A, int LDA,
                         const float *B, int LDB, float *C, int LDC);

static void matrixMultiply1(int M, int K, int N, int blockSizeM, int blockSizeK,
                            int blockSizeN, const float *A, const float *B,
                            float *C);

static void microKernel11(int K, const float *A, int LDA, const float *B,
                          int LDB, float *C, int LDC);

static void microKernel12(int K, const float *A, int LDA, const float *B,
                          int LDB, float *C, int LDC);

static void microKernel13(int K, const float *A, int LDA, const float *B,
                          float *C);

static void microKernel14(int K, const float *A, int LDA, const float *B,
                          float *C);

/* Function Definitions */
/*
 * Arguments    : int numerator
 *                int denominator
 * Return Type  : int
 */
static int div_s32_floor(int numerator, int denominator)
{
  int quotient;
  if (denominator == 0) {
    if (numerator >= 0) {
      quotient = MAX_int32_T;
    } else {
      quotient = MIN_int32_T;
    }
  } else {
    unsigned int absDenominator;
    unsigned int absNumerator;
    unsigned int tempAbsQuotient;
    boolean_T quotientNeedsNegation;
    if (numerator < 0) {
      absNumerator = ~(unsigned int)numerator + 1U;
    } else {
      absNumerator = (unsigned int)numerator;
    }
    if (denominator < 0) {
      absDenominator = ~(unsigned int)denominator + 1U;
    } else {
      absDenominator = (unsigned int)denominator;
    }
    quotientNeedsNegation = ((numerator < 0) != (denominator < 0));
    tempAbsQuotient = absNumerator / absDenominator;
    if (quotientNeedsNegation) {
      absNumerator %= absDenominator;
      if (absNumerator > 0U) {
        tempAbsQuotient++;
      }
      quotient = -(int)tempAbsQuotient;
    } else {
      quotient = (int)tempAbsQuotient;
    }
  }
  return quotient;
}

/*
 * Arguments    : int M
 *                int K
 *                int N
 *                const float *A
 *                int LDA
 *                const float *B
 *                int LDB
 *                float *C
 *                int LDC
 * Return Type  : void
 */
static void macroKernel1(int M, int K, int N, const float *A, int LDA,
                         const float *B, int LDB, float *C, int LDC)
{
  int i;
  int idxA;
  int idxB;
  int idxC;
  int j;
  j = 0;
  idxB = 0;
  while (j <= N - 4) {
    idxC = LDC * j;
    i = 0;
    idxA = 0;
    while (i <= M - 4) {
      microKernel11(K, &A[idxA], LDA, &B[idxB], LDB, &C[idxC], LDC);
      idxA += 4;
      idxC += 4;
      i += 4;
    }
    while (i <= M - 1) {
      microKernel12(K, &A[idxA], LDA, &B[idxB], LDB, &C[idxC], LDC);
      idxA++;
      idxC++;
      i++;
    }
    idxB += LDB << 2;
    j += 4;
  }
  while (j <= N - 1) {
    idxC = LDC * j;
    i = 0;
    idxA = 0;
    while (i <= M - 4) {
      microKernel13(K, &A[idxA], LDA, &B[idxB], &C[idxC]);
      idxA += 4;
      idxC += 4;
      i += 4;
    }
    while (i <= M - 1) {
      microKernel14(K, &A[idxA], LDA, &B[idxB], &C[idxC]);
      idxA++;
      idxC++;
      i++;
    }
    idxB += LDB;
    j++;
  }
}

/*
 * Arguments    : int M
 *                int K
 *                int N
 *                int blockSizeM
 *                int blockSizeK
 *                int blockSizeN
 *                const float *A
 *                const float *B
 *                float *C
 * Return Type  : void
 */
static void matrixMultiply1(int M, int K, int N, int blockSizeM, int blockSizeK,
                            int blockSizeN, const float *A, const float *B,
                            float *C)
{
  int b_j1;
  int i0;
  int i0_ub;
  int k0;
  int k0_ub;
  memset(C, 0, (unsigned int)((M * N) << 2));
  if (blockSizeM >= M) {
    blockSizeM = M;
  } else {
    blockSizeM = (blockSizeM >> 2) << 2;
    if (blockSizeM <= 0) {
      blockSizeM = 1;
    }
  }
  if (blockSizeN >= N) {
    blockSizeN = N;
  } else {
    blockSizeN = (blockSizeN >> 2) << 2;
    if (blockSizeN <= 0) {
      blockSizeN = 1;
    }
  }
  i0_ub = div_s32_floor(M - 1, blockSizeM) + 1;
  k0_ub = div_s32_floor(K - 1, blockSizeK) + 1;
  for (b_j1 = 0; b_j1 < N; b_j1 += blockSizeN) {
    int N2;
    if (b_j1 > N - blockSizeN) {
      N2 = N - b_j1;
    } else {
      N2 = blockSizeN;
    }
    for (k0 = 1; k0 <= k0_ub; k0++) {
      int K2;
      int k;
      k = (k0 - 1) * blockSizeK;
      if (k > K - blockSizeK) {
        K2 = K - k;
      } else {
        K2 = blockSizeK;
      }
      for (i0 = 1; i0 <= i0_ub; i0++) {
        int b_i;
        int i;
        i = (i0 - 1) * blockSizeM;
        if (i > M - blockSizeM) {
          b_i = M - i;
        } else {
          b_i = blockSizeM;
        }
        macroKernel1(b_i, K2, N2, &A[i + M * k], M, &B[k + K * b_j1], K,
                     &C[i + M * b_j1], M);
      }
    }
  }
}

/*
 * Arguments    : int K
 *                const float *A
 *                int LDA
 *                const float *B
 *                int LDB
 *                float *C
 *                int LDC
 * Return Type  : void
 */
static void microKernel11(int K, const float *A, int LDA, const float *B,
                          int LDB, float *C, int LDC)
{
  float b_c;
  float c;
  float c_c;
  float d_c;
  float e_c;
  float f_c;
  float g_c;
  float h_c;
  float i_c;
  float j_c;
  float k_c;
  float l_c;
  float m_c;
  float n_c;
  float o_c;
  float p_c;
  int b_c_tmp;
  int c_c_tmp;
  int c_tmp;
  int d_c_tmp;
  int idxA;
  int idxB;
  int k;
  idxA = 0;
  idxB = 0;
  c = C[0];
  b_c = C[1];
  c_c = C[2];
  d_c = C[3];
  e_c = C[LDC];
  f_c = C[LDC + 1];
  g_c = C[LDC + 2];
  h_c = C[LDC + 3];
  c_tmp = LDC << 1;
  i_c = C[c_tmp];
  j_c = C[c_tmp + 1];
  k_c = C[c_tmp + 2];
  l_c = C[c_tmp + 3];
  m_c = C[LDC * 3];
  b_c_tmp = LDC * 3 + 1;
  n_c = C[b_c_tmp];
  c_c_tmp = LDC * 3 + 2;
  o_c = C[c_c_tmp];
  d_c_tmp = LDC * 3 + 3;
  p_c = C[d_c_tmp];
  for (k = 0; k < K; k++) {
    float a;
    float b;
    float b_a;
    float b_b;
    float c_a;
    float c_b;
    float d_a;
    float d_b;
    a = A[idxA];
    b_a = A[idxA + 1];
    c_a = A[idxA + 2];
    d_a = A[idxA + 3];
    b = B[idxB];
    b_b = B[idxB + LDB];
    c_b = B[idxB + (LDB << 1)];
    d_b = B[idxB + LDB * 3];
    c += a * b;
    b_c += b_a * b;
    c_c += c_a * b;
    d_c += d_a * b;
    e_c += a * b_b;
    f_c += b_a * b_b;
    g_c += c_a * b_b;
    h_c += d_a * b_b;
    i_c += a * c_b;
    j_c += b_a * c_b;
    k_c += c_a * c_b;
    l_c += d_a * c_b;
    m_c += a * d_b;
    n_c += b_a * d_b;
    o_c += c_a * d_b;
    p_c += d_a * d_b;
    idxA += LDA;
    idxB++;
  }
  C[0] = c;
  C[1] = b_c;
  C[2] = c_c;
  C[3] = d_c;
  C[LDC] = e_c;
  C[LDC + 1] = f_c;
  C[LDC + 2] = g_c;
  C[LDC + 3] = h_c;
  C[c_tmp] = i_c;
  C[c_tmp + 1] = j_c;
  C[c_tmp + 2] = k_c;
  C[c_tmp + 3] = l_c;
  C[LDC * 3] = m_c;
  C[b_c_tmp] = n_c;
  C[c_c_tmp] = o_c;
  C[d_c_tmp] = p_c;
}

/*
 * Arguments    : int K
 *                const float *A
 *                int LDA
 *                const float *B
 *                int LDB
 *                float *C
 *                int LDC
 * Return Type  : void
 */
static void microKernel12(int K, const float *A, int LDA, const float *B,
                          int LDB, float *C, int LDC)
{
  float b_c;
  float c;
  float c_c;
  float d_c;
  int c_tmp;
  int idxA;
  int idxB;
  int k;
  idxA = 0;
  idxB = 0;
  c = C[0];
  b_c = C[LDC];
  c_tmp = LDC << 1;
  c_c = C[c_tmp];
  d_c = C[LDC * 3];
  for (k = 0; k < K; k++) {
    float a;
    float b;
    float b_b;
    float c_b;
    float d_b;
    a = A[idxA];
    b = B[idxB];
    b_b = B[idxB + LDB];
    c_b = B[idxB + (LDB << 1)];
    d_b = B[idxB + LDB * 3];
    c += a * b;
    b_c += a * b_b;
    c_c += a * c_b;
    d_c += a * d_b;
    idxA += LDA;
    idxB++;
  }
  C[0] = c;
  C[LDC] = b_c;
  C[c_tmp] = c_c;
  C[LDC * 3] = d_c;
}

/*
 * Arguments    : int K
 *                const float *A
 *                int LDA
 *                const float *B
 *                float *C
 * Return Type  : void
 */
static void microKernel13(int K, const float *A, int LDA, const float *B,
                          float *C)
{
  float b_c;
  float c;
  float c_c;
  float d_c;
  int idxA;
  int idxB;
  int k;
  idxA = 0;
  idxB = 0;
  c = C[0];
  b_c = C[1];
  c_c = C[2];
  d_c = C[3];
  for (k = 0; k < K; k++) {
    float aFloat;
    float b;
    float b_aFloat;
    float c_aFloat;
    float d_aFloat;
    aFloat = A[idxA];
    b_aFloat = A[idxA + 1];
    c_aFloat = A[idxA + 2];
    d_aFloat = A[idxA + 3];
    b = B[idxB];
    c += aFloat * b;
    b_c += b_aFloat * b;
    c_c += c_aFloat * b;
    d_c += d_aFloat * b;
    idxA += LDA;
    idxB++;
  }
  C[0] = c;
  C[1] = b_c;
  C[2] = c_c;
  C[3] = d_c;
}

/*
 * Arguments    : int K
 *                const float *A
 *                int LDA
 *                const float *B
 *                float *C
 * Return Type  : void
 */
static void microKernel14(int K, const float *A, int LDA, const float *B,
                          float *C)
{
  float c;
  int idxA;
  int idxB;
  int k;
  idxA = 0;
  idxB = 0;
  c = C[0];
  for (k = 0; k < K; k++) {
    float aFloat;
    float b;
    aFloat = A[idxA];
    b = B[idxB];
    c += aFloat * b;
    idxA += LDA;
    idxB++;
  }
  C[0] = c;
}

/*
 * Arguments    : c_coder_internal_ctarget_DeepLe *obj
 *                const double indata[3]
 * Return Type  : float
 */
float c_DeepLearningNetwork_predictAn(c_coder_internal_ctarget_DeepLe *obj,
                                      const double indata[3])
{
  static const float A[300] = {
      -5.21003931E-5F,  -0.00585350348F,  0.0510879F,       0.00187931978F,
      0.00249659061F,   -0.0196663029F,   0.00739752F,      -0.000697557F,
      -0.00146606832F,  0.00467301346F,   -0.000110499321F, -0.00776807778F,
      0.0472292788F,    0.00150177942F,   0.00279995496F,   -0.0232601035F,
      0.0111698993F,    0.00263211457F,   0.00571184233F,   0.014390274F,
      -2.53034705E-5F,  -0.00219400693F,  0.0400833748F,    0.00177254446F,
      0.00291442289F,   -0.0199935082F,   -0.00927665178F,  -5.66266172E-5F,
      -0.00660443492F,  0.00189438241F,   0.00148445449F,   -0.16503711F,
      -0.137095585F,    -0.0035358055F,   -0.0367559567F,   0.00348621653F,
      0.208301708F,     -0.22681056F,     0.138813332F,     0.306008935F,
      0.000255450228F,  -0.10897924F,     0.0862717703F,    0.00408825697F,
      -0.00142025074F,  0.0750265345F,    0.255400628F,     -0.272573F,
      -0.147845119F,    0.375907183F,     0.00181417773F,   0.145421132F,
      0.208143324F,     -0.00309077254F,  -0.0130630247F,   0.00551001448F,
      0.180201F,        -0.280397743F,    -0.268902063F,    0.437127799F,
      0.00649861898F,   -0.255419374F,    0.429899305F,     0.184480563F,
      0.0381511897F,    -0.0096874088F,   0.289277405F,     0.229503497F,
      -0.107455656F,    0.0783385783F,    0.0063052238F,    0.0537939332F,
      0.261598706F,     0.127674446F,     0.028013017F,     0.0176897217F,
      0.295789868F,     0.216089904F,     -0.0276230592F,   0.0631721F,
      0.00652231323F,   0.113713413F,     0.0447245613F,    0.176065192F,
      0.0427499898F,    0.0113582F,       0.284929097F,     0.226926714F,
      -0.15166539F,     0.0664140508F,    -6.4162974E-5F,   -0.0190803446F,
      -0.407672375F,    -0.00594103942F,  0.00656533241F,   -0.0210456066F,
      0.053239774F,     -0.00868646707F,  -0.110831216F,    -0.00722646853F,
      -0.000133735259F, -0.00873912591F,  -0.464939684F,    -0.00880964845F,
      0.00692576356F,   -0.00330442679F,  0.0270168502F,    0.000220266753F,
      0.103614755F,     0.0214245785F,    -5.46298361E-5F,  -0.00161725888F,
      -0.277978033F,    -0.00627513602F,  0.00697105192F,   -0.0129774539F,
      0.0407895595F,    -0.0109663429F,   0.0226983745F,    0.00704726437F,
      -0.000142047254F, -0.0120871495F,   0.0597880222F,    -0.0159333143F,
      -0.00218512188F,  -0.0299718101F,   0.0381476618F,    -0.0412674583F,
      0.0677239895F,    -0.000789898448F, -0.000314498699F, -0.0659372434F,
      0.0514722355F,    -0.0123792198F,   -0.000209154445F, -0.0369796939F,
      0.0436466075F,    -0.0360935964F,   0.00596315134F,   0.026312558F,
      -7.17633811E-5F,  -0.0237359218F,   0.0172415078F,    -0.01609548F,
      -0.000717031F,    -0.0370570868F,   -0.00408304157F,  -0.0478304513F,
      -0.0254453644F,   0.00917231105F,   0.00218451745F,   -0.00516827824F,
      0.0729887635F,    -0.00572830252F,  -0.00539829535F,  -0.0283818394F,
      -0.141041577F,    -0.0989139676F,   0.108889185F,     -0.00204118784F,
      0.00219202321F,   0.0562930591F,    0.0300756544F,    -0.00293840212F,
      -0.00947520882F,  -0.0503335111F,   -0.119735546F,    -0.111290395F,
      0.225236475F,     -0.0427818634F,   0.00219053146F,   0.0421329699F,
      0.0146452496F,    -0.00426666951F,  -0.00732334098F,  -0.043830812F,
      -0.150003463F,    -0.105190493F,    0.0799479187F,    0.00666735088F,
      0.00193381356F,   -0.0796690285F,   -0.537881434F,    0.0500917099F,
      0.0501294062F,    -0.0892772526F,   0.247206256F,     -0.0028694137F,
      -0.221704647F,    0.060041897F,     0.00146256131F,   -0.0458251908F,
      -0.568827093F,    0.0215600822F,    0.0517465025F,    -0.0434421971F,
      0.179516211F,     0.0297668222F,    0.309027016F,     0.101754978F,
      0.00201156386F,   0.00157026947F,   -0.494061679F,    0.046591714F,
      0.057635922F,     -0.0821440369F,   0.207041904F,     0.000682968355F,
      -0.0569431782F,   0.136302173F,     -0.00317594828F,  0.028421618F,
      -0.213752389F,    0.00524977548F,   0.000595158315F,  0.0407290943F,
      0.13489303F,      -0.00449078158F,  -0.136341721F,    0.0346599035F,
      -0.00316377869F,  -0.0488055237F,   -0.193471849F,    -0.00205214042F,
      0.00503589911F,   0.0754086375F,    0.0674895048F,    0.0576585643F,
      0.184799731F,     0.0812878385F,    -0.0032301615F,   -0.0377189219F,
      -0.139931828F,    0.00412063254F,   -0.000469037535F, 0.0490906797F,
      0.0872662812F,    0.0259439051F,    0.0952994F,       0.0215083063F,
      -0.0175177418F,   0.149232179F,     0.0183944013F,    -0.0477902777F,
      -0.0619437434F,   -0.59527427F,     0.418135613F,     0.129865304F,
      0.152112469F,     0.0879991F,       -0.0160916466F,   -0.194978699F,
      -0.102433965F,    -0.0678474158F,   -0.0501096435F,   -0.725760877F,
      0.320762455F,     0.127582297F,     0.0769534409F,    0.199885204F,
      -0.0176481791F,   -0.104138419F,    0.234236434F,     -0.0417946801F,
      -0.0439930782F,   -0.636077821F,    0.472985268F,     0.151728466F,
      0.108065747F,     0.299042612F,     -0.00169700396F,  -0.155740589F,
      0.109901533F,     0.0292760227F,    0.130393475F,     -0.226640522F,
      0.19022961F,      -0.0345295221F,   -0.40897432F,     0.130708888F,
      -0.00258792704F,  -0.055372633F,    0.0383562297F,    0.00702057872F,
      0.137340501F,     -0.182684436F,    0.140596554F,     -0.027157072F,
      0.591936886F,     0.219856367F,     -0.00173459644F,  0.0126294354F,
      0.0336105F,       0.0277676526F,    0.149435222F,     -0.223740429F,
      0.160211563F,     -0.049391415F,    -0.090766184F,    0.345294297F};
  static const float c_A[100] = {
      0.00368530932F,  0.0788252F,     0.0388908051F,   -0.00926318672F,
      0.0165605843F,   0.0140008517F,  0.0822624341F,   0.00483048055F,
      -0.0619496666F,  0.0395448618F,  0.0800617412F,   0.207009956F,
      0.0723515F,      -0.121265739F,  0.235900491F,    -0.332028031F,
      0.314229339F,    0.00864609797F, -0.0582159907F,  0.0146299032F,
      -0.296338469F,   -1.07805884F,   0.53578645F,     0.250604093F,
      -0.368076563F,   0.580119073F,   0.134345293F,    0.539257169F,
      -0.376739919F,   -0.74892813F,   -0.0364022218F,  -0.670212686F,
      -0.211743876F,   0.0703038573F,  -0.028372895F,   0.0229542069F,
      0.136201829F,    0.471116751F,   0.115785606F,    -0.147960961F,
      0.053401053F,    0.143967807F,   0.0860152617F,   -0.0525839627F,
      0.117393129F,    0.195905328F,   0.120470196F,    0.0196197256F,
      -0.20073472F,    0.00927698798F, -0.00392396701F, -0.0702216774F,
      -0.0262547545F,  -0.223930478F,  0.0174612869F,   0.21890603F,
      -0.110541686F,   -0.0448486879F, -0.365294725F,   -0.0576072931F,
      -0.186162367F,   -0.875013828F,  -0.131431893F,   0.299815774F,
      -0.00849562604F, 0.0314700454F,  0.24032715F,     0.751677454F,
      0.116903767F,    -0.417561591F,  -0.116586626F,   -0.876710474F,
      -0.244133398F,   0.346419752F,   -0.0388824306F,  0.348553866F,
      0.434009165F,    0.483887762F,   0.0881906077F,   -0.111046731F,
      0.036721576F,    -0.0214269515F, -0.0387394801F,  0.0189145561F,
      0.0738507435F,   -0.067109108F,  -0.342266113F,   -0.0972182676F,
      -0.00372850383F, 0.0289713591F,  0.0684842765F,   0.126137719F,
      -0.0366004147F,  0.0679966956F,  0.200063333F,    -0.0261580236F,
      0.177082449F,    0.234345123F,   -0.0399057604F,  -0.0658776909F};
  static const float b_A[90] = {
      -0.0390498526F,  -0.439507902F,   0.284812033F,   -0.234067217F,
      -0.254390419F,   -0.139628977F,   -0.244053736F,  -0.179787859F,
      -0.687476635F,   0.242516726F,    -0.0346688367F, 1.09123337F,
      0.634603202F,    -0.124851763F,   -0.258052528F,  0.0410607047F,
      0.033054F,       -0.0039266781F,  1.76507914F,    0.29959771F,
      -0.040156F,      0.22246094F,     0.459119499F,   -0.234346196F,
      -0.239229292F,   -0.109942533F,   -0.14410153F,   -0.315406382F,
      0.177723274F,    0.29039526F,     -0.0123442626F, -0.115351163F,
      -0.164472014F,   -0.0482107177F,  -0.173841298F,  0.0333682448F,
      0.0393135957F,   0.129874304F,    -0.54424721F,   0.107334964F,
      -0.0116245216F,  0.471544445F,    0.506967F,      -0.0650182888F,
      -0.165345371F,   0.094952777F,    0.114947155F,   0.131284341F,
      1.05316567F,     0.110709585F,    -0.0135837048F, 0.0659358129F,
      0.274819463F,    -0.102595165F,   -0.166046172F,  0.0625804812F,
      0.0666540414F,   -0.033648055F,   -0.0086643137F, 0.14818123F,
      0.000538963941F, -0.301801741F,   -0.0410655215F, -0.0958167F,
      -0.0755983368F,  0.048673477F,    -0.248680249F,  0.0862369761F,
      -0.0314007401F,  0.249212965F,    0.00192476169F, 0.41912812F,
      -0.144719884F,   -0.0545180924F,  -0.0730620772F, 0.0339112394F,
      -0.0289405584F,  -0.00814715214F, 0.514398575F,   0.19141683F,
      0.000546556083F, 0.371678025F,    0.392538697F,   -0.123101562F,
      -0.0590886921F,  0.0667146F,      -0.184876665F,  -0.0447333902F,
      -0.314454F,      0.42586869F};
  static const float d_A[30] = {
      -0.0686262473F, -0.445102751F,  0.523660302F,   -0.200257272F,
      -0.132478952F,  0.133308783F,   0.0592188388F,  0.0454306938F,
      -0.377587855F,  -0.204671562F,  -0.278115332F,  -0.452131599F,
      -0.543175876F,  0.412341654F,   0.00705988891F, 0.376950353F,
      -0.0200957842F, 0.362740219F,   0.413359046F,   -0.265993476F,
      0.073246412F,   0.173015073F,   0.0795114189F,  -0.164584801F,
      0.0393936634F,  -0.0143012321F, 0.0780747F,     -0.445764393F,
      0.159213036F,   -0.0272671971F};
  static const float fv[30] = {
      -0.756234825F, -0.678904057F,  -0.800389111F, -0.865392566F,
      -0.527903199F, -0.575058F,     -0.692148864F, -0.305814594F,
      -0.360718191F, -0.0995239317F, 0.50783F,      3.35258365F,
      0.69812119F,   0.461332709F,   0.512394667F,  0.985386133F,
      0.501029849F,  0.801815271F,   3.6086359F,    1.00913262F,
      -0.79178673F,  1.05175722F,    -0.285161644F, -0.730326533F,
      -0.495599508F, -0.534022212F,  -0.581010878F, -0.438152611F,
      0.570671856F,  0.0217000172F};
  static const float fv1[10] = {
      0.201695696F,  0.755945146F, -0.173563585F, 0.164323375F, 0.0603933036F,
      -0.384808332F, 0.354060173F, -0.264207F,    0.146861181F, 0.653098166F};
  static const float fv2[10] = {-0.132474273F, -0.0808123F,   0.293516576F,
                                -0.224730358F, -0.200926483F, -0.00480251526F,
                                -0.425897628F, -0.338979632F, 0.0205783267F,
                                -0.563319862F};
  float Z[30];
  float gateValues[30];
  float CS[10];
  float stateValues[10];
  float miniBatch[3];
  float f;
  int k;
  miniBatch[0] = (float)indata[0];
  miniBatch[1] = (float)indata[1];
  miniBatch[2] = (float)indata[2];
  if (!obj->IsNetworkInitialized) {
    for (k = 0; k < 10; k++) {
      obj->NetworkState[0].f1[0].f1[k] = 0.0F;
      obj->NetworkState[0].f1[1].f1[k] = 0.0F;
    }
    obj->IsNetworkInitialized = true;
  }
  matrixMultiply1(30, 10, 1, 96, 144, 180, &A[0],
                  &obj->NetworkState[0].f1[1].f1[0], &Z[0]);
  for (k = 0; k < 30; k++) {
    Z[k] += fv[k];
  }
  matrixMultiply1(30, 3, 1, 96, 144, 180, &b_A[0], &miniBatch[0],
                  &gateValues[0]);
  for (k = 0; k < 30; k++) {
    gateValues[k] = 1.0F / (expf(-(gateValues[k] + Z[k])) + 1.0F);
  }
  matrixMultiply1(10, 10, 1, 96, 144, 180, &c_A[0],
                  &obj->NetworkState[0].f1[1].f1[0], &CS[0]);
  for (k = 0; k < 10; k++) {
    CS[k] += fv1[k];
  }
  matrixMultiply1(10, 3, 1, 96, 144, 180, &d_A[0], &miniBatch[0],
                  &stateValues[0]);
  f = 0.0F;
  for (k = 0; k < 10; k++) {
    float f1;
    float f2;
    f1 = tanhf(stateValues[k] + CS[k]) * gateValues[k] +
         gateValues[k + 10] * obj->NetworkState[0].f1[0].f1[k];
    CS[k] = f1;
    f2 = tanhf(f1) * gateValues[k + 20];
    stateValues[k] = f2;
    obj->NetworkState[0].f1[0].f1[k] = f1;
    obj->NetworkState[0].f1[1].f1[k] = f2;
    f += fv2[k] * f2;
  }
  return fminf(fmaxf(0.0F, f + 0.755889952F), 1.0F);
}

/*
 * File trailer for predictAndUpdateState.c
 *
 * [EOF]
 */
