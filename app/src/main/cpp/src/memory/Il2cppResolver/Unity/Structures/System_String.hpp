#pragma once

#include <asm-generic/fcntl.h>
#include <fcntl.h>
#include "utf8/utf8.h"
namespace Unity
{


    struct System_String : il2cppObject
    {
        int m_iLength;
        char16_t m_wString[1024];

        void Clear()
        {
            if (!this) return;
            
            memset(m_wString, 0, static_cast<size_t>(m_iLength) * 2);
            m_iLength = 0;
        }

        bool isAllocated(char16_t* x) {
            int fd = open("/dev/random", O_WRONLY);
            bool valid = true;
            if (write(fd, x, sizeof(x)) < 0) {
                valid = false;
            }
            close(fd);
            return valid;
        }

        std::string Utf16ToUtf8(char16_t* utf16String, size_t length) {
            std::string utf8String;
            utf8String.reserve(length);
            utf8::unchecked::utf16to8(utf16String, utf16String + length, std::back_inserter(utf8String));
            return utf8String;
        }

        char *str2char(const std::string& str) {
            char *c = new char[str.size() + 1];
            std::strcpy(c, str.data());
            return c;
        }
        std::string get_string() {
            if (!isAllocated(m_wString)) return "ERROR: chars is null";
            return Utf16ToUtf8(m_wString, m_iLength);
        }
        std::string ToString()
        {
            if (!this || m_wString == nullptr || m_iLength == 0)
                return "";
            return str2char(get_string());
            /*std::string retStr;
            mbstate_t state = mbstate_t();
            char buf[MB_CUR_MAX];
            
            for (size_t i = 0; i < m_iLength; ++i)
            {
                size_t ret = wcrtomb(buf, m_wString[i], &state);
                if (ret == (size_t)-1)
                {
                    return "";
                }
                retStr.append(buf, ret);
            }
            return retStr;*/
        }


    };
}
