#pragma once
template<typename P, int X>
class VariadicCoordinateLoader
{
	P arr[X];
	int recurIter = 0;

	template<typename T, typename... Args>
	VariadicCoordinateLoader(T t, Args... args);

	template <typename T>
	void load(T t);

	template<typename T, typename... Args>
	void load(T t, Args... args);

};

template<typename P, int X>
template<typename T, typename ...Args>
inline VariadicCoordinateLoader<P, X>::VariadicCoordinateLoader(T t, Args ...args)
{
	
	load(t, args...);
}

template<typename P, int X>
template<typename T>
inline void VariadicCoordinateLoader<P, X>::load(T t)
{
	arr[recurIter] = t;
	recurIter++;
}

template<typename P, int X>
template<typename T, typename ...Args>
inline void VariadicCoordinateLoader<P, X>::load(T t, Args ...args)
{
	arr[recurIter] = t;
	recurIter++;
	load(args...);
}
