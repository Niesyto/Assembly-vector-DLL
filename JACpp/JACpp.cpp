#include "stdafx.h"
#include "JACpp.h"

void Calc(float *sum, float *x1, float* x2, int size)
{

	// Obliczona suma
	float newSum = 0;

	// Dla całej tablicy
	
	for (int j = 0; j < size; j++) {
		// Zwiększ sume o iloczyn elementow tablicy tablicy
		newSum += *x1 * *x2;
		// Inkrementuj wskażniki
		*x1++;
		*x2++;
	}
	
	// Zapis sumy
	*sum = newSum;

}
