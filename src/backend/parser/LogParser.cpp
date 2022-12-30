
#include <iterator>
#include <string>
#include <iostream>

#include <codecvt>
#include <locale>

#include "backend/parser/LogsParser.hpp"

#define INC_LOG() _fmt_index++; format_char = _format[_fmt_index];

#define INC_STR() _str_index++; log_char = line[_str_index];
#define DEC_STR() _str_index--; log_char = line[_str_index];

#define INC_BOTH() INC_LOG() INC_STR()


namespace backend {
    namespace parser {

        LogsParser::LogsParser(std::string format) : _format(format) {

        };

        ParsedLog LogsParser::parse_line(std::wstring _line) {
            ParsedLog result;
            auto line = std::wstring_convert<std::codecvt_utf8<wchar_t>>().to_bytes(_line);

            while (_str_index < line.size()) {
                log_char = line[_str_index];
                format_char = _format[_fmt_index];

                if (format_char == '%') {
                    INC_LOG()

                    if (format_char == '%' /* %% */) {
                        // do nothing
                    } else if (format_char == 'p') {
                        DEC_STR()
                        std::string path = "";

                        INC_LOG()
                        while (true) {
                            INC_STR()
                            if (log_char == 0 || log_char == ' ') {
                                break;
                            }

                            path += log_char;
                        }

                        result.path = path;
                    } else if (format_char == 'm') {
                        std::string method = "";

                        INC_LOG()
                        DEC_STR()

                        while (true) {
                            INC_STR()

                            if (log_char == 0 || log_char == ' ') {
                                break;
                            }

                            method += log_char;
                        }

                        if (method == "GET") {
                            result.method = ParsedLog::RequestMethod::GET;
                        } else if (method == "POST") {
                            result.method = ParsedLog::RequestMethod::POST;
                        } else if (method == "PUT") {
                            result.method = ParsedLog::RequestMethod::PUT;
                        } else if (method == "DELETE") {
                            result.method = ParsedLog::RequestMethod::DELETE;
                        } else if (method == "PATCH") {
                            result.method = ParsedLog::RequestMethod::PATCH;
                        } else if (method == "TRACE") {
                            result.method = ParsedLog::RequestMethod::TRACE;
                        } else if (method == "OPTIONS") {
                            result.method = ParsedLog::RequestMethod::OPTIONS;
                        } else if (method == "CONNECT") {
                            result.method = ParsedLog::RequestMethod::CONNECT;
                        } else if (method == "HEAD") {
                            result.method = ParsedLog::RequestMethod::HEAD;
                        } else {
                            // TODO: wtf?
                        }
                    }
                } else {
                    INC_BOTH()
                }

            }
        }
    }
}

#undef INC_BOTH
#undef INC_LOG
#undef INC_STR

#undef DEC_STR