#include "pch.h"
#include"CRobot3DOF.h"
#include "math.h"

CRobot3DOF::CRobot3DOF()
{
	InitParams();
	InitTrajectory();
	SolvingPosition();
	SolvingVelocity();
	SolvingAcceleration();
}
void CRobot3DOF::InitParams()
{	
	m_L1 = 100;
	m_L2 = 300;
	m_L3 = 200;

	m_theta1 = 0;
	m_theta2 = 0;
	m_theta3 = 0;
}
void CRobot3DOF::InitTrajectory()
{
	int t = 100;
	for (int i = 0; i <= t; i++)
	{	
		m_xE.Add(100 + 0.25 * i);
		m_yE.Add(100 + 0.1 * i);
		m_zE.Add(100 + 0.3 * i);

		m_vxE.Add(1);
		m_vyE.Add(1);
		m_vzE.Add(1);

		m_axE.Add(0);
		m_ayE.Add(0);
		m_azE.Add(i);
	}
	
}

//CRobot3DOF* pRobot3DOF = NULL;

void DefineFf(smatrix& F, vectorm& f, const vectorm& x)
{
	// input F_jacobian Matrix using Matlab
	// F is jacobian matrix
	// f is vector f

	F.SetSize(3);
	f.SetSize(3);

	double sigma_1 = pRobot3DOF->m_L3 * cos(x[1] + x[2]) + pRobot3DOF->m_L2 * cos(x[1]);
	double sigma_2 = pRobot3DOF->m_L3 * sin(x[1] + x[2]) + pRobot3DOF->m_L2 * sin(x[1]);

	F(0, 0) = -sin(x[0]) * sigma_1;

	F(0, 1) = -cos(x[0]) * sigma_2;

	F(0, 2) = -pRobot3DOF->m_L3 * sin(x[1] + x[2]) * cos(x[0]);

	F(1, 0) = cos(x[0]) * sigma_1;

	F(1, 1) = -sin(x[0]) * sigma_2;

	F(1, 2) = -pRobot3DOF->m_L3 * sin(x[1] + x[2]) * sin(x[0]);

	F(2, 0) = 0;

	F(2, 1) = sigma_1;

	F(2, 2) = pRobot3DOF->m_L3 * cos(x[1] + x[2]);

	f(0) = cos(x[0]) * sigma_1 - pRobot3DOF->m_xE[pRobot3DOF->m_currentIndex];

	f(1) = sin(x[0]) * sigma_1 - pRobot3DOF->m_yE[pRobot3DOF->m_currentIndex];

	f(2) = pRobot3DOF->m_L1 + pRobot3DOF->m_L3 * sin(x[1] + x[2]) + pRobot3DOF->m_L2 * sin(x[1])
		- pRobot3DOF->m_zE[pRobot3DOF->m_currentIndex];
}

bool CRobot3DOF::SolvingPosition()
{
	// TODO: Add your implementation code here.
	vectorm x(3);
	x[0] = PI / 4.0;
	x[1] = PI / 5.0;
	x[2] = PI / 6.0;

	pRobot3DOF = this;
	m_qtheta1.RemoveAll();
	m_qtheta2.RemoveAll();
	m_qtheta3.RemoveAll();

	bool res = true;

	for (int i = 0; i < m_xE.GetSize(); i++)
	{
		m_currentIndex = i;
		if (Newton_Raphson(x, DefineFf) == 0) {
			m_qtheta1.Add(x[0]);
			m_qtheta2.Add(x[1]);
			m_qtheta3.Add(x[2]);
		}
		else {
			m_qtheta1.Add(x[0]);
			m_qtheta2.Add(x[1]);
			m_qtheta3.Add(x[2]);
			res = false;
		}
	}

	return res;
}


bool CRobot3DOF::SolvingVelocity()
{
	// TODO: Add your implementation code here.
	bool res = true;

	m_vtheta1.RemoveAll();
	m_vtheta2.RemoveAll();
	m_vtheta3.RemoveAll();

	smatrix A(3);
	vectorm x(3), b(3);

	for (int i = 0; i < m_qtheta1.GetSize(); i++) 
	{

		double sigma_1 = m_L3 * cos(m_qtheta2[i] + m_qtheta3[i]) + m_L2 * cos(m_qtheta2[i]);
		double sigma_2 = m_L3 * sin(m_qtheta2[i] + m_qtheta3[i]) + m_L2 * sin(m_qtheta2[i]);

		A(0, 0) = -sin(m_qtheta1[i]) * sigma_1;
		A(0, 1) = -cos(m_qtheta1[i]) * sigma_2;
		A(0, 2) = -m_L3 * sin(m_qtheta2[i] + m_qtheta3[i]) * cos(m_qtheta1[i]);

		A(1, 0) = cos(m_qtheta1[i]) * sigma_1;
		A(1, 1) = -sin(m_qtheta1[i]) * sigma_2;
		A(1, 2) = -m_L3 * sin(m_qtheta2[i] + m_qtheta3[i]) * sin(m_qtheta1[i]);

		A(2, 0) = 0;
		A(2, 1) = sigma_1;
		A(2, 2) = m_L3 * cos(m_qtheta2[i] + m_qtheta3[i]);

		b[0] = m_vxE[i];
		b[1] = m_vyE[i];
		b[2] = m_vzE[i];

		if (Gauss_Jordan(A, b, x) != 0) { // ket qua giai sai
			res = false;
		}
		else {
			m_vtheta1.Add(x[0]);
			m_vtheta2.Add(x[1]);
			m_vtheta3.Add(x[2]);
		}
	}

	return res;
}


bool CRobot3DOF::SolvingAcceleration()
{
	// TODO: Add your implementation code here.
	bool res = true;

	m_atheta1.RemoveAll();
	m_atheta2.RemoveAll();
	m_atheta3.RemoveAll();

	smatrix A(3);
	smatrix J(3), Jdot(3);
	vectorm x(3), b(3); // b = A * x

	for (int i = 0; i < m_vtheta1.GetSize(); i++) 
	{

		double Jdot_sigma_1 = 1.5 * m_L3 * sin(m_qtheta1[i] + m_qtheta2[i] + m_qtheta3[i]);
		double Jdot_sigma_2 = 1.5 * m_L3 * cos(m_qtheta1[i] + m_qtheta2[i] + m_qtheta3[i]);
		double Jdot_sigma_3 = 0.5 * m_L3 * sin(m_qtheta2[i] - m_qtheta1[i] + m_qtheta3[i]);
		double Jdot_sigma_4 = 0.5 * m_L3 * cos(m_qtheta2[i] - m_qtheta1[i] + m_qtheta3[i]);
		double Jdot_sigma_5 = 2 * m_L3 * sin(m_qtheta2[i] + m_qtheta3[i]);
		double Jdot_sigma_6 = m_L2 * sin(m_qtheta1[i] + m_qtheta2[i]);
		double Jdot_sigma_7 = m_L2 * cos(m_qtheta1[i] + m_qtheta2[i]);

		Jdot(0, 0) = Jdot_sigma_4 - Jdot_sigma_7 - Jdot_sigma_2;
		Jdot(0, 1) = -Jdot_sigma_4 - Jdot_sigma_7 - Jdot_sigma_2;
		Jdot(0, 2) = m_L3 * sin(m_qtheta2[i] + m_qtheta3[i]) * sin(m_qtheta1[i]) 
				   - 2 * m_L3 * cos(m_qtheta2[i] + m_qtheta3[i]) * cos(m_qtheta1[i]);

		Jdot(1, 0) = -Jdot_sigma_3 - Jdot_sigma_6 - Jdot_sigma_1;
		Jdot(1, 1) = Jdot_sigma_3 - Jdot_sigma_6 - Jdot_sigma_1;
		Jdot(1, 2) = -2 * m_L3 * cos(m_qtheta2[i] + m_qtheta3[i]) * sin(m_qtheta1[i])
				   - m_L3 * sin(m_qtheta2[i] + m_qtheta3[i]) * cos(m_qtheta1[i]);

		Jdot(2, 0) = 0;
		Jdot(2, 1) = -Jdot_sigma_5 - m_L2 * sin(m_qtheta2[i]);
		Jdot(2, 2) = -Jdot_sigma_5;

		double sigma_1 = m_L3 * cos(m_vtheta2[i] + m_vtheta3[i]) + m_L2 * cos(m_vtheta2[i]);
		double sigma_2 = m_L3 * sin(m_vtheta2[i] + m_vtheta3[i]) + m_L2 * sin(m_vtheta2[i]);

		J(0, 0) = -sin(m_vtheta1[i]) * sigma_1;
		J(0, 1) = -cos(m_vtheta1[i]) * sigma_2;
		J(0, 2) = -m_L3 * sin(m_vtheta2[i] + m_vtheta3[i]) * cos(m_vtheta1[i]);

		J(1, 0) = cos(m_vtheta1[i]) * sigma_1;
		J(1, 1) = -sin(m_vtheta1[i]) * sigma_2;
		J(1, 2) = -m_L3 * sin(m_vtheta2[i] + m_vtheta3[i]) * sin(m_vtheta1[i]);

		J(2, 0) = 0;
		J(2, 1) = sigma_1;
		J(2, 2) = m_L3 * cos(m_vtheta2[i] + m_vtheta3[i]);

		A = Jdot + J;

		b[0] = m_axE[i];
		b[1] = m_ayE[i];
		b[2] = m_azE[i];

		if (Gauss_Jordan(A, b, x) != 0) { // ket qua giai sai
			res = false;
		}
		else {
			m_atheta1.Add(x[0]);
			m_atheta2.Add(x[1]);
			m_atheta3.Add(x[2]);
		}

	}

	return res;
}
