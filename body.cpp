#include <algorithm>
#include <cmath>

#include "body.hpp"
#include "component.hpp"
#include "constants.hpp"
#include "rungekutta.hpp"
#include "vec.hpp"

Body::Body() : seconds_elapsed(0) {}

void Body::add_component(Component *c) {
    components.push_back(c);
}

void Body::remove_component(Component *c) {
    auto it = std::find(components.begin(), components.end(), c);
    components.erase(it);
}

void Body::remove_component(std::size_t index) {
    components.erase(components.begin() + index);
}

void Body::update(double time_step) {
    Vec<double, 3> prop_force_vec = {0, 0, 0};
    double total_mass = 0;

    for (Component *c : components) {
        if (c->prop_enabled && c->mass_prop > 0) {
            c->mass_prop = c->mass_prop - c->prop_usage * time_step;
            
            if (c->mass_prop < 0)
                c->mass_prop = 0;

            prop_force_vec[2] += c->prop_force * std::sin(c->prop_angle[0]);
            double horizontal_magnitude = c->prop_force * std::cos(c->prop_angle[0]);

            prop_force_vec[0] += horizontal_magnitude * std::sin(c->prop_angle[1]);
            prop_force_vec[1] += horizontal_magnitude * std::cos(c->prop_angle[1]);
        }

        total_mass += c->get_mass();
    }
    
    this->acc = prop_force_vec * std::pow(total_mass, -1);
    this->acc[2] -= GRAVITY;

    this->vel += this->acc * time_step;
    this->pos += this->vel * time_step;

    seconds_elapsed += time_step;
}

/*
void Body::update(double time_step) {
    Vec<double, 3> prop_force_vec = {0, 0, 0};
    double total_mass = 0;

    for (Component *c : components) {
        if (c->prop_enabled && c->mass_prop > 0) {
            double prop_usage = c->prop_usage;

            // c->mass_prop = rk4<double, double>(this->seconds_elapsed, c->mass_prop, this->seconds_elapsed + time_step, time_step, [&](double x, double y) -> double { return prop_usage * -1; });
            c->mass_prop = c->mass_prop - c->prop_usage * time_step;
            
            if (c->mass_prop < 0)
                c->mass_prop = 0;

            prop_force_vec[2] += c->prop_force * std::sin(c->prop_angle[0]);
            double horizontal_magnitude = c->prop_force * std::cos(c->prop_angle[0]);

            prop_force_vec[0] += horizontal_magnitude * std::sin(c->prop_angle[1]);
            prop_force_vec[1] += horizontal_magnitude * std::cos(c->prop_angle[1]);
        }

        total_mass += c->get_mass();
    }
    
    this->acc = prop_force_vec * std::pow(total_mass, -1);
    this->acc[2] -= GRAVITY;


    this->vel += this->acc * time_step;
    this->pos += this->vel * time_step;

    seconds_elapsed += time_step;
}
*/

double Body::get_seconds_elapsed() const {
    return this->seconds_elapsed;
}

Vec<double, 3> & Body::get_pos() const {
    return const_cast<Body *>(this)->pos;
}

Vec<double, 3> & Body::get_vel() const {
    return const_cast<Body *>(this)->vel;
}

Vec<double, 3> & Body::get_acc() const {
    return const_cast<Body *>(this)->acc;
}