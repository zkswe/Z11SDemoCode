/*
 * ZKCameraView.h
 *
 *  Created on: Mar 10, 2018
 *      Author: guoxs
 */

#ifndef _CONTROL_ZKCAMERAVIEW_H_
#define _CONTROL_ZKCAMERAVIEW_H_

#include "ZKBase.h"
#include "camera/ZKCamera.h"

class ZKCameraViewPrivate;

class ZKCameraView : public ZKBase {
	ZK_DECLARE_PRIVATE(ZKCameraView)

public:
	ZKCameraView(HWND hParentWnd);
	virtual ~ZKCameraView();

	ECameraStatusCode startPreview();
	ECameraStatusCode stopPreview();
	bool isPreviewing() const;

	ECameraStatusCode takePicture();

	void setPosition(const LayoutPosition &position);
	void setRotation(ERotation rotation);
	void setMirror(EMirror mirror);

	void setPictureCallback(ZKCamera::IPictureCallback *pCallback);
	void setErrorCodeCallback(ZKCamera::IErrorCodeCallback *pCallback);

protected:
	ZKCameraView(HWND hParentWnd, ZKBasePrivate *pBP);

	virtual void onBeforeCreateWindow(const Json::Value &json);
	virtual void onAfterCreateWindow(const Json::Value &json);
	virtual const char* getClassName() const { return ZK_CAMERAVIEW; }

	virtual void onDraw(HDC hdc);

private:
	void parseCameraViewAttributeFromJson(const Json::Value &json);

private:
	ZKCamera *mCameraPtr;
};

#endif /* _CONTROL_ZKCAMERAVIEW_H_ */
