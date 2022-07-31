# std-map-implementation
This is my implementation of std::map in the standard C++ library. It mimics much of its behavior like O(1) begin() and end(), and iterators remaining valid after insertions and deletions. The map hold key-value pairs and orders them using a comparison function. Keys are unique, but values can be non-unique. The underlying data structure is a self-balancing binary tree using red-black techniques to ensure logarithmic insert, search, and deletion. 

Definition:
```
template<class Key, class T, class Compare = std::less<Key>>
class Map;
```

## Member Types
| Member type              | Definition                                    |
| ------------------------ | --------------------------------------------- |
| `key_type`               | `Key`                                         |
| `mapped_type`            | `T`                                           |
| `value_type`             | `std::pair<const Key, T>`                     |
| `key_compare`            | `Compare`                                     |
| `reference`              | `value_type&`                                 |
| `const_reference`        | `const value_type&`                           |
| `pointer`                | `value_type*`                                 |
| `const_pointer`          | `const value_type*`                           |
| `iterator`               | Bidirectional iterator to `value_type`        |
| `const_iterator`         | Bidirectional iterator to `const value_type`  |
| `reverse_iterator`       | Bidirectional iterator in reverse order       |
| `const_reverse_iterator` | Bidirectional const_iterator in reverse order |

## Member Functions
| Definition                                                              | Description                              |
| ----------------------------------------------------------------------- | ---------------------------------------- |
| `Map()`                                                                 | Constructs empty map                     |
| `template<class InputIter>` <br> `Map(InputIter first, InputIter last)` | Constructs a map from range of iterators |
| `Map(std::initializer_list<value_type> il)`                             | Constructs a map from initializer list   |
| `Map(const Map& other)`                                                 | Copy constructor                         |
| `Map(Map&& other)`                                                      | Move constructor                         |
| `~Map()`                                                                | Destructor                               |
| `Map& operator=(const Map& other)`                                      | Copy assignment operator                 |
| `Map& operator=(Map&& other)`                                           | Move assignment operator                 |
| `Map& operator=(std::initializer_list<value_type> il)`                  | Initializer list assignment operator     |

### Iterators
| Definition                                        | Description                                      |
| ------------------------------------------------- | ------------------------------------------------ |
| `iterator begin() noexcept`                       | `iterator` to first element (min)                |
| `const_iterator begin() const noexcept`           | `const_iterator` to first element                |
| `iterator end() noexcept`                         | `iterator` to after last element                 |
| `const_iterator end() const noexcept`             | `const_iterator` to after last element           |
| `reverse_iterator rbegin() noexcept`              | `reverse_iterator` to last element (max)         |
| `const_reverse_iterator rbegin() const noexcept`  | `const_reverse_iterator` to last element         |
| `reverse_iterator rend() noexcept`                | `reverse_iterator ` to before first element      |
| `const_reverse_iterator rend() const noexcept`    | `const_reverse_iterator` to before first element |
| `const_iterator cbegin() const noexcept`          | `const_iterator` to first element                |
| `const_iterator cend() const noexcept`            | `const_iterator` to after last element           |
| `const_reverse_iterator crbegin() const noexcept` | `const_reverse_iterator` to last element         |
| `const_reverse_iterator crend() const noexcept`   | `const_reverse_iterator` to before first element |

### Capacity
| Definition                     | Description                     |
| ------------------------------ | ------------------------------- |
| `bool empty() const noexcept`  | Returns true if empty           |
| `size_t size() const noexcept` | Returns number of values in map |

### Element Access
| Definition                                        | Description                                                                               |
| ------------------------------------------------- | ----------------------------------------------------------------------------------------- |
| `mapped_type& operator[] (const key_type& k)`     | Access value with key `k`. If `k` does not exist, insert it with default value.           |
| `mapped_type& operator[] (key_type&& k)`          | Access value with temporary key `k`. If `k` does not exist, insert it with default value. |
| `mapped_type& at (const key_type& k)`             | Access value with key `k`. If `k` does not exist, throws `std::out_of_range()`.           |
| `const mapped_type& at (const key_type& k) const` | Access const value with key `k`. If `k` does not exist, throws `std::out_of_range()`.     |

### Modifiers
| Definition                                                  | Description                                                                                                                                               |
| ----------------------------------------------------------- | -------------------------------------------------------------------------------------------------------------------------------------------------------- |
| `std::pair<iterator,bool> insert (const value_type& val)`   | Insert key-value pair `val`. Returns an iterator-bool pair, with an iterator to the element and a bool representing if a new key was inserted            |
| `std::pair<iterator,bool> insert (value_type&& val)`        | Insert temporary key-value pair `val`. Returns an iterator-bool pair, with an iterator to the element and a bool representing if a new key was inserted |
| `iterator erase( iterator pos )`                            | Erase element given by `pos`. `pos` should be a valid and dereferencable iterator. Returns iterator to element after the one erased                      |
| `iterator erase(const_iterator pos)`                        | Erase element given by `pos`. `pos` should be a valid and dereferencable iterator. Returns iterator to element after the one erased                      |
| `size_t erase(const key_type& k)`                           | Erase element with key `k`. If element exists return 1, otherwise return 0.                                                                               |
| `iterator erase(const_iterator first, const_iterator last)` | Erase range of elements including `first` and excluding `last`. Return iterator to element after last one erased (`last`)                               |
| `void swap(Map& x)`                                         | Swaps the contents of the current map and `x`                                                                                                             |
| `void clear()`                                              | Empties the map                                                                                                                                           |

### Observers
| Definition                     | Description                                            |
| ------------------------------ | ------------------------------------------------------ |
| `key_compare key_comp() const` | Returns the comparator used by the map to order values |

### Lookup
| Definition                                                                       | Description                                                                                                                      |
| -------------------------------------------------------------------------------- | -------------------------------------------------------------------------------------------------------------------------------- |
| `iterator find(const key_type& k)`                                               | Return iterator to pair with key 'k' in map                                                                                      |
| `const_iterator find(const key_type& k) const`                                   | Return const iterator to pair with key 'k' in map                                                                                |
| `size_t count(const key_type& k) const`                                          | Return count of elements in map with key 'k'. Because keys are unique, will be either 0 or 1.                                 |
| `iterator lower_bound(const key_type& k)`                                        | Return iterator to element after lower bound key 'k'                                                                              |
| `const_iterator lower_bound(const key_type& k) const`                            | Return const iterator to element after lower bound key 'k'                                                                        |
| `iterator upper_bound(const key_type& k)`                                        | Return iterator to element before upper bound key 'k'                                                                            |
| `const_iterator upper_bound(const key_type& k) const`                            | Return iterator to element before upper bound key 'k'                                                                            |
| `std::pair<const_iterator, const_iterator> equal_range(const key_type& k) const` | Return a range of iterators containing elements with the key 'k'. Since keys are unique, the range is at most one element wide. |

