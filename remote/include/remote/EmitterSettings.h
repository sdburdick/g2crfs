#pragma once

#include <mixr/base/IComponent.hpp>

namespace mixr {
	namespace crfs {
		class EmitterSettings final : public mixr::base::IComponent {
			DECLARE_SUBCLASS(EmitterSettings, mixr::base::IComponent)

		public:
            EmitterSettings();

			void updateTC(const double dt) override;
			void updateData(const double dt)override;
			void reset() override;

		private:
			bool initialized{};
		};
	}
}