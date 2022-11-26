#ifndef RUNGEKUTTA_HPP
#define RUNGEKUTTA_HPP

#include <functional>

// Fourth order runge-kutta
template <typename Tx, typename Ty>
Ty rk4(Tx x0, Ty y0, Tx x, Tx h, std::function<Ty(Tx, Ty)> dydx) {
    std::size_t n = static_cast<std::size_t>((x - x0) / h);
    
    Ty k1, k2, k3, k4;
    Ty y = y0;

    for (std::size_t i = 0; i < n; ++i) {
        k1 = h * dydx(x0, y);
        k2 = h * dydx(x0 + 0.5 * h, y + 0.5 * k1);
        k3 = h * dydx(x0 + 0.5 * h, y + 0.5 * k2);
        k4 = h * dydx(x0 + h, y + k3);

        y = y + (1.0 / 6.0) * (k1 + 2.0 * k2 + 2.0 * k3 + k4);

        x0 = x0 + h;
    }

    return y;
}


#endif