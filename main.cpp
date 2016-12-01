#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cmath>

#include "Particle.hpp"
#include "ArgumentParser.hpp"

bool fileExist(const std::string&);
void nbodyBruteForce(std::vector<Particle> &, int type=0);
void printHelp();

const double TIMESTAMP   =   1e11;

int main(int argc, char* argv[])
{
    ArgumentParser argument(argc, argv);
    std::vector<Particle> particles;
    
    // Generate random particle with -n value argument
    if(argument.cmdOptionExists("-n"))
    {
        const int N = std::stoi(argument.getCmdOption("-n"));
        
        particles = Particle::generateRandomParticle(N);
        nbodyBruteForce(particles);
    }
    else if(argument.cmdOptionExists("-f"))
    {
        const std::string &filename = argument.getCmdOption("-f");
        if (!filename.empty())
        {
            if(fileExist(filename))
            {
                std::ifstream file(filename);
                std::string line;
                
                // I get all line of argument file
                while(getline(file, line))
                {
                    std::vector<std::string> data_tokens;
                    std::istringstream iss(line);
                    std::string data;
                    
                    while(getline(iss, data, '\t'))
                    {
                        data_tokens.push_back(data);
                    }
                    
                    // If I have not all data I need, error
                    if(data_tokens.size() != 6)
                    {
                        std::cerr << "Error : data in file : " << filename << " aren't well formatted. " << std::endl <<
                        "    rx ry vx vy mass bodie_name" << std::endl;
                        return EXIT_FAILURE;
                    }
                    
                    // One particle = one line of file
                    Particle p(std::stod(data_tokens.at(0)), std::stod(data_tokens.at(1)),
                               std::stod(data_tokens.at(2)), std::stod(data_tokens.at(3)),
                               0.0000e+00, 0.0000e+00,
                               std::stod(data_tokens.at(4)), data_tokens.at(5));
                    
                    particles.emplace_back(p);
                }
                
                int type_output( argument.cmdOptionExists("-o") );
                
                nbodyBruteForce(particles, type_output);
            }
            else
            {
                std::cerr << "Error : file : " << filename << " not found !";
                return EXIT_FAILURE;
            }
        }
        else
        {
            printHelp();
            return EXIT_FAILURE;
        }
    }
    else if(argument.cmdOptionExists("-h"))
    {
        printHelp();
        return EXIT_SUCCESS;
    }
    else
    {
        printHelp();
        return EXIT_FAILURE;
    }
    
    return EXIT_SUCCESS;
}

/**
 *  Run brute force for vector of particles and display result
 */
void nbodyBruteForce(std::vector<Particle>& particles, int type)
{
    const int n = particles.size();
    
    for(;;)
    {
        for(int i = 0; i < n; i++)
        {
            particles[i].resetForce();
            for(int j = 0; j < n; j++)
            {
                if(i != j)
                {
                    particles[i].addForce(particles[j]);
                }
            }
        }
        
        for(auto& particle:particles)
        {
            particle.update(TIMESTAMP);
        }
        
        if(type == 0)
        {
            std::copy(std::begin(particles), std::end(particles), std::ostream_iterator<Particle>(std::cout));
        }
        else
        {
            for(auto& particle:particles)
            {
                particle.displayOutputFile();
            }
        }
    }
}

/**
 *  Display usage of program
 */
void printHelp()
{
    std::cout << "Usage : n_body [options]" << std::endl <<
    "Options:" << std::endl <<
    "   -n     Number of bodies" << std::endl <<
    "   -f     Path to input file contains bodies data" << std::endl <<
    "   -o     If this argument exist, output result are save in file for plot" << std::endl <<
    "   -h     Print this help" << std::endl;
}

/**
 *  Test if file exist
 */
bool fileExist(const std::string& filename) {
    std::ifstream file(filename.c_str());
    
    return file.good();
}
