/*
 * ZKSlideWindow.h
 *
 *  Created on: Jul 3, 2017
 *      Author: guoxs
 */

#ifndef _WINDOW_ZKSLIDEWINDOW_H_
#define _WINDOW_ZKSLIDEWINDOW_H_

#include "ZKWindow.h"
#include "utils/VelocityTracker.h"

class ZKSlideWindowPrivate;

class ZKSlideWindow : public ZKWindow {
	ZK_DECLARE_PRIVATE(ZKSlideWindow)

public:
	ZKSlideWindow(HWND hParentWnd);
	virtual ~ZKSlideWindow();

public:
	class ISlideItemClickListener {
	public:
		virtual ~ISlideItemClickListener() { }
		virtual void onSlideItemClick(ZKSlideWindow *pSlideWindow, int index) = 0;
	};

	void setSlideItemClickListener(ISlideItemClickListener *pListener) {
		mSlideItemClickListenerPtr = pListener;
	}

	class ISlidePageChangeListener {
	public:
		virtual ~ISlidePageChangeListener() { }
		virtual void onSlidePageChange(ZKSlideWindow *pSlideWindow, int page) = 0;
	};

	void setSlidePageChangeListener(ISlidePageChangeListener *pListener);

	int getCurrentPage() const;
	int getPageSize() const;

	void turnToNextPage(bool isAnimatable = false);
	void turnToPrevPage(bool isAnimatable = false);

private:
	typedef struct {
		int curStatus;
		PBITMAP itemStatusPicTab[S_CONTROL_STATUS_TAB_LEN];
		int itemStatusTextColorTab[S_CONTROL_STATUS_TAB_LEN];
		string text;
	} SSlideItemInfo;

	typedef struct {
		SSlideItemInfo *itemList;
		int size;
	} SSlidePageInfo;

	typedef struct {
		SSlidePageInfo *pageList;
		int size;
	} SSlidePageInfosList;

protected:
	ZKSlideWindow(HWND hParentWnd, ZKBasePrivate *pBP);

	virtual void onBeforeCreateWindow(const Json::Value &json);
	virtual const char* getClassName() const { return ZK_SLIDEWINDOW; }

	virtual void onDraw(HDC hdc);
	virtual BOOL onTouchEvent(const MotionEvent &ev);
	virtual void onTimer(int id);

	void drawBackgroundBlt(HDC hdc);
	void drawItemsBlt(HDC hdc);
	void drawItems(HDC hdc);
	void drawItem(HDC hdc, const SSlideItemInfo &item, int xOffset, int yOffset);
	void drawIcon(HDC hdc, const SSlideItemInfo &item, int xOffset, int yOffset);
	void drawText(HDC hdc, const SSlideItemInfo &item, int xOffset, int yOffset);

private:
	BOOL isSliding() const { return mIsSliding; }
	BOOL needToRoll() const { return (mFirstPageXOffset % mPosition.mWidth != 0); }

	int hitItemIndex(int x, int y) const;

	const PBITMAP getItemCurStatusPic(const SSlideItemInfo &item) const;
	int getItemCurTextColor(const SSlideItemInfo &item) const;

	void _section_(zk) parseSlideWindowAttributeFromJson(const Json::Value &json);

private:
	UINT mRows;
	UINT mCols;

	SIZE mItemSize;
	SIZE mIconSize;

	PLOGFONT mLogFontPtr;
	int mFontSize;

	LayoutPadding mPadding;

	int mCurrentPage;
	int mFirstPageXOffset;
	int mFirstPageXOffsetOfDown;

	int mHitIndex;

	BOOL mIsSliding;
	BOOL mIsDamping;

	UINT mRollSpeed;
	int mCurRollSpeed;

	VelocityTracker mVelocityTracker;

	SSlidePageInfosList mSlidePageInfosList;

	ISlideItemClickListener *mSlideItemClickListenerPtr;

	HDC mBackgroundDC;
	HDC mItemsDC;

	bool mIsUsedItemsDC;
};

#endif /* _WINDOW_ZKSLIDEWINDOW_H_ */
