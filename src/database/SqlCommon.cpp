#include "SqlCommon.h"
#include "SHA1.h"

namespace sql
{

string intToStr(int value)
{
	char buffer[32];
    sprintf(buffer, "%d", value);
	return buffer;
}

string intToStr(integer value)
{
	char buffer[64];
    sprintf(buffer, "%ld", (long)value);
	return buffer;
}

string quoteStr(string value)
{
	string s;

	for (string::iterator it = value.begin(); it != value.end(); it++)
	{
		char c = *it;
		s += c;
		if (c == '\'')
			s += c;
	}

	return s;
}

//CRT_SECURE_NO_WARNINGS
#pragma warning(disable : 4996)

string binToHex(const char* buffer, int size)
{
	std::string s;

	char digit[4];

	unsigned char* p = (unsigned char*)buffer;

	for (int index = 0; index < size; index++)
	{
		sprintf(digit, "%02x", *p++);
		s += digit;
	}

	return s;
}

#pragma warning(default : 4996)

string generateSHA(string value)
{
	CSHA1 sha;

	sha.Update((UINT_8*)value.c_str(), value.length());

	sha.Final();

	UINT_8 digest[20];
	if (sha.GetHash(digest))
	{
		const int size = sizeof(digest) / sizeof(UINT_8);
		return binToHex((char*)digest, size);
	}

	return "";
}

string& trimleft(string& s)
{
	string::iterator it;

	for( it = s.begin(); it != s.end(); it++ )
		if( !isspace( *it ) )
			break;

	s.erase( s.begin(), it );
	return s;
}

string& trimright(string& s)
{
	string::difference_type dt;
	string::reverse_iterator it;

	for( it = s.rbegin(); it != s.rend(); it++ )
		if( !isspace( *it ) )
			break;

	dt = s.rend() - it;

	s.erase( s.begin() + dt, s.end() );
	return s;
}

string& trim(string& s)
{
	trimleft( s );
	trimright( s );
	return s;
}

string trim(const string& s)
{
	string t = s;
	return trim(t);
}

//CRT_SECURE_NO_WARNINGS
#pragma warning(disable : 4996)

void listToVector(string s, std::vector<string>& vector, const char* sep)
{
	vector.clear();

	char* buffer = new char[s.length() + 1];

	memcpy(buffer, s.c_str(), s.length());
	buffer[s.length()] = 0;

	char* token = strtok(buffer, sep);

	while (token)
	{
		string sToken = token;
		vector.push_back(trim(sToken));
		token = strtok(NULL, sep);
	}

	delete [] buffer;
}

#pragma warning(default : 4996)


//sql eof
};
