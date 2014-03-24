/////////////////////////////////////////////////////////////////////////////////
// TgcViewer-cpp
// 
// Author: Matias Leone
// 
/////////////////////////////////////////////////////////////////////////////////


#include "TgcViewer/TgcSceneLoader/TgcParserUtils.h"
#include "TgcViewer/TgcGeometry/TgcBoundingBox.h" //required by forward declaration
using namespace TgcViewer;




TgcParserUtils::TgcParserUtils()
{
}

float TgcParserUtils::parseFloat(const string &text)
{
	return (float)atof(text.c_str());
}

int TgcParserUtils::parseInt(const string &text)
{
	return atoi(text.c_str());
}

bool TgcParserUtils::parseBool(const string &text)
{
	if(text == "1" || text == "true")
		return true;
	return false;
}


string TgcParserUtils::trimLeft(const string &text)
{
	size_t startpos = text.find_first_not_of(TGC_PARSER_UTILS_WHITESPACE);
    return (startpos == std::string::npos) ? "" : text.substr(startpos);
}

string TgcParserUtils::trimRight(const string &text)
{
	size_t endpos = text.find_last_not_of(TGC_PARSER_UTILS_WHITESPACE);
    return (endpos == std::string::npos) ? "" : text.substr(0, endpos+1);
}

string TgcParserUtils::trim(const string &text)
{
	return TgcParserUtils::trimRight(TgcParserUtils::trimLeft(text));
}

string TgcParserUtils::toString(const int n)
{
	stringstream ss;
	ss << n;
	return ss.str();
}

string TgcParserUtils::toString(const unsigned int n)
{
	return TgcParserUtils::toString((int)n);
}

string TgcParserUtils::toString(const long n)
{
	stringstream ss;
	ss << n;
	return ss.str();
}

string TgcParserUtils::toString(const float n)
{
	stringstream ss;
	ss << n;
	return ss.str();
}

string TgcParserUtils::toString(const bool n)
{
	return n ? "true" : "false";
}

string TgcParserUtils::toString(const Vector2 &v)
{
	return "(" + TgcParserUtils::toString(v.X) + ", " + TgcParserUtils::toString(v.Y) + ")";
}

string TgcParserUtils::toString(const Vector3 &v)
{
	return "(" + TgcParserUtils::toString(v.X) + ", " + TgcParserUtils::toString(v.Y) + ", " + TgcParserUtils::toString(v.Z) + ")";
}

string TgcParserUtils::toString(const Vector4 &v)
{
	return "(" + TgcParserUtils::toString(v.X) + ", " + TgcParserUtils::toString(v.Y) + ", " + 
		TgcParserUtils::toString(v.Z) + ", " + TgcParserUtils::toString(v.W) + ")";
}

string TgcParserUtils::toString(const Color &c)
{
	return "(" + TgcParserUtils::toString(c.R) + ", " + TgcParserUtils::toString(c.G) + ", " + 
		TgcParserUtils::toString(c.B) + ", " + TgcParserUtils::toString(c.A) + ")";
}

string TgcParserUtils::toString(const TgcBoundingBox* b)
{
	return "Min " + TgcParserUtils::toString(b->pMin) + " - Max " + TgcParserUtils::toString(b->pMax);
}

string TgcParserUtils::getFileNameFromPath(const string &path)
{
	string fileName = path;
	const size_t last_slash_idx = fileName.find_last_of("\\/");
	if (std::string::npos != last_slash_idx)
	{
		fileName.erase(0, last_slash_idx + 1);
	}
	return fileName;
}


void TgcParserUtils::parseFloat3Array(const string &text, float (&data)[3])
{
	string aux = text.substr(1, text.length() -2);
	vector<string> n = TgcParserUtils::split(aux, ',');
	data[0] = TgcParserUtils::parseFloat(n[0]);
	data[1] = TgcParserUtils::parseFloat(n[1]);
	data[2] = TgcParserUtils::parseFloat(n[2]);
}

void TgcParserUtils::parseFloat3ArrayAdapted(const string &text, float (&data)[3])
{
	string aux = text.substr(1, text.length() -2);
	vector<string> n = TgcParserUtils::split(aux, ',');
	data[0] = TgcParserUtils::parseFloat(n[0]);
	data[1] = TgcParserUtils::parseFloat(n[2]);
	data[2] = TgcParserUtils::parseFloat(n[1]);
}

void TgcParserUtils::parseInt3Array(const string &text, int (&data)[3])
{
	string aux = text.substr(1, text.length() -2);
	vector<string> n = TgcParserUtils::split(aux, ',');
	data[0] = TgcParserUtils::parseInt(n[0]);
	data[1] = TgcParserUtils::parseInt(n[1]);
	data[2] = TgcParserUtils::parseInt(n[2]);
}

void TgcParserUtils::parseInt3ArrayAdapted(const string &text, int (&data)[3])
{
	string aux = text.substr(1, text.length() -2);
	vector<string> n = TgcParserUtils::split(aux, ',');
	data[0] = TgcParserUtils::parseInt(n[0]);
	data[1] = TgcParserUtils::parseInt(n[2]);
	data[2] = TgcParserUtils::parseInt(n[1]);
}

void TgcParserUtils::parseFloat2Array(const string &text, float (&data)[2])
{
	string aux = text.substr(1, text.length() -2);
	vector<string> n = TgcParserUtils::split(aux, ',');
	data[0] = TgcParserUtils::parseFloat(n[0]);
	data[1] = TgcParserUtils::parseFloat(n[1]);
}

void TgcParserUtils::parseFloat2ArrayAdapted(const string &text, float (&data)[2])
{
	string aux = text.substr(1, text.length() -2);
	vector<string> n = TgcParserUtils::split(aux, ',');
	data[0] = TgcParserUtils::parseFloat(n[1]);
	data[1] = TgcParserUtils::parseFloat(n[0]);
}

void TgcParserUtils::parseFloat4Array(const string &text, float (&data)[4])
{
	string aux = text.substr(1, text.length() -2);
	vector<string> n = TgcParserUtils::split(aux, ',');
	data[0] = TgcParserUtils::parseFloat(n[0]);
	data[1] = TgcParserUtils::parseFloat(n[1]);
	data[2] = TgcParserUtils::parseFloat(n[2]);
	data[3] = TgcParserUtils::parseFloat(n[3]);
}

vector<string> TgcParserUtils::split(const string &text, char sep) 
{
	vector<string> tokens;
	int start = 0, end = 0;
	while ((end = text.find(sep, start)) != string::npos) 
	{
		tokens.push_back(text.substr(start, end - start));
		start = end + 1;
	}
	tokens.push_back(text.substr(start));
	return tokens;
}


void TgcParserUtils::divFloatArrayValues(float* data, int length, float divValue)
{
    for (int i = 0; i < length; i++)
    {
        data[i] /= divValue;
    }
}

void TgcParserUtils::parseIntStream(const string &text, int* data, int count)
{
	vector<string> textArray = TgcParserUtils::split(text, ' ');
    for (int i = 0; i < count; i++)
    {
		data[i] = TgcParserUtils::parseInt(textArray[i]);
    }
}

void TgcParserUtils::parseFloatStream(const string &text, float* data, int count)
{
	vector<string> textArray = TgcParserUtils::split(text, ' ');
    for (int i = 0; i < count; i++)
    {
		data[i] = TgcParserUtils::parseFloat(textArray[i]);
    }
}


string TgcParserUtils::readAllFile(const string &path)
{
	std::ifstream in(path, std::ios::in | std::ios::binary);
	if (in)
	{
		std::string contents;
		in.seekg(0, std::ios::end);
		contents.resize((unsigned int)in.tellg());
		in.seekg(0, std::ios::beg);
		in.read(&contents[0], contents.size());
		in.close();
		return(contents);
	}
	throw(errno);
}


string TgcParserUtils::toLower(const string &str)
{
	string str2 = str;
	transform(str2.begin(), str2.end(), str2.begin(), ::tolower);
	return str2;
}


string TgcParserUtils::toUpper(const string &str)
{
	string str2 = str;
	transform(str2.begin(), str2.end(), str2.begin(), ::toupper);
	return str2;
}