#include "Level.h"
#include <stdio.h>
#include <string>

using namespace GameEngine;

Level::Level(Graphics* graphics, const char* path) {
	this->graphics = graphics;
	this->levelName = levelName;
	
	if (!this->LoadXML(path)) {
		this->isLoaded = false;
	}
	else {
		this->isLoaded = true;
	}
}

Level::~Level() {

}

void Level::Update() {

}

void Level::Draw() {
	printf("Drawing Background\n");
	this->graphics->SetBackgroundSolid(this->bgColor);
}

bool Level::LoadXML(const char* path) {
	TiXmlDocument doc(path);

	printf("File Path: %s\n", path);

	if (!doc.LoadFile()) {
		return false;
	}

	this->levelDOM = doc.FirstChildElement();
	const char* rootType = this->levelDOM->Attribute("type");

	if (strcmp(rootType, "static") == 0) {
		this->isSolid = true;
	}
	else {
		this->isSolid = false;
	}

	this->parseXML();

	return true;
}

void Level::parseXML() {
	if (this->isSolid) {
		TiXmlElement* bgElement = this->levelDOM->FirstChildElement();

		while (strcmp(bgElement->Value(), "background") != 0) {
			bgElement = bgElement->NextSiblingElement();
		}

		const char* bgRGBs = bgElement->Attribute("color");
		const char* alphas = bgElement->Attribute("alpha");

		int bgRGB, alpha;

		if (bgRGBs) {
			bgRGB = std::stoul(bgRGBs, nullptr, 16);
		}
		else {
			bgRGB = 16777215;			// White background by default
		}

		if (alphas) {
			alpha = atoi(alphas);
		}
		else {
			alpha = 255;				// Fully transparent by default
		}

		Color color;
		color.red = bgRGB >> 16;		// Extract the red value
		color.green = bgRGB >> 8 & 255;	// Extract the green value
		color.blue = bgRGB & 255;		// Extract the blue value
		color.alpha = alpha;

		this->bgColor = color;
	}
}