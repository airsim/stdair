// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// StdAir
#include <stdair/basic/BasConst_General.hpp>
#include <stdair/basic/BasConst_BomDisplay.hpp>
#include <stdair/basic/BasConst_Event.hpp>
#include <stdair/basic/BasConst_Request.hpp>
#include <stdair/basic/BasConst_Inventory.hpp>
#include <stdair/basic/BasConst_BookingClass.hpp>
#include <stdair/basic/BasConst_Yield.hpp>
#include <stdair/basic/BasConst_DefaultObject.hpp>
#include <stdair/basic/BasConst_Period_BOM.hpp>
#include <stdair/basic/BasConst_TravelSolution.hpp>

namespace stdair {

  // ///////// General /////////
  /** Default value for the BOM tree root key (" -- ROOT -- "). */
  const std::string DEFAULT_BOM_ROOT_KEY (" -- ROOT -- ");

  /** Default very small value. */
  const double DEFAULT_EPSILON_VALUE (0.0001); 
  
  /** Default flight speed (number of kilometers per hour). */
  const unsigned int DEFAULT_FLIGHT_SPEED (900);

  /** Default number of generated flight dates. */
  const NbOfFlightDates_T DEFAULT_NB_OF_FLIGHTDATES (0.0);

  /** Null time duration (in boost::time_duration unit).*/
  const Duration_T NULL_BOOST_TIME_DURATION (-1, -1, -1);

  /** Default number of days in a year. */
  const unsigned int DEFAULT_NB_OF_DAYS_IN_A_YEAR (365);

  /** Higher value per thousand */
  const unsigned int DEFAULT_NUMBER_OF_SUBDIVISIONS (1000);

  // //////// (Flight-)Period-related BOM ///////
  /** Default number of duration days. */
  const DayDuration_T DEFAULT_DAY_DURATION (0);

  /** Default date period (0-length, i.e., it lasts one day).*/
  const DatePeriod_T BOOST_DEFAULT_DATE_PERIOD (Date_T (2007, 1, 1),
                                                Date_T (2007, 1, 1));

  /** Day names (in English). */
  const std::string DOW_STR[] =
    {"Mon", "Tue", "Wed", "Thu", "Fri", "Sat", "Sun"};

  /** Default DOW String (e.g., "0000000"). */
  const DOW_String_T DEFAULT_DOW_STRING ("0000000");

  /** Default Date Offset (e.g., 0). */
  const DateOffset_T DEFAULT_DATE_OFFSET (0);


  //  // //////// General ///////
  /** Default date for the General. */
  const Date_T DEFAULT_DATE (2010, boost::gregorian::Jan, 1);

  /** Default date-time. */
  const DateTime_T DEFAULT_DATETIME (DEFAULT_DATE, NULL_BOOST_TIME_DURATION);

  /** Default epsilon duration (1 nanosecond). */
  const Duration_T DEFAULT_EPSILON_DURATION (0, 0, 0, 1);

  /** Number of seconds in one day. */
  const Count_T SECONDS_IN_ONE_DAY (86400);
  
  /** Number of milliseconds in one second */
  const Count_T MILLISECONDS_IN_ONE_SECOND (1000);

  /** Default random seed. */
  const RandomSeed_T DEFAULT_RANDOM_SEED (120765987);

  // //////// Default BOM tree objects /////// ///////
  /** Default origin airport (e.g., "LHR"). */
  const AirportCode_T AIRPORT_LHR ("LHR");
  
  /** Default destination airport (e.g., "SYD"). */
  const AirportCode_T AIRPORT_SYD ("SYD");

  /** London city code (e.g., "LHR"). */
  const CityCode_T POS_LHR ("LHR");

  /** Date. */
  const Date_T DATE_20110115 (2011, boost::gregorian::Jan, 15);
  const Date_T DATE_20111231 (2011, boost::gregorian::Dec, 31);
  
  /** Advance purchase 0 day. */
  const DayDuration_T NO_ADVANCE_PURCHASE (0);
  
  /** Default saturdayStay value (true). */
  const SaturdayStay_T SATURDAY_STAY (true);

  /** Default saturdayStay value (false). */
  const SaturdayStay_T NO_SATURDAY_STAY (false);
  
  /** Default change fees value (true). */
  const ChangeFees_T CHANGE_FEES (true);
  
  /** Default change fees value (false). */
  const ChangeFees_T NO_CHANGE_FEES (false);
  
  /** Default non refundable value (true). */
  const NonRefundable_T NON_REFUNDABLE (true);

  /** Default refundable value (false). */
  const NonRefundable_T No_NON_REFUNDABLE (false);

  /** Default saturdayStay value (true). */
  const SaturdayStay_T DEFAULT_BOM_TREE_SATURDAY_STAY (true);
  
  /** Default change fees value (true). */
  const ChangeFees_T DEFAULT_BOM_TREE_CHANGE_FEES (true);
  
  /** Default non refundable value (true). */
  const NonRefundable_T DEFAULT_BOM_TREE_NON_REFUNDABLE (true);

  /** Stay duration 0 day. */
  const DayDuration_T NO_STAY_DURATION (0);
  
  /** Airline code "BA". */
  const AirlineCode_T AIRLINE_CODE_BA ("BA");

  /** Cabin 'Y'. */
  const CabinCode_T  CABIN_Y ("Y");

  /** Class code 'Y'. */
  const ClassCode_T  CLASS_CODE_Y ("Y");
  
  // //////// Travel solutions related objects///////
  /** Class code 'Q'. */
  const ClassCode_T CLASS_CODE_Q ("Q");
  
  // //////// Booking request related objects///////
  /** Singapour airport (e.g., "SIN"). */
  const AirportCode_T AIRPORT_SIN ("SIN");

  /** Bangkok airport (e.g., "BKK"). */
  const AirportCode_T AIRPORT_BKK ("BKK");

  /** Singapour city code (e.g., "SIN"). */
  const CityCode_T POS_SIN ("SIN");

  /** Economic cabin (e.g., "Eco"). */
  const CabinCode_T CABIN_ECO ("Eco");

  /** Frequent flyer tier (e.g., "M" meaning member). */
  const FrequentFlyer_T FREQUENT_FLYER_MEMBER ("M");

  // //////// Default ///////
  /** Default family code value ("X"). */
  const ClassCode_T DEFAULT_FAMILY_CODE ("0");

  /** Default number of airlines. */
  const NbOfAirlines_T DEFAULT_NBOFAIRLINES (0);

  /** Default flight-path code value (""). */
  const FlightPathCode_T DEFAULT_FLIGHTPATH_CODE ("");

  // //////// Booking-class-related BOM ///////
  /** Default distance value (kilometers). */
  const Distance_T DEFAULT_DISTANCE_VALUE (0);

  /** Default closed class code. */
  const ClassCode_T DEFAULT_CLOSED_CLASS_CODE ("CC");
    
  /** Default number of bookings (with counted cancellation)
      for BookingClass. */
  const NbOfBookings_T DEFAULT_CLASS_NB_OF_BOOKINGS (0);

  /** Default number of booking (without cancellation)
      demands for BookingClass. */
  const NbOfBookings_T DEFAULT_CLASS_TOTAL_NB_OF_BOOKINGS (0);

  /** Default unconstrained demand for BookingClass. */
  const NbOfBookings_T DEFAULT_CLASS_UNCONSTRAINED_DEMAND (0);

  /** Default remaining future demand mean for BookingClass. */
  const NbOfBookings_T DEFAULT_CLASS_REMAINING_DEMAND_MEAN (0);

  /** Default remaining futre demand standard deviation for BookingClass. */
  const NbOfBookings_T DEFAULT_CLASS_REMAINING_DEMAND_STANDARD_DEVIATION (0);

  /** Default number of cancellations for BookingClass. */
  const NbOfCancellations_T DEFAULT_CLASS_NB_OF_CANCELLATIONS (0);

  /** Default number of no-shows for BookingClass. */
  const NbOfNoShows_T DEFAULT_CLASS_NB_OF_NOSHOWS (0);

  /** Default cabin capacity for Leg cabins. */
  const CabinCapacity_T DEFAULT_CABIN_CAPACITY (100.0);

  /** Default committed space value for Leg cabins. */
  const CommittedSpace_T DEFAULT_COMMITTED_SPACE (0.0);

  /** Default commited space value for Leg cabins. */
  const BlockSpace_T DEFAULT_BLOCK_SPACE (0.0);
    
  /** Default null availability (0.0). */
  const Availability_T DEFAULT_NULL_AVAILABILITY (0.0);

  /** Default availability (9.0). */
  const Availability_T DEFAULT_AVAILABILITY (9.0);

  /** Maximal offered capacity in a cabin. */
  const Availability_T MAXIMAL_AVAILABILITY (9999.0);


  // //////// (Segment-)Class-related BOM ///////
  /** Default boolean for censorship flag given the status of
      availability for BookingClass. */
  const CensorshipFlag_T DEFAULT_CLASS_CENSORSHIPFLAG (false);

  /** Default list of censorship flag given the status of 
      availability for BookingClass. */
  const CensorshipFlagList_T DEFAULT_CLASS_CENSORSHIPFLAG_LIST =
    std::vector<CensorshipFlag_T>();

  /** Default booking limit value for BookingClass. */
  const BookingLimit_T DEFAULT_CLASS_BOOKING_LIMIT (9999.0);

  /** Default authorization level for BookingClass. */
  const AuthorizationLevel_T DEFAULT_CLASS_AUTHORIZATION_LEVEL (9999.0);

  /** Default MAX value of authorization level for BookingClass. */
  const AuthorizationLevel_T DEFAULT_CLASS_MAX_AUTHORIZATION_LEVEL (9999.0);

  /** Default MIN value of authorization level for BookingClass. */
  const AuthorizationLevel_T DEFAULT_CLASS_MIN_AUTHORIZATION_LEVEL (0.0);

  /** Default over-booking rate for BookingClass. */
  const OverbookingRate_T DEFAULT_CLASS_OVERBOOKING_RATE (0.0);

  /** Default booking rate for OnD bookings over overall class bookings. */
  const BookingRatio_T DEFAULT_OND_BOOKING_RATE (0.0);

  /** Default Fare value. */
  const Fare_T DEFAULT_FARE_VALUE (0.0);

  /** Default yield value for a virtual class. */
  const Yield_T DEFAULT_CLASS_YIELD_VALUE (0.0);

  /** Default Revenue value. */
  const Revenue_T DEFAULT_REVENUE_VALUE (0.0);

  /** Default load factor value (100%). */
  const Percentage_T DEFAULT_LOAD_FACTOR_VALUE (100.0);


  // //////// (Leg-)YieldRange-related BOM ///////
  /** Default yield value. */
  const Yield_T DEFAULT_YIELD_VALUE (0.0);

  /** Default yield max value. */
  const Yield_T DEFAULT_YIELD_MAX_VALUE (std::numeric_limits<double>::max());
    
  /** Default number of bookings for YieldRangeStruct_T. */
  const NbOfBookings_T DEFAULT_YIELD_NB_OF_BOOKINGS (0.0);

  /** Default booking number. */
  const Identity_T DEFAULT_BOOKING_NUMBER (0);

  /** Default cancellation number for YieldRangeStruct_T. */
  const NbOfCancellations_T DEFAULT_YIELD_NB_OF_CANCELLATIONS (0.0);

  /** Default no-shows number for YieldRangeStruct_T. */
  const NbOfNoShows_T DEFAULT_YIELD_NB_OF_NOSHOWS (0.0);

  /** Default availability for YieldRangeStruct_T. */
  const Availability_T DEFAULT_YIELD_AVAILABILITY (0.0);

  /** Default boolean for booking limit availability for
      YieldRangeStruct_T. */
  const CensorshipFlag_T DEFAULT_YIELD_CENSORSHIPFLAG (false);
  
  /** Default booking limit value for YieldRangeStruct_T. */
  const BookingLimit_T DEFAULT_YIELD_BOOKING_LIMIT (0.0);
  
  /** Default over-booking rate for YieldRangeStruct_T. */
  const OverbookingRate_T DEFAULT_YIELD_OVERBOOKING_RATE (0.0);


  // //////// OnD-related BOM ///////
  /** Default value of Fare. */
  const Fare_T DEFAULT_OND_FARE_VALUE (0.0);


  // //////// Event Generation /////////

  /** Default progress status. */
  const Count_T DEFAULT_PROGRESS_STATUS (0); 

  /** Maximum progress status. */
  const Percentage_T MAXIMUM_PROGRESS_STATUS (100);

  /** Default reference (oldest) date for the events. No event can
      occur before that date. */
  const Date_T DEFAULT_EVENT_OLDEST_DATE (2008, boost::gregorian::Jan, 1);

  /** Default reference (oldest) date-time for the events. No event can
      occur before that date-time. */
  const DateTime_T DEFAULT_EVENT_OLDEST_DATETIME (DEFAULT_EVENT_OLDEST_DATE,
                                                  NULL_BOOST_TIME_DURATION);


  // //////// Booking Request /////////
  /** Default party size in a request. */
  const PartySize_T DEFAULT_PARTY_SIZE (1);

  /** Default duration for a stay. */
  const DayDuration_T DEFAULT_STAY_DURATION (7);

  /** Default Willingness-to-Pay (WTP, as expressed as a monetary unit). */
  const WTP_T DEFAULT_WTP (1000.0);
    
  /** Default departure date. */
  const Date_T DEFAULT_PREFERRED_DEPARTURE_DATE (DEFAULT_DEPARTURE_DATE);

  /** Default preferred departure time (08:00). */
  const Duration_T DEFAULT_PREFERRED_DEPARTURE_TIME (8, 0, 0);
    
  /** Default advance purchase. */
  const DateOffset_T DEFAULT_ADVANCE_PURCHASE (22);

  /** Default request date. */
  const Date_T DEFAULT_REQUEST_DATE (DEFAULT_PREFERRED_DEPARTURE_DATE
                                     - DEFAULT_ADVANCE_PURCHASE);

  /** Default preferred departure time (08:00). */
  const Duration_T DEFAULT_REQUEST_TIME (8, 0, 0);
    
  /** Default request date-time. */
  const DateTime_T DEFAULT_REQUEST_DATE_TIME (DEFAULT_REQUEST_DATE,
                                              DEFAULT_REQUEST_TIME);

  /** Default preferred cabin. */
  const CabinCode_T DEFAULT_PREFERRED_CABIN ("M");

  /** Default point-of-sale. */
  const CityCode_T DEFAULT_POS ("ALL");

  /** Default channel (e.g., "DC" meaning Different Channels). */
  const ChannelLabel_T DEFAULT_CHANNEL ("DC");

  /** DN channel (e.g., direct on-line). */
  const ChannelLabel_T CHANNEL_DN ("DN");

  /** IN channel (e.g., indirect on-line). */
  const ChannelLabel_T CHANNEL_IN ("IN");

  /** Trip type one-way (e.g., "OW"). */
  const TripType_T TRIP_TYPE_ONE_WAY ("OW");

  /** Trip type round-trip (e.g., "RT"). */
  const TripType_T TRIP_TYPE_ROUND_TRIP ("RT");

  /** Trip type inbound (e.g., "RI"). */
  const TripType_T TRIP_TYPE_INBOUND ("RI");

  /** Trip type outbound (e.g., "RO"). */
  const TripType_T TRIP_TYPE_OUTBOUND ("RO");

  /** Default frequent flyer tier (non member). */
  const FrequentFlyer_T DEFAULT_FF_TIER ("N");

  /** Default value of time (expressed as a monetary unit per hour). */
  const PriceValue_T DEFAULT_VALUE_OF_TIME (100.0);
    

  // //////// Travel Solutions ///////
  /** Default Minimal connection time. */
  const Duration_T DEFAULT_MINIMAL_CONNECTION_TIME (0, 30, 0);

  /** Default maximal connection time. */
  const Duration_T DEFAULT_MAXIMAL_CONNECTION_TIME (24, 0, 0);

  /** Default Matching Indicator value. */
  const MatchingIndicator_T DEFAULT_MATCHING_INDICATOR (0.0);

  /** Default currency (euro). */
  const PriceCurrency_T DEFAULT_CURRENCY ("EUR");

  /** Default availability status for a travel solution. */
  const AvailabilityStatus_T DEFAULT_AVAILABILITY_STATUS (false);
  
  /** Default DICO studied date. */
  const Date_T DEFAULT_DICO_STUDIED_DATE;

  // //////// Inventory-related BOM ///////
  /** Default airline code value ("XX"). */
  const AirlineCode_T DEFAULT_AIRLINE_CODE ("XX");

  /** Default airline code value (""). */
  const AirlineCode_T DEFAULT_NULL_AIRLINE_CODE ("");

  /** Default airline code list value (empty vector). */
  const AirlineCodeList_T DEFAULT_AIRLINE_CODE_LIST;

  /** Default flight number (9999). */
  const FlightNumber_T DEFAULT_FLIGHT_NUMBER (9999);

  /** Default guillotine number (9999). */
  const GuillotineNumber_T DEFAULT_GUILLOTINE_NUMBER (9999);
  
  /** Default flight departure date (01/01/1900). */
  const Date_T DEFAULT_DEPARTURE_DATE (1900, boost::gregorian::Jan, 1);
  
  /** Default airport code value ("XXX"). */
  const AirportCode_T DEFAULT_AIRPORT_CODE ("XXX");

  /** Default airport code value ('').. */
  const AirportCode_T DEFAULT_NULL_AIRPORT_CODE ("");
  
  /** Default Origin. */
  const AirportCode_T DEFAULT_ORIGIN ("XXX");
  
  /** Default destination. */
  const AirportCode_T DEFAULT_DESTINATION ("XXX");
  
  /** Default cabin code. */
  const CabinCode_T DEFAULT_CABIN_CODE ("X");

  /** Default fare family Code. */
  const FamilyCode_T DEFAULT_FARE_FAMILY_CODE ("EcoSaver");

  /** Default null fare family Code ("NoFF"). */
  const FamilyCode_T DEFAULT_NULL_FARE_FAMILY_CODE ("NoFF");

  /** Default class code value ("X"). */
  const ClassCode_T DEFAULT_CLASS_CODE ("X");

  /** Default null class code value (""). */
  const ClassCode_T DEFAULT_NULL_CLASS_CODE ("");

  /** Default class code list value (empty vector). */
  const ClassList_StringList_T DEFAULT_CLASS_CODE_LIST;

  /** Default Bid-Price. */
  const BidPrice_T DEFAULT_BID_PRICE (0.0);
  
  /** Default Bid-Price Vector. */
  const BidPriceVector_T DEFAULT_BID_PRICE_VECTOR = std::vector<BidPrice_T>();

  /** Maximal number of legs linked to a single flight-date.
      <br>Note that the number of derived segments is n*(n+1)/2 if n
      is the number of legs. */
  const unsigned short MAXIMAL_NUMBER_OF_LEGS_IN_FLIGHT (7);
  
  /** Maximal number of segments linked to a single O&D
      (Origin & Destination). */
  const unsigned short MAXIMAL_NUMBER_OF_SEGMENTS_IN_OND (3);

  /** Default seat index (for a bucket and/or Bid-Price Vector slot). */
  const SeatIndex_T DEFAULT_SEAT_INDEX (1);

  /** Default number of bookings. */
  const NbOfSeats_T DEFAULT_NULL_BOOKING_NUMBER (0);
  
  /** Default capacity adjustment of the cabin. */
  const CapacityAdjustment_T DEFAULT_NULL_CAPACITY_ADJUSTMENT (0);

  /** Default unsold Protection (UPR). */
  const UPR_T DEFAULT_NULL_UPR (0);

  /** Default value type (within a guillotine block) for fare family. */
  const std::string DEFAULT_FARE_FAMILY_VALUE_TYPE ("FF");

  /** Default value type (within a guillotine block) for segment-cabin. */
  const std::string DEFAULT_SEGMENT_CABIN_VALUE_TYPE ("SC");

  /** Default value for max day-to-departure (365). */
  const int DEFAULT_MAX_DTD = 365;

  /** Defaut data collection point list. */
  const DCPList_T DEFAULT_DCP_LIST = DefaultDCPList::init();
  DCPList_T DefaultDCPList::init() {
    DCPList_T oDCPList;
    //oDCPList.push_back (72);
    oDCPList.push_back (63);oDCPList.push_back (56);oDCPList.push_back (49);
    oDCPList.push_back (42);oDCPList.push_back (35);oDCPList.push_back (31);
    oDCPList.push_back (27);oDCPList.push_back (23);oDCPList.push_back (19);
    oDCPList.push_back (16);oDCPList.push_back (13);oDCPList.push_back (10);
    oDCPList.push_back (7); oDCPList.push_back (5); oDCPList.push_back (3);
    oDCPList.push_back (1); oDCPList.push_back (0);
    // oDCPList.push_back (63); oDCPList.push_back (49);
    // oDCPList.push_back (35); oDCPList.push_back (23); 
    // oDCPList.push_back (16); oDCPList.push_back (10);
    // oDCPList.push_back (5);  oDCPList.push_back (1);
    // oDCPList.push_back (0);
    return oDCPList;
  }
  /** Default frat5 coef map for demand to come forecaster. */
  const DTDFratMap_T DEFAULT_DTD_FRAT5COEF_MAP =
    DefaultDtdFratMap::init();
  DTDFratMap_T DefaultDtdFratMap::init() {
    DTDFratMap_T oDFCMap;
    oDFCMap[71] = 2.50583571429; oDFCMap[63] = 2.55994571429;
    oDFCMap[56] = 2.60841857143; oDFCMap[49] = 2.68888;
    oDFCMap[42] = 2.78583714286; oDFCMap[35] = 2.89091428571;
    oDFCMap[31] = 2.97871428571; oDFCMap[28] = 3.05521428571;
    oDFCMap[24] = 3.15177142857; oDFCMap[21] = 3.22164285714;
    oDFCMap[17] = 3.32237142857; oDFCMap[14] = 3.38697142857;
    oDFCMap[10] = 3.44204285714; oDFCMap[7] = 3.46202857143;
    oDFCMap[5] = 3.47177142857;  oDFCMap[3] = 3.4792;
    oDFCMap[1] = 3.48947142857; // oDFCMap[0] = 3.49111428571;
    return oDFCMap;
  }

  /** Default arrival pattern map. */
  const DTDProbMap_T DEFAULT_DTD_PROB_MAP =
    DefaultDtdProbMap::init();
  DTDProbMap_T DefaultDtdProbMap::init() {
    DTDProbMap_T oDPMap;
    oDPMap[-330] = 0; oDPMap[-150] = 0.1; oDPMap[-92] = 0.2;
    oDPMap[-55] = 0.3; oDPMap[-34] = 0.4; oDPMap[-21] = 0.5;
    oDPMap[-12] = 0.6; oDPMap[-6] = 0.7; oDPMap[-3] = 0.8;
    oDPMap[-1] = 0.9; oDPMap[0] = 1.0;
    return oDPMap;
  }


  // ////////// Key and display related /////////////
  /** Default delimiter for string display (e.g delimiter for inventory key
      and flight-date key). */
  const std::string DEFAULT_KEY_FLD_DELIMITER (";");

  /** Default sub delimiter for string display (e.g delimiter for flight number
      and departure date of a flight-date key). */
  const std::string DEFAULT_KEY_SUB_FLD_DELIMITER (",");

  /** Default token for decoding a full string display. */
  const boost::char_separator<char> DEFAULT_KEY_TOKEN_DELIMITER (";, ");

  /** Default list of full keys. */
  const OnDStringList_T DEFAULT_OND_STRING_LIST;

  
  // ////////// BomManager-related constants ///////////
  /** Array with the indentation spaces needed for all the BOM
      hierachical levels. */
  const std::string DISPLAY_LEVEL_STRING_ARRAY[51] =
  { "", "  ", "    ", "      ",
    "        ", "          ", "            ", "              ",
    "                ", "                  ", "                    ",
    "                      ", "                        ",
    "                          ", "                            ",
    "                              ", "                                ",
    "                                    ",
    "                                      ",
    "                                        ",
    "                                          ",
    "                                            ",
    "                                              ",
    "                                                ",
    "                                                  ",
    "                                                    ",
    "                                                      ",
    "                                                        ",
    "                                                          ",
    "                                                            ",
    "                                                              ",
    "                                                                ",
    "                                                                  ",
    "                                                                    ",
    "                                                                      ",
    "                                                                        ",
    "                                                                          ",
    "                                                                            ",
    "                                                                              ",
    "                                                                                ",
    "                                                                                  ",
    "                                                                                    ",
    "                                                                                      ",
    "                                                                                        ",
    "                                                                                          ",
    "                                                                                            ",
    "                                                                                              ",
    "                                                                                                ",
    "                                                                                                  ",
    "                                                                                                    ",
    "                                                                                                      " };

  
}
