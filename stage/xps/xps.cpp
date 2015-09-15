/*
 * acquisition_utils//acquisition_utils/stage/xps/xps.cpp/xps.cpp
 *
 *  Created on: Sep 11, 2015
 *      Author: igkiou
 */

#include "xps.h"

namespace stage {

namespace xps {

XpsTranslationStage::XpsTranslationStage(const std::string& ipAddress,
									int port,
									double timeOut,
									const std::string& group,
									const std::string positioner) :
		m_ipAddress(ipAddress),
		m_port(port),
		m_socketId(),
		m_timeOut(timeOut),
		m_group(group),
		m_positioner(positioner),
		m_errorCode() {

	m_socketId = TCP_ConnectToServer(m_ipAddress.c_str(), m_port, m_timeOut);
	mexAssert(m_socketId >= 0);

	m_errorCode = GroupKill(m_socketId, m_group);
	mexAssert(m_errorCode == 0);

	m_errorCode = GroupInitialize(m_socketId, m_group);
	mexAssert(m_errorCode == 0);
}

XpsTranslationStage::XpsTranslationStage() :
	XpsTranslationStage("192.168.0.254", 5001, 60, "Group1", "Group1.Pos") { }

XpsTranslationStage::home() {
	m_errorCode = GroupKill(m_socketId, m_group.c_str());
	mexAssert(m_errorCode == 0);

	m_errorCode = GroupInitialize(m_socketId, m_group.c_str());
	mexAssert(m_errorCode == 0);

	m_errorCode = GroupHomeSearch(m_socketId, m_group.c_str());
	mexAssert(m_errorCode == 0);
}

XpsTranslationStage::moveto(double locationInMm) {
	m_errorCode = GroupMoveAbsolute(m_socket, m_positioner.c_str(), 1, &locationInMm);
	mexAssert(m_errorCode == 0);
}

XpsTranslationStage::translate(double distanceInMm) {
	m_errorCode = GroupMoveRelative(m_socketId, m_group.c_str(), 1, &distanceInMm);
	mexAssert(m_errorCode == 0);
}

XpsTranslationStage::moveinc(double distanceInMm, int numMovements) {
	for (int iterMovement = 0; iterMovement < numMovements; ++iterMovement) {
		translate(distanceInMm);
	}
}

double XpsTranslationStage::getpos() const {
	double position;
	m_errorCode = GroupPositionCurrentGet(m_socketId, m_group.c_str(), 1, &position);
	mexAssert(m_errorCode == 0);
	return position;
}

XpsTranslationStage::~XpsTranslationStage() {
	m_errorCode = GroupKill(m_socketId, m_group.c_str());
	mexAssert(m_errorCode == 0);
	TCP_CloseSocket(m_socket);
}

}  // namespace xps

}  // namespace stage

