// gitupdate.cpp : Tento soubor obsahuje funkci main. Provádění programu se tam zahajuje a ukončuje.
//




#define _CTR_SECURE_NO_WARNINGS

#include <iostream>
#include <fstream>
#include <string.h>
#include <conio.h>
#include <windows.h>
#include <stdlib.h>
#include <string>
#include<algorithm>
#include <cstring>
#include <functional>
#include <sstream>


 
//#define START


#pragma comment(linker,"\"/manifestdependency:type='win32' \
name='Microsoft.Windows.Common-Controls' version='6.0.0.0' \
processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"") 

using namespace std;

//vraci jestli nasel novy update
/*bool LoadUpdates() {

}*/

string version = "v1.2";
string str = "";

int create_copy(const char* NameSource, const char* targetName) {
	const unsigned buflen = 4096;
	ifstream source;
	ofstream target;

	unsigned _count = 0;
	char buffer[buflen];
	unsigned loaded;

	source.open(NameSource, ios::in | ios::binary);
	if (!source) {
		return -1;
	}

	target.open(targetName, ios::out | ios::binary);
	if (!target) {
		return -3;
	}

	while (source.read(buffer, buflen), loaded = source.gcount(), loaded > 0) {
		target.write(buffer, loaded);
		_count += loaded;
	}


	source.close();
	target.close();

	return _count;
}

bool FolderExists(const string& path)
{
	DWORD dwAttrib = GetFileAttributesA(path.c_str());
	return dwAttrib != INVALID_FILE_ATTRIBUTES && (dwAttrib & FILE_ATTRIBUTE_DIRECTORY) != 0;
}

void eraseSubStr(std::string& mainStr, const std::string& toErase)
{
	// Search for the substring in string
	size_t pos = mainStr.find(toErase);
	if (pos != std::string::npos)
	{
		// If found then erase it from string
		mainStr.erase(pos, toErase.length());
	}
}

inline bool FileExist(const std::string& name) {
#pragma warning(suppress : 4996)
	if (FILE* file = fopen(name.c_str(), "r")) {
		fclose(file);
		return true;
	}
	else {
		return false;
	}
}

string ToString(int x) {
	stringstream ss;
	ss << x;
	return ss.str();
}


int main()
{
	HWND con = GetConsoleWindow();
#pragma warning(disable: 4996)
	string path = getenv("PRG path");
	string pP = path + "/ver.txt";
	ifstream verL(pP.c_str());
#ifdef START
	getline(verL, version);
#endif
	cout << path << endl;
	if (FileExist("info.txt")) {
		remove("info.txt");
	}
	if (FileExist("p.zip")) {
		remove("p.zip");
	}

    system("curl -L -O -C - https://raw.githubusercontent.com/MitasVit/Patern-Remember-Game/main/info.txt");
	//curl https://codeload.github.com/MitasVit/Patern-Remember-Game/zip/refs/tags/v1.3 >> 13
	ifstream File("info.txt");
	string line[2];
	string must;
	if (File.is_open())
	{
		for(int i = 0; i < 2; i++){
			getline(File, line[i]);
			cout <<  line[i] << endl;
		}
		File.close();
	}
	else
	{
		cout << "Error! File not found!";
		exit(1);
	}
	if (line[0] != version) {
		string t = "New update found version(" + line[0] + "), do you want to install?";
		int tmp = MessageBoxA(NULL, t.c_str(), "New update found", MB_YESNO | MB_ICONQUESTION);
		if (tmp == IDYES) {
			HWND win = FindWindow(NULL, L"Patern Remember Game");
			DestroyWindow(win);
			version = line[0];
#ifdef START
			verL.close();
			ifstream _new(Pp.c_str());
			_new << version;
#endif
			system("CLS");
			str = line[1];
			//Download(con);
			string t2 = "curl -L -C -  " + line[1] + " >> p.zip";
			system(t2.c_str());
            system("mkdir p");
			cout << "powershell -command \"Expand-Archive -Force 'p.zip' 'p'\"" << endl;
			system("powershell -command Expand - Archive - Force 'p.zip' 'p'");
			line[0].erase(remove(line[0].begin(), line[0].end(), 'v'), line[0].end());
			cout << endl <<"line0 " << line[0] << endl;
			string t3 = "Patern-Remember-Game-" + line[0];
			cout << endl << "t3 " << t3 << endl;
			string p1 = "p/" + t3 + "/Patern Remember Game/Debug/Patern Remember Game.exe";
			cout << "p1 " << p1 << endl;
			string full = path + "/Patern Remember Game.exe";
			cout << full << endl;
			create_copy(p1.c_str(), full.c_str());
			ShellExecuteA(NULL, "open", full.c_str(), NULL, NULL, SW_SHOWNORMAL);
			remove("p.zip");
			remove("info.txt");
			system("rmdir p");
			/*
			* --------------------SETUP
			* 
			[Registry]
				Root: HKCU; Subkey: "Environment"; ValueType:string; ValueName: "PRG path"; \
				ValueData: {autopf}\{#MyAppName}; Flags: preservestringtype
			[Setup]
				; Tell Windows Explorer to reload the environment
				ChangesEnvironment=yes
				
				*/

		}
	}
	
	/*cout << endl << endl << endl;
	must = line[1];
	cout << must << endl;
	eraseSubStr(must, "<html><body>You are being <a href=\"");
	eraseSubStr(must, "\" > redirected< / a>.< / body> < / html>");
	cout << must << endl;*/
}