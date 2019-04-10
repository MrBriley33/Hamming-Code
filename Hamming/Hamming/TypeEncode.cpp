#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

using namespace std;
int TypeEncode() {
	fstream Decoded, Encoded;
	Decoded.open("Decoded.txt");
	Encoded.open("Encoded.txt");

	string line;
	char ch1;													//intialising char.
	bool twoCharbin[14], mainBin[20];							//creates the main arrays for binary storage.
	int count = 0;

	cout << "Type your message below and press enter." << endl;
	cin.ignore();
	getline(cin,line);
	cout << endl << "Encoding." << endl << endl;
	while (line.size() > count) {										//runs while it can pull characters 

		ch1 = line[count];
		count++;
		
		int x, y;												//intializing dummy variables
		int dat1, dat2;											//initializing data variable for later use
		dat1 = ch1;												//making data variable equal to ASCII number of char
		x = dat1;												//making dummy variable equal to ASCII number of char

		

		for (int i = 0; i < 7; i++) {							//converts number to binary
			twoCharbin[i] = x % 2;
			x = x / 2;
			cout << twoCharbin[i];								//cout so we can see the binary string for debuging
		}

		cout << ' ' << ch1 << ' ';								//cout so we can seeteh char for debuging

		ch1 = line[count];										//pulls in second char
		count++;

		dat2 = ch1;												//making data variable equal to ASCII number of char
		y = dat2;												//making dummy variable equal to ASCII number of char

		for (int i = 0; i < 7; i++) {
			twoCharbin[i + 7] = y % 2;
			cout << twoCharbin[i + 7];
			y = y / 2;
		}

		int p[3];												//creating parody bit array

												//creating that extra 1 for be taked on in the beginning

		p[1] = (twoCharbin[0] + twoCharbin[2] + twoCharbin[4] + twoCharbin[6] + twoCharbin[8]		//finds first parody bit
			+ twoCharbin[10] + twoCharbin[12]) % 2;
		p[2] = (twoCharbin[1] + twoCharbin[2] + twoCharbin[5] + twoCharbin[6] + twoCharbin[9]		//finds second parody bit
			+ twoCharbin[10] + twoCharbin[13]) % 2;
		p[4] = (twoCharbin[3] + twoCharbin[4] + twoCharbin[5] + twoCharbin[6] + twoCharbin[11]		//finds third parody bit
			+ twoCharbin[12] + twoCharbin[13]) % 2;
		p[8] = (twoCharbin[7] + twoCharbin[8] + twoCharbin[9] + twoCharbin[10] + twoCharbin[11]		//finds fourth parody bit
			+ twoCharbin[12] + twoCharbin[13]) % 2;													//yes its bulky

		//--------------------------------------i beleive what is below is what is causing all the probelms--------
		mainBin[0] = 1;
		int g = 1;
		for (int i = 1; i < 19; i++) {
			if (i == 1 || i == 2 || i == 4 || i == 8) {
				mainBin[i] = p[i];							//puts parody bit in Main1 array
				g++;
			}
			else {
				mainBin[i] = twoCharbin[i - g];				//puts binary stored in Main array into Main1 array
			}
		}
		//---------------------------------------------------------------------------------------------------------
		int dig = 1;;
		int code = 0;

		for (int i = 0; i < 19; i++) {							//binary stored in array into a number
			code = code + (mainBin[i] * dig);
			dig = dig * 2;
		}
		//--------------------------------------------------------------------------------------------------------------------------
																//the rest of these couts are used for debugging
		cout << ' ' << ch1 << ' ';

		for (int i = 0; i < 19; i++) {
			cout << mainBin[i];
		}

		cout << ' ' << p[1] << p[2] << p[4] << p[8];

		cout << ' ' << code << ' ' << setw(3) << right << dat1 << ' ' << setw(3) << right << dat2 << ' ' << dat1 % 2 <<
			(dat1 / 2) % 2 << (dat1 / 4) % 2 << (dat1 / 8) % 2 << (dat1 / 16) % 2 << (dat1 / 32) % 2 << (dat1 / 64) % 2 <<
			dat2 % 2 << (dat2 / 2) % 2 << (dat2 / 4) % 2 << (dat2 / 8) % 2 << (dat2 / 16) % 2 << (dat2 / 32) % 2 << (dat2 / 64) % 2;
		cout << endl;


		cout << "                     ^^ ^   ^ ";
		cout << endl;
		//--------------------------------------------------------------------------------------------------------------------------

		Encoded << code << endl;									//out puts numbers into file for later decoding
	}																//end of while
	cout << endl << "Done!" << endl << endl;
	return 0;
}