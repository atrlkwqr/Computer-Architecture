#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <math.h>

#define TOTAL_BIT 32

using namespace std;

char arr[10000000][20];
int cache[10000000] = { 0 };
int priority[10000000] = { 0 };


int main(int argc, char* argv[])
{
	if (argc == 5) {
		int cachebyte;
		int cacheblock;
		int associativity;
		int tagBit, indexBit, offsetBit = 0;
		unsigned int totalbit = 0;
		int size = 0;
		int hit = 0;
		int minnum;
		int prioritynum = 1;

		ifstream is(argv[1]);

		cachebyte = atoi(argv[2]);
		cacheblock = atoi(argv[3]);
		associativity = atoi(argv[4]);


		offsetBit = log2(cacheblock);
		indexBit = log2(cachebyte / cacheblock / associativity);
		tagBit = TOTAL_BIT - offsetBit - indexBit;


		if (is.fail()) {
			cout << "file does not exist." << endl;
			return 1;
		}

		double checkcacheblock1 = log2(cacheblock);
		int checkcacheblock2 = log2(cacheblock);

		if (checkcacheblock1 != checkcacheblock2) {
			cout << "cacheblock is not a exponentiation of 2." << endl;
			return 1;
		}

		if (!(associativity == 1 || associativity == 2 || associativity == 4 || associativity == 8)) {
			cout << "value of associativity is other than 1, 2, 4 and 8 been entered." << endl;
			return 1;
		}

		if (cachebyte % (cacheblock * associativity) != 0) {
			cout << "cachesize is not a multiple of cacheblock * associativity." << endl;
			return 1;
		}

		for (size; !is.eof(); size++) {
			is >> arr[size];
		}

		for (int i = 1; i < size; i = i + 3) {
			int tagBitarr[TOTAL_BIT] = { 0 };
			int indexBitarr[TOTAL_BIT] = { 0 };
			int address[TOTAL_BIT] = { 0 };
			int temp = 0;
			int min = 0;
			int position = 0;

			totalbit = strtoul(arr[i], NULL, 16);

			while (1)
			{
				address[position] = totalbit % 2;
				totalbit = totalbit / 2;
				position++;
				if (totalbit == 0) break;
			}

			for (int i = TOTAL_BIT - 1; i >= 0; i--)
			{
				if (i >= TOTAL_BIT - tagBit) tagBitarr[temp++] = address[i];
				if (i == TOTAL_BIT - tagBit) temp = 0;
				if (i < TOTAL_BIT - tagBit && i >= TOTAL_BIT - tagBit - indexBit) indexBitarr[temp++] = address[i];
			}

			int intindex = 0;
			unsigned int inttag = 0;

			for (int j = 0; j <= tagBit - 1; j++) inttag = inttag + tagBitarr[tagBit - 1 - j] * pow(2, j);
			for (int j = 0; j <= indexBit - 1; j++) intindex = intindex + indexBitarr[indexBit - 1 - j] * pow(2, j);

			inttag = inttag * pow(2, offsetBit);
			int start = intindex * offsetBit;
			int indexmax = pow(2, indexBit) * offsetBit;

			for (int s = start; s < cachebyte / cacheblock * offsetBit; s = s + indexmax) {
				for (int a = 0; a < offsetBit; a++) {
					if (cache[s] == inttag) {
						hit++;
						// cout << "hit!!!!!!!!!!!!!!!!" << endl;
						for (int b = 0; b < offsetBit; b++) priority[s + b] = prioritynum;
						prioritynum++;
						goto finish;
					}
				}
			}

			minnum = priority[start];
			for (int s = 0; s < associativity; s++) {
				if (priority[start + indexmax * s] <= minnum) {
					minnum = priority[start + indexmax * s];
					min = start + indexmax * s;
				}
			}

			cache[min] = inttag;
			priority[min] = prioritynum;
			prioritynum++;

		finish:;

		}

		cout << "tag: " << tagBit << "bits" << endl;
		cout << "index: " << indexBit << "bits" << endl;
		cout << "offset: " << offsetBit << "bits" << endl;
		cout << "Result: total acces" << size / 3 << ", hit " << hit << ", hit rate " << ((double)hit / ((double)size / 3)) << endl;
		is.close();
	}

	else {
		cout << "In case of not four parameters." << endl;
		return 1;
	}


	return 0;
}