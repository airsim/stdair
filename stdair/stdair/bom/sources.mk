bom_h_sources = \
		$(top_srcdir)/stdair/bom/BomList.hpp \
		$(top_srcdir)/stdair/bom/BomMap.hpp \
		$(top_srcdir)/stdair/bom/BomKey.hpp \
		$(top_srcdir)/stdair/bom/BomRootKey.hpp \
		$(top_srcdir)/stdair/bom/InventoryKey.hpp \
		$(top_srcdir)/stdair/bom/FlightDateKey.hpp \
		$(top_srcdir)/stdair/bom/LegDateKey.hpp \
		$(top_srcdir)/stdair/bom/LegCabinKey.hpp \
		$(top_srcdir)/stdair/bom/SegmentDateKey.hpp \
		$(top_srcdir)/stdair/bom/SegmentCabinKey.hpp \
		$(top_srcdir)/stdair/bom/BookingClassKey.hpp \
		$(top_srcdir)/stdair/bom/NetworkKey.hpp \
		$(top_srcdir)/stdair/bom/NetworkDateKey.hpp \
		$(top_srcdir)/stdair/bom/AirportDateKey.hpp \
		$(top_srcdir)/stdair/bom/OutboundPathKey.hpp \
		$(top_srcdir)/stdair/bom/AirlineFeatureSetKey.hpp \
		$(top_srcdir)/stdair/bom/AirlineFeatureKey.hpp \
		$(top_srcdir)/stdair/bom/DemandStreamKey.hpp \
		$(top_srcdir)/stdair/bom/BomRootTypes.hpp \
		$(top_srcdir)/stdair/bom/BomRoot.hpp \
		$(top_srcdir)/stdair/bom/BomContent.hpp \
		$(top_srcdir)/stdair/bom/BomRootContent.hpp \
		$(top_srcdir)/stdair/bom/BomStopContent.hpp \
		$(top_srcdir)/stdair/bom/BomStructure.hpp \
		$(top_srcdir)/stdair/bom/BomRootStructure.hpp \
		$(top_srcdir)/stdair/bom/BomStopStructure.hpp \
		$(top_srcdir)/stdair/bom/Inventory.hpp \
		$(top_srcdir)/stdair/bom/InventoryContent.hpp \
		$(top_srcdir)/stdair/bom/InventoryTypes.hpp \
		$(top_srcdir)/stdair/bom/InventoryStructure.hpp \
		$(top_srcdir)/stdair/bom/FlightDate.hpp \
		$(top_srcdir)/stdair/bom/FlightDateContent.hpp \
		$(top_srcdir)/stdair/bom/FlightDateTypes.hpp \
		$(top_srcdir)/stdair/bom/FlightDateStructure.hpp \
		$(top_srcdir)/stdair/bom/SegmentDate.hpp \
		$(top_srcdir)/stdair/bom/SegmentDateContent.hpp \
		$(top_srcdir)/stdair/bom/SegmentDateTypes.hpp \
		$(top_srcdir)/stdair/bom/SegmentDateStructure.hpp \
		$(top_srcdir)/stdair/bom/LegDate.hpp \
		$(top_srcdir)/stdair/bom/LegDateContent.hpp \
		$(top_srcdir)/stdair/bom/LegDateTypes.hpp \
		$(top_srcdir)/stdair/bom/LegDateStructure.hpp \
		$(top_srcdir)/stdair/bom/SegmentCabin.hpp \
		$(top_srcdir)/stdair/bom/SegmentCabinContent.hpp \
		$(top_srcdir)/stdair/bom/SegmentCabinTypes.hpp \
		$(top_srcdir)/stdair/bom/SegmentCabinStructure.hpp \
		$(top_srcdir)/stdair/bom/LegCabin.hpp \
		$(top_srcdir)/stdair/bom/LegCabinContent.hpp \
		$(top_srcdir)/stdair/bom/LegCabinTypes.hpp \
		$(top_srcdir)/stdair/bom/LegCabinStructure.hpp \
		$(top_srcdir)/stdair/bom/BookingClass.hpp \
		$(top_srcdir)/stdair/bom/BookingClassContent.hpp \
		$(top_srcdir)/stdair/bom/BookingClassTypes.hpp \
		$(top_srcdir)/stdair/bom/BookingClassStructure.hpp \
		$(top_srcdir)/stdair/bom/Network.hpp \
		$(top_srcdir)/stdair/bom/NetworkContent.hpp \
		$(top_srcdir)/stdair/bom/NetworkTypes.hpp \
		$(top_srcdir)/stdair/bom/NetworkStructure.hpp \
		$(top_srcdir)/stdair/bom/NetworkDate.hpp \
		$(top_srcdir)/stdair/bom/NetworkDateContent.hpp \
		$(top_srcdir)/stdair/bom/NetworkDateTypes.hpp \
		$(top_srcdir)/stdair/bom/NetworkDateStructure.hpp \
		$(top_srcdir)/stdair/bom/AirportDate.hpp \
		$(top_srcdir)/stdair/bom/AirportDateContent.hpp \
		$(top_srcdir)/stdair/bom/AirportDateTypes.hpp \
		$(top_srcdir)/stdair/bom/AirportDateStructure.hpp \
		$(top_srcdir)/stdair/bom/OutboundPath.hpp \
		$(top_srcdir)/stdair/bom/OutboundPathContent.hpp \
		$(top_srcdir)/stdair/bom/OutboundPathTypes.hpp \
		$(top_srcdir)/stdair/bom/OutboundPathStructure.hpp \
		$(top_srcdir)/stdair/bom/AirlineFeatureSet.hpp \
		$(top_srcdir)/stdair/bom/AirlineFeatureSetContent.hpp \
		$(top_srcdir)/stdair/bom/AirlineFeatureSetTypes.hpp \
		$(top_srcdir)/stdair/bom/AirlineFeatureSetStructure.hpp \
		$(top_srcdir)/stdair/bom/AirlineFeature.hpp \
		$(top_srcdir)/stdair/bom/AirlineFeatureContent.hpp \
		$(top_srcdir)/stdair/bom/AirlineFeatureTypes.hpp \
		$(top_srcdir)/stdair/bom/AirlineFeatureStructure.hpp \
		$(top_srcdir)/stdair/bom/BomChildrenHolder.hpp \
		$(top_srcdir)/stdair/bom/BomChildrenHolderImp.hpp \
		$(top_srcdir)/stdair/bom/BomIterator.hpp \
		$(top_srcdir)/stdair/bom/OptimizerStruct.hpp \
		$(top_srcdir)/stdair/bom/DoWStruct.hpp \
		$(top_srcdir)/stdair/bom/TravelSolutionStruct.hpp \
		$(top_srcdir)/stdair/bom/TravelSolutionTypes.hpp \
		$(top_srcdir)/stdair/bom/BookingRequestStruct.hpp \
		$(top_srcdir)/stdair/bom/AirlineStruct.hpp \
		$(top_srcdir)/stdair/bom/DemandStreamStructure.hpp \
		$(top_srcdir)/stdair/bom/DemandStreamContent.hpp \
		$(top_srcdir)/stdair/bom/DemandStream.hpp \
		$(top_srcdir)/stdair/bom/DemandStreamTypes.hpp \
		$(top_srcdir)/stdair/bom/EventStruct.hpp \
		$(top_srcdir)/stdair/bom/EventQueue.hpp \
		$(top_srcdir)/stdair/bom/EventTypes.hpp \
		$(top_srcdir)/stdair/bom/BomManager.hpp \
		$(top_srcdir)/stdair/bom/Structure.hpp \
		$(top_srcdir)/stdair/bom/BRKey.hpp \
		$(top_srcdir)/stdair/bom/BRTypes.hpp \
		$(top_srcdir)/stdair/bom/IN.hpp \
		$(top_srcdir)/stdair/bom/INKey.hpp \
		$(top_srcdir)/stdair/bom/FDTypes.hpp \
		$(top_srcdir)/stdair/bom/FDKey.hpp \
		$(top_srcdir)/stdair/bom/NDTypes.hpp \
		$(top_srcdir)/stdair/bom/NDKey.hpp \
		$(top_srcdir)/stdair/bom/NDTypes.hpp
bom_cc_sources = \
		$(top_srcdir)/stdair/bom/BomRootKey.cpp \
		$(top_srcdir)/stdair/bom/InventoryKey.cpp \
		$(top_srcdir)/stdair/bom/FlightDateKey.cpp \
		$(top_srcdir)/stdair/bom/LegDateKey.cpp \
		$(top_srcdir)/stdair/bom/LegCabinKey.cpp \
		$(top_srcdir)/stdair/bom/SegmentDateKey.cpp \
		$(top_srcdir)/stdair/bom/SegmentCabinKey.cpp \
		$(top_srcdir)/stdair/bom/BookingClassKey.cpp \
		$(top_srcdir)/stdair/bom/NetworkKey.cpp \
		$(top_srcdir)/stdair/bom/NetworkDateKey.cpp \
		$(top_srcdir)/stdair/bom/AirportDateKey.cpp \
		$(top_srcdir)/stdair/bom/OutboundPathKey.cpp \
		$(top_srcdir)/stdair/bom/AirlineFeatureSetKey.cpp \
		$(top_srcdir)/stdair/bom/AirlineFeatureKey.cpp \
		$(top_srcdir)/stdair/bom/DemandStreamKey.cpp \
		$(top_srcdir)/stdair/bom/BomRoot.cpp \
		$(top_srcdir)/stdair/bom/BomRootContent.cpp \
		$(top_srcdir)/stdair/bom/Inventory.cpp \
		$(top_srcdir)/stdair/bom/InventoryContent.cpp \
		$(top_srcdir)/stdair/bom/FlightDate.cpp \
		$(top_srcdir)/stdair/bom/FlightDateContent.cpp \
		$(top_srcdir)/stdair/bom/SegmentDate.cpp \
		$(top_srcdir)/stdair/bom/SegmentDateContent.cpp \
		$(top_srcdir)/stdair/bom/LegDate.cpp \
		$(top_srcdir)/stdair/bom/LegDateContent.cpp \
		$(top_srcdir)/stdair/bom/SegmentCabin.cpp \
		$(top_srcdir)/stdair/bom/SegmentCabinContent.cpp \
		$(top_srcdir)/stdair/bom/LegCabin.cpp \
		$(top_srcdir)/stdair/bom/LegCabinContent.cpp \
		$(top_srcdir)/stdair/bom/BookingClass.cpp \
		$(top_srcdir)/stdair/bom/BookingClassContent.cpp \
		$(top_srcdir)/stdair/bom/Network.cpp \
		$(top_srcdir)/stdair/bom/NetworkContent.cpp \
		$(top_srcdir)/stdair/bom/NetworkDate.cpp \
		$(top_srcdir)/stdair/bom/NetworkDateContent.cpp \
		$(top_srcdir)/stdair/bom/AirportDate.cpp \
		$(top_srcdir)/stdair/bom/AirportDateContent.cpp \
		$(top_srcdir)/stdair/bom/OutboundPath.cpp \
		$(top_srcdir)/stdair/bom/OutboundPathContent.cpp \
		$(top_srcdir)/stdair/bom/AirlineFeatureSet.cpp \
		$(top_srcdir)/stdair/bom/AirlineFeatureSetContent.cpp \
		$(top_srcdir)/stdair/bom/AirlineFeature.cpp \
		$(top_srcdir)/stdair/bom/AirlineFeatureContent.cpp \
		$(top_srcdir)/stdair/bom/OptimizerStruct.cpp \
		$(top_srcdir)/stdair/bom/DoWStruct.cpp \
		$(top_srcdir)/stdair/bom/TravelSolutionStruct.cpp \
		$(top_srcdir)/stdair/bom/BookingRequestStruct.cpp \
		$(top_srcdir)/stdair/bom/AirlineStruct.cpp \
		$(top_srcdir)/stdair/bom/DemandStreamContent.cpp \
		$(top_srcdir)/stdair/bom/DemandStream.cpp \
		$(top_srcdir)/stdair/bom/EventStruct.cpp \
		$(top_srcdir)/stdair/bom/EventQueue.cpp \
		$(top_srcdir)/stdair/bom/BomManager.cpp
