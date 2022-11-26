///////////////////////////////////////////////////////////////////////////////
// Class: Body                                                               //
// Simulates flight using Runge-Kutta integration                            //
///////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <iomanip>
#include <sstream>
#include <cstdint>

#include "vec.hpp"
#include "SI_units.hpp"
#include "constants.hpp"
#include "body.hpp"
#include "component.hpp"

int main() {
    constexpr double time_step = 1.0 * SI::ms;

    // Print a status message every simulation second
    constexpr uint64_t print_step = static_cast<uint64_t>(1.0 * SI::s / time_step);

    Body rocket;
    Component *c = new Component;

    // Add components to rocket
    c->mass_dry = 20.0 * SI::kg;
    c->mass_prop = 80.0 * SI::kg;
    c->prop_force = 250.0 * SI::N;
    c->prop_usage = 0.1 * SI::kg / 1.0 * SI::s;
    c->prop_angle = Vec<double, 3> {45 * DEG_TO_RAD, 45 * DEG_TO_RAD, 0};
    c->prop_enabled = true;

    rocket.add_component(c);
    
    uint64_t time_step_count = 0;
    std::cout << "          " << std::left << std::setw(20) << "Position (m)" << ' ' << std::setw(20) << "Velocity (m/s)" << ' ' << std::setw(20) << "Acceleration (m/s^2)" << std::endl;
    
    auto print_info = [&time_step, &time_step_count, &rocket]() -> void {
        std::ostringstream output;
        output << std::right << std::setw(8) << time_step_count * time_step << "s " << std::left << std::setw(20) << rocket.get_pos() << ' ' << std::setw(20) << rocket.get_vel() << ' ' << std::setw(20) << rocket.get_acc();
        std::cout << "\r" << output.str() << std::flush;
    };
    
    // Flight simulation
    do {
        if (time_step_count % print_step  == 0)
            print_info();
        
        rocket.update(time_step);
        time_step_count++;
    } while (rocket.get_pos()[2] >= 0);

    print_info();

    return 0;
}