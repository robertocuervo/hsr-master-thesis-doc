#include "json_reader.h"
#include <fstream>
#include <iostream>
#include <filesystem>
#include <glm/detail/type_vec3.hpp>
#include <json/json.h>


glm::vec3 JsonReader::getReferenceSphere1() const {
	auto referenceSphere1X = this->root.get("referenceSphere1X", 0.0);
	auto referenceSphere1Y = this->root.get("referenceSphere1Y", 0.0);
	auto referenceSphere1Z = this->root.get("referenceSphere1Z", 0.0);
	return glm::vec3(referenceSphere1X.asFloat(), referenceSphere1Y.asFloat(), referenceSphere1Z.asFloat());
}

glm::vec3 JsonReader::getReferenceSphere2() const {
	auto referenceSphere2X = this->root.get("referenceSphere2X", 0.0);
	auto referenceSphere2Y = this->root.get("referenceSphere2Y", 0.0);
	auto referenceSphere2Z = this->root.get("referenceSphere2Z", 0.0);
	return glm::vec3(referenceSphere2X.asFloat(), referenceSphere2Y.asFloat(), referenceSphere2Z.asFloat());
}

glm::vec3 JsonReader::getReferenceSphere3() const {
	auto referenceSphere3X = this->root.get("referenceSphere3X", 0.0);
	auto referenceSphere3Y = this->root.get("referenceSphere3Y", 0.0);
	auto referenceSphere3Z = this->root.get("referenceSphere3Z", 0.0);
	return glm::vec3(referenceSphere3X.asFloat(), referenceSphere3Y.asFloat(), referenceSphere3Z.asFloat());
}

glm::vec3 JsonReader::getCalibrationVertex1() const {
	auto calibrationVertex1X = this->root.get("calibrationVertex1X", 0.0);
	auto calibrationVertex1Y = this->root.get("calibrationVertex1Y", 0.0);
	auto calibrationVertex1Z = this->root.get("calibrationVertex1Z", 0.0);
	return glm::vec3(calibrationVertex1X.asFloat(), calibrationVertex1Y.asFloat(), calibrationVertex1Z.asFloat());
}

glm::vec3 JsonReader::getCalibrationVertex2() const {
	auto calibrationVertex2X = this->root.get("calibrationVertex2X", 0.0);
	auto calibrationVertex2Y = this->root.get("calibrationVertex2Y", 0.0);
	auto calibrationVertex2Z = this->root.get("calibrationVertex2Z", 0.0);
	return glm::vec3(calibrationVertex2X.asFloat(), calibrationVertex2Y.asFloat(), calibrationVertex2Z.asFloat());
}

glm::vec3 JsonReader::getCalibrationVertex3() const {
	auto calibrationVertex3X = this->root.get("calibrationVertex3X", 0.0);
	auto calibrationVertex3Y = this->root.get("calibrationVertex3Y", 0.0);
	auto calibrationVertex3Z = this->root.get("calibrationVertex3Z", 0.0);
	return glm::vec3(calibrationVertex3X.asFloat(), calibrationVertex3Y.asFloat(), calibrationVertex3Z.asFloat());
}

std::vector<std::string> JsonReader::getStlFilePaths() const {
	auto stlFilePaths = this->root.get("stlFilePaths", "STL file path not found");
	std::vector<std::string> stlFilePathsResult;
	for (auto filePath : stlFilePaths) {
		stlFilePathsResult.push_back(filePath.asString());
	}
	return stlFilePathsResult;
}

double JsonReader::getFrequency() const {
	auto frequency = this->root.get("frequency", 0.0);
	return frequency.asDouble();
}

bool JsonReader::isReferenceCubeActivated() const {
	auto displayReferenceCube = this->root.get("displayReferenceCube", true);
	return displayReferenceCube.asBool();
}

std::string JsonReader::getPathToMvmFile() const {
	auto mvmFilePath = this->root.get("mvmFilePath", "mvmFilePath");
	return mvmFilePath.asString();
}

std::string JsonReader::getPathToMvmReferenceFile() const {
	auto mvmReferenceFilePath = this->root.get("mvmReferenceFilePath", "mvmReferenceFilePath");
	return mvmReferenceFilePath.asString();
}

int JsonReader::getScreenWidth() const {
	auto screenWidth = this->root.get("screenWidth", 1920);
	return screenWidth.asInt();
}

int JsonReader::getScreenHeight() const {
	auto sceenHeight = this->root.get("sceenHeight", 1080);
	return sceenHeight.asInt();
}


void JsonReader::parseJsonFile(const std::string pathToJsonFile) {
	if (std::experimental::filesystem::exists(pathToJsonFile)) {
		std::ifstream jsonFile(pathToJsonFile, std::ifstream::binary);
		Json::CharReaderBuilder builder;
		std::string errors;
		auto parseFromStreamOk = Json::parseFromStream(builder, jsonFile, &this->root, &errors);
		if (!parseFromStreamOk) {
			std::cerr << "Error at reading json: " << errors << "\n";
			throw std::logic_error{"Error at reading json configuration file"};
		}
	}
	else {
		std::cerr << "The given json file " + pathToJsonFile + " does not exist\n";
		throw std::invalid_argument{"The given json file does not exist"};
	}
}
