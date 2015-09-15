/*
 * stage.h
 *
 *  Created on: Aug 13, 2015
 *      Author: igkiou
 */

#ifndef STAGE_H_
#define STAGE_H_

#include "mex_utils.h"

namespace stage {

class TranslationStageInterface {
public:
	TranslationStageInterface() = default;
	TranslationStageInterface(const TranslationStageInterface& other) = delete;
	TranslationStageInterface& operator=(const TranslationStageInterface& other) = delete;

	virtual bool isOpen() const = 0;
	virtual void home() = 0;
	virtual void moveto(double locationInMm) = 0;
	virtual void translate(double distanceInMm) = 0;
	virtual void moveinc(double distanceInMm, int numMovements) = 0;
	virtual double getpos() const = 0;

	virtual ~TranslationStageInterface() = default;
};


class RotationStageInterface {
public:
	RotationStageInterface() = default;
	RotationStageInterface(const RotationStageInterface& other) = delete;
	RotationStageInterface& operator=(const RotationStageInterface& other) = delete;

	virtual bool isOpen() const = 0;
	virtual void home() = 0;
	virtual void moveto(double angleInDegrees) = 0;
	virtual void rotate(double angleInDegrees) = 0;
	virtual void moveinc(double angleInDegrees, int numMovements) = 0;
	virtual double getpos() const = 0;

	virtual ~RotationStageInterface() = default;
};

}  // namespace stage

#endif /* STAGE_H_ */
