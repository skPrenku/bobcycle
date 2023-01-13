#include "usb.h"
#include <iomanip>
#include <Windows.h>


disks onlineDisk[6];


disks::disks() {
	GetDiskFreeSpaceExA(NULL,
		NULL,
		(PULARGE_INTEGER)&totalBytes,
		(PULARGE_INTEGER)&totalFreeBytes);
}

disks::disks(std::string drive) {
	GetDiskFreeSpaceExA(drive.c_str(),
		NULL,
		(PULARGE_INTEGER)&totalBytes,
		(PULARGE_INTEGER)&totalFreeBytes);
	diskName = drive.c_str();
}

bool listDrives(int& totalDisks)
{
	const DWORD bufferLength = 50;
	char buffer[bufferLength];
	int result = 0;


	result = GetLogicalDriveStrings(bufferLength, (LPWSTR)&buffer);

	for (int i = 0; i < result * 2; i++)
	{
		switch (buffer[i])
		{
		case driveLetters::c:
			onlineDisk[0] = disks("C:\\");
			break;
		case driveLetters::d:
			onlineDisk[1] = disks("D:\\");
			break;
		case driveLetters::e:
			onlineDisk[2] = disks("E:\\");
			break;
		case driveLetters::f:
			onlineDisk[3] = disks("F:\\");
			break;
		case driveLetters::g:
			onlineDisk[4] = disks("G:\\");
			break;
		case driveLetters::h:
			onlineDisk[5] = disks("H:\\");
			break;
		default:
			break;
		}

	}
	totalDisks = result / 4;



	return result;
}





void displayDisks() {

	int activeDisks;

	if (listDrives(activeDisks) == 0)
	{
		printf("Reading Drives failed, ERROR CODE: %d", GetLastError());
	}
	else {
		printf("Total Drives found: %d \n\n", activeDisks);

		for (int i = 0; i < activeDisks; i++)
		{



			std::cout << "Disk: " << onlineDisk[i].diskName.c_str() << std::endl;

			std::cout << "Disk Space: " << std::fixed << std::setprecision(2) << double(onlineDisk[i].totalBytes) / 1073741824 << " GB" << std::endl;
			std::cout << "Disk Space: " << std::fixed << std::setprecision(2) << double(onlineDisk[i].totalFreeBytes) / 1073741824 << " GB" << std::endl;
			/* devide by 1073741824 to get the right Disk-Space on windows*/



		}
	}

}