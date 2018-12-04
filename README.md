# Triangle challenge

The challenge is as follows: Given the triangle's three sides as input return whether the triangle is equilateral, isosceles or scalene (or not a triangle).

Given the triangle's three sides `a,b,c`, a triangle must satisfy the triangular inequality for each side of `a,b,c`:
```
a + b > c && a + c > b && b + c > a
```
If one of the sides of the triangle is `0` then we have a (valid) *degenerate triangle*.

Each source code has assert-style testing functions where both some trivial input and random inputs are tested. Integer (type) overflow is tested as well.

### C++

For compiling C++
```
g++ -Wall -Wextra -o triangle triangle.cpp
```
Run as
```
./triangle
```
The function `triangle_type test_triangle(const T &i, const T &j, const T &k)` takes three generic-typed side lengths as input and tests whether the triple `(i,j,k)` forms a triangle as explained above. The function returns an `enum` type that encodes the type of triangle.

Using generics allows to test the source code on several types (e.g. `unsigned` and `doubles`).

### Java

For compiling Java
```
javac Triangle.java
```
Run as
```
java -ea Triangle
```
where the `-ea` flag enables the `assert` option.

The function `public static triangleType test_triangle(int i, int j, int k)` takes three integer-typed side lengths as input and tests whether the triple `(i,j,k)` forms a triangle as explained above. The function returns an `enum` type that encodes the type of triangle.

As opposed to C++, arithmetics with generic types is non-trivial in Java. As a consequence, the Java implementation is restricted to signed integers.
