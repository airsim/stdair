stdair_bom_h_sources = \
		$(top_srcdir)/stdair/bom/BomAbstract.hpp \
		$(top_srcdir)/stdair/bom/key_types.hpp \
		$(top_srcdir)/stdair/bom/KeyAbstract.hpp \
		$(top_srcdir)/stdair/bom/BomKeyManager.hpp \
		$(top_srcdir)/stdair/bom/ParsedKey.hpp \
		$(top_srcdir)/stdair/bom/BomManager.hpp \
		$(top_srcdir)/stdair/bom/BomRetriever.hpp \
		$(top_srcdir)/stdair/bom/BomArchive.hpp \
		$(top_srcdir)/stdair/bom/BomDisplay.hpp \
		$(top_srcdir)/stdair/bom/BomHolderKey.hpp \
		$(top_srcdir)/stdair/bom/BomRootKey.hpp \
		$(top_srcdir)/stdair/bom/YieldStoreKey.hpp \
		$(top_srcdir)/stdair/bom/InventoryKey.hpp \
		$(top_srcdir)/stdair/bom/FlightDateKey.hpp \
		$(top_srcdir)/stdair/bom/LegDateKey.hpp \
		$(top_srcdir)/stdair/bom/LegCabinKey.hpp \
		$(top_srcdir)/stdair/bom/SegmentDateKey.hpp \
		$(top_srcdir)/stdair/bom/SegmentCabinKey.hpp \
		$(top_srcdir)/stdair/bom/FareFamilyKey.hpp \
		$(top_srcdir)/stdair/bom/BookingClassKey.hpp \
		$(top_srcdir)/stdair/bom/BucketKey.hpp \
		$(top_srcdir)/stdair/bom/FlightPeriodKey.hpp \
		$(top_srcdir)/stdair/bom/SegmentPeriodKey.hpp \
		$(top_srcdir)/stdair/bom/AirlineFeatureKey.hpp \
		$(top_srcdir)/stdair/bom/EventQueueKey.hpp \
		$(top_srcdir)/stdair/bom/InventoryTypes.hpp \
		$(top_srcdir)/stdair/bom/FlightDateTypes.hpp \
		$(top_srcdir)/stdair/bom/SegmentDateTypes.hpp \
		$(top_srcdir)/stdair/bom/LegDateTypes.hpp \
		$(top_srcdir)/stdair/bom/SegmentCabinTypes.hpp \
		$(top_srcdir)/stdair/bom/FareFamilyTypes.hpp \
		$(top_srcdir)/stdair/bom/LegCabinTypes.hpp \
		$(top_srcdir)/stdair/bom/BookingClassTypes.hpp \
		$(top_srcdir)/stdair/bom/BucketTypes.hpp \
		$(top_srcdir)/stdair/bom/FlightPeriodTypes.hpp \
		$(top_srcdir)/stdair/bom/SegmentPeriodTypes.hpp \
		$(top_srcdir)/stdair/bom/AirlineFeatureTypes.hpp \
		$(top_srcdir)/stdair/bom/TravelSolutionTypes.hpp \
		$(top_srcdir)/stdair/bom/VirtualClassTypes.hpp \
		$(top_srcdir)/stdair/bom/FareOptionTypes.hpp \
		$(top_srcdir)/stdair/bom/BookingRequestTypes.hpp \
		$(top_srcdir)/stdair/bom/OptimisationNotificationTypes.hpp \
		$(top_srcdir)/stdair/bom/EventQueueTypes.hpp \
		$(top_srcdir)/stdair/bom/EventTypes.hpp \
		$(top_srcdir)/stdair/bom/YieldStoreTypes.hpp \
		$(top_srcdir)/stdair/bom/BomHolder.hpp \
		$(top_srcdir)/stdair/bom/BomRoot.hpp \
		$(top_srcdir)/stdair/bom/Inventory.hpp \
		$(top_srcdir)/stdair/bom/FlightDate.hpp \
		$(top_srcdir)/stdair/bom/SegmentDate.hpp \
		$(top_srcdir)/stdair/bom/LegDate.hpp \
		$(top_srcdir)/stdair/bom/SegmentCabin.hpp \
		$(top_srcdir)/stdair/bom/FareFamily.hpp \
		$(top_srcdir)/stdair/bom/LegCabin.hpp \
		$(top_srcdir)/stdair/bom/BookingClass.hpp \
		$(top_srcdir)/stdair/bom/Bucket.hpp \
		$(top_srcdir)/stdair/bom/FlightPeriod.hpp \
		$(top_srcdir)/stdair/bom/SegmentPeriod.hpp \
		$(top_srcdir)/stdair/bom/AirlineFeature.hpp \
		$(top_srcdir)/stdair/bom/YieldStore.hpp \
		$(top_srcdir)/stdair/bom/DoWStruct.hpp \
		$(top_srcdir)/stdair/bom/PeriodStruct.hpp \
		$(top_srcdir)/stdair/bom/TravelSolutionStruct.hpp \
		$(top_srcdir)/stdair/bom/VirtualClassStruct.hpp \
		$(top_srcdir)/stdair/bom/FareOptionStruct.hpp \
		$(top_srcdir)/stdair/bom/BookingRequestStruct.hpp \
		$(top_srcdir)/stdair/bom/OptimisationNotificationStruct.hpp \
		$(top_srcdir)/stdair/bom/AirlineStruct.hpp \
		$(top_srcdir)/stdair/bom/EventStruct.hpp \
		$(top_srcdir)/stdair/bom/EventQueue.hpp \
		$(top_srcdir)/stdair/bom/AirportPair.hpp \
		$(top_srcdir)/stdair/bom/AirportPairKey.hpp \
		$(top_srcdir)/stdair/bom/AirportPairTypes.hpp \
		$(top_srcdir)/stdair/bom/PosChannel.hpp \
		$(top_srcdir)/stdair/bom/PosChannelKey.hpp \
		$(top_srcdir)/stdair/bom/PosChannelTypes.hpp \
		$(top_srcdir)/stdair/bom/AirlineClassList.hpp \
		$(top_srcdir)/stdair/bom/AirlineClassListKey.hpp \
		$(top_srcdir)/stdair/bom/AirlineClassListTypes.hpp \
		$(top_srcdir)/stdair/bom/DatePeriod.hpp \
		$(top_srcdir)/stdair/bom/DatePeriodKey.hpp \
		$(top_srcdir)/stdair/bom/DatePeriodTypes.hpp \
		$(top_srcdir)/stdair/bom/TimePeriod.hpp \
		$(top_srcdir)/stdair/bom/TimePeriodKey.hpp \
		$(top_srcdir)/stdair/bom/TimePeriodTypes.hpp
stdair_bom_cc_sources = \
		$(top_srcdir)/stdair/bom/BomKeyManager.cpp \
		$(top_srcdir)/stdair/bom/ParsedKey.cpp \
		$(top_srcdir)/stdair/bom/BomManager.cpp \
		$(top_srcdir)/stdair/bom/BomRetriever.cpp \
		$(top_srcdir)/stdair/bom/BomArchive.cpp \
		$(top_srcdir)/stdair/bom/BomDisplay.cpp \
		$(top_srcdir)/stdair/bom/BomHolderKey.cpp \
		$(top_srcdir)/stdair/bom/BomRootKey.cpp \
		$(top_srcdir)/stdair/bom/YieldStoreKey.cpp \
		$(top_srcdir)/stdair/bom/InventoryKey.cpp \
		$(top_srcdir)/stdair/bom/FlightDateKey.cpp \
		$(top_srcdir)/stdair/bom/LegDateKey.cpp \
		$(top_srcdir)/stdair/bom/LegCabinKey.cpp \
		$(top_srcdir)/stdair/bom/SegmentDateKey.cpp \
		$(top_srcdir)/stdair/bom/SegmentCabinKey.cpp \
		$(top_srcdir)/stdair/bom/FareFamilyKey.cpp \
		$(top_srcdir)/stdair/bom/BookingClassKey.cpp \
		$(top_srcdir)/stdair/bom/BucketKey.cpp \
		$(top_srcdir)/stdair/bom/FlightPeriodKey.cpp \
		$(top_srcdir)/stdair/bom/SegmentPeriodKey.cpp \
		$(top_srcdir)/stdair/bom/AirlineFeatureKey.cpp \
		$(top_srcdir)/stdair/bom/EventQueueKey.cpp \
		$(top_srcdir)/stdair/bom/BomRoot.cpp \
		$(top_srcdir)/stdair/bom/Inventory.cpp \
		$(top_srcdir)/stdair/bom/FlightDate.cpp \
		$(top_srcdir)/stdair/bom/SegmentDate.cpp \
		$(top_srcdir)/stdair/bom/LegDate.cpp \
		$(top_srcdir)/stdair/bom/SegmentCabin.cpp \
		$(top_srcdir)/stdair/bom/FareFamily.cpp \
		$(top_srcdir)/stdair/bom/LegCabin.cpp \
		$(top_srcdir)/stdair/bom/BookingClass.cpp \
		$(top_srcdir)/stdair/bom/Bucket.cpp \
		$(top_srcdir)/stdair/bom/FlightPeriod.cpp \
		$(top_srcdir)/stdair/bom/SegmentPeriod.cpp \
		$(top_srcdir)/stdair/bom/AirlineFeature.cpp \
		$(top_srcdir)/stdair/bom/YieldStore.cpp \
		$(top_srcdir)/stdair/bom/DoWStruct.cpp \
		$(top_srcdir)/stdair/bom/PeriodStruct.cpp \
		$(top_srcdir)/stdair/bom/TravelSolutionStruct.cpp \
		$(top_srcdir)/stdair/bom/VirtualClassStruct.cpp \
		$(top_srcdir)/stdair/bom/FareOptionStruct.cpp \
		$(top_srcdir)/stdair/bom/BookingRequestStruct.cpp \
		$(top_srcdir)/stdair/bom/OptimisationNotificationStruct.cpp \
		$(top_srcdir)/stdair/bom/AirlineStruct.cpp \
		$(top_srcdir)/stdair/bom/EventStruct.cpp \
		$(top_srcdir)/stdair/bom/EventQueue.cpp \
		$(top_srcdir)/stdair/bom/AirportPair.cpp \
		$(top_srcdir)/stdair/bom/AirportPairKey.cpp \
		$(top_srcdir)/stdair/bom/PosChannel.cpp \
		$(top_srcdir)/stdair/bom/PosChannelKey.cpp \
		$(top_srcdir)/stdair/bom/AirlineClassList.cpp \
		$(top_srcdir)/stdair/bom/AirlineClassListKey.cpp \
		$(top_srcdir)/stdair/bom/DatePeriod.cpp \
		$(top_srcdir)/stdair/bom/DatePeriodKey.cpp \
		$(top_srcdir)/stdair/bom/TimePeriod.cpp \
		$(top_srcdir)/stdair/bom/TimePeriodKey.cpp

