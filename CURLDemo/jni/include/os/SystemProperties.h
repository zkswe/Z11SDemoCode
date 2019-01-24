/*
 * SystemProperties.h
 *
 *  Created on: Aug 19, 2017
 *      Author: guoxs
 */

#ifndef _OS_SYSTEM_PROPERTIES_H_
#define _OS_SYSTEM_PROPERTIES_H_

class SystemProperties {
public:
	static int setInt(const char *key, const int value);
	static int getInt(const char *key, int *value, const int defValue);

	static int setString(const char *key, const char *value);
	static int getString(const char *key, char *value, const char *defValue);

};


class SysPropUtil {
public:
	static int setString(std::string key, std::string value) {
        return SystemProperties::setString(key.c_str(), value.c_str());
	};

	static std::string getString(std::string key, std::string def) {
		char outBuf[128] = {0};
        SystemProperties::getString(key.c_str(), outBuf, def.c_str());
        return std::string(outBuf);
	}

	static int setInt(std::string key, int value) {

		return SystemProperties::setInt(key.c_str(), value);
	}

	static int getInt(std::string key, int def) {
		int out = 0;
		SystemProperties::getInt(key.c_str(), &out, def);
		return out;
	}
};

#endif /* _OS_SYSTEM_PROPERTIES_H_ */
