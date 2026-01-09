#include "remote/CPR_Receiver.h"

namespace mixr {
	namespace crfs {
		IMPLEMENT_SUBCLASS(CPR_Receiver, "CPR_Receiver")
		EMPTY_SLOTTABLE(CPR_Receiver)
		//EMPTY_SERIALIZER(CPR_Receiver)

        CPR_Receiver::CPR_Receiver() : io_context(){
			STANDARD_CONSTRUCTOR()
            
                
            udp_endpoint = std::make_shared<asio::ip::udp::endpoint> (asio::ip::make_address(interface_ip), udp_port);
            
            udp_socket = std::make_unique<asio::ip::udp::socket>(io_context, *udp_endpoint);

            monitor_thread = std::make_unique<std::thread>([&]() {
#ifdef _WIN32
                SetThreadDescription(GetCurrentThread(), L"UDP_Monitor_Thread");
#endif

                while (keep_running) {
                    // Wait for 1 second
                    std::this_thread::sleep_for(std::chrono::seconds(1));

                    // Get the current count and reset it to 0 simultaneously
                    uint32_t current_pps = message_count.exchange(0);

                    // Report to console
                    std::cout << "[Monitor] Packets received in last second: " << current_pps << " Hz\n" << std::endl;
                }
            });

		}
        void CPR_Receiver::copyData(const CPR_Receiver& org, const bool cc)
        {
            if (cc) {
                //Resource Allocation : The object knows it must allocate fresh memory for any internal components rather than just pointing to org memory.
            }
            else {
                //need to delete existing pointers to prevent memory leaks
            }
            // 1. Call the base class copyData first!
            BaseClass::copyData(org);

            // 2. Copy local
            // this->myVariable = org.myVariable;
        }
        void CPR_Receiver::deleteData() {
            BaseClass::deleteData();
            keep_running = false;
        }

		void CPR_Receiver::reset() {
			BaseClass::reset();
            //workerThread is saved in the class, need to spawn off a lambda function to run it.  It will take control of the socket we are using, so move the unique pointer
            if (workerThread && workerThread->joinable()) {

            }
            else {
                workerThread = std::make_unique<std::thread>([this, socket_ptr = std::shared_ptr<udp::socket>(std::move(udp_socket))]() {
#ifdef _WIN32
                    SetThreadDescription(GetCurrentThread(), L"CPR_Receiver");
#endif

                    auto last_time = std::chrono::steady_clock::now();
                    while (keep_running) {
                        try {
                            CPR_Packet incoming_packet;
                            incoming_packet.seq = 0;
                            incoming_packet.timestamp_ns = 0;
                            incoming_packet.value = 0;

                            udp::endpoint remote_endpoint;

                            size_t len = socket_ptr->receive_from(
                                asio::buffer(&incoming_packet, sizeof(CPR_Packet)),
                                remote_endpoint
                            );

                            if (len == sizeof(CPR_Packet)) {
                                message_count++;
                                //  std::cout << "Received Seq: " << incoming_packet.seq
                                  //    << " | TS: " << incoming_packet.timestamp_ns
                                    //  << " | Val: " << incoming_packet.value << std::endl;
                            }
                            else {
                                std::cerr << "Received packet of unexpected size: " << len << " bytes" << std::endl;
                            }
                        }
                        catch (std::exception& e) {
                            std::cerr << "Error: " << e.what() << std::endl;
                        }
                    }
                    });//closes thread running lambda
            }
            
                
		}


        void CPR_Receiver::updateData(const double dt) {
            // Update internal state
            BaseClass::updateData(dt);

            
		}


		void CPR_Receiver::updateTC(const double dt) {
			
			BaseClass::updateTC(dt);
		}
	}
}