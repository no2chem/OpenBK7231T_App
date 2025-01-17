#ifndef __PREFABMANAGER_H__
#define __PREFABMANAGER_H__

#include "sim_local.h"
#include "PrefabManager.h"

class PrefabManager {
	class CSimulator *sim;
	TArray<class CShape*> prefabs;

	class CShape *generateLED_CW();
	class CShape *generateLED_RGB();
	class CShape *generateBulb();
	class CShape *generateWB3S();
	class CShape *generateButton();
	class CShape *generateTest();
	class CShape *generateGND();
	class CShape *generateVDD();
public:
	PrefabManager(CSimulator *ps) {
		sim = ps;
	}
	void createDefaultPrefabs();
	void addPrefab(CShape *o);
	CShape *findPrefab(const char *name);
	CShape *instantiatePrefab(const char *name);

};
#endif
