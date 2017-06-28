#include "mvm_parser.h"
#include <istream>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <array>
#include <bitset>

std::ostream& operator<<(std::ostream& out, const MvmFileCamera& camera) {
	out << "---- MvmFileCamera ----" << std::endl;
	out << "MvmFileCamera Number: " << int{camera.cameraNumber} << '\n';
	out << "Data Length: " << int{camera.bitDataLength} << '\n';
	out << "Step Number: " << camera.stepNumber << '\n';
	out << "Data Mapping: " << camera.dataMapping << '\n';
	auto index{0};
	for_each(camera.convertedLeds.cbegin(), camera.convertedLeds.cend(), [&](const auto led) {
		         out << "MvmLed " << index + 1 << ": " << std::to_string(led) << '\n';
		         out << "Luminosity " << index + 1 << ": " << std::to_string(int{camera.luminosities[index]}) << '\n';
		         index++;
	         });
	return out;
}

template <typename ResultType, unsigned N>
ResultType readIntegralBigEndian(const std::array<char, N> const& buffer, const unsigned offset = 0) {
	if (offset >= N) {
		throw std::logic_error{"offset must not be >= N"};
	}
	auto nOfByte = std::min(N - offset, sizeof(ResultType));
	ResultType res{};
	for (auto i = offset; i < nOfByte + offset; i++) {
		res <<= CHAR_BIT;
		//TODO check with Thomas, too low level and sure dangerous. But if I don't do this, a bit in the result is changed
		res += static_cast<int>(std::bitset<CHAR_BIT>(buffer[i]).to_ullong());
	}
	return res;
}

template <unsigned N>
void readRecursive(const std::array<char, N> const& buffer, const unsigned offset) {}

template <unsigned N, typename Next, typename...Types>
void readRecursive(std::array<char, N> const& buffer, const unsigned offset, Next& next, Types&... rest) {
	next = readIntegralBigEndian<Next>(buffer, offset);
	readRecursive(buffer, offset + sizeof(Next), rest...);
}

template <unsigned N, typename...Types>
void readAll(const std::array<char, N> const& buffer, Types&... rest) {
	readRecursive(buffer, 0, rest...);
}

std::streamoff MvmFileManager::getFileLength(std::ifstream& mvm_file) const {
	mvm_file.seekg(0, mvm_file.end);
	return mvm_file.tellg();
}

MvmFileCamera MvmFileManager::getCameraData(std::ifstream& mvm_file, const int fileIndex) const {
	MvmFileCamera camera{};
	mvm_file.seekg(fileIndex);
	std::array<char, cameraArrayLength> cameraData{};
	mvm_file.read(cameraData.data(), cameraArrayLength);
	readAll(cameraData, camera.cameraNumber, camera.bitDataLength, camera.stepNumber, camera.dataMapping,
	        camera.leds[0], camera.leds[1], camera.leds[2], camera.leds[3], camera.leds[4], camera.leds[5], camera.leds[6],
	        camera.leds[7], camera.leds[8], camera.leds[9], camera.leds[10], camera.leds[11], camera.leds[12], camera.leds[13],
	        camera.leds[14], camera.leds[15], camera.leds[16], camera.leds[17],
	        camera.luminosities[0], camera.luminosities[1], camera.luminosities[2], camera.luminosities[3],
	        camera.luminosities[4], camera.luminosities[5], camera.luminosities[6], camera.luminosities[7],
	        camera.luminosities[8], camera.luminosities[9], camera.luminosities[10],
	        camera.luminosities[11], camera.luminosities[12], camera.luminosities[13], camera.luminosities[14],
	        camera.luminosities[15], camera.luminosities[16], camera.luminosities[17]);
	camera.translateLedCoordinates();
	return camera;

}

Frame MvmFileManager::getFrameFromCameradata(const MvmFileCamera camera1, const MvmFileCamera camera2, const MvmFileCamera camera3) const {
	Frame frame{};
	frame.stepNumber = camera1.stepNumber;
	frame.timeStamp = frame.stepNumber / timeStampInterval;
	frame.leds = this->getLedsFromCameras(camera1, camera2, camera3);
	return frame;
}

std::vector<MvmLed> MvmFileManager::getLedsFromCameras(const MvmFileCamera camera1, const MvmFileCamera camera2, const MvmFileCamera camera3) const {
	std::vector<MvmLed> result{};
	for (size_t index = 0, ilen = camera1.convertedLeds.size(); index < ilen; ++index) {
		MvmLed led{};
		//		led.initPositions(camera1.convertedLeds.at(index), camera3.convertedLeds.at(index), -camera2.convertedLeds.at(index));
		led.initPositions(camera1.convertedLeds.at(index), camera2.convertedLeds.at(index), camera3.convertedLeds.at(index));
		//		led.initLuminosities(camera1.luminosities.at(index), camera3.luminosities.at(index), camera2.luminosities.at(index));
		led.initLuminosities(camera1.luminosities.at(index), camera2.luminosities.at(index), camera3.luminosities.at(index));
		result.push_back(led);
	}
	return result;
}

void MvmFileManager::swapCoordinates(Frame& frame) {
	std::transform(frame.leds.begin(), frame.leds.end(), frame.leds.begin(), [](MvmLed& led) {
		               auto tempPositionY = led.ledPosition.y;
		               led.ledPosition.y = led.ledPosition.z;
		               led.ledPosition.z = -tempPositionY;
		               auto tempLuminosityY = led.luminosities.y;
		               led.luminosities.y = led.luminosities.z;
		               led.luminosities.z = tempLuminosityY;
		               return led;
	               });
}

std::vector<Frame> MvmFileManager::getFramesFromMvmFile(const std::string pathTofile) {
	std::ifstream mvm_file(pathTofile, std::ios::in | std::ios::binary);
	static_assert(CHAR_BIT == 8, "Expecting char to consist of 8 bits");
	try {
		auto fileLenght = getFileLength(mvm_file);
		auto fileIndex{firstFileIndex};

		while (fileIndex < fileLenght) {
			auto camera1 = getCameraData(mvm_file, fileIndex);
			fileIndex += fileIndexOffset;
			auto camera2 = getCameraData(mvm_file, fileIndex);
			fileIndex += fileIndexOffset;
			auto camera3 = getCameraData(mvm_file, fileIndex);
			fileIndex += fileIndexOffset;
			auto frame = this->getFrameFromCameradata(camera1, camera2, camera3);
			this->frames.push_back(frame);
		}
		mvm_file.close();
		return this->frames;

	} catch (std::ifstream::failure e) {
		mvm_file.close();
		std::cerr << "Exception opening/reading/closing " + pathTofile + "\n";
		throw std::logic_error{"Exception opening/reading/closing mvn file"};
	}
	catch (...) {
		mvm_file.close();
		std::cerr << "Unhandled Exception opening/reading/closing mvn file\n";
		throw std::logic_error{"Unhandled Exception opening/reading/closing mvn file"};
	}
}

void MvmFileManager::transformLedCoordinates(std::vector<Frame>& frames) {
	std::for_each(frames.begin(), frames.end(), [](Frame& frame) {
		              swapCoordinates(frame);
	              });
}
