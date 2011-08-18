A Rule Engine for the Airline Market Simulator
==============================================

Abstract
--------

Some components of the Airline Market Simulator project ()
Specifications for a rule engine for the simulation-related components
(e.g., Pricing, Yield Calculation/Retrieval and Customer Choice Model)


```c++
typedef std::string HashKey_T;
```

```c++
class BomKeyManager {
  static HashKey_T makeKey (...);
};
```

```c++
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
```

```c++
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
```

```c++
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
```

```c++
class RuleManager {
  //
  std::multimap<HashKey_T, RuleBucket<FareRuleStruct> > _fareRuleBucket;
  std::multimap<HashKey_T, RuleBucket<YieldRuleStruct> > _yieldRuleBucket;
  std::multimap<HashKey_T, RuleBucket<CCRuleStruct> > _ccRuleBucket;
  //
  BomRoot* _parent;
};
```

```c++
template <RULE_TYPE>
struct RuleBucket {
  //
  HashKey_T _key;
  //
  std::list<ExtraRuleStruct<RULE_TYPE> > _extraRuleList;
};
```

