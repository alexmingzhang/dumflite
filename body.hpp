///////////////////////////////////////////////////////////////////////////////
// Class: Body                                                               //
// A thing that is made of components, meant for some kind of flying machine //
//                                                                           //
// Example:                                                                  //
//      Body rocket;                                                         //
//      Component *c = new Component;                                        //
//      c->mass_dry = 20.0 * SI::kg;                                         //
//      c->mass_prop = 80.0 * SI::kg;                                        //
//      c->prop_force = 250.0 * SI::N;                                       //
//      c->prop_usage = 0.1 * SI::kg / 1.0 * SI::s;                          //
//      c->prop_angle = Vec<double, 3> {90 * DEG_TO_RAD, 0, 0};              //
//      c->prop_enabled = true;                                              //
//                                                                           //
//      rocket.add_component(c);                                             //
///////////////////////////////////////////////////////////////////////////////

#ifndef BODY_HPP
#define BODY_HPP

#include <vector>
#include "vec.hpp"

class Component;

class Body {
    public:
        Body();
        
        void add_component(Component *c);
        void remove_component(Component *c);
        void remove_component(std::size_t index);

        void update(double time_step);
        double get_seconds_elapsed() const;

        Vec<double, 3> & get_pos() const;
        Vec<double, 3> & get_vel() const;
        Vec<double, 3> & get_acc() const;
    private:
        std::vector<Component *> components;
        Vec<double, 3> pos, vel, acc;
        double seconds_elapsed;
};

#endif