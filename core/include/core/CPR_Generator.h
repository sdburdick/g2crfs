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
            float compute_value_for(const Client& c) {
                // Example: client-specific data
                return static_cast<float>(seq_) * 0.01f;
            }

            void runNetworkThread();
            
            std::unique_ptr <std::thread> udpThread;
            
            std::unique_ptr <udp::socket> socket_ptr;
            std::vector<Client> clients_;
            uint32_t seq_;

            
		};
	}
}