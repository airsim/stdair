#ifndef __STDAIR_CMD_CMDBOMMANAGER_HPP
#define __STDAIR_CMD_CMDBOMMANAGER_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <iosfwd>
// StdAir
#include <stdair/stdair_inventory_types.hpp>
#include <stdair/bom/TravelSolutionTypes.hpp>
#include <stdair/command/CmdAbstract.hpp>

namespace stdair {

  /// Forward declarations
  class BomRoot;
  struct BookingRequestStruct;


  /**
   * Class wrapping utility functions for handling the BOM tree
   * objects.
   */
  class CmdBomManager : public CmdAbstract {
  public:

    // //////////////// BOM initialisation support methods /////////////////
    /**
     * Build a sample BOM tree, and attach it to the given reference.
     *
     * As for now, two inventories (one for BA, another for AF) are
     * built, each containing one flight. One of those flights has two
     * legs (and therefore three segments).
     *     
     * @param BomRoot& Top of the BOM tree, to which the sample should
     *        be attached.
     */
    static void buildSampleBom (BomRoot&);

    /**
     * Build a sample bom tree for RMOL.
     *
     * @param BomRoot& Top of the BOM tree, to which the sample should
     *        be attached.
     */
    static void buildSampleBomForRMOL (BomRoot&, const CabinCapacity_T&);

    /**
     * Build a sample bom tree for SimFQT.
     *
     * @param BomRoot& Top of the BOM tree, to which the sample should
     *        be attached.
     */
    static void buildSampleBomForFareQuoter (BomRoot&);

    /**
     * Build a sample list of travel solutions.
     *
     * As of now (March 2011), that list is made of the following
     * travel solutions:
     * <ul>
     *  <li>BA9</li>
     *  <li>LHR-SYD</li>
     *  <li>2011-06-10</li>
     * </ul>
     *
     * @param TravelSolutionList_T& Sample list of travel solution structures.
     *        It should be given empty. It is altered with the returned sample.
     */
    static void buildSampleTravelSolutionForPricing (TravelSolutionList_T&);

    /**
     * Build a sample list of travel solutions.
     *
     * As of now (March 2011), that list is made of the following
     * travel solutions:
     * <ul>
     *  <li>BA9</li>
     *  <li>LHR-SYD</li>
     *  <li>2011-06-10</li>
     *  <li>Q</li>
     *  <li>WTP: 900</li>
     *  <li>Change fee: 20; Non refundable; Saturday night stay</li>
     * </ul>
     *
     * @param TravelSolutionList_T& Sample list of travel solution structures.
     *        It should be given empty. It is altered with the returned sample.
     */
    static void buildSampleTravelSolutions (TravelSolutionList_T&);

    /**
     * Build a sample booking request structure.
     *
     * As of now (March 2011), that booking request is made of the
     * following parameters:
     * <ul>
     *  <li>Return trip (inbound): LHR-SYD (POS: LHR, Channel: DN), </li>
     *  <li>Departing 10-JUN-2011 around 8:00, staying 7 days</li>
     *  <li>Requested on 15-MAY-2011 at 10:00</li>
     *  <li>Economy cabin, 3 persons, FF member</li>
     *  <li>WTP: 1000.0 EUR</li>
     *  <li>Dis-utility: 100.0 EUR/hour</li>
     * </ul>
     *
     * @return BookingRequestStruct& Sample booking request structure.
     */
    static BookingRequestStruct buildSampleBookingRequest();

    /**
     * Build a sample booking request structure, mainly for the CRS tests.
     *
     * As of now (March 2011), that booking request is made of the
     * following parameters:
     * <ul>
     *  <li>Return trip (inbound): SIN-BKK (POS: SIN, Channel: IN), </li>
     *  <li>Departing 30-JAN-2010 around 10:00, staying 7 days</li>
     *  <li>Requested on 22-JAN-2010 at 10:00</li>
     *  <li>Economy cabin, 3 persons, FF member</li>
     *  <li>WTP: 1000.0 EUR</li>
     *  <li>Dis-utility: 100.0 EUR/hour</li>
     * </ul>
     *
     * @return BookingRequestStruct& Sample booking request structure.
     */
    static BookingRequestStruct buildSampleBookingRequestForCRS();
  };
}
#endif // ___STDAIR_CMD_CMDBOMMANAGER_HPP
