#pragma once

class CRobot3DOF;
static CRobot3DOF* pRobot3DOF;
void DefineFf(smatrix& F, vectorm& f, const vectorm& x);

class CRobot3DOF
{
public:
	CRobot3DOF();

	double m_theta1, m_theta2, m_theta3;
	double m_L1, m_L2, m_L3;
	void InitParams();

	int m_currentIndex;
	CDoubleArray m_ttheta1, m_ttheta2, m_ttheta3; // trajectory
	CDoubleArray m_xE, m_yE, m_zE; // end point
	CDoubleArray m_vxE, m_vyE, m_vzE; // velocity of the end point
	CDoubleArray m_axE, m_ayE, m_azE; // acceleration of the end point
	void InitTrajectory();

	CDoubleArray m_qtheta1, m_qtheta2, m_qtheta3; // position
	CDoubleArray m_vtheta1, m_vtheta2, m_vtheta3; // velocity
	CDoubleArray m_atheta1, m_atheta2, m_atheta3; // acceleration

	bool SolvingPosition();
	bool SolvingVelocity();
	bool SolvingAcceleration();
};