// Project Euler #222: Sphere packing
#include <iostream>
#include <vector>
#include <algorithm>  // sort()
#include <cmath>
#include <iomanip>    // std::setprecision()
#include <iterator>


template <typename T>
std::ostream& operator<<(std::ostream& out, const std::vector<T>& v)
{
  out << '[';
  if (!v.empty()) {
    copy(v.begin(), v.end(), std::ostream_iterator<T>(out, ", "));
    out << "\b\b";
  }
  out << ']';
  return out;
}


std::vector<size_t> insertRadii(size_t n)
{
  size_t r;
  std::vector<size_t> radii_input_vector;

  // std::ifstream fileAlias("fileName.txt");   // #include <fstream>
  // fileAlias>>r;                              // (You can use radii_test.txt,
  //                                                which includes 20000 radii)
  // Fill the radii_input_vector
  while(n--){
    std::cin >> r;
    radii_input_vector.push_back(r * 1000);     // mm to μm
  }
  return radii_input_vector;
}


double getMinPipeLength(size_t R, std::vector<size_t> radii_input_vector)
{
  // Sort the radii_input_vector vector, descenting.
  sort(radii_input_vector.begin(),
       radii_input_vector.end(),
       std::greater<size_t>());

  #ifdef DEBUG
  std::cout << "Sphere radii descending: " << radii_input_vector << "\n";
  #endif

  // Devide the vector int two vectors, alternately
  std::vector<size_t> radii_1, radii_2;

  for (size_t i = 0; i < radii_input_vector.size(); ++i) {
    if (i % 2 == 0)
      radii_1.push_back(radii_input_vector[i]);
    else if (i % 2 == 1)
      radii_2.push_back(radii_input_vector[i]);
  }

  #ifdef DEBUG
  std::cout << "\nradii_1: " << radii_1 << "\n";
  std::cout << "radii_2: " << radii_2 << "\n";
  #endif

  // Building the final vector of the radii with the positioning sequence
  std::vector<size_t> radii_final = radii_1;

  for (size_t i = radii_2.size() - 1; i != -1; --i)
    radii_final.push_back(radii_2[i]);

  #ifdef DEBUG
  std::cout << "\n" << "Final radius order is: " << radii_final << "\n";
  #endif

  // Finally, calculate the length in query (l)

  // Initialize l with first + last radii
  double l = radii_final.front() + radii_final.back();
  #ifdef DEBUG
  std::cout << "\n" << "length is initialized with r_0 + r_(n-1): "
            << std::fixed << l << "\n\n";
  #endif

  // Add every y at length
  double c = 0.0, y, t;
  for (size_t i = 1; i < radii_final.size(); ++i) {
    // Kahan summation method
    y = 2 * sqrt(R * (radii_final[i-1] + radii_final[i] - R)) - c;
    // std::cout << "New square root" << "\n";
    // std::cout << std::fixed << std::setprecision(15)
    //           << "y is: " << y << "\n";
    t = l + y;
    // std::cout << "t is: " << t << "\n";
    c = (t - l);
    c -= y;
    // std::cout << "c is: " << c << "\n";
    l = t;
    //std::cout << "l is: " << l << "\n\n";

    // Without Kahan algorithm = naive summation
    // l = l + 2 * sqrt((double)R * ((double)radii_final[i-1]
    //     + (double)radii_final[i]-(double)R));

    // std::cout << "Square root No " << i << " is: ";
    //           << (sqrt((double)R * ((double)radii_final[i - 1]
    //               + (double)radii_final[i] - (double)R)))
    //           << "\n";
  }
  return l;
}


int main()
{
  // R = tube radius
  // n = number of spheres
  // r = sphere radius input
  std::ios::sync_with_stdio(0);
  std::cin.tie(0);

  size_t R, n;
  std::cin >> R >> n;
  R *= 1000;  // mm to μm

  std::cout << std::fixed << std::setprecision(0)
            << getMinPipeLength(R, insertRadii(n)) << "\n";
}
