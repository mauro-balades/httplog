
#include <string>

#ifndef __BACKEND_LOGS_PARSER_H_
#define __BACKEND_LOGS_PARSER_H_

namespace backend {
    namespace parser {
        struct ParsedLog {
            std::string path;

            enum RequestMethod {
                GET,
                POST,
                PUT,
                DELETE,
                PATCH,
                TRACE,
                OPTIONS,
                CONNECT,
                HEAD,
            } method;
        };

        class LogsParser {
            public:
                LogsParser(std::string format);
                ~LogsParser() = default;

                ParsedLog parse_line(std::wstring line);

            private:
                std::string _format;

                int _str_index = 0;
                int _fmt_index = 0;

                char log_char;
                char format_char;
        };
    }
}

#endif // __BACKEND_LOGS_PARSER_H_
