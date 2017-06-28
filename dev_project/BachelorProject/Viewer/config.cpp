#include "config.h"

double ConfigurationData::frequency = 200;
bool ConfigurationData::displayReferenceCube = false;
 std::string ConfigurationData::pathToMvmFile = "../Viewer/DemoData/mvm_File/tmjright7.mvm";
//const char* ConfigurationData::pathToMvmFile = "../Viewer/DemoData/mvm_File/tmjright7.mvm";
 std::string ConfigurationData::pathToMvmRefFile = "../Viewer/DemoData/mvm_File/tmjright1.mvm";
//const char* ConfigurationData::pathToMvmRefFile = "../Viewer/DemoData/mvm_File/tmjright1.mvm";
glm::vec3 ConfigurationData::referenceSphere1{glm::vec3(36.9f, -15.84f, 76.66f)};
glm::vec3 ConfigurationData::referenceSphere2{glm::vec3(55.58f, -22.26f, 76.82f)};
glm::vec3 ConfigurationData::referenceSphere3{glm::vec3(52.59f, -0.21f, 76.69f)};
glm::vec3 ConfigurationData::calibrationVertex1{glm::vec3(-9.96f, -11.84f, 35.24f)};
glm::vec3 ConfigurationData::calibrationVertex2{glm::vec3(9.76f, -11.9f, 35.1f)};
glm::vec3 ConfigurationData::calibrationVertex3{glm::vec3(0.33f, 8.04f, 35.14f)};
std::vector<std::string> ConfigurationData::stlFiles{ "../Viewer/DemoData/stl_File/CR.stl", "../Viewer/DemoData/stl_File/CL.stl", "../Viewer/DemoData/stl_File/FL.stl", "../Viewer/DemoData/stl_File/FR.stl", "../Viewer/DemoData/stl_File/Mandibular2_red_bin.stl", "../Viewer/DemoData/stl_File/Maxillary2_red_bin.stl" };
GLuint ConfigurationData::screenWidth = 1920;
GLuint ConfigurationData::screenHeight = 1080;
