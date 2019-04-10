#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
//dual char hamming program

// this program takes 2 chars from a text file, converts them to binary,then finds and inserts parody bits
//in the (1,2,4,8) poistion, taks on an extra 1 at the beginning then converts the binary string to a number
//to be saved into a txt file for later decryption.

using namespace std;
int DataEncode();
int TypeEncode();
int Decode();


int main() {
	fstream Decoded, Encoded;
	string command;
	cout << "Enter command: (Decode or Encode or Exit): ";
	while(cin >> command) {
		

		if (command == "Encode" || command == "encode") {											// start of if for(Encode)
			cout << "Encode from data or type? (Data or Type): ";
			cin >> command;
			if (command == "Type" || command == "type") {
				TypeEncode();
			}
			if (command == "Data" || command == "data") {
				DataEncode();
			}

		//-----------------------------------------------------------------------------------------------------------------
		}																	// end of if(Encode)
		if (command == "Decode" || command == "decode") {											// start of if for(Decode) 
			Decode();


			cout << "Done..." << endl << endl;
		}																	// end of if(Decode)

		if (command == "Exit" || command == "exit") {
			Encoded.close();
			Decoded.close();
			return 0;
		}
		
		cout << "Enter command: (Decode or Encode or Exit):";
	}

	Encoded.close();
	Decoded.close();
	return 0;
}//end of main