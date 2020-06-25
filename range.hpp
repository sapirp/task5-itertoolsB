
#ifndef RANGE_HPP
#define RANGE_HPP

//#include <sys/types.h> //int

/**
 * for (iterator it = iterable.begin(); it != iterable.end(); ++it) {
    int x = *it;
    ...
}
 */
namespace itertools
{
    class range
    {
        int _begin;
        int _end;

    public:
        range(int begin, int end) : _begin(begin), _end(end){};

        typedef int value_type;

        class iterator
        {
            int val;

        public:
            iterator(int value) : val(value) {}

            int operator*() const
            {
                return val;
            }
            bool operator==(const iterator &other) const
            {
                return val == other.val;
            }
            bool operator!=(const iterator &other) const
            {
                return !(*this == other);
            }
            iterator &operator++()
            {
                ++val;
                return *this;
            } //prefix ++
        };

        iterator begin() { return iterator(_begin); }
        iterator end() { return iterator(_end); }
    };
} // namespace itertools

#endif