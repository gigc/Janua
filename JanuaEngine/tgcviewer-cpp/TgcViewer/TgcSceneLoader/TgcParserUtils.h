/////////////////////////////////////////////////////////////////////////////////
// TgcViewer-cpp
// 
// Author: Matias Leone
// 
/////////////////////////////////////////////////////////////////////////////////


#pragma once


//General Includes:
#include <string>
#include <vector>
#include <fstream>
#include <cerrno>
#include <sstream>
#include <algorithm>
using namespace std;

//Project Includes:
#include "TgcViewer/globals.h"
#include "TgcViewer/Math/Vector2.h"
#include "TgcViewer/Math/Vector3.h"
#include "TgcViewer/Math/Vector4.h"
#include "TgcViewer/Math/Color.h"

//Forward declaration for "TgcViewer/TgcGeometry/TgcBoundingBox.h"
namespace TgcViewer {class TgcBoundingBox;}


namespace TgcViewer
{




/**
* Useful functions for parsing strings and data convertion
*/
class TgcParserUtils
{

public:

	#define TGC_PARSER_UTILS_WHITESPACE " \n\r\t"


	/**
	* Parse float from string
	*/
	static float parseFloat(const string &text);

	/**
	* Parse int from string
	*/
	static int parseInt(const string &text);

	/**
	* Parse bool from string
	*/
	static bool parseBool(const string &text);

	/**
	* Left trim for the string
	*/
	static string trimLeft(const string &text);

	/**
	* Right trim for the string
	*/
	static string trimRight(const string &text);

	/**
	* Left and right trim for the string
	*/
	static string trim(const string &text);

	/**
	* Converts int to string
	*/
	static string toString(const int n);

	/**
	* Converts unsgined int to string
	*/
	static string toString(const unsigned int n);

	/**
	* Converts long to string
	*/
	static string toString(const long n);

	/**
	* Converts float to string
	*/
	static string toString(const float n);

	/**
	* Converts bool to string
	*/
	static string toString(const bool n);

	/**
	* Converts Vector2 to string
	*/
	static string toString(const Vector2 &v);

	/**
	* Converts Vector3 to string
	*/
	static string toString(const Vector3 &v);

	/**
	* Converts Vector4 to string
	*/
	static string toString(const Vector4 &v);

	/**
	* Converts Color to string
	*/
	static string toString(const Color &c);

	/**
	* Converts TgcBoundingBox to string
	*/
	static string toString(const TgcBoundingBox* b);
	

	/**
	* Retrieves the filename of a file from its absolute path.
	* Ex: C:\\folder1\file.jpg => file.jpg
	*/
	static string getFileNameFromPath(const string &path);

	/**
	* Parse string "[-8.00202,-6.87125,0]" to a float[3] array.
	* @param text string in the form [-8.00202,-6.87125,0]
	* @param data float array[3]
	*/
	static void TgcParserUtils::parseFloat3Array(const string &text, float (&data)[3]);

	/**
	* Parse string "[-8.00202,-6.87125,0]" to a float[3] array.
	* It swaps (x,y,z) to (x,z,y)  
	* @param text string in the form [-8.00202,-6.87125,0]
	* @param data float array[3]
	*/
	static void TgcParserUtils::parseFloat3ArrayAdapted(const string &text, float (&data)[3]);

	/**
	* Parse string "[4,2,1]" to a int[3] array.
	* @param text string in the form [4,2,1]
	* @param data int array[3]
	*/
	static void TgcParserUtils::parseInt3Array(const string &text, int (&data)[3]);

	/**
	* Parse string "[4,2,1]" to a int[3] array.
	* It swaps (x,y,z) to (x,z,y)  
	* @param text string in the form [4,2,1]
	* @param data int array[3]
	*/
	static void TgcParserUtils::parseInt3ArrayAdapted(const string &text, int (&data)[3]);

	/**
	* Parse string "[-8.00202,-6.87125]" to a float[2] array.
	* @param text string in the form [-8.00202,-6.87125]
	* @param data float array[2]
	*/
	static void TgcParserUtils::parseFloat2Array(const string &text, float (&data)[2]);

	/**
	* Parse string "[-8.00202,-6.87125]" to a float[2] array.
	* It swaps (x,y) to (y, x)  
	* @param text string in the form [-8.00202,-6.87125]
	* @param data float array[2]
	*/
	static void TgcParserUtils::parseFloat2ArrayAdapted(const string &text, float (&data)[2]);

	/**
	* Parse string "[-8.00202,-6.87125,0,0.211]" to a float[4] array.
	* @param text string in the form [-8.00202,-6.87125,0,0.211]
	* @param data float array[4]
	*/
	static void TgcParserUtils::parseFloat4Array(const string &text, float (&data)[4]);

	/**
	* Split the string text by the delimiter sep.
	* @param text
	* @param sep delimiter character
	* @return array of tokens
	*/
	static vector<string> TgcParserUtils::split(const string &text, char sep);

	/**
	* Div all the values of the array by divValue
	* @param data the array of values
	* @param length length of the array
	* @param divValue division to apply to every value of the array
	*/
	static void divFloatArrayValues(float* data, int length, float divValue);

	/**
	* Parse the following stream of ints: 15 10 16 11 16 10 16 11 17 12 17 11 17 12...
	* @param text text to be parsed
	* @param data the array to be filled (already allocated)
	* @param count the total numbers to parse
	*/
	static void parseIntStream(const string &text, int* data, int count);

	/**
	* Parse the following stream of ints: -74.1818 0.0 1.01613 -49.6512 0.0 1.01613...
	* @param text text to be parsed
	* @param data the array to be filled (already allocated)
	* @param count the total numbers to parse
	*/
	static void parseFloatStream(const string &text, float* data, int count);



	/**
	* Reads all the contents of text file and stores it in a string
	* @param path absolute file path
	* @param file string
	*/
	static string readAllFile(const string &path);



	/**
	* Converts a string to lower case
	*/
	static string toLower(const string &str);

	/**
	* Converts a string to upper case
	*/
	static string toUpper(const string &str);


private:
	
	TgcParserUtils();


};




}