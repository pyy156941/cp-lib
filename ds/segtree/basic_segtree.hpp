#pragma once

template <typename M>
struct segtree
{
    using T = typename M::value_type;

    int size;
    vector <T> tree;
    M monoid;

    segtree(const vector <T>& _a, const M& _m) : size(_a.size()), monoid(_m) // from array, 1-indexed (maybe add 0 to front here?)
    {
        tree.resize(4 * size + 1);
        build(1, 1, size, _a);
    }

    segtree(const int& _size, const M& _m) : size(_size), monoid(_m) { tree.resize(4 * size + 1, monoid.identity); } // empty init with just size

    void pushup(int cur) { tree[cur] = monoid.merge(tree[ls(cur)], tree[rs(cur)]); }

    void build(int cur, int s, int t, const vector <T>& _a)
    {
        if (s == t)
        {
            tree[node] = _a[s];
            return;
        }
        int mid = (s + t) >> 1;
        build(ls(cur), s, mid, _a);
        build(rs(cur), mid + 1, t, _a);
        pushup(cur);
    }
}