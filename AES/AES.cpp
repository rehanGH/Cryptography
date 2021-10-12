#include<iostream> 
using namespace std;

void KeyExpansion() {}

void SubBytes(unsigned char* state) {}
void ShiftRows(unsigned char* state) {}
void MixColumns() {}
void AddRoundKey(unsigned char* state, unsigned char* roundKey) {}

void AES_Encrypt(unsigned char* message, unsigned char* key){
	unsigned char state[16];

	for(int i = 0; i < 16; i++)
		state[i] = message[i];

	int numOfRounds = 1;
	KeyExpansion();
	AddRoundKey(state, key); // Initial Round

	for(int i = 0; i < numOfRounds; i++){
		SubBytes(state);
		ShiftRows(state);
		MixColumns();
		AddRoundKey(state, key);
	}

	// Final Round
	SubBytes(state);
	ShiftRows(state);
	MixColumns();
	AddRoundKey(state, key);
}

int main(){
	unsigned char message[] = "This is a message me will encrypt usign AES";
	unsigned char key[16] = {
		1, 2, 3, 4,
		5, 6, 7, 8,
		9, 10, 11, 12,
		13, 14, 15, 16,
	};
	
	AES_Encrypt(message, key);

	return 0;
}