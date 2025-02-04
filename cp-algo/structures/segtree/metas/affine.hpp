#ifndef CP_ALGO_STRUCTURES_SEGMENT_TREE_METAS_AFFINE_HPP
#define CP_ALGO_STRUCTURES_SEGMENT_TREE_METAS_AFFINE_HPP
#include "base.hpp"
#include "../../../math/affine.hpp"
namespace cp_algo::structures::segtree::metas {
    template<typename base>
    struct affine_meta: base_meta<affine_meta<base>> {
        using meta = affine_meta;
        using lin = math::lin<base>;

        base sum = 0;
        lin to_push = {};

        affine_meta() {}
        affine_meta(base sum): sum(sum) {}

        void push(meta *L, meta *R, size_t l, size_t r) override {
            if(to_push.a != 1 || to_push.b != 0) {
                sum = to_push.a * sum + to_push.b * (r - l);
                if(r - l > 1) {
                    L->to_push.prepend(to_push);
                    R->to_push.prepend(to_push);
                }
                to_push = {};
            }
        }

        void pull(meta const& L, meta const& R, size_t, size_t) override {
            sum = L.sum + R.sum;
        }
    };
}
#endif // CP_ALGO_STRUCTURES_SEGMENT_TREE_METAS_AFFINE_HPP