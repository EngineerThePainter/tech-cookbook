#ifndef QUICK_EXCHANGE_HPP
#define QUICK_EXCHANGE_HPP

namespace details
{

    template <typename T>
    class Array
    {
    public:
        Array(Array<T> const &);
        Array<T> &operator=(Array<T> const &);
        void exchangeWith(Array<T> *b)
        {
            T *tmp = data;
            data = b->data;
            b->data = tmp;
        }
        T &operator[](std::size_t k) { return data[k]; }

    private:
        T *data;
    };

    template <typename T>
    void quickExchange(T *a, T *b)
    {
        T tmp(*a);
        *a = *b;
        *b = tmp;
    }

    template <typename T>
    void quickExchange(Array<T> a, Array<T> b)
    {
        a->exchangeWith(b);
    }

} // namespace details

#endif // QUICK_EXCHANGE_HPP