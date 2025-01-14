#ifdef WINDOWS
#include "Controller_SimulatorLink.h"
#include "Shape.h"
#include "Junction.h"
#include "sim_import.h"


CControllerSimulatorLink::CControllerSimulatorLink() {

}
class CControllerBase *CControllerSimulatorLink::cloneController(class CShape *origOwner, class CShape *newOwner) {
	CControllerSimulatorLink *r = new CControllerSimulatorLink();
	for (int i = 0; i < related.size(); i++) {
		r->addRelatedJunction(newOwner->findShapeByName_r(related[i]->getName())->asJunction());
	}
	return r;
}
void CControllerSimulatorLink::onDrawn() {
	for (int i = 0; i < related.size(); i++) {
		CJunction *ju = related[i];
		int gpio = ju->getGPIO();
		float v = ju->getVoltage();
		if (gpio < 0)
			continue;
		if (!SIM_IsPinInput(gpio)) {
			bool bVal = SIM_GetSimulatedPinValue(gpio);
			ju->setCurrentSource(true);
			if (bVal)
				ju->setVoltage(3.3f);
			else
				ju->setVoltage(0.0f);
		}
		else {
			if (ju->getVisitCount() == 0)
				v = 3.3f;
			SIM_SetSimulatedPinValue(gpio, v > 1.5f);
			ju->setCurrentSource(false);
		}
	}
}

#endif
