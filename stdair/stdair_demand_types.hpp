#ifndef __STDAIR_STDAIR_DEMAND_TYPES_HPP
#define __STDAIR_STDAIR_DEMAND_TYPES_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <string>
#include <vector>
#include <list>
#include <map>
// Boost (Extended STL)
#include <boost/tuple/tuple.hpp>
// StdAir
#include <stdair/stdair_basic_types.hpp>
#include <stdair/stdair_maths_types.hpp>
#include <stdair/stdair_inventory_types.hpp>


namespace stdair {

  // //////// Type definitions /////////
  /** Define the availability option allowing the ticket change. */
  typedef bool ChangeFees_T;

  /** Define the refundable availability of a tickets. */
  typedef bool NonRefundable_T;

  /** Define the saturday stay of a tickets. */
  typedef bool SaturdayStay_T;

  /** Define the average ratio (between 0 and 100 percent) of demand with
      a saturday stay status equal to TRUE. */
  typedef double SaturdayStayRatio_T;

  /** Define the average ratio of demand with change fee
      availability. */
  typedef double ChangeFeesRatio_T;

  /** Define the average ratio of demand with non-refundable
      availability. */
  typedef double NonRefundableRatio_T;

  /** Define the disutility of restriction. */
  typedef double Disutility_T;

  /** Define the passenger characteristics, leisure or business
      for instance (1-letter-code, e.g., L or B). */
  typedef std::string PassengerType_T;

  /** Define the identifier of a distribution pattern (e.g., 1). */
  typedef std::string DistributionPatternId_T;

  /** Define the identifier of a cancellation rate curve (e.g., C1). */
  typedef std::string CancellationRateCurveId_T;

  /** Define the identifier of an airline preference set list (e.g., AP1). */
  typedef std::string AirlinePreferenceId_T;

  /** Define a cancellation & and no-show rate pair. */
  typedef std::pair<Percentage_T, Percentage_T> CancellationNoShowRatePair_T;

  /** Define the identifier of a demand characteristics pattern
      (e.g. Ch12); for a customer choice model   */
  typedef std::string CharacteristicsPatternId_T;

  /** Define characteristics component index (e.g. W for WTP) */
  typedef std::string CharacteristicsIndex_T;

  /** Define a Willingness-To-Pay (WTP) (e.g., 1000.0 Euros). */
  typedef double WTP_T;

  /** Define the name of a WTP-component of characteristics pattern. */
  typedef boost::tuples::tuple<double, WTP_T> CharacteristicsWTP_tuple_T;
  
  /** Define the <WTP, demand> pair type.*/
  typedef std::pair<WTP_T, MeanStdDevPair_T> WTPDemandPair_T;

  /** Define a number of cancellations (travellers). */
  typedef NbOfRequests_T NbOfCancellations_T;

  /** Define a number of no-shows. */
  typedef NbOfRequests_T NbOfNoShows_T;

  /** Define a indicator of demand to class matching. */
  typedef double MatchingIndicator_T;

  /** Type definition for the hashed key of the DemandStreamKey object. */
  typedef std::string DemandStreamKeyStr_T;

  /** Type of booking channel (D=direct, I=indirect, N=oNline, F=oFfline). */
  typedef std::string ChannelLabel_T;

  /** Type of frequent flyer (P=Platinum, G=Gold, S=Silver, M=Member, N=None).*/
  typedef std::string FrequentFlyer_T;

  /** Define the Request status for booking (1-letter-code, e.g.,
      B: booked, C: cancelled, R: Rejected). */
  typedef std::string RequestStatus_T;

  /** Define a map between a BookingID and a TravelSolutionID. */
  typedef std::map<Identity_T, Identity_T> BookingTSIDMap_T;

  /** Define a pair (cabin code, class code) e.g., (economy, K). */
  typedef std::pair<CabinCode_T, ClassCode_T> CabinClassPair_T;

  /** Define a list of pair (cabin code, class code). */
  typedef std::list<CabinClassPair_T> CabinClassPairList_T;

  /** Define the forecast booking requests proportion. */
  typedef double ProportionFactor_T;

  /** Define the list of forecast booking requests proportions. */
  typedef std::list<ProportionFactor_T> ProportionFactorList_T;

  /** Define the O&D string key (e.g. "SQ;11,2010-Feb-08;SIN,BKK"). */
  typedef std::string OnDString_T;

  /** Define the list of O&D string key. */
  typedef std::list<OnDString_T> OnDStringList_T;

}
#endif // __STDAIR_STDAIR_DEMAND_TYPES_HPP
