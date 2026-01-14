#pragma once

#include <mixr/base/IComponent.hpp>
#include "CRFS_Packet_for_Receivers.h"

#include "shared/asio-1.36.0/asio.hpp"
#include <chrono>
#include <thread>
#include <vector>
#include <atomic>
#include <string>

using asio::ip::udp;

namespace mixr {
	namespace crfs {
        struct Client {
            asio::ip::udp::endpoint endpoint;
            CPR_Packet packet;
        };

		class CPR_Generator final : public mixr::base::IComponent {
			DECLARE_SUBCLASS(CPR_Generator, mixr::base::IComponent)

		public:
            CPR_Generator();

			void updateTC(const double dt) override;
			void updateData(const double dt)override;
			void reset() override;


            void add_client(const udp::endpoint& ep);
            void tick();


		private:

            asio::io_context io_context;
            float compute_value_for(const Client& c);

            void runNetworkThread();
            
            std::unique_ptr <std::thread> udpThread;
            
            std::shared_ptr<asio::ip::udp::endpoint> udp_endpoint;

            std::string interface_ip = "127.0.0.1";
            //std::string interface_ip = "192.168.4.47"; //outgoing IP interface on this computer.  Needs to be able to connect to the net you are transmitting to
            unsigned short udp_port = 5100; //outgoing port on this computer.  does not match the connected clients, just needs to be free and usable

            std::unique_ptr <udp::socket> socket_ptr;
            std::vector<Client> clients_;
            uint32_t seq_;

            
		};
	}
}