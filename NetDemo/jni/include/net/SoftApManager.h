#ifndef _NET_SOFT_AP_MANAGER_H_
#define _NET_SOFT_AP_MANAGER_H_

#include <vector>

#include "system/Thread.h"
#include "utils/MessageQueue.h"

typedef enum {
	E_SOFTAP_DISABLED,
	E_SOFTAP_ENABLING,
	E_SOFTAP_ENABLED,
	E_SOFTAP_DISABLING,
	E_SOFTAP_ENABLE_ERROR
} ESoftApState;

class SoftApManager {
public:
	SoftApManager();
	~SoftApManager();

	bool init();

	void setEnable(bool isEnable);
	bool isEnable() const;

	ESoftApState getSoftApState() const;

	const char* getIp() const;

	void setSsidAndPwd(const char *ssid, const char *pwd);

	const char* getSsid() const;
	const char* getPwd() const;

	class ISoftApStateListener {
	public:
		virtual ~ISoftApStateListener() { }
		virtual void handleSoftApState(ESoftApState state) = 0;
	};

	void addSoftApStateListener(ISoftApStateListener *pListener);
	void removeSoftApStateListener(ISoftApStateListener *pListener);

private:
	void updateSoftApState(ESoftApState state);

	typedef enum {
		E_MSGTYPE_ENABLE = 1,
		E_MSGTYPE_DISABLE,
		E_MSGTYPE_SET_SSID_PWD,
		E_MSGTYPE_QUIT_THREAD
	} EMessageType;

	class SoftApThread : public Thread {
	public:
		SoftApThread(SoftApManager &sam) : mSAM(sam) { }

		bool start();
		void stop();

	protected:
		virtual bool readyToRun();
		virtual bool threadLoop();

	private:
		SoftApManager &mSAM;
	};

private:
	MessageQueue mMsgQueue;

	ESoftApState mState;

	mutable Mutex mLock;

	std::vector<ISoftApStateListener *> mSoftApStateListenerList;
	mutable Mutex mListenerLock;

	SoftApThread mSoftApThread;
};

#endif	// _NET_SOFT_AP_MANAGER_H_
