#include "ArgumentParser.hpp"

/**
    Put all arg in vector of string
 */
ArgumentParser::ArgumentParser(int argc, char **argv)
{
    _argc = argc;
    for (int i=1; i < _argc; ++i)
    {
        this->_tokens.push_back(std::string(argv[i]));
    }
}

/**
    Get argument following the option
 */
const std::string& ArgumentParser::getCmdOption(const std::string &option) const
{
    static const std::string empty = "";
    std::vector<std::string>::const_iterator itr;
    itr =  std::find(this->_tokens.begin(), this->_tokens.end(), option);
    
    if (itr != this->_tokens.end() && ++itr != this->_tokens.end())
    {
        return *itr;
    }
    return empty;
}

bool ArgumentParser::cmdOptionExists(const std::string &option) const
{
    return std::find(this->_tokens.begin(), this->_tokens.end(), option)
    != this->_tokens.end();
}

int ArgumentParser::getArgc()
{
    return _argc;
}
