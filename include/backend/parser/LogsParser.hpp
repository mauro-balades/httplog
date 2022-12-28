
#include <string>

#ifndef __BACKEND_LOGS_PARSER_H_
#define __BACKEND_LOGS_PARSER_H_

namespace backend {
    namespace parser {
        struct ParsedLog {
            
        };

        class LogsParser {
            public:
                LogsParser(std::string format) : _format(format) {};
                ~LogsParser() = default;

                ParsedLog parse_line(std::wstring line);

            private:
                std::string _format;

                int _str_index = 0;
                int _fmt_index = 0;
        };
    }
}

#endif // __BACKEND_LOGS_PARSER_H_
