#include "Hardware.h"
#include "libraries/GPUDetect/include/DeviceId.h"

Hardware* Hardware::GetHardware()
{
	Hardware* h = new Hardware();

	SDL_GetVersion(&h->sdlVersion);
	h->glVersion = glGetString(GL_VERSION);

	h->cpu.cpuCount = SDL_GetCPUCount();
	h->cpu.cpuCacheLineSize = SDL_GetCPUCacheLineSize();

	h->ram = SDL_GetSystemRAM() / 1000.0f;

	h->caps._3DNow = SDL_Has3DNow();
	h->caps.altiVec = SDL_HasAltiVec();
	h->caps.avx = SDL_HasAVX();
	h->caps.avx2 = SDL_HasAVX2();
	h->caps.mmx = SDL_HasMMX();
	h->caps.rdtsc = SDL_HasRDTSC();
	h->caps.sse = SDL_HasSSE();
	h->caps.sse2 = SDL_HasSSE2();
	h->caps.sse3 = SDL_HasSSE3();
	h->caps.sse41 = SDL_HasSSE41();
	h->caps.sse42 = SDL_HasSSE42();

	if (getGraphicsDeviceInfo(&h->gpu.vendor, &h->gpu.id, &h->gpu.name, &h->gpu.budget, &h->gpu.usage, &h->gpu.available, &h->gpu.reserved)) {
		h->gpu.budget /= 1024.0f * 1024.0f;
		h->gpu.usage /= 1024.0f * 1024.0f;
		h->gpu.available /= 1024.0f * 1024.0f;
		h->gpu.reserved /= 1024.0f * 1024.0f;
	}

	return h;
}