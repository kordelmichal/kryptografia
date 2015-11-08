#define _CRT_SECURE_NO_WARNINGS
#include "MP3Player.h"

#include <sstream>
#include <cstdio>
#include <iostream>
#include <osrng.h>
using CryptoPP::AutoSeededRandomPool;

#include <iostream>
using std::cout;
using std::cerr;
using std::endl;

#include <string>
using std::string;

#include <cstdlib>
using std::exit;

#include <cryptlib.h>
using CryptoPP::Exception;

#include <hex.h>
using CryptoPP::HexEncoder;
using CryptoPP::HexDecoder;

#include <filters.h>
using CryptoPP::StringSink;
using CryptoPP::StringSource;
using CryptoPP::StreamTransformationFilter;

#include <des.h>
using CryptoPP::DES_EDE2;

#include <modes.h>
using CryptoPP::CBC_Mode;

#include <secblock.h>
using CryptoPP::SecByteBlock;
#include <iostream>
#include <string>
#include <modes.h>
#include <aes.h>
#include <filters.h>
#include <fstream>
#include <Windows.h>
#include <bitset>



int main(int argc, char* argv[]) {
	int keyId = stoi(string(argv[2]));



	std::ifstream t("msg.txt");
	std::string text((std::istreambuf_iterator<char>(t)),
		std::istreambuf_iterator<char>());
	string bText = "";
	for (std::size_t i = 0; i < text.size(); ++i)
	{
		bText +=std::bitset<8>(text.c_str()[i]).to_string();
	}
	cout << bText << endl;

	std::ifstream t2(argv[1]);
	std::string keys((std::istreambuf_iterator<char>(t2)),
		std::istreambuf_iterator<char>());

	int newlineNumber = 0;
	for (int i = 0; i < keys.length(); i++) {
		if (keys.at(i) == '\n' || keys.at(i) == '\r') {
			newlineNumber++;
		}
	}

	const unsigned int keysNr = newlineNumber + 1;
	string* key = new string[keysNr];
	char temp[16];

	
	std::stringstream ss(keys.c_str());
	std::string to;

	if (keys.c_str() != NULL)
	{
		int i = 0;
		while (std::getline(ss, to, '\n')) {
			key[i++] = string(to);
		}
	}

	string str1 = "";
	char abc[3][16];
	for (int i = 0; i < 16; i++) {
		char test[] = { 'a', 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0 };
		abc[0][i] = key[0].at(i) ^ test[i];
		str1 += abc[0][i];
	}
	str1 = str1 + "\n";

	for (int i = 0; i < 16; i++) {
		char test[] = { 'b', 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0 };
		abc[1][i] = key[1].at(i) ^ test[i];
		str1 += abc[1][i];

	}
	str1 = str1 + "\n";

	for (int i = 0; i < 16; i++) {
		char test[] = { 'c', 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0 };
		abc[2][i] = key[2].at(i) ^ test[i];
		str1 += abc[2][i];

	}
	str1 = str1 + "\n";

	std::ofstream out("xor.txt");
	cout << str1;
	out << str1;
	out.close();


	HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);
	DWORD mode = 0;
	GetConsoleMode(hStdin, &mode);
	SetConsoleMode(hStdin, mode & (~ENABLE_ECHO_INPUT));
	string password;
	cout << "Key ID: 0. Enter the password" << endl;
	getline(std::cin, password);

	string pMode;
	std::cout << "Ciphering (c), or deciphering(d)? :";
	std::cin >> pMode;

	std::string iv = "aaaaaaaaaaaaaaaa";
	string cipher, encoded, recovered;


	std::string ciphertext;
	std::string decryptedtext;
	std::string result_string;



	// Ciphering
	if (pMode.at(0) == 'c') {
		CryptoPP::AES::Encryption aesEncryption((byte *)key[keyId].c_str(), CryptoPP::AES::DEFAULT_KEYLENGTH);
		CryptoPP::CBC_Mode_ExternalCipher::Encryption cbcEncryption(aesEncryption, (byte *)iv.c_str());

		CryptoPP::StreamTransformationFilter stfEncryptor(cbcEncryption, new CryptoPP::StringSink(ciphertext));
		stfEncryptor.Put(reinterpret_cast<const unsigned char*>((const char*)text.c_str()), text.length() + 1);
		stfEncryptor.MessageEnd();

		encoded.clear();
		StringSource(ciphertext, true,
			new HexEncoder(
				new StringSink(encoded)
				) // HexEncoder
			); // StringSource

		char *name2;
		name2 = (char*)malloc(encoded.length() + 1);

		strcpy(name2, encoded.c_str());
		const char* hex_str = name2;
		unsigned int ch;
		for (; std::sscanf(hex_str, "%2x", &ch) == 1; hex_str += 2)
			result_string += ch;

		bText = "";
		for (std::size_t i = 0; i < result_string.size(); ++i)
		{
			bText += std::bitset<8>(result_string.c_str()[i]).to_string();
		}
		cout << bText << endl;

		std::ofstream out("c.txt");
		out << bText;
		out.close();
	}
	// Deciphering
	else if (pMode.at(0) == 'd') {

		CryptoPP::AES::Decryption aesDecryption((byte *)key[keyId].c_str(), CryptoPP::AES::DEFAULT_KEYLENGTH);
		CryptoPP::CBC_Mode_ExternalCipher::Decryption cbcDecryption(aesDecryption, (byte *)iv.c_str());

		CryptoPP::StreamTransformationFilter stfDecryptor(cbcDecryption, new CryptoPP::StringSink(result_string));
		stfDecryptor.Put(reinterpret_cast<const unsigned char*>(text.c_str()), text.size());
		stfDecryptor.MessageEnd();
		
		std::ofstream out("d.txt");
		out << result_string;
		out.close();
	}
	else {
		cout << "Unknown mode!" << endl;
	}



	system("pause");

	return 0;
}