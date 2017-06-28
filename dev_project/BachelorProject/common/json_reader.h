#pragma once
#include <json/json.h>
#include "../Viewer/config.h"


class JsonReader {

public:
	JsonReader();
	void parseJsonFile(const std::string pathToJsonFile);
	void setUpConfigurationData() const;
private:
	Json::Value root;
	ConfigurationData configurationData;
	void getReferenceSphere1() const;
	void getReferenceSphere2() const;
	void getReferenceSphere3() const;
	void getCalibrationVertex1() const;
	void getCalibrationVertex2() const;
	void getCalibrationVertex3() const;
	void getStlFilePaths() const;
	void getFrequency() const;
	void getReferenceCubeBoolean() const;
	void getPathsToMvmFiles() const;
	void getScreenMeasures() const;
};
