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
#include <iomanip>

#define DIVIDER_32 1000000000000    // 12 zeros
#define DIVIDER_35 1000000000000000    // 15 zeros

typedef long long unsigned int llunint;

llunint perf_counter_to_k_counter(llunint perf_counter) {
  // sqroot = pow(2,perf_counter+1)-1;
  // k_counter = (sqroot+1)/2-1;
  // or
  // k_counter = pow(2, perf_counter+1)/2-1;
  // or
  // k_counter = pow(2, perf_counter)-1;    // using this
  return pow(2, perf_counter)-1;
}

llunint k_counter_to_k(llunint k_counter) {
  // std::cout << "works with: " << k_counter << std::endl;
  // sqroot = (k_counter+1)*2-1;
  // k = (pow(sqroot,2)-1)/4;
  // return (pow((k_counter+1)*2-1,2)-1)/4;
  // or
  return k_counter*(k_counter+1);
}

/* Overload in case k overflows the long long unsigned int type (llunint or uint64_t).
 * 1st overflow occurs @ perf_counter > 32 (DIVIDER_32) and the next @ perf_counter > 35.
 * In the end, an unsigned __int128 is printed.
 */
llunint k_counter_to_k(llunint k_counter, const llunint devider){

  llunint leading  = k_counter/devider;
  llunint trailing = k_counter%devider;

  llunint f_k = printf("%llu", leading*(k_counter+1) + (trailing*(k_counter+1))/devider);    // leading + leading of trailing

  f_k += printf("%llu", (trailing*(k_counter+1))%devider);                  // trailing of trailing

  return f_k;
}

int main() {

  llunint q, a, b, k_counter_check = 0;
  std::cin >> q;

  while(q--) {
    std::cin >> a >> b;

    llunint perf_counter = 0;

  while(++perf_counter) {

      /* Print-test
      std::cout << "perf_counter increase point: "
      << "perf_counter= "<<perf_counter << ", k_counter= " << perf_counter_to_k_counter(perf_counter) << std::endl;

      if(perf_counter<31) {
        std::cout << "P(";
        std::cout << k_counter_to_k(perf_counter_to_k_counter(perf_counter)) << ")= "
        << std::fixed << std::setprecision(15) << (double)perf_counter/perf_counter_to_k_counter(perf_counter)
        << std::setprecision(0) << std::endl;
      }
      else if(31 <= perf_counter && perf_counter < 34) {
        std::cout << "P(";
        std::cout << k_counter_to_k(perf_counter_to_k_counter(perf_counter), DIVIDER_32) << ")= "
        << std::fixed << std::setprecision(20) << (double)perf_counter/perf_counter_to_k_counter(perf_counter)
        << std::setprecision(0) << std::endl;
      }
      else {
        std::cout << "P(";
        std::cout << k_counter_to_k(perf_counter_to_k_counter(perf_counter), DIVIDER_35) << ")= "
        << std::fixed << std::setprecision(20) << (double)perf_counter/perf_counter_to_k_counter(perf_counter)
        << std::setprecision(0) << std::endl;
      }
      */

      if( (double)(perf_counter-1)/(perf_counter_to_k_counter(perf_counter)-1) < (double)a/b ) {
       //  k_counter = ceil((double)(perf_counter-1)/((double)a/b));
       //  std::cout << std::setprecision(20)<<"1: " << ceil((double)(perf_counter-1)/((double)a/b)) << std::endl;
       //  std::cout << "2: "<<(double)(perf_counter-1)/((double)a/b) << std::endl;

        /* ceil((double)(perf_counter-1)/((double)a/b)) is the k_counter that corresponds to P(q) = (double)a/b. The answer
         * is the k that corresponds to this k_counter (if) or the next (else). In case that the next k refers to a perfect
         * partition, then the first smaller than P(q) proportion corresponds to the second next k (else if).
         */
        if( (perf_counter-1)/ceil((double)(perf_counter-1)/((double)a/b)) < ((double)a/b) ) {
          if(perf_counter < 31) {
            std::cout << k_counter_to_k(ceil((double)(perf_counter-1)/((double)a/b))) << std::endl;
          }
          else if(31 <= perf_counter && perf_counter < 34) {
            std::cout << k_counter_to_k(ceil((double)(perf_counter-1)/((double)a/b)), DIVIDER_32) << std::endl;
          }
          else{
            std::cout << k_counter_to_k(ceil((double)(perf_counter-1)/((double)a/b)), DIVIDER_35) << std::endl;
          }
        }

        else if( log2 (ceil((double)(perf_counter-1)/((double)a/b))+1) == (llunint) log2 (ceil((double)(perf_counter-1)/((double)a/b))+1) ) {
          if(perf_counter < 31) {
            std::cout << k_counter_to_k(ceil((double)(perf_counter-1)/((double)a/b))+2) << std::endl;
          }
          else if(31 <= perf_counter && perf_counter < 34) {
            std::cout << k_counter_to_k(ceil((double)(perf_counter-1)/((double)a/b))+2, DIVIDER_32) << std::endl;
          }
          else {
            std::cout << k_counter_to_k(ceil((double)(perf_counter-1)/((double)a/b))+2, DIVIDER_35) << std::endl;
          }
        }

        else {
          if(perf_counter < 31) {
            std::cout << k_counter_to_k(ceil((double)(perf_counter-1)/((double)a/b))+1) << std::endl;
          }
          else if(31 <= perf_counter && perf_counter < 34) {
            std::cout << k_counter_to_k(ceil((double)(perf_counter-1)/((double)a/b))+1, DIVIDER_32) << std::endl;
          }
          else{
            std::cout << k_counter_to_k(ceil((double)(perf_counter-1)/((double)a/b))+1, DIVIDER_35) << std::endl;
          }
        }
        break;
      }
    }
  }
}
