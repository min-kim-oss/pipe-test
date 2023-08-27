#include <stdio.h>
#include <unistd.h> 

int main(int argc, char** argv)
{
    execlp("bluetoothctl", "bluetoothctl", NULL);
    return 0;
}