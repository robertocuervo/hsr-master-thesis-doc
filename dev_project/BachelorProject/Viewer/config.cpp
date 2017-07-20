#include "config.h"

JsonReader ConfigurationData::jsonReader = JsonReader();

std::string ConfigurationData::getPathToMvmFile() {
	return jsonReader.getPathToMvmFile();
}

std::string ConfigurationData::getPathToMvmRefFile() {
	return jsonReader.getPathToMvmReferenceFile();
}

double ConfigurationData::getFrequency() {
	return jsonReader.getFrequency();
}

bool ConfigurationData::getDisplayReferenceCube() {
	return jsonReader.isReferenceCubeActivated();
}

glm::vec3 ConfigurationData::getReferenceSphere1() {
	return jsonReader.getReferenceSphere1();
}

glm::vec3 ConfigurationData::getReferenceSphere2() {
	return jsonReader.getReferenceSphere2();
}

glm::vec3 ConfigurationData::getReferenceSphere3() {
	return jsonReader.getReferenceSphere3();
}

glm::vec3 ConfigurationData::getCalibrationVertex1() {
	return jsonReader.getCalibrationVertex1();
}

glm::vec3 ConfigurationData::getCalibrationVertex2() {
	return jsonReader.getCalibrationVertex2();
}

glm::vec3 ConfigurationData::getCalibrationVertex3() {
	return jsonReader.getCalibrationVertex3();
}

std::vector<std::string> ConfigurationData::getStlFilesPaths() {
	return jsonReader.getStlFilePaths();
}

GLuint ConfigurationData::getScreenWidth() {
	return jsonReader.getScreenWidth();
}

GLuint ConfigurationData::getScreenHeight() {
	return jsonReader.getScreenHeight();
}

void ConfigurationData::parseConfigFile(const std::string pathToJsonFile) {
	if (pathToJsonFile == "")
		jsonReader.parseJsonFile("D:\\Users\\Koni\\Documents\\GitHub\\BA\\BachelorProject\\Debug\\config.json");
	else
		jsonReader.parseJsonFile(pathToJsonFile);
}
