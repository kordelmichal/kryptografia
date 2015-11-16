#define _CRT_SECURE_NO_WARNINGS
#include "MP3Player.h"

// g++ -g3 -ggdb -O0 -DDEBUG -I/usr/include/cryptopp Driver.cpp -o Driver.exe -lcryptopp -lpthread
// g++ -g -O2 -DNDEBUG -I/usr/include/cryptopp Driver.cpp -o Driver.exe -lcryptopp -lpthread
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
/*
CryptoPP::SecByteBlock HexDecodeString(const char *hex)
{
CryptoPP::StringSource ss(hex, true, new CryptoPP::HexDecoder);
CryptoPP::SecByteBlock result((size_t)ss.MaxRetrievable());
ss.Get(result, result.size());
return result;
}*/


int main(int argc, char* argv[]) {

	//HMODULE DLL = LoadLibrary(_T("cryptopp.dll"));
	//
	// Key and IV setup
	//AES encryption uses a secret key of a variable length (128-bit, 196-bit or 256-
	//bit). This key is secretly exchanged between two parties before communication
	//begins. DEFAULT_KEYLENGTH= 16 bytes



	MP3Player player;
	HANDLE hFile = CreateFile("es.mp3", // open MYFILE.TXT
		GENERIC_READ,
		FILE_SHARE_READ, // share for reading
		NULL, // no security
		OPEN_EXISTING, // existing file only
		FILE_ATTRIBUTE_NORMAL, // normal file
		NULL); // no attr
	assert(hFile != INVALID_HANDLE_VALUE);

	// Get FileSize
	DWORD fileSize = GetFileSize(hFile, NULL);
	assert(fileSize != INVALID_FILE_SIZE);

	// Alloc buffer for file
	char* mp3Buffer = (char*)LocalAlloc(LPTR, fileSize);

	// Read file and fill mp3Buffer
	DWORD bytesRead;
	DWORD resultReadFile = ReadFile(hFile, (BYTE*)mp3Buffer, fileSize, &bytesRead, NULL);
	assert(resultReadFile != 0);
	assert(bytesRead == fileSize);

	// Close File
	CloseHandle(hFile);

	//player.OpenFromMemory((BYTE*)mp3Buffer + 1000000, fileSize - 1000000);

	//player.Play();

	///*while (...) {
	//// Do here your synchro in the demo using
	//...
	//double playerPositionInSeconds = player.GetPosition()
	//...
	//}*/
	//Sleep(10000);
	//player.Close();





	std::string key = "0123456789abcdef";
	std::string iv = "aaaaaaaaaaaaaaaa";
	string cipher, encoded, recovered;


	std::string plaintext = "name macmilan age 24 ciy bonn country germanyname macmilan age 24 ciy bonn country germanyname macmilan age 24 ciy bonn country germany";
	std::string ciphertext;
	std::string decryptedtext;



	CryptoPP::AES::Encryption aesEncryption((byte *)key.c_str(), CryptoPP::AES::DEFAULT_KEYLENGTH);
	CryptoPP::CBC_Mode_ExternalCipher::Encryption cbcEncryption(aesEncryption, (byte *)iv.c_str());

	CryptoPP::StreamTransformationFilter stfEncryptor(cbcEncryption, new CryptoPP::StringSink(ciphertext));
	stfEncryptor.Put(reinterpret_cast<const unsigned char*>((const char*)mp3Buffer), 50000);
	stfEncryptor.MessageEnd();


	// Pretty print
	encoded.clear();
	StringSource(ciphertext, true,
		new HexEncoder(
			new StringSink(encoded)
			) // HexEncoder
		); // StringSource



	char *name2;
	name2 = (char*)malloc(encoded.length() + 1); // don't forget to free!!!!
												 //s2 = Database_row_count; // I forget if the string class can implicitly be converted to char*
												 //s2[0] = '1';
	cout << "asdf" << endl;

	strcpy(name2, encoded.c_str());

	const char* hex_str = name2;

	std::string result_string;
	unsigned int ch;
	for (; std::sscanf(hex_str, "%2x", &ch) == 1; hex_str += 2)
		result_string += ch;



	CryptoPP::AES::Decryption aesDecryption((byte *)key.c_str(), CryptoPP::AES::DEFAULT_KEYLENGTH);
	CryptoPP::CBC_Mode_ExternalCipher::Decryption cbcDecryption(aesDecryption, (byte *)iv.c_str());

	CryptoPP::StreamTransformationFilter stfDecryptor(cbcDecryption, new CryptoPP::StringSink(decryptedtext));
	stfDecryptor.Put(reinterpret_cast<const unsigned char*>(result_string.c_str()), result_string.size());
	stfDecryptor.MessageEnd();
	/*std::cout << "Decrypted Text: " << std::endl;
	std::cout << decryptedtext;
	std::cout << std::endl << std::endl;*/


	char* mp3Decrypted = (char*)LocalAlloc(LPTR, fileSize);
	const char* constDecrypted = decryptedtext.c_str();

	for (int i = 0; i <= 200000; i++) {
		mp3Decrypted[i] = constDecrypted[i];
	}
	for (int i = 200000; i < fileSize; i++) {
		mp3Buffer[i] = 0;
	}

	player.OpenFromMemory((BYTE*)mp3Decrypted, fileSize);

	player.Play();

	/*while (...) {
	// Do here your synchro in the demo using
	...
	double playerPositionInSeconds = player.GetPosition()
	...
	}*/
	Sleep(10000);
	player.Close();

	system("pause");

	return 0;
}