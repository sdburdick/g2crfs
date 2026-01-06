#include "core/EmitterSettingsManager.h"

namespace mixr {
	namespace crfs {
		IMPLEMENT_SUBCLASS(EmitterSettingsManager, "EmitterSettingsManager")
		EMPTY_SLOTTABLE(EmitterSettingsManager)
		//EMPTY_SERIALIZER(EmitterSettingsManager)

        EmitterSettingsManager::EmitterSettingsManager() {
			STANDARD_CONSTRUCTOR()
		}
        void EmitterSettingsManager::copyData(const EmitterSettingsManager& org, const bool cc)
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
        void EmitterSettingsManager::deleteData() {
            BaseClass::deleteData();
        }
		void EmitterSettingsManager::reset() {
			BaseClass::reset();
		}


		void EmitterSettingsManager::updateData(const double dt) {
			// Update internal state
			BaseClass::updateData(dt);
		}


		void EmitterSettingsManager::updateTC(const double dt) {
			
			BaseClass::updateTC(dt);
		}
	}
}