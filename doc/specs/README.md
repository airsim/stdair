:Author: Denis Arnaud <denis dot arnaud_fedora at m4x dot org>
:Creation Date: Aug. 18, 2011
:Version: Aug. 18, 2011 -- First release

A Rule Engine for the Airline Market Simulator
==============================================

Abstract
--------

Some components of the Airline Market Simulator project ()
Specifications for a rule engine for the simulation-related components
(e.g., Pricing, Yield Calculation/Retrieval and Customer Choice Model)


<blockquote>
  typedef std::string HashKey_T;
</blockquote>

<blockquote>
  class BomKeyManager {
    static HashKey_T makeKey (...);
  };
</blockquote>

<blockquote>
  struct FareRuleStruct {
    //
    HashKey_T describeKey (...) {
      return BomKeyManager::makeKey (...);
    }
    //
    // ////// Attributes /////
    AirlineCodeList_T _airlineCodeList;
    AirportCode_T _origin;
    AirportCode_T _destination;
    // ...
  };
</blockquote>

<blockquote>
  template <RULE_TYPE>
  struct BaseRuleStruct {
    //
    HashKey_T describeKey (...) {
      return BomKeyManager::makeKey (...);
    }
    //
    // ////// Attributes /////
    AirlineCodeList_T _airlineCodeList;
    AirportCode_T _origin;
    AirportCode_T _destination; 
    // ...
  };
</blockquote>

<blockquote>
  template <RULE_TYPE>
  struct ExtraRuleStruct {
    //
    HashKey_T describeKey (...) {
      return BomKeyManager::makeKey (...);
    }
    //
    // ////// Attributes /////
    Period_T _departurePeriod;
    Duration_T _advancePurchase;
    Duration_T _minimumStay;
    // ...
  };
</blockquote>

<blockquote>
  class RuleManager {
    //
    std::multimap<HashKey_T, RuleBucket<FareRuleStruct> > _fareRuleBucket;
    std::multimap<HashKey_T, RuleBucket<YieldRuleStruct> > _yieldRuleBucket;
    std::multimap<HashKey_T, RuleBucket<CCRuleStruct> > _ccRuleBucket;
    //
    BomRoot* _parent;
  };
</blockquote>

<blockquote>
  template <RULE_TYPE>
  struct RuleBucket {
    //
    HashKey_T _key;
    //
    std::list<ExtraRuleStruct<RULE_TYPE> > _extraRuleList;
  };
</blockquote>

