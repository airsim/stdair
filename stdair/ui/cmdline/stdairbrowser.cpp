// STL
#include <cassert>
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
// Boost (Extended STL)
#include <boost/date_time/gregorian/gregorian.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/program_options.hpp>
//#include <boost/tokenizer.hpp>
//#include <boost/regex.hpp>
// StdAir
#include <stdair/bom/ClassAvailabilityMapHolderStruct.hpp>
#include <stdair/service/Logger.hpp>

// ///////// M A I N ////////////
int main (int argc, char* argv[]) {

  //
  stdair::ClassAvailabilityMapHolderStruct lCAMStruct1;
  stdair::ClassAvailabilityMapHolderStruct lCAMStruct2 (lCAMStruct1);
  std::cout << lCAMStruct1 << " - " << lCAMStruct2 << std::endl;
  
  return 0;
}
