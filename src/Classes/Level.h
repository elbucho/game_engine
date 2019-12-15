#ifndef LEVEL_H_
#define LEVEL_H_

#include "Graphics.h"
#include "Structs/Color.h"
#include "../Includes/tinyxml.h"

namespace GameEngine {
	class Level {
	public:
		Level(Graphics* graphics, const char* path);
		~Level();
		void Update();
		void Draw();

		bool IsLoaded() { return this->isLoaded; }
	private:
		Graphics* graphics;
		const char* levelName;
		TiXmlElement* levelDOM;
		bool isSolid;
		bool isLoaded;

		bool LoadXML(const char* path);
		void parseXML();
		Color bgColor;
	};
}

#endif