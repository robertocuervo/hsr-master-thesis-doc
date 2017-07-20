#pragma once
#include <json/json.h>
#include <glm/detail/type_vec3.hpp>

class JsonReader {

public:
	void parseJsonFile(const std::string pathToJsonFile);
	glm::vec3 getReferenceSphere1() const;
	glm::vec3 getReferenceSphere2() const;
	glm::vec3 getReferenceSphere3() const;
	glm::vec3 getCalibrationVertex1() const;
	glm::vec3 getCalibrationVertex2() const;
	glm::vec3 getCalibrationVertex3() const;
	std::vector<std::string> getStlFilePaths() const;
	double getFrequency() const;
	bool isReferenceCubeActivated() const;
	std::string getPathToMvmFile() const;
	std::string getPathToMvmReferenceFile() const;
	int getScreenWidth() const;
	int getScreenHeight() const;
private:
	Json::Value root;

};
