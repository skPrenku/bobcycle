#pragma once
#include <iostream>


enum driveLetters {

	c = 0x43,
	d = 0x44,
	e = 0x45,
	f = 0x46,
	g = 0x47,
	h = 0x48
};


struct disks
{

	disks();

	disks(std::string drive);


	std::string diskName;
	__int64 totalBytes = 0;
	__int64 totalFreeBytes = 0;

};



bool listDrives(int& totalDisks);


void displayDisks();