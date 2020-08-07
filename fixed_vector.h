#include <array>
#include <stdexcept>

//#include <bits/stl_vector.h>
//#include <bits/vector.tcc>

using std::size_t;

template <typename T, size_t N>
class FixedVector{
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
    constexpr FixedVector() : size_{}, array{} {}

    template<typename... Args>
    constexpr FixedVector(Args&& ...args) :
        array{std::forward<Args>(args)...},
        size_{sizeof...(args)}
    {}

    template <typename Iter>
    FixedVector(Iter first, Iter last)
    {
        auto len = std::distance(first, last);
        if (len <= 0 || len > N) {
            throw std::invalid_argument{"Bad iterators in ctor(first, last)"};
        }
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
    inline constexpr size_type size() const noexcept { return size_; }
    inline constexpr bool empty() const noexcept { return size_ == 0; }

    void push_back(const T& item)
    {
        if (size_ >= N - 1)
            throw std::out_of_range{"Push back out of range"};
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

    friend constexpr bool operator==(const FixedVector& l, const FixedVector& r)
    {
        for (int i = 0; i < N; ++i) {
            if (l[i] != r[i])
                return false;
        }
        return true;
    }

private:
    size_type size_;
    std::array<T, N> array;
};


