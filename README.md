# ft_container_push

## Implement 3 containers of the C++ standard template library : vector, stack and map (C++98 standard).
## Use of this project isn't just to master the containers but to handle templates and getting used to generic programming.

We use cppreference.com and cplusplus.com as main reference. 
Some usefull references and tips:

## std::allocator in detail
https://medium.com/@vgasparyan1995/what-is-an-allocator-c8df15a93ed
https://stackoverflow.com/questions/31358804/whats-the-advantage-of-using-stdallocator-instead-of-new-in-c

In short :

std::vector<X> v;
v.reserve(4);        // (1)
v.push_back( X{} );  // (2)
v.push_back( X{} );  // (3)
v.clear();           // (4)

Here line (1) must allocate enough memory for four objects, but not construct them yet. Then lines (2) and (3) must construct objects into the allocated memory. Then line (4) must destroy those objects, but not deallocate the memory. Finally, in the vector's destructor, all the memory can be deallocated.

So the vector cannot just use new X() or delete &m_data[1] to create and destroy the objects, it must perform allocation/deallocation separately from construction/destruction. A container's allocator template argument defines the policy that should be used for (de)allocating memory and constructing/destructing objects, allowing the container's use of memory to be customised. The default policy is the std::allocator type.

So you use an allocator when an allocator is required (such as when using a container) and you use std::allocator when you don't want to provide a custom allocator and just want the standard one.
_________________________________________________________________________________________________________________________________________________________________________________

## Typedefs and member types

What is the actual meaning of member types(value_type, allocator_type, etc.) ?

They are typedefs to the corresponding types that the templated container is using.

For example, value_type corresponds to the type of the element that the vector can hold. So std::vector<int>::value_type would be int, and std::vector<float>::value_type would be float.

Having the commonly-used types available as a type on the container is useful when the container's type itself is unknown.

___________________________________________________________________________________________________

## Operator overloads

Quick reminder :
Mutating operators like += or -= return by reference, because they return the mutated object itself (by: return *this;)
Normal operators like + or - should return by value, because a new object needs to be constructed to hold the result.

NOTE
after logical analysis, pre increment/decrement might always be more light to calculate then post.
https://en.cppreference.com/w/cpp/language/operator_incdec
https://stackoverflow.com/questions/24901/is-there-a-performance-difference-between-i-and-i-in-c
____________________________________________________________________________________________________

## Random access iterators
https://www.geeksforgeeks.org/random-access-iterators-in-cpp/

_____________________________________________________________________________________________________


The size of a container is the number of elements it contains. ... The capacity of a container is the maximum number of elements it could contain without having to allocate new memory.

_____________________________________________________________________________________________________

## std::uninitialized
  
Why do we use std::uninitialized_copy with vector?
https://stackoverflow.com/questions/60910216/c-stdcopy-vs-stduninitialized-copy
(short answer = allocators) use it when memory was allocated but not initialized

_____________________________________________________________________________________________________

## iterator_traits
https://stackoverflow.com/questions/6742008/what-are-the-typical-use-cases-of-an-iterator-trait
https://www.lix.polytechnique.fr/~liberti/public/computing/prog/libstdc++/iterator_traits.html
  
_____________________________________________________________________________________________________
  
## ENABLE_IF  
  
ENABLE_IF is a a compile-time switch for templates

Used when template substitution causes an error.
The compiler should simply ignores this candidate and looks at the others.

"Substitution Failure Is Not An Error", or SFINAE.
Implementation + use in case of vector : https://eli.thegreenplace.net/2014/sfinae-and-enable_if/

_____________________________________________________________________________________________________

Explicit keyword for constructors
short answer, don't allow implicit conversion
https://stackoverflow.com/questions/121162/what-does-the-explicit-keyword-mean


_____________________________________________________________________________________________________

type_traits
compile-time conditions on what should be accepted as valid code and what not
https://www.sandordargo.com/blog/2021/04/07/what-are-type-traits


Metaprogramming
Calculation at compile time to save runtime memory
https://en.wikipedia.org/wiki/Template_metaprogramming
