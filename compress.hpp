#ifndef COMPRESS_HPP
#define COMPRESS_HPP

#include <vector>
using namespace std;

namespace itertools
{
    template <typename T>
    class compress
    {
        T &it; //We don't want to duplicate the container.
        vector<bool> &bool_filter;
        decltype((it.begin())) _begin; //decltype uses to deduce runtime type of an object
        decltype((it.begin())) _end;

    public:
        //l-value ctor
        compress(T &iter, vector<bool> &filter) : it(iter), bool_filter(filter), _begin(it.begin()), _end(iter.end()) {}
        //We need a reference to reference ctor in order to support passing reference of rvalue
        compress(T &&iter, vector<bool> &filter) : it(iter), bool_filter(filter), _begin(it.begin()), _end(iter.end()) {}

        class iterator
        {
            compress &_compress;
            decltype((it.begin())) container_iterator;
            int index;

            void filtering()
            {
                //Check for first element
                for (; container_iterator != _compress._end && !_compress.bool_filter[index]; ++container_iterator, ++index)
                    ; //skip who ever not matching the filter
            }

        public:
            iterator(compress &compress) : container_iterator(compress.it.begin()), _compress(compress), index(0)
            {
                filtering();
            }

            auto operator*() const
            {
                return *container_iterator;
            }

            bool operator==(const iterator &other) const
            {
                return container_iterator == _compress.it.end();
            }

            bool operator!=(const iterator &other) const
            {
                return !(*this == other);
            }

            iterator &operator++()
            {
                ++container_iterator;
                ++index;
                filtering();
                return *this;
            } //prefix ++
        };

        auto begin() { return iterator(*this); }
        auto end() { return iterator(*this); }
    };
} // namespace itertools

#endif