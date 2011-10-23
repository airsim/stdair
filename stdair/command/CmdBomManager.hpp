#ifndef __STDAIR_CMD_CMDBOMMANAGER_HPP
#define __STDAIR_CMD_CMDBOMMANAGER_HPP

// //////////////////////////////////////////////////////////////////////
// Import section
// //////////////////////////////////////////////////////////////////////
// STL
#include <iosfwd>
// StdAir
#include <stdair/stdair_inventory_types.hpp>
#include <stdair/basic/SampleType.hpp>
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
    //
    friend class STDAIR_Service;
  private:

    // //////////////// BOM initialisation support methods /////////////////
    /**
     * Build a full sample BOM tree (i.e., with objects for all the components)
     * and attach it to the given reference.
     *
     * That method calls in sequence the corresponding specific methods for
     * all the main components: Schedule, Inventory, Pricing,
     * Revenue Accounting, Demand Generation and Customer Choice.
     *
     * @param BomRoot& Top of the BOM tree, to which the sample should
     *        be attached.
     */

    static void buildSampleBom (BomRoot&);

    /**
     * Build a sample BOM tree, with mainly Inventory-related objects,
     * and attach it to the given reference.
     *
     * As for now, two inventories (one for BA, another for AF) are
     * built, each containing one flight. One of those flights has two
     * legs (and therefore three segments).
     *     
     * @param BomRoot& Top of the BOM tree, to which the sample should
     *        be attached.
     * @param const SampleType& The type of component for which the BOM tree
     *        should be built.
     */
    static void buildSampleInventory (BomRoot&);

    /**
     * Build a dummy inventory, containing a dummy flight-date with a single
     * leg-cabin and some virtual booking classes. That structure is the bare
     * minimum required to perform an optimisation on a leg-cabin.
     *
     * As for now, that method is only called by RMOL.
     *
     * @param BomRoot& Top of the BOM tree, to which the sample should
     *        be attached.
     * @param const CabinCapacity_T& Capacity of the single
     *        leg-cabin on which the optimisation should be performed.
     */
    static void buildDummyInventory (BomRoot&, const CabinCapacity_T&);

    /**
     * Build a sample BOM tree, with mainly Pricing-related objects,
     * and attach it to the given reference.
     *
     * @param BomRoot& Top of the BOM tree, to which the sample should
     *        be attached.
     */
    static void buildSamplePricing (BomRoot&);

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

    /**
     * Build a sample BOM tree, and attach it to the given reference.
     *
     * As for now, two inventories (one for SQ, another for CX) are
     * built, each containing one flight. This sample bom provides an     
     * example for airline partnerships.
     *     
     * @param BomRoot& Top of the BOM tree, to which the sample should
     *        be attached.
     */
    static void buildPartnershipsSampleInventoryAndRM (BomRoot&);    
    static void buildPartnershipsSamplePricing (BomRoot&);

    static void buildSampleBomForPartnershipsFareQuoter (BomRoot&);
    static void buildSampleBomForPartnershipsAirRAC (BomRoot&);
    
  };
}
#endif // ___STDAIR_CMD_CMDBOMMANAGER_HPP
