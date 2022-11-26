#include "component.hpp"
#include "vec.hpp"

double Component::get_mass() const {
    return mass_dry + mass_prop;
}
