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
#include "../stage.h"

namespace stage {

namespace xps {

class XpsTranslationStage : public TranslationStageInterface {
public:


private:
	std::string m_ipAddress;
	int m_socketId;
	int m_port;
	double m_timeOut;
	std::string m_group;


}  // namespace xps

}  // namespace stage

#endif /* XPS_H_ */
