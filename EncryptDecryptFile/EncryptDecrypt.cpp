#include <bits/stdc++.h>
#include <fstream>
using namespace std;
  
class EncryptDecrypt{
	private:
		int key;
		string fileName;
		char c;
	public:
		void encrypt(string);
		void decrypt();
};

void EncryptDecrypt::encrypt(string input){
	cout << "Enter Key: ";
	cin >> key;

	fstream fin, fout;

	fin.open(input, fstream::in);
	fout.open("encrypt.txt", fstream::out);

	while(fin >> noskipws >> c){
		int temp = (c + key);

		fout << (char)temp;
	}

	fin.close();
	fout.close();
}

void EncryptDecrypt::decrypt(){
	cout << "Enter Key: ";
	cin >> key;

	fstream fin, fout;

	fin.open("encrypt.txt", fstream::in);
	fout.open("decrypt.txt", fstream::out);

	while(fin >> noskipws >> c){
		int temp = (c - key);
		fout << (char)temp;
	}

	fin.close();
	fout.close();
}

int main()
{
    EncryptDecrypt encdec;
	string input;
    char c;
    cout << "\nEnter Your Choice : ->" << endl;
    cout << "1. encrypt" << endl;
    cout << "2. decrypt" << endl;
    cin >> c;
    cin.ignore();
	
	cout << "Enter file name with .txt: "<<endl;
	cin >> input;

    switch (c) {
		case '1': {
			encdec.encrypt(input);
			break;
		}
		case '2': {
			encdec.decrypt();
			break;
		}
    }
}