#pragma once
#include <aes.h>
#include <windows.h>

using namespace CryptoPP;

/*
	�򵥵�AES�����㷨
	ʹ��nopadding�������
	����û��ȥ��nopadding
*/
class AesHelper
{
public:
	AesHelper();
	~AesHelper();

public:
	std::string AesEncrypt(const std::string& originalData, const std::string& aesKey); //��ͨ����
	std::string AesDecrypt(const std::string& encryptData, const std::string& aesKey);	//��ͨ����
};

