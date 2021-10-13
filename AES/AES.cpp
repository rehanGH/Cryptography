#include "AES.h"
#include<iostream> 
#include<cstring>
using namespace std;

void AES::KeyExpansionCore(unsigned char* in, unsigned char i){
	// Rotate Left
	unsigned int* q = (unsigned int*)in;
	*q = (*q >> 8) | ((*q & 0xff) << 24); // int is stored i nthe opposite way so we rotate left

	// S-Box four bytes
	in[0] = s_box[in[0]]; 	in[1] = s_box[in[1]];
	in[2] = s_box[in[2]]; 	in[3] = s_box[in[3]];

	// RCon
	in[0] ^= rcon[i];
}

void AES::KeyExpansion(unsigned char* inputKey, unsigned char* expandedKeys) {
	for(int i = 0; i < 16; i++)
		expandedKeys[i] = inputKey[i];

	int bytesGenerated = 16;
	int rconIteration = 1;
	unsigned char temp[4];

	while(bytesGenerated < 176){
		for(int i = 0; i < 4; i++)
			temp[i] = expandedKeys[i + bytesGenerated - 4];
		
		if(bytesGenerated % 16 == 0){
			KeyExpansionCore(temp, rconIteration);
			rconIteration++;	
		}

		for(unsigned char a = 0; a < 4; a++){
			expandedKeys[bytesGenerated] = expandedKeys[bytesGenerated - 16] ^ temp[a];
			bytesGenerated++;
		}
	}
}

void AES::SubBytes(unsigned char* state) {
	for(int i = 0; i < 16; i++)
		state[i] = s_box[state[i]];
}

void AES::ShiftRows(unsigned char* state) {
		unsigned char temp[16];

	temp[0] = state[0];
	temp[1] = state[5];
	temp[2] = state[10];
	temp[3] = state[15];

	temp[4] = state[4];
	temp[5] = state[9];
	temp[6] = state[14];
	temp[7] = state[3];
	
	temp[8] = state[8];
	temp[9] = state[13];
	temp[10] = state[2];
	temp[11] = state[7];

	temp[12] = state[12];
	temp[13] = state[1];
	temp[14] = state[6];
	temp[15] = state[11];
	
	for(int i = 0; i < 16; i++)
		state[i] = temp[i];

	delete[] temp;
}

void AES::MixColumns(unsigned char* state) {
	unsigned char temp[16];

	temp[0] = (unsigned char)(mul2[state[0]] ^ mul3[state[1]] ^ state[2] ^ state[3]);
	temp[1] = (unsigned char)(state[0] ^ mul2[state[1]] ^ mul3[state[2]] ^ state[3]);
	temp[2] = (unsigned char)(state[0] ^ state[1] ^ mul2[state[2]] ^ mul3[state[3]]);
	temp[3] = (unsigned char)(mul3[state[0]] ^ state[1] ^ state[2] ^ mul2[state[3]]);

	temp[4] = (unsigned char)(mul2[state[4]] ^ mul3[state[5]] ^ state[6] ^ state[7]);
	temp[5] = (unsigned char)(state[4] ^ mul2[state[5]] ^ mul3[state[6]] ^ state[7]);
	temp[6] = (unsigned char)(state[4] ^ state[5] ^ mul2[state[6]] ^ mul3[state[7]]);
	temp[7] = (unsigned char)(mul3[state[4]] ^ state[5] ^ state[6] ^ mul2[state[7]]);

	temp[8] = (unsigned char)(mul2[state[8]] ^ mul3[state[9]] ^ state[10] ^ state[11]);
	temp[9] = (unsigned char)(state[8] ^ mul2[state[9]] ^ mul3[state[10]] ^ state[11]);
	temp[10] = (unsigned char)(state[8] ^ state[9] ^ mul2[state[10]] ^ mul3[state[11]]);
	temp[11] = (unsigned char)(mul3[state[8]] ^ state[9] ^ state[10] ^ mul2[state[11]]);

	temp[12] = (unsigned char)(mul2[state[12]] ^ mul3[state[13]] ^ state[14] ^ state[15]);
	temp[13] = (unsigned char)(state[12] ^ mul2[state[13]] ^ mul3[state[14]] ^ state[15]);
	temp[14] = (unsigned char)(state[12] ^ state[13] ^ mul2[state[14]] ^ mul3[state[15]]);
	temp[15] = (unsigned char)(mul3[state[12]] ^ state[13] ^ state[14] ^ mul2[state[15]]);

	for(int i = 0; i < 16; i++)
		state[i] = temp[i];

	delete[] temp;
}

void AES::AddRoundKey(unsigned char* state, unsigned char* roundKey) {
	for(int i = 0; i < 16; i++)
		state[i] ^= roundKey[i]; // ^= means XOR
}

void AES::AES_Encrypt(unsigned char* message, unsigned char* key){
	unsigned char state[16];

	for(int i = 0; i < 16; i++)
		state[i] = message[i];

	int numOfRounds = 9;
	KeyExpansion(key, expandedKey);
	AddRoundKey(state, key); // Initial Round

	for(int i = 0; i < numOfRounds; i++){
		SubBytes(state);
		ShiftRows(state);
		MixColumns(state);
		AddRoundKey(state, expandedKey + (16 * (i + 1)));
	}

	// Final Round
	SubBytes(state);
	ShiftRows(state);
	AddRoundKey(state, expandedKey + 160);

	// copy over message with encyption

	for(int i = 0; i < 16; i++)
		message[i] = state[i];
	
}

void AES::printHex(unsigned char x){
	if(x / 16 < 10)
		cout<<(char)((x / 16) + '0');
	if(x / 16 >= 10)
		cout<<(char)((x / 16 - 10) + 'A');

	if(x % 16 < 10)
		cout<<(char)((x % 16) + '0');
	if(x % 16 >= 10)
		cout<<(char)((x % 16) + 'A');
}

int main(){
	unsigned char message[] = "This is a message me will encrypt usign AES";
	unsigned char key[16] = {
		1, 2, 3, 4,
		5, 6, 7, 8,
		9, 10, 11, 12,
		13, 14, 15, 16,
	};
	
	int originalLen = strlen((const char*) message);
	int lenOfPaddedMessage = originalLen;

	if(lenOfPaddedMessage % 16 == 0)
		lenOfPaddedMessage = (lenOfPaddedMessage / 16 + 1) * 16;

	unsigned char* paddedMessage = new unsigned char[lenOfPaddedMessage];
	for(int i = 0; i < lenOfPaddedMessage; i++){
		if(i >= originalLen)
			paddedMessage[i] = 0;
		else
			paddedMessage[i] = message[i];
	}

	// encrypt padded message: 
	for(int i = 0; i < lenOfPaddedMessage; i += 16)
		AES::AES_Encrypt(paddedMessage + i, key);

	cout<<"\nEncrypted Message: "<<endl;
	for(int i = 0; i < lenOfPaddedMessage; i++){
		AES::printHex(paddedMessage[i]);
		cout<<" ";
	}

	delete[] paddedMessage;

	return 0;
}