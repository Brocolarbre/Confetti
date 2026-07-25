#pragma once

#if defined(CONFETTI_STATIC)
	#define CONFETTI_API
#else
	#if defined(_WIN32)
		#if defined(CONFETTI_BUILD)
			#define CONFETTI_API __declspec(dllexport)
		#else
			#define CONFETTI_API __declspec(dllimport)
		#endif
	#else
		#define CONFETTI_API __attribute__((visibility("default")))
	#endif
#endif