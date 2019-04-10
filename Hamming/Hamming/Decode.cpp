#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

using namespace std;

int Decode() {
	cout << "Decoding" << endl;

	fstream Decoded, Encoded;
	Decoded.open("Decoded.txt");
	Encoded.open("Encoded.txt");
	int a = 0, b = 0;
	char ch1, ch2;
	int num;
	int count;
	int f = 0;
	char sent[10000];
	
	//---------------------------------------------------------------------------------------------------------
	while (Encoded >> num) {
		int numS = num;

		bool fullBin[20], unsepChars[14];

		for (int i = 0; i < 19; i++) {													//converting coded number to binary in array
			fullBin[i] = num % 2;
			num = num / 2;
		}
	//---------------------------------------------------------------------------------------------------------
		bool p[8];																		//creating parody bit array

		p[1] = (fullBin[3] + fullBin[6] + fullBin[9] + fullBin[11] + fullBin[13]		//finds first parody bit
			+ fullBin[15] + fullBin[17]) % 2;
		p[2] = (fullBin[5] + fullBin[6] + fullBin[10] + fullBin[11] + fullBin[14]		//finds second parody bit
			+ fullBin[15] + fullBin[18]) % 2;
		p[4] = (fullBin[7] + fullBin[9] + fullBin[10] + fullBin[11] + fullBin[16]		//finds third parody bit
			+ fullBin[17] + fullBin[18]) % 2;
		p[8] = (fullBin[12] + fullBin[13] + fullBin[14] + fullBin[15] + fullBin[16]		//finds fourth parody bit
			+ fullBin[17] + fullBin[18]) % 2;											//yes its bulky

	//---------------------------------------------------------------------------------------------------------
		bool par[8];

		int g = 1;
		for (int i = 1; i < 19; i++) {													//puts parody bits in par function and puts char bits
			if(i == 1 || i == 2 || i == 4 || i == 8){									//in unsepChars function
				par[i] = fullBin[i];
				g++;
			}
			else {
				unsepChars[i - g] = fullBin[i];
			}
		}

		//---------------------------------------------------------------------------------------------------------
		int err = 0;

		if (par[1] != p[1]) { err = err + 1; }											//tests if parody bits dont match for error corrections
		if (par[2] != p[2]) { err = err + 2; }
		if (par[4] != p[4]) { err = err + 4; }
		if (par[8] != p[8]) { err = err + 8; }

		if (err > 0) {																	//corrects mistransmitted bit
			if (unsepChars[err - 1] == 1) {
				unsepChars[err - 1] = 0;
			}
			else {
				unsepChars[err - 1] = 1;
			}
		}
	//---------------------------------------------------------------------------------------------------------
		count = 1;
		for (int i = 0; i != 7; i++) {													//converts char bits into their number equivilent for
			b = b + (unsepChars[i] * count);											//ASCII conversion later
			count = count * 2;
		}

		count = 1;
		for (int i = 7; i != 14; i++) {													//converts char bits into their number equivilent for
			a = a + (unsepChars[i] * count);											//ASCII conversion later
			count = count * 2;
		}
		
		ch1 = b;
		ch2 = a;
		
	//-------------------------------------------------------------------------------------------------------------------------------------
																					//couts for debugging
		cout << numS << ' ';

		for (int i = 0; i < 19; i++) {												
			cout << fullBin[i];
		}

		cout << ' ' << par[1] << par[2] << par[4] << par[8];

		cout << ' ' << p[1] << p[2] << p[4] << p[8] << ' ';

		int h = 1;
		for (int i = 1; i < 19; i++) {
			if (i == 1 || i == 2 || i == 4 || i == 8) {
				h++;
			}
			else {
				cout << unsepChars[i - h];
			}
		}

		cout << setw(2) << right << err << ' ';

		cout << setw(3) << b << ' ' << setw(3) << a << ' ' << ch1 << ' ' << ch2;

		cout << endl;

		//------------------------------------------------------------------------------------------------------------------------------------

		
		sent[f] = ch1;
		f++;
		sent[f] = ch2;
		f++;

		Decoded << ch1 << ch2;

		a = 0;
		b = 0;

	}																							//end of while

	cout << endl << "Your Decoded Sentence is in Decoded.txt." << endl;

	/*for (int i = 0; i < f; i++) {
		cout << sent[i];
		}
	}*/
	cout << endl;
	

	return 0;
	}

	
