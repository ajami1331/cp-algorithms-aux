#ifndef CP_ALGO_DATA_STRUCTURES_TREAP_HPP
#define CP_ALGO_DATA_STRUCTURES_TREAP_HPP
#include "../random/rng.hpp"
#include "treap/common.hpp"
#include <array>
namespace cp_algo::data_structures::treap {
    template<typename meta>
    struct node: std::enable_shared_from_this<node<meta>> {
        using treap = std::shared_ptr<node>;
        meta _meta;
        int prior = random::rng();
        size_t size = 1;
        treap children[2] = {nullptr, nullptr};
        enum subtree {L, R};

        node() {}
        node(meta _meta): _meta(_meta) {}
        node(meta _meta, int prior): _meta(_meta), prior(prior) {}

        static treap make_treap(auto...args) {
            return std::make_shared<node>(args...);
        }

        treap pull() {
            _meta.pull(children[L], children[R]);
            size = 1 + _safe(children[L], size) + _safe(children[R], size);
            return this->shared_from_this();
        }

        treap push() {
            _meta.push(children[L], children[R]);
            return this->shared_from_this();
        }

        // set i-th child and pull metadata
        treap set(subtree i, treap t) {
            children[i] = t;
            return pull();
        }

        // push changes and detach the i-th child
        treap cut(subtree i) {
            return children[i];
        }

        static treap merge(treap A, treap B) {
            if(!_safe(A, push()) || !_safe(B, push())) {
                return A ? A : B;
            } else if(A->prior < B->prior) {
                return A->set(R, merge(A->cut(R), B));
            } else {
                return B->set(L, merge(A, B->cut(L)));
            }
        }

        // return {L, R}, where |L|=k or L=A when |A| < k
        static std::array<treap, 2> split(treap A, size_t k) {
            if(!_safe(A, push())) {
                return {nullptr, nullptr};
            } else if(_safe(A->children[L], size) >= k) {
                auto [split_L, split_R] = split(A->cut(L), k);
                return {split_L, A->set(L, split_R)};
            } else {
                k -= _safe(A->children[L], size) + 1;
                auto [split_L, split_R] = split(A->cut(R), k);
                return {A->set(R, split_L), split_R};
            }
        }

        static void exec_on_segment(treap &A, size_t l, size_t r, auto func) {
            auto [LM, R] = split(A, r);
            auto [L, M] = split(LM, l);
            func(M);
            A = merge(L, merge(M, R));
        }

        static void insert(treap &A, size_t pos, treap t) {
            auto [L, R] = split(A, pos);
            A = merge(L, merge(t, R));
        }

        static void erase(treap &A, size_t pos) {
            auto [L, MR] = split(A, pos);
            auto [M, R] = split(MR, 1);
            A = merge(L, R);
        }

        static void exec_on_each(treap &A, auto func) {
            if(A) {
                exec_on_each(A->children[L], func);
                func(A);
                exec_on_each(A->children[R], func);
            }
        }

        treap pull_all() {
            _safe(children[L], pull_all());
            _safe(children[R], pull_all());
            return pull();
        }

        treap push_all() {
            push();
            _safe(children[L], push_all());
            _safe(children[R], push_all());
            return this->shared_from_this();
        }

        static treap build(auto const& nodes) {
            std::vector<treap> st;
            for(auto cur: nodes) {
                while(st.size() >= 2 && st[st.size() - 2]->prior > cur->prior) {
                    st.pop_back();
                }
                if(!st.empty() && st.back()->prior > cur->prior) {
                    cur->set(L, st.back());
                    st.pop_back();
                }
                if(!st.empty() && st.back()->prior < cur->prior) {
                    st.back()->set(R, cur);
                }
                st.push_back(cur);
            }
            return st.empty() ? nullptr : st[0]->pull_all();
        }
    };

    struct null_meta {
        void pull(auto const, auto const) {}
        void push(auto&, auto&) {}
    };
}
#endif // CP_ALGO_DATA_STRUCTURES_TREAP_HPP