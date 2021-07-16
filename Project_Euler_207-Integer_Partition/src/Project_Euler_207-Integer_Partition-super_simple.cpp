/**
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include <iostream>
#include <cmath>

int main() {
  std::ios::sync_with_stdio(0);
  std::cin.tie(0);
  size_t q, a, b;
  std::cin >> q;
  size_t sqroot, k_counter, Perf_counter;

  while (q--) {
    std::cin >> a >> b;
    sqroot = 3; k_counter = 1; Perf_counter = 1;
    // P(k = 2) = (double)Perf_counter / k_counter = 1 / 1 = 1
    while(sqroot += 2){
      ++k_counter;

      // {if((t-(int)t) == 0)} If t is an int, the partition is perfect.
      if (log2(sqroot + 1) - (int)log2(sqroot + 1) == 0) {
        ++Perf_counter;
      }
      // std::cout << Perf_counter << " " << k_counter << std::endl;
      // std::cout << (double)Perf_counter / k_counter << std::endl;
      if ((double)Perf_counter / k_counter < (double)a / b) {
        std::cout << std::fixed << (sqroot * sqroot - 1) / 4 << std::endl;
        break;
      }
    }
  }
}
