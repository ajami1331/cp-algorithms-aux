#ifndef CP_ALGO_MATH_FACTORIZE_HPP
#define CP_ALGO_MATH_FACTORIZE_HPP
#include "primality.hpp"
#include "../random/rng.hpp"
#include <generator>
namespace cp_algo::math {
    // https://en.wikipedia.org/wiki/Pollard%27s_rho_algorithm
    template<typename _Int>
    auto proper_divisor(_Int m) {
        using Int = std::make_signed_t<_Int>;
        using base = dynamic_modint<Int>;
        return m % 2 == 0 ? 2 : base::with_mod(m, [&]() {
            base t = random::rng();
            auto f = [&](auto x) {
                return x * x + t;
            };
            base x = 0, y = 0;
            base g = 1;
            while(g == 1) {
                for(int i = 0; i < 64; i++) {
                    x = f(x);
                    y = f(f(y));
                    if(x == y) [[unlikely]] {
                        t = random::rng();
                        x = y = 0;
                    } else {
                        base t = g * (x - y);
                        g = t == 0 ? g : t;
                    }
                }
                g = std::gcd(g.getr(), m);
            }
            return g.getr();
        });
    }
    template<typename Int>
    std::generator<Int> factorize(Int m) {
        if(is_prime(m)) {
            co_yield m;
        } else if(m > 1) {
            auto g = proper_divisor(m);
            co_yield std::ranges::elements_of(factorize(g));
            co_yield std::ranges::elements_of(factorize(m / g));
        }
    }
}
#endif // CP_ALGO_MATH_FACTORIZE_HPP
