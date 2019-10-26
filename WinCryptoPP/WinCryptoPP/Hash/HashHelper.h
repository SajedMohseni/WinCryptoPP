#pragma once
#include <string>
#include <hex.h>
#include <md5.h>
#include <sha.h>
#include <files.h>
#include <windows.h>

using namespace CryptoPP;

class HashHelper
{
public:
	HashHelper();
	~HashHelper();
	
public:
	std::string CalMD5FromFile(char* pszFileName);				//�����ļ���MD5ֵ
	std::string CalMD5FromMem(PBYTE pData, DWORD dwDataSize);	//�����ڴ����ݵ�MD5ֵ
	std::string CalSha1FromFile(char* pszFileName);				//�����ļ���SHA1ֵ
	std::string CalSha1FromMem(PBYTE pData, DWORD dwDataSize);	//�����ڴ����ݵ�SHA1ֵ
	std::string CalSha256FromFile(char* pszFileName);			//�����ļ���SHA256ֵ
	std::string CalSha256FromMem(PBYTE pData, DWORD dwDataSize);//�����ڴ����ݵ�SHA256ֵ
};

