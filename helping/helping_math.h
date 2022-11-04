#pragma once
#include <cmath>
namespace helping_function
{
	double round(double val, int digits_count = 2)
	{
		int k = std::pow(10, digits_count);
		return std::round(val * k) / k;
	}
	double lerp(double a, double b, double t)
	{
		return a + (b - a) * t;
	}
}
