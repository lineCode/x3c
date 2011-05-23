/*! \file pathstr.h
 *  \brief Included by portimpl.h to implement path functions.
 *  \author Zhang Yun Gui, X3 C++ PluginFramework
 *  \date   2011.5.23
 */
#ifndef X3_PORTABILITY_PATHSTR_IMPL_H
#define X3_PORTABILITY_PATHSTR_IMPL_H

static inline bool IsPathSlash(wchar_t c)
{
    return L'\\' == c || L'/' == c;
}

char* PathFindFileNameA(const char* path)
{
    const char* p1 = strrchr(path, '\\');
    const char* p2 = strrchr(path, '/');

    p1 = (!p1 || p2 && p2 > p1) ? p2 : p1;

    return const_cast<char*>(p1 ? p1 + 1 : p1);
}

wchar_t* PathFindFileNameW(const wchar_t* path)
{
    const wchar_t* p1 = wcsrchr(path, L'\\');
    const wchar_t* p2 = wcsrchr(path, L'/');

    p1 = (!p1 || p2 && p2 > p1) ? p2 : p1;

    return const_cast<wchar_t*>(p1 ? p1 + 1 : p1);
}

bool PathIsRelativeW(const wchar_t* path)
{
    return !path || wcsrchr(path, L':') == NULL
        && _wcsnicmp(path, L"\\\\", 2) != 0
        && _wcsnicmp(path, L"//", 2) != 0;
}

void PathStripPathW(wchar_t* path)
{
    wchar_t* filename = PathFindFileNameW(path);

    if (filename && filename > path)
    {
        while (*filename)
        {
            *path++ = *filename++;
        }
        *path = *filename;
    }
}

void PathRemoveFileSpecW(wchar_t* path)
{
    wchar_t* filename = PathFindFileNameW(path);

    if (filename && filename > path)
    {
        *(filename - 1) = 0;
    }
}

void PathRemoveExtensionW(wchar_t* path)
{
    wchar_t* dot = wcsrchr(path, L'.');

    if (dot)
    {
        *dot = 0;
    }
}

void PathRemoveBackslashW(wchar_t* path)
{
    int len = wcslen(path);

    if (len > 0 && IsPathSlash(path[len - 1]))
    {
        path[len - 1] = 0;
    }
}

void PathAppendW(wchar_t* path, const wchar_t* more)
{
    ASSERT(path && more);
    int len = wcslen(path);

    if (len > 0 && !IsPathSlash(path[len - 1]))
    {
        strcat_s(path, MAX_PATH, L"/");
    }
    strcat_s(path, MAX_PATH, IsPathSlash(*more) ? more + 1 : more);
}

wchar_t* PathAddBackslashW(wchar_t* path)
{
    int len = wcslen(path);

    if (len > 0 && !IsPathSlash(path[len - 1]))
    {
        strcat_s(path, MAX_PATH, L"/");
    }

    return path;
}

void PathRenameExtensionW(wchar_t* path, const wchar_t* more)
{
    wchar_t* dot = wcsrchr(path, L'.');

    if (!dot)
    {
        dot = path + wcslen(path);
    }
    wcscpy_s(dot, MAX_PATH - (dot - path), more);
}

#endif // X3_PORTABILITY_PATHSTR_IMPL_H