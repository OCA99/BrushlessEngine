#include "libraries/SDL/include/SDL.h"

#include <string>

struct CPU {
	int cpuCount;
	int cpuCacheLineSize;
};

struct CAPS {
	bool _3DNow;
	bool altiVec;
	bool avx;
	bool avx2;
	bool mmx;
	bool rdtsc;
	bool sse;
	bool sse2;
	bool sse3;
	bool sse41;
	bool sse42;
};

struct GPU {
	unsigned int vendor;
	unsigned int id;
	std::wstring name;
	unsigned long long budget;
	unsigned long long usage;
	unsigned long long available;
	unsigned long long reserved;
};

class Hardware {
public:
	Hardware() {}

	static Hardware* GetHardware();

	SDL_version sdlVersion;
	CPU cpu;
	float ram;
	CAPS caps;
	GPU gpu;
};