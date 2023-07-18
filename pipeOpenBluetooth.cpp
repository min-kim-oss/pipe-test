#include <stdio.h>

int main(int argc, char** argv)
{
    FILE *fp = NULL;
    char line[10240];

    if((fp = popen("bluetoothctl","r")) == NULL){
        printf("no end\n");
        return 1;
    }

    while(fgets(line,10240,fp) != NULL){
        printf("%s",line);
    }

    pclose(fp);
    return 0;
}