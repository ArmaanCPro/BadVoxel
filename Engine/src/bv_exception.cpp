#include "bv_exception.h"
#include <sstream>

bv_exception::bv_exception( int line,const char* file ) noexcept
	:
	line( line ),
	file( file )
{}

const char* bv_exception::what() const noexcept
{
	std::ostringstream oss;
	oss << GetType() << std::endl
		<< GetOriginString();
	whatBuffer = oss.str();
	return whatBuffer.c_str();
}

const char* bv_exception::GetType() const noexcept
{
	return "Chili Exception";
}

int bv_exception::GetLine() const noexcept
{
	return line;
}

const std::string& bv_exception::GetFile() const noexcept
{
	return file;
}

std::string bv_exception::GetOriginString() const noexcept
{
	std::ostringstream oss;
	oss << "[File] " << file << std::endl
		<< "[Line] " << line;
	return oss.str();
}