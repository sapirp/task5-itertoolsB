#ifndef FILTERFALSE_HPP
#define FILTERFALSE_HPP

namespace itertools
{
    template <typename Functor, typename T>
    class filterfalse
    {
        Functor func;
        T &it;

    public:
        filterfalse(Functor func, T &iter) : func(func), it(iter) {}

        class iterator
        {
            Functor filter;
            T &_it;
            decltype((it.begin())) container_iterator;
            void filtering()
            {
                for (; container_iterator != _it.end() && filter(*container_iterator); ++container_iterator)
                    ; //skip who ever not matching the filter
            }

        public:
            iterator(Functor operation, T &it) : filter(operation), _it(it), container_iterator(_it.begin())
            {
                filtering();
            }

            auto operator*() const
            {
                return *container_iterator;
            }

            bool operator==(const iterator &other) const
            {
                return container_iterator == _it.end();
            }

            bool operator!=(const iterator &other) const
            {
                return !(*this == other);
            }

            iterator &operator++()
            {
                ++container_iterator;
                filtering();
                return *this;
            } //prefix ++
        };

        iterator begin()
        {
            return iterator(func, it);
        }

        iterator end()
        {
            return iterator(func, it);
        }
    };
} // namespace itertools

#endif