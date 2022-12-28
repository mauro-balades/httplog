
#include <iterator>
#include <string>
#include <iostream>

#include <codecvt>
#include <locale>

#include "backend/parser/LogsParser.hpp"

#define INC_BOTH() _fmt_index++; _str_index++;

namespace backend {
    namespace parser {
        ParsedLog LogsParser::parse_line(std::wstring _line) {
            auto line = std::wstring_convert<std::codecvt_utf8<wchar_t>>().to_bytes(_line);

            while (_str_index < line.size()) {
                auto log_char = line[_str_index];
                auto format_char = _format[_fmt_index];

                if (format_char == '%') {
                    std::cout << "FOUND!\nFOUND!" << std::endl;
                    _str_index++;
                } else {
                    INC_BOTH()
                }

            }
        }
    }
}
