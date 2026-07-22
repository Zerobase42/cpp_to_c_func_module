
namespace std {
inline unsigned char next_permutation_int(int* arr, int n) {
    if (n <= 1) return 0;
    int i = n - 1, i1, i2, t;
    while (1) {
        i1 = i;
        if (arr[--i] < arr[i1]) {
            i2 = n;
            while (arr[i] >= arr[--i2]);
            t = arr[i];
            arr[i] = arr[i2];
            arr[i2] = t;
            for (int l = i1, r = n - 1; l < r; ++l, --r) {
                t = arr[l];
                arr[l] = arr[r];
                arr[r] = t;
            }  // reverse
            return 1;
        }
        if (i == 0) {
            for (int l = 0, r = n - 1; l < r; ++l, --r) {
                int t = arr[l];
                arr[l] = arr[r];
                arr[r] = t;
            }  // reverse
            return 0;
        }
    }
}
#ifdef __cplusplus
template <typename T>
bool next_permutation(T first, T last) {
    if (first == last) return false;
    T i = last;
    if (first == --i) return false;
    while (true) {
        T i1, i2;
        i1 = i if (*--i < *i1) {
            i2 = last;
            while (!(*i < *--i2));
            std::iter_swap(i, i2);
            std::reverse(i1, last);
            return true;
        }
        if (i == first) {
            std::reverse(first, last);
            return false;
        }
    }
}
#endif
}  // namespace std