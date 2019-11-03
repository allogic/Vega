#pragma once

#include <Vega/Std.hpp>

#include <Vega/Core/Core.hpp>

namespace Vega::Utility::Parser {
  template<typename ... Aliases>
  static std::string Match(const std::vector<std::string> &args, std::string fallback, Aliases &&... alias) {
    std::stringstream ss;

    for (const auto &arg : args) ss << arg << ' ';

    std::string argsFormatted(ss.str());

    ss.clear();
    ss.str("");

    ss << '(';
    ((ss << alias << '|'), ...);
    ss.seekp(-1, std::ios_base::end);
    ss << ")=.*?\\s{1}";

    std::regex expression(ss.str());
    std::smatch matches;
    std::regex_search(argsFormatted, matches, expression);

    if (matches.size() == 0) return fallback;

    std::string result = matches[0].str();

    result.erase(std::end(result) - 1);

    std::size_t delimiterStart = result.find('=');
    std::size_t resultLength = result.length() - 1;

    if (resultLength - delimiterStart <= 0) return fallback;

    return result.substr(delimiterStart + 1, resultLength);
  }
}