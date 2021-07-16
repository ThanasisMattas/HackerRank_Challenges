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
// #include <cstdint>


/* For the first in query P, we will iterate through square roots, to find the
 * 1st smaller P, while listing any sqroot found, in the process. For every new
 * query we will search through the list first, before iterating through square
 * roots. Map is not used, because map-keys are sorted and we will want to ite-
 * rate through the listed sequence.
 */

class Node
{
  size_t sqroot;
  size_t k_counter, perf_counter;
  Node* next;
  Node* last;

  public:
    // constructor
    Node (size_t sqroot, size_t k_counter, size_t perf_counter)
    {
      this->sqroot = sqroot;
      this->k_counter = k_counter;
      this->perf_counter = perf_counter;
      next = nullptr;
      last = nullptr;
    }

    // mutators
    void set_sqroot(size_t sqroot) {
      this->sqroot = sqroot;
    }
    void set_k_counter(size_t k_counter) {
      this->k_counter = k_counter;
    }
    void set_perf_counter(size_t perf_counter) {
      this->perf_counter = perf_counter;
    }
    void set_next(Node* next) {
      this->next = next;
    }
    void set_last(Node* last) {
      this->last = last;
    }

    // accessors
    size_t get_sqroot() {
      return sqroot;
    }
    size_t get_k_counter() {
      return k_counter;
    }
    size_t get_perf_counter() {
      return perf_counter;
    }
    Node* get_next() {
      return next;
    }
    Node* get_last() {
      return last;
    }
};

class LinkedList
{
    public:
    Node* insert(Node* head,
                 size_t sqroot,
                 size_t k_counter,
                 size_t perf_counter)
    {
      Node* temp = new Node(sqroot, k_counter, perf_counter);
      Node* current=head;

      if (current->get_last()) {
        current->get_last()->set_next(temp);
        current->set_last(temp);
      }
      else {
        current->set_next(temp);
        current->set_last(temp);
      }
      delete temp;
      return head;
    }

    // Search though the list to find the smaller P that was 1st listed. If
    // there isn't any smaller P yet listed, return last sqroot listed, in
    // order to be the startpoint to iterate again (and continue listing
    // sqroots).
    std::pair<size_t, std::pair<size_t, size_t> > search_for_k(
        Node* head,
        double query)
    {
      size_t sqroot, k_counter = 0, perf_counter = 0;
      Node* start = head;

      while(start) {
        if ((double)start->get_perf_counter() / start->get_k_counter()
            < query) {
          std::cout << std::fixed
                    << ((start->get_sqroot()) * (start->get_sqroot()) - 1) / 4
                    << "\n";
          sqroot = 0;
          break;
        }else {
          sqroot =  start->get_sqroot();
          k_counter = start->get_k_counter();
          perf_counter = start->get_perf_counter();
          start = start->get_next();
        }
      }
      // std::pair<size_t,size_t> counters_pair(k_counter, perf_counter);
      // std::pair<size_t, std::pair<size_t, size_t> >
      //     sqroot_counters_pair(sqroot, counters_pair);
      return std::pair<size_t, std::pair<size_t, size_t> >(
          sqroot,
          std::pair<size_t,size_t>(k_counter, perf_counter)
      );
    } // search_for_k

    void printList(Node* head)
    {
      Node* current = head;
      std::cout << "\nPrint P_vector\n  P   sqrt perf k\n";
      while (current) {
        std::cout << std::setprecision(3)
                  << (double)current->get_perf_counter()
                         / current->get_k_counter() << "   "
                  << current->get_sqroot() << "   "
                  << current->get_perf_counter() << "   "
                  << current->get_k_counter() << "\n";
        current = current->get_next();
      }
    }
};

int main()
{
  std::ios::sync_with_stdio(0);
  std::cin.tie(0);

  size_t q, a, b;
  std::cin >> q;
  while (q--) {
    std::cin >> a >> b;

    size_t sqroot = 3, k_counter = 1, perf_counter = 1;

    Node* head = new Node(sqroot,k_counter, perf_counter);
    // P(k = 2) = (double)perf_counter / k_counter] = 1 / 1 = 1
    LinkedList p_list;

    // sqroot, k_counter, perf_counter
    std::pair<size_t, std::pair<size_t, size_t> > lastListed_sqroot =
        p_list.search_for_k(head, (double)a / b);

    if(lastListed_sqroot.first == 0)
    continue;                                        // Meaning that a corresponding k is already found

    sqroot = lastListed_sqroot.first;                // If program reaches this point, then there isn't any smaller P listed, so m
    k_counter = lastListed_sqroot.second.first;      // iterations will continue from the last listed P. Of course listing new k
    perf_counter = lastListed_sqroot.second.second;  // numbers process will continue, too.

    while (sqroot += 2) {
      ++k_counter;

      // {if((t-(size_t)t)==0)} If t is an int, the partition is perfect.
      if (log2(sqroot + 1) - (size_t)log2(sqroot + 1) == 0) {
        ++perf_counter;
      }
      std::cout << "perf_counter= " << perf_counter << " "
                << "k_counter= " << k_counter << "\n";

      // list the new k
      head = p_list.insert(head, sqroot, k_counter, perf_counter);

      std::cout << "P(" << (sqroot * sqroot - 1) / 4 << ")= "
                << (double)perf_counter / (double)k_counter << "\n";
      if ((double)perf_counter / k_counter < (double)a / b) {
        std::cout << std::fixed << (sqroot * sqroot - 1) / 4 << "\n";
        break;
      }
    }
  }
}
