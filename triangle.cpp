#include <assert.h>
#include <cmath>
#include <iostream>
#include <random>

// no_triangle=0, equilateral=1, isosceles=2, scalene=3
enum triangle_type { no_triangle, equilateral, isosceles, scalene };

template <typename T>
triangle_type test_triangle(const T &i, const T &j, const T &k) {

   // negative length test
   // note: 0 values are possible (degenerate triangles)
   if (i < 0 || j < 0 || k < 0)
      return no_triangle; // not a triangle

   // if hypotenuse is larger than the sum of the catheti than it is not a
   // triangle (subtraction prevents overflow)
   if (i < std::max(j, k) - std::min(j, k) ||
       j < std::max(i, k) - std::min(i, k) ||
       k < std::max(i, j) - std::min(i, j))
      return no_triangle;

   if (i == j && j == k)
      return equilateral;
   else if (i == j || i == k || j == k)
      return isosceles;
   else
      return scalene;
}

// simple routine to interpret the output
std::string output(const int value) {

   switch (value) {
   case no_triangle:
      return "NOT A TRIANGLE";
      break;
   case equilateral:
      return "EQUILATERAL";
      break;
   case isosceles:
      return "ISOSCELES";
      break;
   case scalene:
      return "SCALENE";
      break;
   }
   return "UNDEFINED";
}

void random_test() {

   const int range_from = 0;
   const int range_to = 5000000;

   std::random_device rand_dev;
   std::mt19937 generator(rand_dev());
   std::uniform_int_distribution<int> distr(range_from, range_to);

   // not a triangle
   for (int i = 0; i < 100; ++i) {
      std::vector<int> v(3);
      v[0] = distr(generator);
      v[1] = distr(generator);
      v[2] = v[0] + v[1] + 1; // triangular inequality fails
      std::shuffle(std::begin(v), std::end(v), generator);
      assert(test_triangle(v[0], v[1], v[2]) == no_triangle);
   }

   // equilateral
   for (int i = 0; i < 100; ++i) {
      std::vector<int> v(3);
      v[0] = distr(generator);
      v[1] = v[0];
      v[2] = v[1];
      std::shuffle(std::begin(v), std::end(v), generator);
      assert(test_triangle(v[0], v[1], v[2]) == equilateral);
   }

   // isosceles
   for (int i = 0; i < 100; ++i) {
      std::vector<int> v(3);
      v[0] = distr(generator);
      v[1] = v[0];
      v[2] = v[0] + 1;
      std::shuffle(std::begin(v), std::end(v), generator);
      assert(test_triangle(v[0], v[1], v[2]) == isosceles);
   }

   // scalene
   for (int i = 0; i < 100; ++i) {
      std::vector<int> v(3);
      v[0] = distr(generator);
      v[1] = v[0] + 1;
      v[2] = v[0] + 2;
      std::shuffle(std::begin(v), std::end(v), generator);
      assert(test_triangle(v[0], v[1], v[2]) == scalene);
   }
}

void simple_test() {

   // triangles
   assert(test_triangle(0, 0, 0) == equilateral);
   assert(test_triangle(0, 1, 1) == isosceles);
   assert(test_triangle(5, 10, 10) == isosceles);

   // no triangles
   assert(test_triangle(0, 1, 2) == no_triangle);
   assert(test_triangle(0, 0, -1) == no_triangle);
   assert(test_triangle(10, 1, 20) == no_triangle);

   // testing overflow
   assert(test_triangle(std::numeric_limits<int>::max(),
                        std::numeric_limits<int>::max(),
                        std::numeric_limits<int>::max()) == equilateral);
   assert(test_triangle(std::numeric_limits<int>::max(),
                        std::numeric_limits<int>::max(), 1) == isosceles);
   assert(test_triangle(std::numeric_limits<int>::max(),
                        std::numeric_limits<int>::max() - 1,
                        std::numeric_limits<int>::max() - 2) == scalene);
   assert(test_triangle(std::numeric_limits<int>::max(), 1, 2) == no_triangle);

   // testing types
   assert(test_triangle((int)2, (int)3, (int)4) == scalene);
   assert(test_triangle((unsigned int)2, (unsigned int)3, (unsigned int)4) ==
          scalene);
   assert(test_triangle((float)1.5, (float)2.3, (float)3.1) == scalene);
   assert(test_triangle((double)1.5, (double)2.3, (double)3.1) == scalene);
}

int main() {

   simple_test();
   random_test();

   return 0;
}
