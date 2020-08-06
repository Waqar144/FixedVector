#include <array>
#include <stdexcept>

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
    constexpr FixedVector() = default;

    //iterators
    inline constexpr iterator begin() noexcept { return array.begin(); }
    inline constexpr const_iterator begin() const noexcept { return array.begin(); }
    inline constexpr const_iterator cbegin() const noexcept { return array.cbegin(); }
    inline constexpr reverse_iterator rbegin() noexcept { return array.rbegin(); }
    inline constexpr const_reverse_iterator rbegin() const noexcept { return array.rbegin(); }
    inline constexpr const_reverse_iterator crbegin() const noexcept { return array.crbegin(); }

    //functions
    inline constexpr const_reference at(size_type i) const { return array.at(i); }
    inline constexpr const_pointer const_data() const noexcept { return array.data(); }
    inline constexpr pointer data() noexcept { return array.data(); }

    void push_back(const T& item)
    {
        if (size >= N - 1)
            throw std::out_of_range{"Push back out of range"};
        array[size++] = item;
    }

    //operators

private:
    size_type size;
    std::array<T, N> array;
};

