#pragma once

static int g_Count = 0;

/**
 * 注册定时器
 * 在此数组中添加即可
 */
static S_ACTIVITY_TIMEER REGISTER_ACTIVITY_TIMER_TAB[] = {

	{1,  1000}, //定时器id=1 , 时间间隔1秒 ，单位毫秒
};

static void onUI_init(){
    //Tips :添加 UI初始化的显示代码到这里,如:mText1Ptr->setText("123");

}

static void onUI_quit() {

}


static void onProtocolDataUpdate(const SProtocolData &data) {
    // 串口数据回调接口
}

static bool onUI_Timer(int id){
	switch (id) {
	case 1:
		char buf[64] = {0};
		snprintf(buf, sizeof(buf), "%d + 1 = %d", g_Count, g_Count + 1);
        mTextview1Ptr->setText(buf);
        ++g_Count;
		break;
	}
    return true;
}


static bool onmainActivityTouchEvent(const MotionEvent &ev) {
    // 返回false触摸事件将继续传递到控件上，返回true表示该触摸事件在此被拦截了，不再传递到控件上
    return false;
}
