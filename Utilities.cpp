#include "Utilities.h"
#include <string>

namespace sdds
{
    char Utilities::m_delimiter = ',';

    std::string trim(const std::string &str)
    {
        size_t first = str.find_first_not_of(' ');
        if (first == std::string::npos)
            return "";
        size_t last = str.find_last_not_of(' ');
        return str.substr(first, (last - first + 1));
    }

    void Utilities::setFieldWidth(size_t newWidth)
    {
        m_widthField = newWidth;
    };

    size_t Utilities::getFieldWidth() const
    {
        return m_widthField;
    };

    std::string Utilities::extractToken(const std::string &str, size_t &next_token_char, bool &more)
    {

        if (str[next_token_char] == m_delimiter)
        {
            more = false;
            throw std::invalid_argument("Delimiter at next_token_char");
        }

        size_t nextDelimiter = str.find(m_delimiter, next_token_char);

        if (nextDelimiter == next_token_char)
        {
            next_token_char++;
            more = str.find(m_delimiter, next_token_char) != std::string::npos;
            return "";
        }
        else if (nextDelimiter == std::string::npos)
        {
            more = false;
            nextDelimiter = str.length();
        }
        else
        {
            more = true;
        }

        std::string content = str.substr(next_token_char, nextDelimiter - next_token_char);
        size_t contentSize = content.size();

        content = trim(content);

        next_token_char = nextDelimiter + 1;

        if (contentSize > m_widthField)
            setFieldWidth(contentSize);
        return content;
    };

    void Utilities::setDelimiter(char newDelimiter)
    {
        m_delimiter = newDelimiter;
    };

    char Utilities::getDelimiter()
    {
        return m_delimiter;
    };

}