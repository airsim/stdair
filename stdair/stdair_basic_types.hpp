#ifndef __STDAIR_STDAIR_BASIC_TYPES_HPP
#define __STDAIR_STDAIR_BASIC_TYPES_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <string>
#include <list>

namespace stdair {

  // //////////////////////////////////////////////////////////////////////
  // Basic types
  /** Location code (3-letter-code, e.g., LON). */
  typedef std::string LocationCode_T;
  
  /** Define a distance (kilometers). */
  typedef unsigned long int Distance_T;

  /** Define the Airport Code type (3-letter-code, e.g., LHR). */
  typedef LocationCode_T AirportCode_T;

  /** City code */
  typedef LocationCode_T CityCode_T;

  /** Define the key description. */
  typedef std::string KeyDescription_T;
  
  /** Define the Airline Code type (2-letter-code, e.g., BA). */
  typedef std::string AirlineCode_T;

  /** Define the type for flight numbers. */
  typedef unsigned short FlightNumber_T;

  /** Define the type for data table numbers. */
  typedef unsigned short TableID_T;

  /** Define the cabin code (class of service, e.g., first, business,
      economy). */
  typedef std::string CabinCode_T;

  /** Define the code of the fare family (e.g., 1, 2, 3, etc.). */
  typedef std::string FamilyCode_T;

  /** Define the code of the policy (e.g., 1, 2, 3, etc.). */
  typedef std::string PolicyCode_T;

  /** Define the code of the nesting structure (e.g., "default"). */
  typedef std::string NestingStructureCode_T;

  /** Define the code of the nesting node (e.g., 1, 2, 3, etc). */
  typedef std::string NestingNodeCode_T;

  /** Define the booking class code (product segment class, e.g., H,
      B, K, etc.). */
  typedef std::string ClassCode_T;

  /** Define a identity number. */
  typedef unsigned long Identity_T;

  /** Type of trip type (RO=outbound of round-trip, RI=inbound of round-trip, 
      OW=one way). */
  typedef std::string TripType_T;

  /** Monetary value */
  typedef double MonetaryValue_T;
  
  /** Real number */
  typedef double RealNumber_T;
  
  /** Define a percentage value (between 0 and 100%). */
  typedef double Percentage_T;

  /** Define a price value (e.g., 1000.0 Euros). */
  typedef double PriceValue_T;

  /** Define a yield value (e.g., 1000.0 Euros). */
  typedef double YieldValue_T;

  /** Define a price currency (e.g., EUR for Euros). */
  typedef std::string PriceCurrency_T;

  /** Define an amount of revenue. */
  typedef double Revenue_T;

  /** Define the name of a multiplier. */
  typedef double Multiplier_T;
  
  /** Define the number of seats (it can be non integer, because the
      overbooking can be applied at booking class or PNR level). */
  typedef double NbOfSeats_T;

  /** Count */
  typedef unsigned int Count_T;
  
  /** Number of passengers (in a group) for a booking. */
  typedef short PartySize_T;

  /** Define a number of requests. */
  typedef double NbOfRequests_T;

  /** Define a number of bookings. */
  typedef NbOfRequests_T NbOfBookings_T;

  /** Define a number of cancellations. */
  typedef NbOfRequests_T NbOfCancellations_T;

  /** Define a number of travel solutions
      (in a travel solution block). */
  typedef unsigned short NbOfTravelSolutions_T;

  /** Define the list of class codes as a string. */
  typedef std::string ClassList_String_T;

  /** Define a number of segment-dates (in a path). */
  typedef unsigned short NbOfSegments_T;

  /** Define a number of airlines (in a path). */
  typedef unsigned short NbOfAirlines_T;

  /** Define an availability. */
  typedef double Availability_T;

  /** Define the price of a travel solution. */
  typedef double Fare_T;

  /** Define the censorship flag. */
  typedef bool Flag_T;

  /** Define the unsigned index type. */
  typedef unsigned int UnsignedIndex_T;

  /** Define the number of booking classes. */
  typedef unsigned int NbOfClasses_T;

  /** Define the number of fare families. */
  typedef unsigned int NbOfFareFamilies_T;

  // ///////////// Technical ////////////////
  /** File or directory name.
      <br>It may contain paths, relative or absolute (e.g., /foo/bar
      or C:\foo\bar). */
  typedef std::string Filename_T;
  
  /** Define the file address type (e.g. "a_directory/a_filename").
      <br>NOTE: That type should be deprecated. */
  typedef std::string FileAddress_T;

  /** Progress status (usually, a percentage expressed as a floating
      point number). */
  typedef float ProgressPercentage_T;

}
#endif // __STDAIR_STDAIR_BASIC_TYPES_HPP
