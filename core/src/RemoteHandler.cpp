#include "core/RemoteHandler.h"

namespace mixr {
	namespace crfs {
		IMPLEMENT_SUBCLASS(RemoteHandler, "RemoteHandler")
		EMPTY_SLOTTABLE(RemoteHandler)
		//EMPTY_SERIALIZER(RemoteHandler)

        RemoteHandler::RemoteHandler() {
			STANDARD_CONSTRUCTOR()
		}
        void RemoteHandler::copyData(const RemoteHandler& org, const bool cc)
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
        void RemoteHandler::deleteData() {
            BaseClass::deleteData();
        }
		void RemoteHandler::reset() {
			BaseClass::reset();
		}

		void RemoteHandler::updateData(const double dt) {
			// Update internal state
			BaseClass::updateData(dt);
		}


		void RemoteHandler::updateTC(const double dt) {
			
			BaseClass::updateTC(dt);
		}
	}
}