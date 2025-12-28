#pragma once

#ifdef _WIN32
	#ifdef CONFETTIENGINE_STATIC
		#define CONFETTIENGINE_EXPORT
	#else
		#ifdef CONFETTIENGINE_EXPORT
			#define CONFETTIENGINE_EXPORT __declspec(dllexport)
		#else
			#define CONFETTIENGINE_EXPORT __declspec(dllimport)
		#endif
	#endif
#elif __linux__
	#define CONFETTIENGINE_EXPORT
#endif