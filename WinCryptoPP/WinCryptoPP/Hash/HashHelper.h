#pragma once
#include <string>
#include <hex.h>
#include <md5.h>
#include <sha.h>
#include <files.h>
#include <windows.h>

using namespace CryptoPP;

std::string CalMD5ByFile(char* pszFileName);				//�����ļ���MD5ֵ
std::string CalMD5ByMem(PBYTE pData, DWORD dwDataSize);		//�����ڴ����ݵ�MD5ֵ
std::string CalSha1ByFile(char* pszFileName);				//�����ļ���SHA1ֵ
std::string CalSha1ByMem(PBYTE pData, DWORD dwDataSize);	//�����ڴ����ݵ�SHA1ֵ
std::string CalSha256ByFile(char* pszFileName);				//�����ļ���SHA256ֵ
std::string CalSha256ByMem(PBYTE pData, DWORD dwDataSize);	//�����ڴ����ݵ�SHA256ֵ
