# Install script for directory: /home/localoriuser/dev/sim/stdair/stdairgit/stdair

# Set the install prefix
IF(NOT DEFINED CMAKE_INSTALL_PREFIX)
  SET(CMAKE_INSTALL_PREFIX "/usr")
ENDIF(NOT DEFINED CMAKE_INSTALL_PREFIX)
STRING(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
IF(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  IF(BUILD_TYPE)
    STRING(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  ELSE(BUILD_TYPE)
    SET(CMAKE_INSTALL_CONFIG_NAME "Debug")
  ENDIF(BUILD_TYPE)
  MESSAGE(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
ENDIF(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)

# Set the component getting installed.
IF(NOT CMAKE_INSTALL_COMPONENT)
  IF(COMPONENT)
    MESSAGE(STATUS "Install component: \"${COMPONENT}\"")
    SET(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  ELSE(COMPONENT)
    SET(CMAKE_INSTALL_COMPONENT)
  ENDIF(COMPONENT)
ENDIF(NOT CMAKE_INSTALL_COMPONENT)

# Install shared libraries without execute permission?
IF(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  SET(CMAKE_INSTALL_SO_NO_EXE "0")
ENDIF(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "runtime")
  FOREACH(file
      "$ENV{DESTDIR}/usr/lib/libstdair.so.99.99.99"
      "$ENV{DESTDIR}/usr/lib/libstdair.so.99.99"
      "$ENV{DESTDIR}/usr/lib/libstdair.so"
      )
    IF(EXISTS "${file}" AND
       NOT IS_SYMLINK "${file}")
      FILE(RPATH_CHECK
           FILE "${file}"
           RPATH "")
    ENDIF()
  ENDFOREACH()
  list(APPEND CPACK_ABSOLUTE_DESTINATION_FILES
   "/usr/lib/libstdair.so.99.99.99;/usr/lib/libstdair.so.99.99;/usr/lib/libstdair.so")
FILE(INSTALL DESTINATION "/usr/lib" TYPE SHARED_LIBRARY FILES
    "/home/localoriuser/dev/sim/stdair/stdairgit/stdair/libstdair.so.99.99.99"
    "/home/localoriuser/dev/sim/stdair/stdairgit/stdair/libstdair.so.99.99"
    "/home/localoriuser/dev/sim/stdair/stdairgit/stdair/libstdair.so"
    )
  FOREACH(file
      "$ENV{DESTDIR}/usr/lib/libstdair.so.99.99.99"
      "$ENV{DESTDIR}/usr/lib/libstdair.so.99.99"
      "$ENV{DESTDIR}/usr/lib/libstdair.so"
      )
    IF(EXISTS "${file}" AND
       NOT IS_SYMLINK "${file}")
      FILE(RPATH_REMOVE
           FILE "${file}")
      IF(CMAKE_INSTALL_DO_STRIP)
        EXECUTE_PROCESS(COMMAND "/usr/bin/strip" "${file}")
      ENDIF(CMAKE_INSTALL_DO_STRIP)
    ENDIF()
  ENDFOREACH()
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "runtime")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "devel")
  list(APPEND CPACK_ABSOLUTE_DESTINATION_FILES
   "/usr/include/stdair/stdair_types.hpp;/usr/include/stdair/stdair_demand_types.hpp;/usr/include/stdair/stdair_date_time_types.hpp;/usr/include/stdair/STDAIR_Service.hpp;/usr/include/stdair/stdair_event_types.hpp;/usr/include/stdair/stdair_inventory_types.hpp;/usr/include/stdair/stdair_basic_types.hpp;/usr/include/stdair/stdair_fare_types.hpp;/usr/include/stdair/stdair_log.hpp;/usr/include/stdair/stdair_service_types.hpp;/usr/include/stdair/stdair_exceptions.hpp;/usr/include/stdair/stdair_rm_types.hpp;/usr/include/stdair/stdair_db.hpp;/usr/include/stdair/stdair_maths_types.hpp")
FILE(INSTALL DESTINATION "/usr/include/stdair" TYPE FILE FILES
    "/home/localoriuser/dev/sim/stdair/stdairgit/stdair/stdair_types.hpp"
    "/home/localoriuser/dev/sim/stdair/stdairgit/stdair/stdair_demand_types.hpp"
    "/home/localoriuser/dev/sim/stdair/stdairgit/stdair/stdair_date_time_types.hpp"
    "/home/localoriuser/dev/sim/stdair/stdairgit/stdair/STDAIR_Service.hpp"
    "/home/localoriuser/dev/sim/stdair/stdairgit/stdair/stdair_event_types.hpp"
    "/home/localoriuser/dev/sim/stdair/stdairgit/stdair/stdair_inventory_types.hpp"
    "/home/localoriuser/dev/sim/stdair/stdairgit/stdair/stdair_basic_types.hpp"
    "/home/localoriuser/dev/sim/stdair/stdairgit/stdair/stdair_fare_types.hpp"
    "/home/localoriuser/dev/sim/stdair/stdairgit/stdair/stdair_log.hpp"
    "/home/localoriuser/dev/sim/stdair/stdairgit/stdair/stdair_service_types.hpp"
    "/home/localoriuser/dev/sim/stdair/stdairgit/stdair/stdair_exceptions.hpp"
    "/home/localoriuser/dev/sim/stdair/stdairgit/stdair/stdair_rm_types.hpp"
    "/home/localoriuser/dev/sim/stdair/stdairgit/stdair/stdair_db.hpp"
    "/home/localoriuser/dev/sim/stdair/stdairgit/stdair/stdair_maths_types.hpp"
    )
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "devel")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "devel")
  list(APPEND CPACK_ABSOLUTE_DESTINATION_FILES
   "/usr/include/stdair/basic/float_utils_google.hpp;/usr/include/stdair/basic/BasChronometer.hpp;/usr/include/stdair/basic/ProgressStatus.hpp;/usr/include/stdair/basic/ProgressStatusSet.hpp;/usr/include/stdair/basic/BasConst_Inventory.hpp;/usr/include/stdair/basic/BasLogParams.hpp;/usr/include/stdair/basic/BasTypes.hpp;/usr/include/stdair/basic/StructAbstract.hpp;/usr/include/stdair/basic/BasConst_DefaultObject.hpp;/usr/include/stdair/basic/BasConst_Event.hpp;/usr/include/stdair/basic/BasConst_Period_BOM.hpp;/usr/include/stdair/basic/BasDBParams.hpp;/usr/include/stdair/basic/BasFileMgr.hpp;/usr/include/stdair/basic/BasParserTypes.hpp;/usr/include/stdair/basic/BasConst_TravelSolution.hpp;/usr/include/stdair/basic/ForecastingMethod.hpp;/usr/include/stdair/basic/BasConst_BomDisplay.hpp;/usr/include/stdair/basic/BasConst_Request.hpp;/usr/include/stdair/basic/YieldRange.hpp;/usr/include/stdair/basic/RandomGeneration.hpp;/usr/include/stdair/basic/BasConst_BookingClass.hpp;/usr/include/stdair/basic/EventType.hpp;/usr/include/stdair/basic/BasParserHelperTypes.hpp;/usr/include/stdair/basic/PassengerType.hpp;/usr/include/stdair/basic/BasConst_Yield.hpp;/usr/include/stdair/basic/float_utils.hpp;/usr/include/stdair/basic/BasConst_General.hpp")
FILE(INSTALL DESTINATION "/usr/include/stdair/basic" TYPE FILE FILES
    "/home/localoriuser/dev/sim/stdair/stdairgit/stdair/basic/float_utils_google.hpp"
    "/home/localoriuser/dev/sim/stdair/stdairgit/stdair/basic/BasChronometer.hpp"
    "/home/localoriuser/dev/sim/stdair/stdairgit/stdair/basic/ProgressStatus.hpp"
    "/home/localoriuser/dev/sim/stdair/stdairgit/stdair/basic/ProgressStatusSet.hpp"
    "/home/localoriuser/dev/sim/stdair/stdairgit/stdair/basic/BasConst_Inventory.hpp"
    "/home/localoriuser/dev/sim/stdair/stdairgit/stdair/basic/BasLogParams.hpp"
    "/home/localoriuser/dev/sim/stdair/stdairgit/stdair/basic/BasTypes.hpp"
    "/home/localoriuser/dev/sim/stdair/stdairgit/stdair/basic/StructAbstract.hpp"
    "/home/localoriuser/dev/sim/stdair/stdairgit/stdair/basic/BasConst_DefaultObject.hpp"
    "/home/localoriuser/dev/sim/stdair/stdairgit/stdair/basic/BasConst_Event.hpp"
    "/home/localoriuser/dev/sim/stdair/stdairgit/stdair/basic/BasConst_Period_BOM.hpp"
    "/home/localoriuser/dev/sim/stdair/stdairgit/stdair/basic/BasDBParams.hpp"
    "/home/localoriuser/dev/sim/stdair/stdairgit/stdair/basic/BasFileMgr.hpp"
    "/home/localoriuser/dev/sim/stdair/stdairgit/stdair/basic/BasParserTypes.hpp"
    "/home/localoriuser/dev/sim/stdair/stdairgit/stdair/basic/BasConst_TravelSolution.hpp"
    "/home/localoriuser/dev/sim/stdair/stdairgit/stdair/basic/ForecastingMethod.hpp"
    "/home/localoriuser/dev/sim/stdair/stdairgit/stdair/basic/BasConst_BomDisplay.hpp"
    "/home/localoriuser/dev/sim/stdair/stdairgit/stdair/basic/BasConst_Request.hpp"
    "/home/localoriuser/dev/sim/stdair/stdairgit/stdair/basic/YieldRange.hpp"
    "/home/localoriuser/dev/sim/stdair/stdairgit/stdair/basic/RandomGeneration.hpp"
    "/home/localoriuser/dev/sim/stdair/stdairgit/stdair/basic/BasConst_BookingClass.hpp"
    "/home/localoriuser/dev/sim/stdair/stdairgit/stdair/basic/EventType.hpp"
    "/home/localoriuser/dev/sim/stdair/stdairgit/stdair/basic/BasParserHelperTypes.hpp"
    "/home/localoriuser/dev/sim/stdair/stdairgit/stdair/basic/PassengerType.hpp"
    "/home/localoriuser/dev/sim/stdair/stdairgit/stdair/basic/BasConst_Yield.hpp"
    "/home/localoriuser/dev/sim/stdair/stdairgit/stdair/basic/float_utils.hpp"
    "/home/localoriuser/dev/sim/stdair/stdairgit/stdair/basic/BasConst_General.hpp"
    )
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "devel")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "devel")
  list(APPEND CPACK_ABSOLUTE_DESTINATION_FILES
   "/usr/include/stdair/bom/BomJSONExport.hpp;/usr/include/stdair/bom/LegCabin.hpp;/usr/include/stdair/bom/EventQueueTypes.hpp;/usr/include/stdair/bom/AirportPairTypes.hpp;/usr/include/stdair/bom/SnapshotStruct.hpp;/usr/include/stdair/bom/TimePeriodKey.hpp;/usr/include/stdair/bom/OptimisationNotificationStruct.hpp;/usr/include/stdair/bom/SegmentCabin.hpp;/usr/include/stdair/bom/EventTypes.hpp;/usr/include/stdair/bom/VirtualClassTypes.hpp;/usr/include/stdair/bom/PeriodStruct.hpp;/usr/include/stdair/bom/AirlineClassList.hpp;/usr/include/stdair/bom/BucketKey.hpp;/usr/include/stdair/bom/BucketTypes.hpp;/usr/include/stdair/bom/FareFamily.hpp;/usr/include/stdair/bom/Bucket.hpp;/usr/include/stdair/bom/key_types.hpp;/usr/include/stdair/bom/SegmentPeriodTypes.hpp;/usr/include/stdair/bom/AirlineClassListTypes.hpp;/usr/include/stdair/bom/LegDate.hpp;/usr/include/stdair/bom/BomAbstract.hpp;/usr/include/stdair/bom/BomRoot.hpp;/usr/include/stdair/bom/InventoryKey.hpp;/usr/include/stdair/bom/PosChannelTypes.hpp;/usr/include/stdair/bom/TimePeriod.hpp;/usr/include/stdair/bom/AirlineFeatureTypes.hpp;/usr/include/stdair/bom/GuillotineBlockTypes.hpp;/usr/include/stdair/bom/BomJSONImport.hpp;/usr/include/stdair/bom/BookingClassKey.hpp;/usr/include/stdair/bom/FareFamilyKey.hpp;/usr/include/stdair/bom/FareFamilyTypes.hpp;/usr/include/stdair/bom/DatePeriodTypes.hpp;/usr/include/stdair/bom/YieldFeaturesKey.hpp;/usr/include/stdair/bom/SegmentDateKey.hpp;/usr/include/stdair/bom/DatePeriodKey.hpp;/usr/include/stdair/bom/YieldStore.hpp;/usr/include/stdair/bom/BookingRequestTypes.hpp;/usr/include/stdair/bom/LegCabinKey.hpp;/usr/include/stdair/bom/EventStruct.hpp;/usr/include/stdair/bom/BomArchive.hpp;/usr/include/stdair/bom/BookingClassTypes.hpp;/usr/include/stdair/bom/TravelSolutionStruct.hpp;/usr/include/stdair/bom/KeyAbstract.hpp;/usr/include/stdair/bom/BomManager.hpp;/usr/include/stdair/bom/DatePeriod.hpp;/usr/include/stdair/bom/SnapshotTypes.hpp;/usr/include/stdair/bom/BookingClass.hpp;/usr/include/stdair/bom/BomHolderKey.hpp;/usr/include/stdair/bom/SegmentPeriodKey.hpp;/usr/include/stdair/bom/AirlineFeatureKey.hpp;/usr/include/stdair/bom/YieldFeatures.hpp;/usr/include/stdair/bom/FareFeaturesKey.hpp;/usr/include/stdair/bom/InventoryTypes.hpp;/usr/include/stdair/bom/GuillotineBlockKey.hpp;/usr/include/stdair/bom/YieldStoreKey.hpp;/usr/include/stdair/bom/FlightPeriodKey.hpp;/usr/include/stdair/bom/FlightPeriod.hpp;/usr/include/stdair/bom/BookingRequestStruct.hpp;/usr/include/stdair/bom/LegDateKey.hpp;/usr/include/stdair/bom/SegmentDate.hpp;/usr/include/stdair/bom/VirtualClassStruct.hpp;/usr/include/stdair/bom/DoWStruct.hpp;/usr/include/stdair/bom/SegmentCabinKey.hpp;/usr/include/stdair/bom/BomRootKey.hpp;/usr/include/stdair/bom/TravelSolutionTypes.hpp;/usr/include/stdair/bom/LegDateTypes.hpp;/usr/include/stdair/bom/FareOptionStruct.hpp;/usr/include/stdair/bom/EventQueue.hpp;/usr/include/stdair/bom/AirlineClassListKey.hpp;/usr/include/stdair/bom/LegCabinTypes.hpp;/usr/include/stdair/bom/EventQueueKey.hpp;/usr/include/stdair/bom/FareFeatures.hpp;/usr/include/stdair/bom/PosChannel.hpp;/usr/include/stdair/bom/Inventory.hpp;/usr/include/stdair/bom/FareFeaturesTypes.hpp;/usr/include/stdair/bom/BomHolder.hpp;/usr/include/stdair/bom/AirportPair.hpp;/usr/include/stdair/bom/BomDisplay.hpp;/usr/include/stdair/bom/TimePeriodTypes.hpp;/usr/include/stdair/bom/PosChannelKey.hpp;/usr/include/stdair/bom/AirlineStruct.hpp;/usr/include/stdair/bom/SegmentDateTypes.hpp;/usr/include/stdair/bom/AirportPairKey.hpp;/usr/include/stdair/bom/SegmentPeriod.hpp;/usr/include/stdair/bom/FlightPeriodTypes.hpp;/usr/include/stdair/bom/RMEventTypes.hpp;/usr/include/stdair/bom/ParsedKey.hpp;/usr/include/stdair/bom/GuillotineBlock.hpp;/usr/include/stdair/bom/FareOptionTypes.hpp;/usr/include/stdair/bom/YieldStoreTypes.hpp;/usr/include/stdair/bom/RMEventStruct.hpp;/usr/include/stdair/bom/OptimisationNotificationTypes.hpp;/usr/include/stdair/bom/BomRetriever.hpp;/usr/include/stdair/bom/FlightDateTypes.hpp;/usr/include/stdair/bom/BomKeyManager.hpp;/usr/include/stdair/bom/SegmentCabinTypes.hpp;/usr/include/stdair/bom/FlightDateKey.hpp;/usr/include/stdair/bom/FlightDate.hpp;/usr/include/stdair/bom/AirlineFeature.hpp;/usr/include/stdair/bom/YieldFeaturesTypes.hpp")
FILE(INSTALL DESTINATION "/usr/include/stdair/bom" TYPE FILE FILES
    "/home/localoriuser/dev/sim/stdair/stdairgit/stdair/bom/BomJSONExport.hpp"
    "/home/localoriuser/dev/sim/stdair/stdairgit/stdair/bom/LegCabin.hpp"
    "/home/localoriuser/dev/sim/stdair/stdairgit/stdair/bom/EventQueueTypes.hpp"
    "/home/localoriuser/dev/sim/stdair/stdairgit/stdair/bom/AirportPairTypes.hpp"
    "/home/localoriuser/dev/sim/stdair/stdairgit/stdair/bom/SnapshotStruct.hpp"
    "/home/localoriuser/dev/sim/stdair/stdairgit/stdair/bom/TimePeriodKey.hpp"
    "/home/localoriuser/dev/sim/stdair/stdairgit/stdair/bom/OptimisationNotificationStruct.hpp"
    "/home/localoriuser/dev/sim/stdair/stdairgit/stdair/bom/SegmentCabin.hpp"
    "/home/localoriuser/dev/sim/stdair/stdairgit/stdair/bom/EventTypes.hpp"
    "/home/localoriuser/dev/sim/stdair/stdairgit/stdair/bom/VirtualClassTypes.hpp"
    "/home/localoriuser/dev/sim/stdair/stdairgit/stdair/bom/PeriodStruct.hpp"
    "/home/localoriuser/dev/sim/stdair/stdairgit/stdair/bom/AirlineClassList.hpp"
    "/home/localoriuser/dev/sim/stdair/stdairgit/stdair/bom/BucketKey.hpp"
    "/home/localoriuser/dev/sim/stdair/stdairgit/stdair/bom/BucketTypes.hpp"
    "/home/localoriuser/dev/sim/stdair/stdairgit/stdair/bom/FareFamily.hpp"
    "/home/localoriuser/dev/sim/stdair/stdairgit/stdair/bom/Bucket.hpp"
    "/home/localoriuser/dev/sim/stdair/stdairgit/stdair/bom/key_types.hpp"
    "/home/localoriuser/dev/sim/stdair/stdairgit/stdair/bom/SegmentPeriodTypes.hpp"
    "/home/localoriuser/dev/sim/stdair/stdairgit/stdair/bom/AirlineClassListTypes.hpp"
    "/home/localoriuser/dev/sim/stdair/stdairgit/stdair/bom/LegDate.hpp"
    "/home/localoriuser/dev/sim/stdair/stdairgit/stdair/bom/BomAbstract.hpp"
    "/home/localoriuser/dev/sim/stdair/stdairgit/stdair/bom/BomRoot.hpp"
    "/home/localoriuser/dev/sim/stdair/stdairgit/stdair/bom/InventoryKey.hpp"
    "/home/localoriuser/dev/sim/stdair/stdairgit/stdair/bom/PosChannelTypes.hpp"
    "/home/localoriuser/dev/sim/stdair/stdairgit/stdair/bom/TimePeriod.hpp"
    "/home/localoriuser/dev/sim/stdair/stdairgit/stdair/bom/AirlineFeatureTypes.hpp"
    "/home/localoriuser/dev/sim/stdair/stdairgit/stdair/bom/GuillotineBlockTypes.hpp"
    "/home/localoriuser/dev/sim/stdair/stdairgit/stdair/bom/BomJSONImport.hpp"
    "/home/localoriuser/dev/sim/stdair/stdairgit/stdair/bom/BookingClassKey.hpp"
    "/home/localoriuser/dev/sim/stdair/stdairgit/stdair/bom/FareFamilyKey.hpp"
    "/home/localoriuser/dev/sim/stdair/stdairgit/stdair/bom/FareFamilyTypes.hpp"
    "/home/localoriuser/dev/sim/stdair/stdairgit/stdair/bom/DatePeriodTypes.hpp"
    "/home/localoriuser/dev/sim/stdair/stdairgit/stdair/bom/YieldFeaturesKey.hpp"
    "/home/localoriuser/dev/sim/stdair/stdairgit/stdair/bom/SegmentDateKey.hpp"
    "/home/localoriuser/dev/sim/stdair/stdairgit/stdair/bom/DatePeriodKey.hpp"
    "/home/localoriuser/dev/sim/stdair/stdairgit/stdair/bom/YieldStore.hpp"
    "/home/localoriuser/dev/sim/stdair/stdairgit/stdair/bom/BookingRequestTypes.hpp"
    "/home/localoriuser/dev/sim/stdair/stdairgit/stdair/bom/LegCabinKey.hpp"
    "/home/localoriuser/dev/sim/stdair/stdairgit/stdair/bom/EventStruct.hpp"
    "/home/localoriuser/dev/sim/stdair/stdairgit/stdair/bom/BomArchive.hpp"
    "/home/localoriuser/dev/sim/stdair/stdairgit/stdair/bom/BookingClassTypes.hpp"
    "/home/localoriuser/dev/sim/stdair/stdairgit/stdair/bom/TravelSolutionStruct.hpp"
    "/home/localoriuser/dev/sim/stdair/stdairgit/stdair/bom/KeyAbstract.hpp"
    "/home/localoriuser/dev/sim/stdair/stdairgit/stdair/bom/BomManager.hpp"
    "/home/localoriuser/dev/sim/stdair/stdairgit/stdair/bom/DatePeriod.hpp"
    "/home/localoriuser/dev/sim/stdair/stdairgit/stdair/bom/SnapshotTypes.hpp"
    "/home/localoriuser/dev/sim/stdair/stdairgit/stdair/bom/BookingClass.hpp"
    "/home/localoriuser/dev/sim/stdair/stdairgit/stdair/bom/BomHolderKey.hpp"
    "/home/localoriuser/dev/sim/stdair/stdairgit/stdair/bom/SegmentPeriodKey.hpp"
    "/home/localoriuser/dev/sim/stdair/stdairgit/stdair/bom/AirlineFeatureKey.hpp"
    "/home/localoriuser/dev/sim/stdair/stdairgit/stdair/bom/YieldFeatures.hpp"
    "/home/localoriuser/dev/sim/stdair/stdairgit/stdair/bom/FareFeaturesKey.hpp"
    "/home/localoriuser/dev/sim/stdair/stdairgit/stdair/bom/InventoryTypes.hpp"
    "/home/localoriuser/dev/sim/stdair/stdairgit/stdair/bom/GuillotineBlockKey.hpp"
    "/home/localoriuser/dev/sim/stdair/stdairgit/stdair/bom/YieldStoreKey.hpp"
    "/home/localoriuser/dev/sim/stdair/stdairgit/stdair/bom/FlightPeriodKey.hpp"
    "/home/localoriuser/dev/sim/stdair/stdairgit/stdair/bom/FlightPeriod.hpp"
    "/home/localoriuser/dev/sim/stdair/stdairgit/stdair/bom/BookingRequestStruct.hpp"
    "/home/localoriuser/dev/sim/stdair/stdairgit/stdair/bom/LegDateKey.hpp"
    "/home/localoriuser/dev/sim/stdair/stdairgit/stdair/bom/SegmentDate.hpp"
    "/home/localoriuser/dev/sim/stdair/stdairgit/stdair/bom/VirtualClassStruct.hpp"
    "/home/localoriuser/dev/sim/stdair/stdairgit/stdair/bom/DoWStruct.hpp"
    "/home/localoriuser/dev/sim/stdair/stdairgit/stdair/bom/SegmentCabinKey.hpp"
    "/home/localoriuser/dev/sim/stdair/stdairgit/stdair/bom/BomRootKey.hpp"
    "/home/localoriuser/dev/sim/stdair/stdairgit/stdair/bom/TravelSolutionTypes.hpp"
    "/home/localoriuser/dev/sim/stdair/stdairgit/stdair/bom/LegDateTypes.hpp"
    "/home/localoriuser/dev/sim/stdair/stdairgit/stdair/bom/FareOptionStruct.hpp"
    "/home/localoriuser/dev/sim/stdair/stdairgit/stdair/bom/EventQueue.hpp"
    "/home/localoriuser/dev/sim/stdair/stdairgit/stdair/bom/AirlineClassListKey.hpp"
    "/home/localoriuser/dev/sim/stdair/stdairgit/stdair/bom/LegCabinTypes.hpp"
    "/home/localoriuser/dev/sim/stdair/stdairgit/stdair/bom/EventQueueKey.hpp"
    "/home/localoriuser/dev/sim/stdair/stdairgit/stdair/bom/FareFeatures.hpp"
    "/home/localoriuser/dev/sim/stdair/stdairgit/stdair/bom/PosChannel.hpp"
    "/home/localoriuser/dev/sim/stdair/stdairgit/stdair/bom/Inventory.hpp"
    "/home/localoriuser/dev/sim/stdair/stdairgit/stdair/bom/FareFeaturesTypes.hpp"
    "/home/localoriuser/dev/sim/stdair/stdairgit/stdair/bom/BomHolder.hpp"
    "/home/localoriuser/dev/sim/stdair/stdairgit/stdair/bom/AirportPair.hpp"
    "/home/localoriuser/dev/sim/stdair/stdairgit/stdair/bom/BomDisplay.hpp"
    "/home/localoriuser/dev/sim/stdair/stdairgit/stdair/bom/TimePeriodTypes.hpp"
    "/home/localoriuser/dev/sim/stdair/stdairgit/stdair/bom/PosChannelKey.hpp"
    "/home/localoriuser/dev/sim/stdair/stdairgit/stdair/bom/AirlineStruct.hpp"
    "/home/localoriuser/dev/sim/stdair/stdairgit/stdair/bom/SegmentDateTypes.hpp"
    "/home/localoriuser/dev/sim/stdair/stdairgit/stdair/bom/AirportPairKey.hpp"
    "/home/localoriuser/dev/sim/stdair/stdairgit/stdair/bom/SegmentPeriod.hpp"
    "/home/localoriuser/dev/sim/stdair/stdairgit/stdair/bom/FlightPeriodTypes.hpp"
    "/home/localoriuser/dev/sim/stdair/stdairgit/stdair/bom/RMEventTypes.hpp"
    "/home/localoriuser/dev/sim/stdair/stdairgit/stdair/bom/ParsedKey.hpp"
    "/home/localoriuser/dev/sim/stdair/stdairgit/stdair/bom/GuillotineBlock.hpp"
    "/home/localoriuser/dev/sim/stdair/stdairgit/stdair/bom/FareOptionTypes.hpp"
    "/home/localoriuser/dev/sim/stdair/stdairgit/stdair/bom/YieldStoreTypes.hpp"
    "/home/localoriuser/dev/sim/stdair/stdairgit/stdair/bom/RMEventStruct.hpp"
    "/home/localoriuser/dev/sim/stdair/stdairgit/stdair/bom/OptimisationNotificationTypes.hpp"
    "/home/localoriuser/dev/sim/stdair/stdairgit/stdair/bom/BomRetriever.hpp"
    "/home/localoriuser/dev/sim/stdair/stdairgit/stdair/bom/FlightDateTypes.hpp"
    "/home/localoriuser/dev/sim/stdair/stdairgit/stdair/bom/BomKeyManager.hpp"
    "/home/localoriuser/dev/sim/stdair/stdairgit/stdair/bom/SegmentCabinTypes.hpp"
    "/home/localoriuser/dev/sim/stdair/stdairgit/stdair/bom/FlightDateKey.hpp"
    "/home/localoriuser/dev/sim/stdair/stdairgit/stdair/bom/FlightDate.hpp"
    "/home/localoriuser/dev/sim/stdair/stdairgit/stdair/bom/AirlineFeature.hpp"
    "/home/localoriuser/dev/sim/stdair/stdairgit/stdair/bom/YieldFeaturesTypes.hpp"
    )
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "devel")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "devel")
  list(APPEND CPACK_ABSOLUTE_DESTINATION_FILES
   "/usr/include/stdair/factory/FacAbstract.hpp;/usr/include/stdair/factory/FacBomManager.hpp;/usr/include/stdair/factory/FacBom.hpp")
FILE(INSTALL DESTINATION "/usr/include/stdair/factory" TYPE FILE FILES
    "/home/localoriuser/dev/sim/stdair/stdairgit/stdair/factory/FacAbstract.hpp"
    "/home/localoriuser/dev/sim/stdair/stdairgit/stdair/factory/FacBomManager.hpp"
    "/home/localoriuser/dev/sim/stdair/stdairgit/stdair/factory/FacBom.hpp"
    )
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "devel")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "devel")
  list(APPEND CPACK_ABSOLUTE_DESTINATION_FILES
   "/usr/include/stdair/dbadaptor/DbaAirline.hpp;/usr/include/stdair/dbadaptor/DbaAbstract.hpp")
FILE(INSTALL DESTINATION "/usr/include/stdair/dbadaptor" TYPE FILE FILES
    "/home/localoriuser/dev/sim/stdair/stdairgit/stdair/dbadaptor/DbaAirline.hpp"
    "/home/localoriuser/dev/sim/stdair/stdairgit/stdair/dbadaptor/DbaAbstract.hpp"
    )
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "devel")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "devel")
  list(APPEND CPACK_ABSOLUTE_DESTINATION_FILES
   "/usr/include/stdair/command/DBManagerForAirlines.hpp;/usr/include/stdair/command/CmdBomManager.hpp;/usr/include/stdair/command/CmdBomSerialiser.hpp;/usr/include/stdair/command/CmdAbstract.hpp")
FILE(INSTALL DESTINATION "/usr/include/stdair/command" TYPE FILE FILES
    "/home/localoriuser/dev/sim/stdair/stdairgit/stdair/command/DBManagerForAirlines.hpp"
    "/home/localoriuser/dev/sim/stdair/stdairgit/stdair/command/CmdBomManager.hpp"
    "/home/localoriuser/dev/sim/stdair/stdairgit/stdair/command/CmdBomSerialiser.hpp"
    "/home/localoriuser/dev/sim/stdair/stdairgit/stdair/command/CmdAbstract.hpp"
    )
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "devel")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "devel")
  list(APPEND CPACK_ABSOLUTE_DESTINATION_FILES
   "/usr/include/stdair/service/DBSessionManager.hpp;/usr/include/stdair/service/STDAIR_ServiceContext.hpp;/usr/include/stdair/service/ServiceAbstract.hpp;/usr/include/stdair/service/FacServiceAbstract.hpp;/usr/include/stdair/service/Logger.hpp;/usr/include/stdair/service/FacSupervisor.hpp;/usr/include/stdair/service/FacSTDAIRServiceContext.hpp")
FILE(INSTALL DESTINATION "/usr/include/stdair/service" TYPE FILE FILES
    "/home/localoriuser/dev/sim/stdair/stdairgit/stdair/service/DBSessionManager.hpp"
    "/home/localoriuser/dev/sim/stdair/stdairgit/stdair/service/STDAIR_ServiceContext.hpp"
    "/home/localoriuser/dev/sim/stdair/stdairgit/stdair/service/ServiceAbstract.hpp"
    "/home/localoriuser/dev/sim/stdair/stdairgit/stdair/service/FacServiceAbstract.hpp"
    "/home/localoriuser/dev/sim/stdair/stdairgit/stdair/service/Logger.hpp"
    "/home/localoriuser/dev/sim/stdair/stdairgit/stdair/service/FacSupervisor.hpp"
    "/home/localoriuser/dev/sim/stdair/stdairgit/stdair/service/FacSTDAIRServiceContext.hpp"
    )
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "devel")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "runtime")
  FOREACH(file
      "$ENV{DESTDIR}/usr/lib/libstdairuicl.so.99.99.99"
      "$ENV{DESTDIR}/usr/lib/libstdairuicl.so.99.99"
      "$ENV{DESTDIR}/usr/lib/libstdairuicl.so"
      )
    IF(EXISTS "${file}" AND
       NOT IS_SYMLINK "${file}")
      FILE(RPATH_CHECK
           FILE "${file}"
           RPATH "")
    ENDIF()
  ENDFOREACH()
  list(APPEND CPACK_ABSOLUTE_DESTINATION_FILES
   "/usr/lib/libstdairuicl.so.99.99.99;/usr/lib/libstdairuicl.so.99.99;/usr/lib/libstdairuicl.so")
FILE(INSTALL DESTINATION "/usr/lib" TYPE SHARED_LIBRARY FILES
    "/home/localoriuser/dev/sim/stdair/stdairgit/stdair/libstdairuicl.so.99.99.99"
    "/home/localoriuser/dev/sim/stdair/stdairgit/stdair/libstdairuicl.so.99.99"
    "/home/localoriuser/dev/sim/stdair/stdairgit/stdair/libstdairuicl.so"
    )
  FOREACH(file
      "$ENV{DESTDIR}/usr/lib/libstdairuicl.so.99.99.99"
      "$ENV{DESTDIR}/usr/lib/libstdairuicl.so.99.99"
      "$ENV{DESTDIR}/usr/lib/libstdairuicl.so"
      )
    IF(EXISTS "${file}" AND
       NOT IS_SYMLINK "${file}")
      FILE(RPATH_REMOVE
           FILE "${file}")
      IF(CMAKE_INSTALL_DO_STRIP)
        EXECUTE_PROCESS(COMMAND "/usr/bin/strip" "${file}")
      ENDIF(CMAKE_INSTALL_DO_STRIP)
    ENDIF()
  ENDFOREACH()
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "runtime")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "devel")
  list(APPEND CPACK_ABSOLUTE_DESTINATION_FILES
   "/usr/include/stdair/ui/cmdline/SReadline.hpp")
FILE(INSTALL DESTINATION "/usr/include/stdair/ui/cmdline" TYPE FILE FILES "/home/localoriuser/dev/sim/stdair/stdairgit/stdair/ui/cmdline/SReadline.hpp")
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "devel")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "runtime")
  IF(EXISTS "$ENV{DESTDIR}/usr/bin/stdair" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/usr/bin/stdair")
    FILE(RPATH_CHECK
         FILE "$ENV{DESTDIR}/usr/bin/stdair"
         RPATH "")
  ENDIF()
  list(APPEND CPACK_ABSOLUTE_DESTINATION_FILES
   "/usr/bin/stdair")
FILE(INSTALL DESTINATION "/usr/bin" TYPE EXECUTABLE FILES "/home/localoriuser/dev/sim/stdair/stdairgit/stdair/stdair")
  IF(EXISTS "$ENV{DESTDIR}/usr/bin/stdair" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/usr/bin/stdair")
    FILE(RPATH_REMOVE
         FILE "$ENV{DESTDIR}/usr/bin/stdair")
    IF(CMAKE_INSTALL_DO_STRIP)
      EXECUTE_PROCESS(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}/usr/bin/stdair")
    ENDIF(CMAKE_INSTALL_DO_STRIP)
  ENDIF()
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "runtime")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "devel")
  IF(EXISTS "$ENV{DESTDIR}/usr/share/stdair/CMake/stdair-library-depends.cmake")
    FILE(DIFFERENT EXPORT_FILE_CHANGED FILES
         "$ENV{DESTDIR}/usr/share/stdair/CMake/stdair-library-depends.cmake"
         "/home/localoriuser/dev/sim/stdair/stdairgit/stdair/CMakeFiles/Export/_usr/share/stdair/CMake/stdair-library-depends.cmake")
    IF(EXPORT_FILE_CHANGED)
      FILE(GLOB OLD_CONFIG_FILES "$ENV{DESTDIR}/usr/share/stdair/CMake/stdair-library-depends-*.cmake")
      IF(OLD_CONFIG_FILES)
        MESSAGE(STATUS "Old export file \"$ENV{DESTDIR}/usr/share/stdair/CMake/stdair-library-depends.cmake\" will be replaced.  Removing files [${OLD_CONFIG_FILES}].")
        FILE(REMOVE ${OLD_CONFIG_FILES})
      ENDIF(OLD_CONFIG_FILES)
    ENDIF(EXPORT_FILE_CHANGED)
  ENDIF()
  list(APPEND CPACK_ABSOLUTE_DESTINATION_FILES
   "/usr/share/stdair/CMake/stdair-library-depends.cmake")
FILE(INSTALL DESTINATION "/usr/share/stdair/CMake" TYPE FILE FILES "/home/localoriuser/dev/sim/stdair/stdairgit/stdair/CMakeFiles/Export/_usr/share/stdair/CMake/stdair-library-depends.cmake")
  IF("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    list(APPEND CPACK_ABSOLUTE_DESTINATION_FILES
     "/usr/share/stdair/CMake/stdair-library-depends-debug.cmake")
FILE(INSTALL DESTINATION "/usr/share/stdair/CMake" TYPE FILE FILES "/home/localoriuser/dev/sim/stdair/stdairgit/stdair/CMakeFiles/Export/_usr/share/stdair/CMake/stdair-library-depends-debug.cmake")
  ENDIF("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "devel")

