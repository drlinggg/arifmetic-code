#include <bits/stdc++.h>
#define fast std::cin.tie(0);std::ios_base::sync_with_stdio(0);
using namespace std;
typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;
const ll RBN = 1e9+7;
const ll RSN = -(1e9+7);
const double PI = 3.141592653589793;
//mt19937_64 rnd(chrono::steady_clock::now().time_since_epoch().count()); ll gen(){return rnd()%100;}

struct chars {
    ld count = 0;
    ld l;
    ld r;
    char this_char;
};

struct MinHeap {
    //non-increasing
    vector<chars> heap;

    void sift_up(ll index) {
        while (index > 0 && heap[(index-1)/2].count > heap[index].count) {
            ll parent = (index-1)/2;
            swap(heap[index],heap[parent]);
            index = parent;
        }
    }
    void sift_down(ll index) {
        while (2*index+1 < heap.size()) {
            ll left = 2 * index + 1;
            ll right = 2 * index + 2;
            ll j = left;
            if ((right < heap.size()) && (heap[right].count < heap[left].count)) {
                j = right;
            }
            if (heap[index].count <= heap[j].count) {
                break;
            }
            swap(heap[index], heap[j]);
            index = j;
        }
    }

    void insert(chars value) {
        heap.push_back(value);
        sift_up(heap.size()-1);

    }
    chars extract_min() {
        chars value = heap[0];
        heap[0] = heap[heap.size()-1];
        heap.pop_back();
        sift_down(0);
        sift_up(heap.size()-1);
        return value;
    }
};


signed main() {
    fast;
    vector<char> input;
    chars novels[26];
    for (ll i = 0; i < 26; i++) {
        novels[i].count = 0;
        novels[i].this_char = (char) ('a' + i);
    }
    char c;
    ll count = 0;
    while (cin >> c) {
        if (c == '1') {
            break;
        }
        count++;
        novels[c-'a'].count++;
        input.push_back(c);
    }
    vector<chars>smh;
    for (ll i = 0; i < 26; i++) {
        if (novels[i].count != 0) {
            novels[i].count = novels[i].count / float(count);
            smh.push_back(novels[i]);
        }
    }

    smh[0].l = 0;
    smh[0].r = smh[0].count;
    smh[smh.size()-1].l = 1-smh[smh.size()-1].count;
    smh[smh.size()-1].r = 1;
    for (ll i = 1; i < smh.size()-1; i++) {
        smh[i].l = smh[i-1].r;
        smh[i].r = smh[i].l+smh[i].count;
    }
    ld l = 0;
    ld r = 1;
    for (ll i = 0; i < input.size(); i++) {
        for (ll j = 0; j < smh.size(); j++) {
            if (smh[j].this_char == input[i]) {
                l = smh[j].l;
                r = smh[j].r;
                break;
            }
        }
        for (ll j = 0; j < smh.size(); j++) {
            if (j != 0)
                smh[j].l = smh[j-1].r;
            else
                smh[j].l = l;
            smh[j].r = (smh[j].count * (r - l)) + smh[j].l;
        }
      cout << '';
    }
    cout << l;
    return 0;
}
