#pragma once

#include <string>
#include <vector>




/*
* 特征码类
* 未支持跨进程
*/

class YSignatureCode {
private:
	enum class SignatureElementType {
		none,
		whole,
		vague
	};

	typedef struct _SignatureElement {
		SignatureElementType type;
		size_t length;
		std::vector<unsigned char> data;
	} SignatureElement, * PSignatureElement;

private:
	size_t m_offset;
	std::vector<SignatureElement> m_signtureCode;
public:
	YSignatureCode();
	YSignatureCode(const std::string& hexStringData);
	~YSignatureCode();

private:
	/*
	* 将特征码字符串转换为Element
	* 标准格式示例： "48 &?? ?? 65*20 88"
	* &表示返回时的会以此字节为起始地址，加在字节前面即可，示例中即偏移为1
	*	以最后一个&为准
	* ??表示模糊匹配此字节
	* *xx表示上一个字节的重复次数，示例就是重复0x65 20次，是十进制
	*/
	size_t stringToElement(const std::string& hexStringData, std::vector<SignatureElement>& signature, size_t& offset);


public:

	/*
	* 限定大小查找特征码
	*/ 

	void* search(const void* startAddress, size_t size, const std::string& hexStringData);

	
	/*
	* 限定范围查找特征码
	*/
	void* search(const void* startAddress, const void* endAddress, const std::string& hexStringData);


	
};



// #include "YSignatureCode.cpp"