#include "stdafx.h"
#include "ProcessData.h"
#include <vector>
#include <fstream>


ProcessData::ProcessData()
{
}

ProcessData::~ProcessData()
{
}

void ProcessData::run(int numberOfThreads, string inputPath, bool isAsmDllSelected) {
	
	std::vector<float> dataPoints;
	//Wczytanie danych z pliku
	try {
		ifstream dataFile;
		dataFile.open(inputPath);
		if (dataFile.is_open()) {
			float x;
			while (!dataFile.eof()) {
				dataFile >> x;
				dataPoints.push_back(x);
			}
		}
		dataFile.close();
	}
	catch (...) {
		throw string("Nie udało się wczytać danych");
	}
	
	


	thread* threads = new thread[numberOfThreads];
	int size = dataPoints.size();

	std::vector<float>vectorOfSums(numberOfThreads);
	float sum=0;

	//Wektor długości (x-ów)
	std::vector<float> widths;
	//Wektor wysokości (y-ków)
	std::vector<float> heights;
	

	for (int i = 0; i < (size - 3); i = i + 2)
	{
		float x = dataPoints[i+2]- dataPoints[i];
		widths.push_back(x);
		float y = (dataPoints[i+1] + dataPoints[i+3])/2;
		heights.push_back(y);
	}

	//Ilość danych w wektorach
	int widthsSize = (dataPoints.size()/2)-1;
	int threadSize = ceil(widths.size() / (float)numberOfThreads);

	while (threadSize % 4 != 0)
		threadSize++;



	for (int i = widthsSize; i < threadSize*numberOfThreads; i++)
	{
		heights.push_back(0);
		widths.push_back(0);
	}

	//Start zegara
	clock_t begin = clock();



	if (isAsmDllSelected) {
		HMODULE DLL = LoadLibrary(TEXT("JAAsm4.dll"));
		if (DLL == NULL) {
			throw string("Problem ze znalezieniem biblioteki.");
		}

		//Ładowanie biblioteki asm
		MyProc1 procedure = (MyProc1)GetProcAddress(DLL, "calc");

		//Wyjątek w przypadku braku biblioteki
		if (!procedure)
			throw string("Problem z wczytaniem funkcji z biblioteki.");

		for (int i = 0; i < numberOfThreads; i++)
		{
			//Tworzenie nowego wątku
			threads[i] = thread(procedure, &vectorOfSums[i], &widths[i*threadSize], &heights[i*threadSize], threadSize);
		}
		for (int i = 0; i < numberOfThreads; i++)
		{
			threads[i].join();
		}	
	}
	else {
		//Obsługa dla biblioteki c++
		HMODULE DLL = LoadLibrary(TEXT("JACpp.dll"));
		if (DLL == NULL) {
			throw string("Nie znaleziono biblioteki c++");
		}

		//Ładowanie biblioteki C++
		JACpp procedure = (JACpp)GetProcAddress(DLL, "Calc");

		//Wyjątek w przypadku braku biblioteki
		if (!procedure)
			throw string("Nie udalo sie znalezc funkcji");


		for (int i = 0; i < numberOfThreads; i++)
		{
			//Tworzenie nowego wątku
			threads[i] = thread(procedure, &vectorOfSums[i], &widths[i*threadSize], &heights[i*threadSize], threadSize);
		}
		for (int i = 0; i < numberOfThreads; i++)
		{
			threads[i].join();
		}
	}

	

	clock_t end = clock();
	for (int i = 0; i < vectorOfSums.size(); i++)
		sum = sum + vectorOfSums[i];

	double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
	std::cout << "Czas obliczen: " << elapsed_secs << endl;

	//Zapis do pliku tu dodać;
	cout << "Wynik: " << sum << endl;

	return;

}


