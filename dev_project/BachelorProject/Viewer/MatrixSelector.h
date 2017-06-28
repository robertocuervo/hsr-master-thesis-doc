#ifndef MATRIXSELECTOR_H
#define MATRIXSELECTOR_H
#include <vector>
#include <algorithm>
#include "target_frame_structs.h"
#include <memory>

enum StrategyType {
	HighestMinLuminosity,
	HighestAvgLuminosity,
	MovementAvg,
	Fixed
};

class Strategy {
public:
	virtual ~Strategy() = default;

	virtual int select(const std::vector<TransformData> transformData, const std::vector<LuminosityData> luminosityData) {
		return 0;
	};
};

class HighestMinimumLuminosity : public Strategy {
public:
	HighestMinimumLuminosity() : Strategy() {};

	int select(const std::vector<TransformData> transformData, const std::vector<LuminosityData> luminosityData) override {
		for (auto i = 0; i + 1 < transformData.size(); i += 2) {
			auto lowestMinimum = std::min(luminosityData.at(i + 1).min.x, std::min(luminosityData.at(i + 1).min.y, luminosityData.at(i + 1).min.z));
			highestMinimumLuminosity = std::max(lowestMinimum, highestMinimumLuminosity);
			if (highestMinimumLuminosity == lowestMinimum) {
				resultIndex = i;
			}
		}
		return resultIndex;
	}

private:
	float highestMinimumLuminosity = 0.0f;
	int resultIndex = 0;
};

class HighestAverageLuminosity : public Strategy {
public:
	int select(const std::vector<TransformData> transformData, const std::vector<LuminosityData> luminosityData) override {
		for (auto i = 0; i + 1 < transformData.size(); i += 2) {
			highestAverageLuminosity = std::max(glm::length(luminosityData.at(i + 1).average), highestAverageLuminosity);
			if (highestAverageLuminosity == glm::length(luminosityData.at(i + 1).average))
				resultIndex = i;
		}
		return resultIndex;
	}

private:
	float highestAverageLuminosity = 0.0f;
	int resultIndex = 0;
};

class First : public Strategy {
public:
	int select(const std::vector<TransformData> transformData, const std::vector<LuminosityData> luminosityData) override {
		return 0;
	}
};

class MatrixSelector {
public:
	MatrixSelector(int type) {
		switch (type) {
		case HighestMinLuminosity:
			strategy = std::unique_ptr<Strategy>(std::make_unique<HighestMinimumLuminosity>());
			break;
		case HighestAvgLuminosity:
			strategy = std::unique_ptr<Strategy>(std::make_unique<HighestAverageLuminosity>());
			break;
		case Fixed:
			strategy = std::unique_ptr<Strategy>(std::make_unique<First>());
			break;
		default:
			strategy = nullptr;
		}
	}

	int execute(const std::vector<TransformData> transformData, const std::vector<LuminosityData> luminosityData) const {
		return strategy->select(transformData, luminosityData);
	}

private:
	std::unique_ptr<Strategy> strategy;
};
#endif
