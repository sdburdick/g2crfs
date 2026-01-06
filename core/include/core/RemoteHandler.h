#pragma once

#include <mixr/base/IComponent.hpp>

namespace mixr {
	namespace crfs {
		class RemoteHandler final : public mixr::base::IComponent {
			DECLARE_SUBCLASS(RemoteHandler, mixr::base::IComponent)

		public:
            RemoteHandler();

			void updateTC(const double dt) override;
			void updateData(const double dt)override;
			void reset() override;

		private:
			bool initialized{};
		};
	}
}