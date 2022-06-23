#include <windows.h>
#include <unistd.h>

void clearChromeCache()
{
    system("taskkill /F /IM chrome* /T > nul");
    sleep(1);
    
    char path[256] = "\"C:\\Users\\";
    strcat(path,getenv("USERNAME"));
    strcat(path,"\\AppData\\Local\\Google\\Chrome\\User Data\\Default\\Cache\"");

    char removePath[256]="";
    strcat(removePath,"rmdir /Q /S ");
    strcat(removePath,path);

    system(removePath);

    char createPath[256]="";
    strcat(createPath,"mkdir ");
    strcat(createPath,path);
    
    system(createPath);
}

void clearBrowserCache()
{
    clearChromeCache();
}