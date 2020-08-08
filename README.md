# FixedVector

A fixed size vector, which is actually a wrapper over `std::array` but provides an interface similar to `std::vector`.

## Build

```sh
mkdir build && cd build
cmake .. && make
./tests
```

## Usage

```
#include "fixed_vector.h"

int main()
{
	FixedVector<int, 5> fv {1, 2, 3, 4, 5};
	static_assert(fv.size() == 5);
}
```

## LICENSE

MIT