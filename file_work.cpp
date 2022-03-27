#include <iostream>
#include <Windows.h>

#define FILE_ATTRIBUTES (FILE_ATTRIBUTE_ARCHIVE | FILE_ATTRIBUTE_NORMAL | FILE_ATTRIBUTE_HIDDEN | FILE_ATTRIBUTE_READONLY | FILE_ATTRIBUTE_SYSTEM)

using namespace std;

namespace IO
{
    BOOL move_file(LPCSTR from, LPCSTR to)
    {
        return MoveFileA(from, to);
    }

    BOOL is_exist(LPCSTR path, BOOL is_file)
    {
        if (is_file)
        {
            DWORD dwAttributes = GetFileAttributesA(path);
            return (dwAttributes != INVALID_FILE_ATTRIBUTES 
                    && !(dwAttributes & FILE_ATTRIBUTE_DIRECTORY));
        }
        else
        {
            DWORD dwAttributes = GetFileAttributesA(path);
            return dwAttributes != INVALID_FILE_ATTRIBUTES 
                    && (dwAttributes & FILE_ATTRIBUTE_DIRECTORY);
        }
    }

    LONGLONG get_file_size(LPCSTR file_name)
    {
        WIN32_FILE_ATTRIBUTE_DATA fa;
        if(!GetFileAttributesExA(file_name, GetFileExInfoStandard, &fa))
            return -1;
        
        LARGE_INTEGER size;
        size.HighPart = fa.nFileSizeHigh;
        size.LowPart = fa.nFileSizeLow;
        return size.QuadPart;
    }

    void search(string path, LPCSTR file_name)
    {
        WIN32_FIND_DATAA fd;
        string dir = path;
        HANDLE it = FindFirstFileA((dir + "\\*.*").c_str(), &fd);

        if (it != INVALID_HANDLE_VALUE)
        {
            do
            {
                 dir = path + "\\" + fd.cFileName;
                 if (fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY && lstrcmpA(fd.cFileName, ".") != 0 && lstrcmpA(fd.cFileName, "..") != 0)
                 {
                     search(dir, file_name);
                 }
                 else if ((fd.dwFileAttributes & FILE_ATTRIBUTES))
                 {
                     if(lstrcmpA(fd.cFileName, file_name))
                     {
                        cout << dir << endl;
                        break;
                     }
                 }
            } while(FindNextFileA(it, &fd));
            FindClose(it);
        }
    }
}

int main()
{
    return 0;
}