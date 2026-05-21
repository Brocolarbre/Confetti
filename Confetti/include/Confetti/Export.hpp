#pragma once

#ifdef _WIN32
	#ifdef CONFETTI_STATIC
		#define CONFETTI_EXPORT
	#else
		#ifdef CONFETTI_EXPORT
			#define CONFETTI_EXPORT __declspec(dllexport)
		#else
			#define CONFETTI_EXPORT __declspec(dllimport)
		#endif
	#endif
#elif __linux__
	#define CONFETTI_EXPORT
#endif