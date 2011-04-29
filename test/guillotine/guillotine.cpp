// STL
#include <cassert>
#include <iostream>
#include <string>
// BOOST
#include <boost/multi_array.hpp>

// ////////// M A I N //////////////
int main (int argc, char* argv[]) {
  typedef boost::multi_array<double, 2> Guillotine_Block_T;

  Guillotine_Block_T lSnapShotHolder (boost::extents[3][5]);
  double lValue = 0.0;

  // Assigne values to the elements.
  for (Guillotine_Block_T::index i = 0; i < 3; ++i) {
    for (Guillotine_Block_T::index j = 0; j < 5; ++j, ++lValue) {
      lSnapShotHolder[i][j] = lValue;
    }
  }

  typedef Guillotine_Block_T::index_range range;
  
  Guillotine_Block_T::array_view<1>::type myview1 =
    lSnapShotHolder [ boost::indices[range(0,3)][2] ];

  std::cout << myview1[0] << ", " << myview1[1] << std::endl;
  myview1[0] = 1000;

  Guillotine_Block_T::array_view<1>::type myview2 =
    lSnapShotHolder [ boost::indices[range(0,3)][2] ];

  std::cout << myview2[0] << ", " << myview2[1] << std::endl;

  Guillotine_Block_T::array_view<1>::type myview3 = myview2;
  myview3[0] = 0;
  std::cout << myview3[0] << ", " << myview3[1] << std::endl;
  return 0;
}
