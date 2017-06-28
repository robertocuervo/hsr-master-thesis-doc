#pragma once
#ifndef MVM_PARSER_H
#define MVM_PARSER_H
#include <vector>
#include "mvm_camera.h"
#include "../Viewer/frame.h"

class MvmFileManager {
public:
	static constexpr int fileIndexOffset = 256;
	static constexpr int firstFileIndex = 1024;
	static constexpr int cameraArrayLength = 62;
	static constexpr float timeStampInterval = 200;

	std::vector<Frame> getFramesFromMvmFile(const std::string pathTofile);
	void transformLedCoordinates(std::vector<Frame> &frames);
	static void swapCoordinates(Frame& frame);
private:
	std::vector<Frame> frames{};
	std::streamoff getFileLength(std::ifstream& mvm_file) const;
	MvmFileCamera getCameraData(std::ifstream& mvm_file, const int fileIndex) const;
	Frame getFrameFromCameradata(const MvmFileCamera camera1, const MvmFileCamera camera2, const MvmFileCamera camera3) const;
	std::vector<MvmLed> getLedsFromCameras(const MvmFileCamera camera1, const MvmFileCamera camera2, const MvmFileCamera camera3) const;
	
};
#endif
