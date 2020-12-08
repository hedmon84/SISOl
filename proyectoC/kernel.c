#define TRUE 1
#define FALSE 0

void putInMemory(int segment, int address, char character);
void printChar(char ch);
void printString(char *str);
void readFile(char *fileName, char *buffer);
void readString(char *buffer);
void readSector(char *buffer, int sector);
char readChar();
int compareFileNameStrings(char str1[6], char str2[6]);
void handleInterrupt21(int AX, int BX, int CX, int DX);
void loadFileIntoBuffer(char *fileSectorPointers, char *buffer);
int binToDec(char *fileSectorPointer);
int power(int base, int exp);
void executeProgram(char *name, int segment);
void moveByteToMemory(char byte, int segment);
void launchProgram(int segment);
void terminate();
void clearScreen();

char line[80];
char buffer[13312];
int main()
{

    // readFile("message.c", buffer);
    // printString(buffer);

    makeInterrupt21();
    executeProgram("shell", 0x2000);

    while (1)
    {
    }
    return 0;
}

void terminate()
{

    executeProgram("shell", 0x2000);
}

void executeProgram(char *name, int segment)
{
    char buffer[13312];
    int i = 0;
    int j = 0;

    readFile(name, buffer);

    for (i = 0; i < 13312; i++)
    {
        putInMemory(segment, i, buffer[i]);
    }

    launchProgram(segment);
}

int power(int base, int exp)
{
    int i, p;

    p = 1;

    for (i = 1; i <= exp; i++)
    {
        p = p * base;
    }

    return p;
}

int binToDec(char *fileSectorPointer)
{

    char b = fileSectorPointer[0];
    int i = 0;
    int index = 0;
    int x = 0;
    int y = 0;

    for (i = 7; i >= 0; i--)
    {
        x = b & 1;
        if (x == 0)
        {
        }
        else
        {
            y += power(2, index);
        }

        b >>= 1;
        index++;
    }

    return y;
}

void loadFileIntoBuffer(char *fileSectorPointers, char *buffer)
{
    int i = 0;
    int sectorNumber = 0;

    sectorNumber = binToDec(fileSectorPointers);

    if (sectorNumber == 0)
    {

        return;
    }

    do
    {
        sectorNumber = binToDec(fileSectorPointers);
        readSector(buffer, sectorNumber);

        buffer += 512;
        fileSectorPointers++;

    } while (sectorNumber != 0);

    //printString("\n\r");
}

int compareFileNameStrings(char str1[6], char str2[6])
{

    int i = 0;
    int isEqual = TRUE;

    for (i = 0; i < 6; i++)
    {
        if (str1[i] != str2[i])
        {
            isEqual = FALSE;
            return isEqual;
        }
    }

    return isEqual;
}

void printString(char *str)
{
    while (*str != '\0')
    {
        printChar(*str);
        str = str + 1;
    }
}

void readString(char *buffer)
{

    char c = 'a';
    int i = 0;
    while (c != 13 && 1)
    {
        c = readChar();

        if (c != 8)
        {
            //line[i] = c;
            *buffer++ = c;
            i++;
            printChar(c);
        }
        else
        {
            if (i > 0)
            {
                i--;
                buffer--;
            }

            printChar(0x8);
            printChar(' ');
            printChar(0x8);
        }
    }

    //line[i + 1] = '\0';
    *++buffer = '\0';
}

void readFile(char *fileName, char *buffer)
{

    char sectorContent[512];

    char *diskFileName;
    char *fileSectorPointers;
    int sectorNumber = 2;
    int bytesRead = 0;
    int strsAreEqual = FALSE;

    readSector(sectorContent, sectorNumber);

    diskFileName = sectorContent;

    for (bytesRead = 0; bytesRead < 512; bytesRead += 32)
    {

        strsAreEqual = compareFileNameStrings(diskFileName, fileName);

        if (strsAreEqual == TRUE)
        {
            fileSectorPointers = diskFileName + 6;
            loadFileIntoBuffer(fileSectorPointers, buffer);
            return;
        }

        diskFileName += 32;
    }

    return;
}

void handleInterrupt21(int AX, int BX, int CX, int DX)
{
    if (AX == 0)
    {
        printString(BX);
    }
    else if (AX == 1)
    {
        readString(BX);
    }
    else if (AX == 2)
    {
        readSector(BX, CX);
    }
    else if (AX == 3)
    {
        readFile(BX, CX);
    }
    else if (AX == 4)
    {
        executeProgram(BX, CX);
    }
    else if (AX == 5)
    {
        terminate();
    }
    else if (AX == 6)
    {
        clearScreen();
    }
    else
    {
        printString("Error on interrupt 21, unknown command on register AX!\0");
    }
}