#include <iostream>
using namespace std;

string XOR(string data, char key[]){
	string xorstring = data;
	for(int i = 0; i < xorstring.size(); i++)
		xorstring[i] = data[i] ^ key[i % (6 / sizeof(char))];
	
	return xorstring;
}

int main(){
	char key[6];
	string input;
	cout<<"Please enter message to be encrypted or decrypted"<<endl;
	cin>>input;
	
	for(int i = 1; i < 7; i++){
		cout<< "Enter letter or number (" << i << ") for key:" <<endl;
		cin>> key[i]; 
	}

	cout<<XOR(input, key)<<endl;

	return 0;
}