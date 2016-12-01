#ifndef Particle_hpp
#define Particle_hpp

#include <iostream>
#include <vector>

/**
    This class allows to create a particle and 
    to apply the calculation of the NBody problem
 */
constexpr double    G           =   6.673e-11;

class Particle{
    double _rx, _ry;      //position
    double _vx, _vy;      //velocity
    double _fx, _fy;      //force
    double _mass;         //mass
    std::string _name;
    
public:
    
    Particle(double rx, double ry, double vx, double vy, double fx, double fy, double mass, std::string name)
    :_rx(rx), _ry(ry),
     _vx(vx), _vy(vy),
     _fx(fx), _fy(fy),
     _mass(mass),
     _name(name){}
    
    Particle& update(double);
    Particle& resetForce();
    Particle& addForce(Particle& p);
    
    void displayOutputFile();
    
    //static method
    static std::vector<Particle> generateRandomParticle(int);
    static std::string randomName(size_t);
    static double getRand(int);
    static double getRandMass(int);
    
    friend std::ostream& operator<<(std::ostream& str, Particle const& p)
    {
        return str <<
            "name == " << p._name <<
            " rx == " << p._rx << " ry == " << p._ry <<
            " vx == " << p._vx << " vy == " << p._vy <<
            " mass == " << p._mass << std::endl;
    }
};

#endif /* Particle_hpp */
