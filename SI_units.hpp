///////////////////////////////////////////////////////////////////////////////
// SI Units                                                                  //
///////////////////////////////////////////////////////////////////////////////

#ifndef SI_UNITS_HPP
#define SI_UNITS_HPP

namespace SI {
    // TIME
    constexpr double ms     = 0.001;
    constexpr double s      = 1.0;
    constexpr double min    = 60.0;
    constexpr double hour   = 3600.0;

    // LENGTH
    constexpr double mm     = 0.001;
    constexpr double cm     = 0.01;
    constexpr double m      = 1.0;
    constexpr double km     = 1000.0;

    // MASS
    constexpr double g      = 0.001;
    constexpr double kg     = 1.0;

    // FORCE
    constexpr double N      = 1.0;
    constexpr double kN     = 1000.0;
}

#endif