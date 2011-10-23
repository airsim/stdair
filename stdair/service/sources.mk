stdair_svc_h_sources = \
	$(top_srcdir)/stdair/service/ServiceAbstract.hpp \
	$(top_srcdir)/stdair/service/FacSupervisor.hpp \
	$(top_srcdir)/stdair/service/FacServiceAbstract.hpp \
	$(top_srcdir)/stdair/service/FacSTDAIRServiceContext.hpp \
	$(top_srcdir)/stdair/service/Logger.hpp \
	$(top_srcdir)/stdair/service/DBSessionManager.hpp \
	$(top_srcdir)/stdair/service/STDAIR_ServiceContext.hpp
stdair_svc_cc_sources = \
	$(top_srcdir)/stdair/service/ServiceAbstract.cpp \
	$(top_srcdir)/stdair/service/FacSupervisor.cpp \
	$(top_srcdir)/stdair/service/FacServiceAbstract.cpp \
	$(top_srcdir)/stdair/service/FacSTDAIRServiceContext.cpp \
	$(top_srcdir)/stdair/service/Logger.cpp \
	$(top_srcdir)/stdair/service/DBSessionManager.cpp \
	$(top_srcdir)/stdair/service/STDAIR_ServiceContext.cpp \
	$(top_srcdir)/stdair/service/STDAIR_Service.cpp
