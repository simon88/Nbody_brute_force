#include <cmath>
#include <random>

#include "Particle.hpp"

Particle& Particle::update(double timestamp)
{
    _vx += timestamp;
    
    return *this;
}

Particle& Particle::resetForce()
{
    _fx = 0.0;
    _fy = 0.0;
    
    return *this;
}

Particle& Particle::addForce(Particle& p)
{
    double EPS = 3E4;
    double dx = _rx - p._rx;
    double dy = _ry - p._ry;
    double dist = sqrt(dx*dx + dy*dy);
    double F = (G * _mass * p._mass) / (dist*dist + EPS*EPS);
    
    _fx += F * dx / dist;
    _fy += F * dy / dist;
    
    return *this;
}

std::vector<Particle> Particle::generateRandomParticle(int n)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, 100);
    
    std::vector<Particle> particles;
    particles.reserve(n);
    
    for(int i = 0; i < n; i++)
    {
        particles.emplace_back(Particle::getRand(dis(gen)), Particle::getRand(dis(gen)),
                               Particle::getRand(dis(gen)), Particle::getRand(dis(gen)),
                               Particle::getRand(dis(gen)), Particle::getRand(dis(gen)),
                               Particle::getRandMass(dis(gen)), Particle::randomName(5));
    }
    
    return particles;
}

void Particle::displayOutputFile()
{
    std::cout << _rx << " " << _ry << " " << 0.00 << " ";
    std::cout << _vx << " " << _vy << " " << 0.00 << std::endl;
}

std::string Particle::randomName(size_t length)
{
    auto randchar = []() -> char
    {
        const char charset[] =
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";
        const size_t max_index = (sizeof(charset) - 1);
        return charset[ rand() % max_index ];
    };
    
    std::string str(length,0);
    std::generate_n( str.begin(), length, randchar );
    
    return str;
}

double Particle::getRand(int random)
{
    return 1e18*exp(-1.8)*(.5- random );
}

double Particle::getRandMass(int random)
{
    return 1.98892e30*random + 1e20;
}
