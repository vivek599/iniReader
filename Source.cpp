#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <map>

using namespace std;


#define STRINGIFY(s) #s


void removeChar(string& str, const char* charsToRemove) 
{
	for (unsigned int i = 0; i < strlen(charsToRemove); ++i) 
	{
		str.erase( remove(str.begin(), str.end(), charsToRemove[i]), str.end() );
	}
}

void GetBool(bool& variable, string _variableName, string variableName, string variableValue)
{
	removeChar(variableName, " ");
	string valuestring = variableValue;
	removeChar(valuestring, " ");
	if (variableName == _variableName)
	{
		variable = (valuestring == "true" || variableValue == "1") ? true : false;
	}
}

void GetInt(int& variable, string _variableName, string variableName, string variableValue)
{
	removeChar(variableName, " ");
	string valuestring = variableValue;
	removeChar(valuestring, " ");
	if (variableName == _variableName)
	{
		variable = stoi(valuestring);
	}
}

void GetString(string& variable, string _variableName, string variableName, string variableValue)
{
	removeChar(variableName, " ");
	if (variableName == _variableName)
	{
		size_t quotePos_start = variableValue.find('"');
		size_t quotePos_end = variableValue.length() - strlen(strrchr(variableValue.c_str(), '"'));
		string valuestring = variableValue.substr(quotePos_start, quotePos_end - quotePos_start + 1);
		variable = valuestring;
	}
}

void GetFloat( float& variable, string _variableName, string variableName, string variableValue)
{
	removeChar(variableName, " ");
	string valuestring = variableValue;
	removeChar(valuestring, " ");
	if (variableName == _variableName)
	{
		variable = stof(valuestring);
	}
}

int main()
{
	bool	bLoaded = false;
	string	path = "";
	float	factor = 0.0f;
	int		count = 0;

	ifstream inifile("Config/config.ini");

	if (!inifile.good())
	{
		cout << "bad file!" << endl;
		system("pause");
		return 0;
	}

	while (!inifile.eof())
	{
		string line;
		getline(inifile, line, '\n');

		if (line.length() != 0)
		{
			size_t equalPos = line.find("=");
			if (equalPos != string::npos)
			{
				string variableName = line.substr(0, equalPos);
				string variableValue = line.substr(equalPos + 1, line.length());

				GetBool(bLoaded, STRINGIFY(bLoaded), variableName, variableValue);
				GetInt(count, STRINGIFY(count), variableName, variableValue);
				GetFloat(factor, STRINGIFY(factor), variableName, variableValue);
				GetString(path, STRINGIFY(path), variableName, variableValue);
			}
		}
	}

	inifile.close();

	cout << STRINGIFY(bLoaded) << " = " << bLoaded << endl;
	cout << STRINGIFY(path) << " = " << path << endl;
	cout << STRINGIFY(factor) << " = " << factor << endl;
	cout << STRINGIFY(count) << " = " << count << endl;

	system("pause");
	return 0;
}