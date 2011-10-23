stdair_bas_h_sources = \
	$(top_srcdir)/stdair/basic/float_utils.hpp \
	$(top_srcdir)/stdair/basic/float_utils_google.hpp \
	$(top_srcdir)/stdair/basic/BasTypes.hpp \
	$(top_srcdir)/stdair/basic/BasParserTypes.hpp \
	$(top_srcdir)/stdair/basic/BasParserHelperTypes.hpp \
	$(top_srcdir)/stdair/basic/BasConst_General.hpp \
  $(top_srcdir)/stdair/basic/BasConst_DefaultObject.hpp \
	$(top_srcdir)/stdair/basic/BasConst_Event.hpp \
	$(top_srcdir)/stdair/basic/BasConst_Request.hpp \
	$(top_srcdir)/stdair/basic/BasConst_Inventory.hpp \
	$(top_srcdir)/stdair/basic/BasConst_BookingClass.hpp \
	$(top_srcdir)/stdair/basic/BasConst_Yield.hpp \
	$(top_srcdir)/stdair/basic/BasConst_Period_BOM.hpp \
	$(top_srcdir)/stdair/basic/BasConst_TravelSolution.hpp \
	$(top_srcdir)/stdair/basic/BasConst_BomDisplay.hpp \
	$(top_srcdir)/stdair/basic/StructAbstract.hpp \
	$(top_srcdir)/stdair/basic/BasChronometer.hpp \
	$(top_srcdir)/stdair/basic/YieldRange.hpp \
	$(top_srcdir)/stdair/basic/BasFileMgr.hpp \
	$(top_srcdir)/stdair/basic/BasLogParams.hpp \
	$(top_srcdir)/stdair/basic/BasDBParams.hpp \
	$(top_srcdir)/stdair/basic/PassengerType.hpp \
	$(top_srcdir)/stdair/basic/EventType.hpp \
	$(top_srcdir)/stdair/basic/SampleType.hpp \
	$(top_srcdir)/stdair/basic/ServiceInitialisationType.hpp \
	$(top_srcdir)/stdair/basic/ForecastingMethod.hpp \
	$(top_srcdir)/stdair/basic/RandomGeneration.hpp \
	$(top_srcdir)/stdair/basic/ProgressStatus.hpp \
	$(top_srcdir)/stdair/basic/ProgressStatusSet.hpp \
	$(top_srcdir)/stdair/basic/DemandGenerationMethod.hpp\
	$(top_srcdir)/stdair/basic/PartnershipTechnique.hpp\
	$(top_srcdir)/stdair/basic/ContinuousAttributeLite.hpp\
	$(top_srcdir)/stdair/basic/DictionaryManager.hpp
stdair_bas_cc_sources = \
	$(top_srcdir)/stdair/basic/BasConst.cpp \
	$(top_srcdir)/stdair/basic/BasChronometer.cpp \
	$(top_srcdir)/stdair/basic/YieldRange.cpp \
	$(top_srcdir)/stdair/basic/BasFileMgr.cpp \
	$(top_srcdir)/stdair/basic/BasLogParams.cpp \
	$(top_srcdir)/stdair/basic/BasDBParams.cpp \
	$(top_srcdir)/stdair/basic/PassengerType.cpp \
	$(top_srcdir)/stdair/basic/EventType.cpp \
	$(top_srcdir)/stdair/basic/SampleType.cpp \
	$(top_srcdir)/stdair/basic/ServiceInitialisationType.cpp \
	$(top_srcdir)/stdair/basic/ForecastingMethod.cpp \
	$(top_srcdir)/stdair/basic/RandomGeneration.cpp \
	$(top_srcdir)/stdair/basic/ProgressStatus.cpp \
	$(top_srcdir)/stdair/basic/ProgressStatusSet.cpp \
	$(top_srcdir)/stdair/basic/DemandGenerationMethod.cpp\
	$(top_srcdir)/stdair/basic/PartnershipTechnique.cpp\
	$(top_srcdir)/stdair/basic/DictionaryManager.cpp
