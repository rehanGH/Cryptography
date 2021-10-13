# Cryptography

The Internals of AES

There are 4 layers to complete an encryption using AES.
The layers include SubByte, ShiftRows, MixColumn, and XOR round key layer.
Depending on the key length, you have to do more or less rounds
AES-128 has 10 rounds
AES-192 has 12 rounds 
And AES-256 consists of 14 rounds
All rounds complete each layer except for the last round where there is no MixColumn layer.

SubBytes Layer

A state represents a 4 X 4 matrix of the plaintext XORed with 1st round key
Each byte in the state is replaced by a byte found in the S-box table 
The S-box table consists of 256 unique bytes.
Ex. the byte 68 (represented in hexadecimal) replaced through using the S-box table will become 45 as you look at the 6 for the row and 8 for the column.

s-Box table

   | 0  1  2  3  4  5  6  7  8  9  a  b  c  d  e  f
---|--|--|--|--|--|--|--|--|--|--|--|--|--|--|--|--|
00 |63 7c 77 7b f2 6b 6f c5 30 01 67 2b fe d7 ab 76 
10 |ca 82 c9 7d fa 59 47 f0 ad d4 a2 af 9c a4 72 c0 
20 |b7 fd 93 26 36 3f f7 cc 34 a5 e5 f1 71 d8 31 15 
30 |04 c7 23 c3 18 96 05 9a 07 12 80 e2 eb 27 b2 75 
40 |09 83 2c 1a 1b 6e 5a a0 52 3b d6 b3 29 e3 2f 84 
50 |53 d1 00 ed 20 fc b1 5b 6a cb be 39 4a 4c 58 cf 
60 |d0 ef aa fb 43 4d 33 85 45 f9 02 7f 50 3c 9f a8 
70 |51 a3 40 8f 92 9d 38 f5 bc b6 da 21 10 ff f3 d2 
80 |cd 0c 13 ec 5f 97 44 17 c4 a7 7e 3d 64 5d 19 73 
90 |60 81 4f dc 22 2a 90 88 46 ee b8 14 de 5e 0b db 
a0 |e0 32 3a 0a 49 06 24 5c c2 d3 ac 62 91 95 e4 79 
b0 |e7 c8 37 6d 8d d5 4e a9 6c 56 f4 ea 65 7a ae 08 
c0 |ba 78 25 2e 1c a6 b4 c6 e8 dd 74 1f 4b bd 8b 8a 
d0 |70 3e b5 66 48 03 f6 0e 61 35 57 b9 86 c1 1d 9e 
e0 |e1 f8 98 11 69 d9 8e 94 9b 1e 87 e9 ce 55 28 df 
f0 |8c a1 89 0d bf e6 42 68 41 99 2d 0f b0 54 bb 16 

ShiftRows Layer

This layer will shift each byte in each row by a certain amount depending on what row it is on.
The first row will not shift at all
The second row will shift 1 byte to the left
The third row will shift 2 bytes to the left 
and the fourth row will shift 3 bytes to the left

MixColumns Layer

In this layer you will multiply the state matrix by the fixed matrix
Each row from the fixed matrix is multiplied by a column in the state matrix, to provide an output byte
This layer provides diffusion to the ciphertext

Key Schedule

Rijndael’s Key schedule involves:
Splitting up the initial key into 4 separate arrays consisting of 4 bytes each, represented by w[0], w[1], w[2], w[3]
To create a subkey which will be used in the first rounds, you will have to first get w[4]
To geet w[4]: You will first shift the bytes of the w[3] array to the left once
Then you will use the S-box table to substitute the values of the now shifted w[3] array to create a new array - (same S-Box shown in SubByte layer)
Lastly you will add a round constant to the new array which will is (01, 00, 00, 00) to get w[4]
w[4]’s 4 bytes will be the starting values of the first subkey
To get the remainder of the subkey you will have to XOR
w[5] = w[4] ⊕ w[1], w[6] = w[5] ⊕ w[2], w[7] = w[6] ⊕ w[3]
This will get you the subkey for the first round: {w[4],w[5]w[6]w[7]}

XOR Round Key  

The XOR Round Key layer involves XORing a subkey created through using Rijndael’s Key Schedule with the state matrix depending on the round.
Each subkey is the same size as the state matrix
XORing is dependent on the position of the byte from each matrix


