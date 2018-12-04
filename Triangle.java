import java.util.Random;
import java.util.ArrayList;
import java.util.Collections;

public class Triangle{

   enum triangleType { no_triangle, equilateral, isosceles, scalene };

   public static triangleType test_triangle(int i, int j, int k){

      // negative length test
      // note: 0 values are possible (degenerate triangles)
      if (i < 0 || j < 0 || k < 0)
         return triangleType.no_triangle; // not a triangle

      // if hypotenuse is larger than the sum of the catheti than it is not a
      // triangle (subtraction prevents overflow)
      if(i < Math.abs(j - k) || j < Math.abs(i - k) || k < Math.abs(i - j))
            return triangleType.no_triangle;

      if (i == j && j == k)
         return triangleType.equilateral;
      else if (i == j || i == k || j == k)
         return triangleType.isosceles;
      else
         return triangleType.scalene;
   }

   public static void main(String[] args){

      simple_test();
      random_test();

   }

   public static void simple_test() {

      // triangles
      assert(test_triangle(0, 0, 0) == triangleType.equilateral);
      assert(test_triangle(0, 1, 1) == triangleType.isosceles);
      assert(test_triangle(5, 10, 10) == triangleType.isosceles);

      // no triangles
      assert(test_triangle(0, 1, 2) == triangleType.no_triangle);
      assert(test_triangle(0, 0, -1) == triangleType.no_triangle);
      assert(test_triangle(10, 1, 20) == triangleType.no_triangle);

      // testing overflow
      assert(test_triangle(Integer.MAX_VALUE,
                           Integer.MAX_VALUE,
                           Integer.MAX_VALUE) == triangleType.equilateral);
      assert(test_triangle(Integer.MAX_VALUE,
                           Integer.MAX_VALUE, 1) == triangleType.isosceles);
      assert(test_triangle(Integer.MAX_VALUE,
                           Integer.MAX_VALUE - 1,
                           Integer.MAX_VALUE - 2) == triangleType.scalene);
      assert(test_triangle(Integer.MAX_VALUE, 1, 2) == triangleType.no_triangle);

   }

   public static void random_test() {

      final int range_from = 0;
      final int range_to = 5000000; //less than MAX_VALUE to prevent overflow

      Random rand = new Random();

      // not a triangle
      for (int i = 0; i < 100; ++i) {
         ArrayList<Integer> v = new ArrayList<Integer>();
         int x = rand.nextInt(range_to) + range_from;
         int y = rand.nextInt(range_to) + range_from;
         v.add(x);
         v.add(y);
         v.add(x + y + 1); // triangular inequality fails
         Collections.shuffle(v);
         assert(test_triangle(v.get(0), v.get(1), v.get(2)) == triangleType.no_triangle);
      }

      // equilateral
      for (int i = 0; i < 100; ++i) {
         ArrayList<Integer> v = new ArrayList<Integer>();
         int x = rand.nextInt(range_to) + range_from;
         v.add(x);
         v.add(x);
         v.add(x);
         assert(test_triangle(v.get(0), v.get(1), v.get(2)) == triangleType.equilateral);
      }

      // isosceles
      for (int i = 0; i < 100; ++i) {
         ArrayList<Integer> v = new ArrayList<Integer>();
         int x = rand.nextInt(range_to) + range_from;
         v.add(x);
         v.add(x);
         v.add(x + 1);
         Collections.shuffle(v);
         assert(test_triangle(v.get(0), v.get(1), v.get(2)) == triangleType.isosceles);
      }

      //scalene
      for (int i = 0; i < 100; ++i) {
         ArrayList<Integer> v = new ArrayList<Integer>();
         int x = rand.nextInt(range_to) + range_from + 1;
         v.add(x);
         v.add(x - 1);
         v.add(x + 1);
         Collections.shuffle(v);
         assert(test_triangle(v.get(0), v.get(1), v.get(2)) == triangleType.scalene);
      }
   }

}
