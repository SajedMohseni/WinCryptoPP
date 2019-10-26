#include "AesHelper.h"


AesHelper::AesHelper()
{
}


AesHelper::~AesHelper()
{
}

std::string AesHelper::AesEncrypt(const std::string& originalData, const std::string& aesKey)
{
	std::string encryptResult;
	//������
	AESEncryption aesEncryptor;
	//����ԭʼ���ݿ�
	unsigned char inBlock[AES::BLOCKSIZE];
	//���ܺ��������ݿ�
	unsigned char outBlock[AES::BLOCKSIZE];
	//��������Ϊȫ0
	unsigned char xorBlock[AES::BLOCKSIZE];

	DWORD dwOffset = 0;
	BYTE* pEncryptData = 0;
	DWORD dwEncryptDataSize = 0;

	//��ȡԭʼ���ݵ��ڴ�ָ��
	const char* pOriginalData = (const char*)originalData.c_str();
	//����ԭʼ���ݵ�ʵ�ʳ���
	DWORD dwOriginalDataSize = originalData.length();
	//����ԭʼ���ݵĳ���,����128λ����,��������0����(nopadding��䷽ʽ)
	DWORD dwQuotient = dwOriginalDataSize / AES::BLOCKSIZE;	//��
	DWORD dwRemaind = dwOriginalDataSize % AES::BLOCKSIZE;	//����
	if (dwRemaind != 0)
	{
		dwQuotient++;
	}

	//���붯̬�ڴ�
	dwEncryptDataSize = dwQuotient*AES::BLOCKSIZE;
	pEncryptData = new BYTE[dwEncryptDataSize];
	if (pEncryptData == NULL)
	{
		return encryptResult;
	}

	//������Կ
	aesEncryptor.SetKey((const unsigned char*)aesKey.c_str(), aesKey.length());

	do 
	{
		//����
		::RtlZeroMemory(inBlock, AES::BLOCKSIZE);
		::RtlZeroMemory(xorBlock, AES::BLOCKSIZE);
		::RtlZeroMemory(outBlock, AES::BLOCKSIZE);

		if (dwOffset <= (dwOriginalDataSize - AES::BLOCKSIZE))
		{
			::RtlCopyMemory(inBlock, (PVOID)(pOriginalData + dwOffset), AES::BLOCKSIZE);
		}
		else
		{
			::RtlCopyMemory(inBlock, (PVOID)(pOriginalData + dwOffset), (dwOriginalDataSize - dwOffset));
		}

		//����
		aesEncryptor.ProcessAndXorBlock(inBlock, xorBlock, outBlock);
		//����
		::RtlCopyMemory((PVOID)(pEncryptData + dwOffset), outBlock, AES::BLOCKSIZE);
		//��������
		dwOffset = dwOffset + AES::BLOCKSIZE;
		dwQuotient--;
	} while (dwQuotient > 0);

	encryptResult.resize(dwEncryptDataSize);
	::RtlCopyMemory((char *)encryptResult.c_str(), pEncryptData, dwEncryptDataSize);
	delete[] pEncryptData;
	return encryptResult;
}

std::string AesHelper::AesDecrypt(const std::string& encryptData, const std::string& aesKey)
{
	std::string originalResult;
	// ������
	AESDecryption aesDecryptor;
	// �����������ݿ�
	unsigned char inBlock[AES::BLOCKSIZE];
	// ���ܺ���������ݿ�
	unsigned char outBlock[AES::BLOCKSIZE];
	// �����趨ȫΪ0
	unsigned char xorBlock[AES::BLOCKSIZE];

	DWORD dwOffset = 0;
	BYTE* pDecryptData = NULL;
	DWORD dwDecryptDataSize = 0;

	const char* pEncryptData = encryptData.c_str();
	DWORD dwEncryptData = encryptData.length();
	//�������ĵĳ���,������128λ����,���������0����
	DWORD dwQuotient = dwEncryptData / AES::BLOCKSIZE;	//��
	DWORD dwRemaind = dwEncryptData % AES::BLOCKSIZE;	//����
	if (dwRemaind != 0)
	{
		dwQuotient++;
	}

	//���붯̬�ڴ�
	dwDecryptDataSize = dwQuotient*AES::BLOCKSIZE;
	pDecryptData = new BYTE[dwDecryptDataSize];
	if (pDecryptData == NULL)
	{
		return originalResult;
	}

	//������Կ
	aesDecryptor.SetKey((const unsigned char*)aesKey.c_str(), aesKey.length());

	do 
	{
		// ����
		::RtlZeroMemory(inBlock, AES::BLOCKSIZE);
		::RtlZeroMemory(xorBlock, AES::BLOCKSIZE);
		::RtlZeroMemory(outBlock, AES::BLOCKSIZE);

		// ��ȡ���ܿ�
		if (dwOffset <= (dwDecryptDataSize - AES::BLOCKSIZE))
		{
			::RtlCopyMemory(inBlock, (PVOID)(pEncryptData + dwOffset), AES::BLOCKSIZE);
		}
		else
		{
			::RtlCopyMemory(inBlock, (PVOID)(pEncryptData + dwOffset), (dwEncryptData - dwOffset));
		}

		//����
		aesDecryptor.ProcessAndXorBlock(inBlock, xorBlock, outBlock);
		//����
		::RtlCopyMemory((PVOID)(pDecryptData + dwOffset), outBlock, AES::BLOCKSIZE);
		//��������
		dwOffset = dwOffset + AES::BLOCKSIZE;
		dwQuotient--;
	} while (dwQuotient > 0);

	//��������
	originalResult.resize(dwDecryptDataSize);

	::RtlCopyMemory((char *)originalResult.c_str(), pDecryptData, dwDecryptDataSize);
	delete[] pDecryptData;
	return originalResult;
}