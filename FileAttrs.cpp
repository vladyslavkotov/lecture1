#include "FileAttrs.h"

#include<string>

FileAttrs::FileAttrs(std::wstring name, std::wstring size, std::wstring type, std::wstring created, std::wstring accessed, std::wstring modified) :
	Name(name),
	Size(size),
	Type(type),
	Created(created),
	Accessed(accessed),
	Modified(modified)
{
}