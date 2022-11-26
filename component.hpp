///////////////////////////////////////////////////////////////////////////////
// Class: Component                                                          //
// Components that make up a "body"; can have a propellor/propellent         //
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

#ifndef COMPONENT_HPP
#define COMPONENT_HPP

#include "vec.hpp"

class Body;

class Component {
    public:
        double mass_dry, mass_prop, prop_force, prop_usage;
        Vec<double, 3> prop_angle;   // Pitch, yaw, roll
        bool prop_enabled;
        Body *parent;

        double get_mass() const;
};

#endif