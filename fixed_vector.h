/*
MIT License

Copyright (c) 2020 Waqar Ahmed

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/
#include <array>
#include <cassert>

using std::size_t;

class FixedVectorBase {
public:
    constexpr FixedVectorBase() : size_{} {}
    constexpr FixedVectorBase(size_t sz) : size_{sz} {}
    inline constexpr size_t size() const noexcept { return size_; }
    inline constexpr bool empty() const noexcept { return size_ == 0; }
protected:
    size_t size_;
};


template <typename T, size_t N>
class FixedVector : public FixedVectorBase {
public:
    using iterator                  = typename std::array<T,N>::iterator;
    using const_iterator            = typename std::array<T,N>::const_iterator;
    using reverse_iterator          = typename std::array<T,N>::reverse_iterator;
    using const_reverse_iterator    = typename std::array<T,N>::const_reverse_iterator;
    using size_type                 = typename std::array<T,N>::size_type;
    using value_type                = T;
    using reference                 = T&;
    using const_reference           = const T&;
    using pointer                   = T*;
    using const_pointer             = const T*;

    //constructors
    constexpr FixedVector() : FixedVectorBase{}, array{} {}

    template<typename... Args,
             typename = typename std::enable_if<
                 std::is_same<typename std::common_type_t<Args...>, T>::value
                 >::type
             >
    constexpr FixedVector(Args&& ...args) :
        FixedVectorBase{sizeof...(args)},
        array{std::forward<Args>(args)...}
    {}

    //alias this
    template<typename Iter>
    using IsIterator = typename std::enable_if<!std::is_same<typename std::iterator_traits<Iter>::value_type, void>::value>::type;

    template <typename Iter, typename = IsIterator<Iter> >
    FixedVector(Iter first, Iter last)
    {
        using Type = typename std::decay<decltype (*first)>::type;
        static_assert (std::is_same<Type, T>::value, "Invalid Type in iterators");

        auto len = std::distance(first, last);
        assert(len > 0 || len < N);
        size_ = len;
        std::copy(first, last, begin());
    }

    //iterators
    inline constexpr iterator begin() noexcept { return array.begin(); }
    inline constexpr const_iterator begin() const noexcept { return array.begin(); }
    inline constexpr const_iterator cbegin() const noexcept { return array.cbegin(); }
    inline constexpr reverse_iterator rbegin() noexcept { return array.rbegin(); }
    inline constexpr const_reverse_iterator rbegin() const noexcept { return array.rbegin(); }
    inline constexpr const_reverse_iterator crbegin() const noexcept { return array.crbegin(); }

    inline constexpr iterator end() noexcept { return array.end(); }
    inline constexpr const_iterator end() const noexcept { return array.end(); }
    inline constexpr const_iterator cend() noexcept { return array.cend(); }
    inline constexpr iterator rend() noexcept { return array.rend(); }
    inline constexpr const_iterator rend() const noexcept { return array.rend(); }
    inline constexpr const_iterator crend() noexcept { return array.crend(); }

    //functions
    inline constexpr const_reference at(size_type i) const { return array.at(i); }
    inline constexpr const_pointer const_data() const noexcept { return array.data(); }
    inline constexpr pointer data() noexcept { return array.data(); }

    void push_back(const T& item)
    {
        assert(size_ < N);
        array[size_++] = item;
    }

    iterator insert(iterator pos, const T& value)
    {
        *pos = value;
        return pos;
    }

    iterator insert(iterator pos, T&& value)
    {
        *pos = std::move(value);
        return pos;
    }

    template <typename Iter>
    iterator insert(iterator pos, Iter first, Iter last)
    {
        auto len = std::distance(first, last);
        if (len <= 0)
            return pos;

        for (; first != last; ++first, pos++) {
            *pos = *first;
        }
        return pos;
    }

    //operators
    inline constexpr reference operator[](size_type i) noexcept { return array[i]; }
    inline constexpr const_reference operator[](size_type i) const noexcept { return array[i]; }


private:
    std::array<T, N> array;
};

template<typename T, size_t N>
constexpr bool operator==(const FixedVector<T, N>& l, const FixedVector<T, N>& r)
{
    for (int i = 0; i < N; ++i) {
        if (l[i] != r[i])
            return false;
    }
    return true;
}


