# Triangle challenge

The challenge is as follows: given the triangle's three sides as input return whether the triangle is equilateral, isosceles or scalene (or not a triangle).

Given the triangle's three sides `a,b,c`, a triangle must satisfy the triangular inequality for each side `a,b,c`, namely:
```
a + b > c && a + c > b && b + c > a
```
If one of the sides of the triangle is `0` then we have a (valid) *degenerate triangle*.

Each source code has assert-style testing functions where both trivial inputs and random inputs are tested. Integer (type) overflow is tested as well. In fact, the test for triangle inequality (e.g. `a+b`) may generate an overflow. To avoid this, each sum is converted into a difference on positive integers (this implies no underflow). In case of unsigned types (wrt C++), overflow is handled with a *wrap around* policy (i.e. `(MAX_VALUE + 1) == 0` evaluates to true). To avoid this, an always positive difference was ensured.

### C++

For compiling (`-Wall -Wextra` enable extra warnings):
```
g++ -Wall -Wextra -o triangle triangle.cpp
```
Run as:
```
./triangle
```
The template function `triangle_type test_triangle(const T &i, const T &j, const T &k)` takes three generic-typed side lengths as input and tests whether the triple `(i,j,k)` forms a triangle as explained above. The function returns an `enum` type that encodes the type of triangle.

Using generics allows to test the code on several types (e.g. `unsigned`, `doubles`, etc.).

### Java

For compiling:
```
javac Triangle.java
```
Run:
```
java -ea Triangle
```
where the `-ea` flag enables the `assert` option.

The function `public static triangleType test_triangle(int i, int j, int k)` takes three integer-typed side lengths as input and tests whether the triple `(i,j,k)` forms a triangle as explained above. The function returns an `enum` type that encodes the type of triangle.

As opposed to C++, arithmetics with generic types are non-trivial in Java. As a consequence, the Java implementation is restricted to signed integers.
