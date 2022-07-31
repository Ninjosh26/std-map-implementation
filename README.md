# std-map-implementation
This is my implementation of std::map in the standard C++ library. It mimics much of its behavior like O(1) begin() and end(), and iterators remaining valid after insertions and deletions. The map hold key-value pairs and orders them using a comparison function. The underlying data structure is a self-balancing binary tree using red-black techniques to ensure logarithmic insert, search, and deletion. 

Definition:
```
template<class Key, class T, class Compare = std::less<Key>>
class Map;
```

## Member Types
| Member type              | Definition                                    |
| ------------------------ | --------------------------------------------- |
| `key_type`               | `Key`                                         |
| `mapped_type             | `T`                                           |
| `value_type`             | `std::pair<const Key, T>`                     |
| `key_compare`            | `Compare                                      |
| `reference`              | `value_type&`                                 |
| `const_reference`        | `const value_type&`                           |
| `pointer`                | `value_type*`                                 |
| `const_pointer`          | `const value_type*`                           |
| `iterator`               | Bidirectional iterator to `value_type`        |
| `const_iterator`         | Bidirectional iterator to `const value_type`  |
| `reverse_iterator`       | Bidirectional iterator in reverse order       |
| `const_reverse_iterator` | Bidirectional const_iterator in reverse order |

## Member Functions
`Map()`: Constructs empty map
```
template<class IntputIter>
Map(InputIter first, InputIter last) : Constructs a map from  range of map iterators
```
