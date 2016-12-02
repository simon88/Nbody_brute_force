#ifndef ArgumentParser_hpp
#define ArgumentParser_hpp

#include <iostream>
#include <vector>
#include <algorithm>

/**
    This class makes it possible to manage the arguments 
    received by the program
 */
class ArgumentParser{
    
public:
    ArgumentParser(int argc, char **argv);
    
    const std::string& getCmdOption(const std::string &option) const;
    bool cmdOptionExists(const std::string &option) const;
    int getArgc();
    
private:
    int _argc;
    std::vector<std::string>_tokens;
};

#endif /* ArgumentParser_hpp */
