#ifdef RDRAND_FUNC_H
#error Already included
#else
#define RDRAND_FUNC_H

extern "C" void rdrand_func1(size_t *pOut);
extern "C" void rdrand_func4(size_t *pOut);
extern "C" void rdrand_func8(size_t *pOut);
extern "C" void rdrand_func16(size_t *pOut);
extern "C" void rdrand_func32(size_t *pOut);
extern "C" void rdrand_func64(size_t *pOut);
extern "C" void rdrand_func128(size_t *pOut);
extern "C" void rdrand_func256(size_t *pOut);
extern "C" void rdrand_func512(size_t *pOut);
extern "C" void rdrand_func1024(size_t *pOut);

#endif
