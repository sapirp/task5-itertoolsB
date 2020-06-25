#ifndef ACCUMULATE_HPP
#define ACCUMULATE_HPP

#include <functional>

namespace itertools
{

    template <typename T, typename lambada = std::plus<>>
    class accumulate
    {
        T &container;
        lambada fun;

    public:
                accumulate(T &it) : accumulate(it, fun) {}

        accumulate(T &it, lambada func) : container(it) {}

        class iterator
        {
            T &it;
            decltype((container.begin())) container_iterator;
            lambada _fun;
            typename T::value_type sum;

        public:
            iterator(T &iter, lambada func) : it(iter), container_iterator(it.begin()), _fun(func), sum(*container_iterator) {}

            auto operator*() const
            {
                return sum;
            }

            bool operator==(const iterator &other) const
            {
                return container_iterator == it.end();
            }

            bool operator!=(const iterator &other) const
            {
                return !(*this == other);
            }

            //++i
            iterator &operator++()
            {
                ++container_iterator;
                sum = _fun(sum, *container_iterator); //Perform the function.
                return *this;
            }
        };

        auto begin()
        {
            return iterator(container, fun);
        }
        auto end()
        {
            return iterator(container, fun);
        }
    };
} // namespace itertools

#endif