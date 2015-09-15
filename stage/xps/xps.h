/*
 * xps.h
 *
 *  Created on: Aug 13, 2015
 *      Author: igkiou
 */

#ifndef XPS_H_
#define XPS_H_

#include <string>
#include "XPS_Q8_drivers.h"
#include "XPS_Q8_errors.h"
#include "../stage.h"

namespace stage {

namespace xps {

class XpsTranslationStage : public TranslationStageInterface {
public:

	XpsTranslationStage();
	XpsTranslationStage(const std::string& ipAddress, int port, double timeOut,
						const std::string& group, const std::string positioner);

	bool isOpen() const override;
	void home() override;
	void moveto(double locationInMm) override;
	void translate(double distanceInMm) override;
	void moveinc(double distanceInMm, int numMovements) override;
	double getpos() const override;

private:
	std::string m_ipAddress;
	int m_port;
	int m_socketId;
	double m_timeOut;
	std::string m_group;
	std::string m_positioner;
	int m_errorCode;
};

}  // namespace xps

}  // namespace stage

#endif /* XPS_H_ */
