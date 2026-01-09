#include "core/CPR_Generator.h"


//builds and sends the CRFS Packet for Receivers, or CPR.  Determines what energy stimulated each definied receiver -
//what power, what frequency, what angle, and what time of arrival

namespace mixr {
    namespace crfs {
        IMPLEMENT_SUBCLASS(CPR_Generator, "CPR_Generator") 
        EMPTY_SLOTTABLE(CPR_Generator)
        //EMPTY_SERIALIZER(CPR_Generator)

        CPR_Generator::CPR_Generator() : io_context(){
              
            STANDARD_CONSTRUCTOR()
            
            udp_endpoint = std::make_shared<asio::ip::udp::endpoint>(asio::ip::make_address(interface_ip), udp_port);
            socket_ptr = std::make_unique<asio::ip::udp::socket>(io_context, *udp_endpoint);
            udpThread = std::move(std::make_unique<std::thread>(std::thread(&CPR_Generator::runNetworkThread, this)));
		}
        void CPR_Generator::copyData(const CPR_Generator& org, const bool cc)
        {
            BaseClass::copyData(org, cc);
            if (cc) {
                //Resource Allocation : The object knows it must allocate fresh memory for any internal components rather than just pointing to org memory.
            }
            else {
                //need to delete existing pointers to prevent memory leaks
            }
            // this->myVariable = org.myVariable;
        }
        void CPR_Generator::deleteData() {
            io_context.stop();
            if (udpThread->joinable()) udpThread->join();
            BaseClass::deleteData();

        }
		void CPR_Generator::reset() {
			BaseClass::reset();
            //this would have to be coordinated with the subscriber
            add_client(udp::endpoint(asio::ip::make_address("127.0.0.1"), 5001));
		}

        void CPR_Generator::add_client(const udp::endpoint& ep) {
            Client c{};
            c.endpoint = ep;
            clients_.push_back(c);
        }
        
        void CPR_Generator::runNetworkThread() {
            SetThreadDescription(GetCurrentThread(), L"CPR_Generator IO Context");
            io_context.run();
        }

        float CPR_Generator::compute_value_for(const Client& c) {
            // Example: client-specific data
            return static_cast<float>(seq_) * 0.01f;
        }

        void CPR_Generator::tick() {
            const uint64_t now_ns =
                duration_cast<std::chrono::nanoseconds>(
                    std::chrono::steady_clock::now().time_since_epoch()
                ).count();
            
            for (auto& c : clients_) {
                c.packet.seq = seq_;
                c.packet.timestamp_ns = now_ns;
                c.packet.value = compute_value_for(c);


                socket_ptr->async_send_to(
                    asio::buffer(&c.packet, sizeof(CPR_Packet)),
                    c.endpoint,
                    [](std::error_code /*ec*/, std::size_t /*bytes*/) {
                        // Intentionally ignore errors for real-time data
                    }
                );
            }

            ++seq_;
        }

		void CPR_Generator::updateData(const double dt) {
			// Update internal state
			BaseClass::updateData(dt);
		}


		void CPR_Generator::updateTC(const double dt) {
            tick();
			BaseClass::updateTC(dt);
		}
	}
}