#include<iostream>
#include<fstream>

using namespace std;

int main(){
	int inputED, key;
	string inputFN;
	cout<<"Press 1 to Encrypt file\nPress 2  to Decrypt file"<<endl;
	cin>>inputED;
	cout<<"Enter File Name : "<<endl;
	cin>>inputFN;
	cout<<"Enter Key : "<<endl;
	cin>>key;
	
	if(inputED == 1){
		char c;
		ifstream fin;
		ofstream fout;
		fin.open(inputFN.c_str(), ios::binary); // read character by character
		inputFN = "encrypted file";
		fout.open(inputFN.c_str(), ios::binary); // read character by character

		while(!fin.eof()){ // will run till fin has data in it
			fin>>noskipws>>c;
			int temp = (c + key);
			fout<<(char)temp; 
		}
		fin.close();
		fout.close();
	} else if(inputED == 2){
		char c;
		ifstream fin;
		ofstream fout;
		fin.open(inputFN.c_str(), ios::binary); // read character by character
		inputFN = "decrypted file";
		fout.open(inputFN.c_str(), ios::binary); // read character by character

		while(!fin.eof()){ // will run till fin has data in it
			fin>>noskipws>>c;
			int temp = (c - key);
			fout<<(char)temp; 
		}
		fin.close();
		fout.close();
	}

	return 0;
}