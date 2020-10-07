file(GLOB SRC "*.cpp")
add_executable(packet_inspector ${SRC} ../include/protocols.h ../include/network_inspector.h network_inspector.cpp ../include/swap6.h ../include/stats.h)
