#include "stdafx.h"
#include "ProcessData.h"

int main(int argc, char *argv[])
{
	try {
		bool isAsmDllSelected = false;
		//Sciezka do pliku z danymi
		string inputPath = "";
		//Sciezka wyjsciowa
	
		SYSTEM_INFO systemInfo;
		GetSystemInfo(&systemInfo);
		//Ilosc watkow
		int numberOfThreads = systemInfo.dwNumberOfProcessors;

		for (int i = 1; i < argc; i++) {
			string s(argv[i]);
			if (s.compare("-i") == 0) {
				if (i + 1 < argc) {
					string s2(argv[i + 1]);
					inputPath = s2;
				}
				else {
					throw string("Bledna sciezka do pliku");
				}
			}
			else if (s.compare("-t") == 0) {
				if (i + 1 < argc) {
					string s2(argv[i + 1]);
					numberOfThreads = stoi(s2);
					if (numberOfThreads < 1)
						numberOfThreads = 1;
					else if (numberOfThreads > 64)
						numberOfThreads = 64;
				}
				else {
					throw string("Bledna ilosc watkow");
				}
			}
			else if (s.compare("-d") == 0) {
				if (i + 1 < argc) {
					string s2(argv[i + 1]);
					isAsmDllSelected = s2.compare("1") == 0;
				}
				else {
					throw string("Nie wybrano biblioteki");
				}
			}
		}

		if (inputPath == "") {
			throw string("Nie podano sciezki do pliku");
		}
		

		ProcessData proc;

		proc.run(numberOfThreads, inputPath, isAsmDllSelected);

	}
	catch (string e) {
		cout << e << endl;
	}
	system("pause");
}

