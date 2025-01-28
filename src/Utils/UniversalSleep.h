#ifndef UNIVERSALSLEEP_H
#define UNIVERSALSLEEP_H

#include <iostream>

class UniversalSleep {
public:
	UniversalSleep();

	void initialiseSleep() {
		m_targetTime = 0.0f;
		m_elapsedTime = 0.0f;
		m_isSleeping = false;
	}

	void start(float waitTime) {
		m_targetTime = waitTime;
		m_elapsedTime = 0.0f;
		m_isSleeping = true;
	}

	void update(float dt) {
		if (m_isSleeping) {
			m_elapsedTime += dt;

			if (m_elapsedTime >= m_targetTime) {
				//Time has passed
				m_isSleeping = false;
				std::cout << "Timer has finished" << std::endl;
			}
		}
	}

	bool isCurrentlySleeping() const {
		return m_isSleeping;
	}

private:
	float m_targetTime;
	float m_elapsedTime;
	bool m_isSleeping;
};

#endif //UNIVERSALSLEEP_H