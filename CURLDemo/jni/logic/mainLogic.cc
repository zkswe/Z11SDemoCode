#pragma once
#include "uart/ProtocolSender.h"
#include "utils/TimeHelper.h"
#include "restclient-cpp/restclient.h"



#include "../curl/curl.h"
int testCURLSSL () {
    CURL *curl;
    CURLcode res;

    curl = curl_easy_init();
    if (curl)
    {
        curl_easy_setopt(curl, CURLOPT_URL, "https://www.baidu.com");
        /* google.com is redirected, so we tell LibCurl to follow redirection */
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
        /* SSL Options */
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER , 1);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST , 1);
        /* Provide CA Certs from http://curl.haxx.se/docs/caextract.html */
        curl_easy_setopt(curl, CURLOPT_CAINFO, "/etc/cacert.pem");

        /* Perform the request, res will get the return code */
        res = curl_easy_perform(curl);
        /* Check for errors */
        if(res != CURLE_OK)
            LOGD("curl_easy_perform() failed: %s\n", curl_easy_strerror(res));

        LOGD("success");
        /* Always cleanup */
        curl_easy_cleanup(curl);
    }

    return 0;
}



/**
 * 注册定时器
 * 填充数组用于注册定时器
 * 注意：id不能重复
 */
static S_ACTIVITY_TIMEER REGISTER_ACTIVITY_TIMER_TAB[] = {
	//{0,  6000}, //定时器id=0, 时间间隔6秒
	//{1,  1000},
};

/**
 * 当界面构造时触发
 */
static void onUI_init(){
    //Tips :添加 UI初始化的显示代码到这里,如:mText1Ptr->setText("123");

}

/**
 * 当切换到该界面时触发
 */
static void onUI_intent(const Intent *intentPtr) {
    if (intentPtr != NULL) {
        //TODO
    }
}

/*
 * 当界面显示时触发
 */
static void onUI_show() {

}

/*
 * 当界面隐藏时触发
 */
static void onUI_hide() {

}

/*
 * 当界面完全退出时触发
 */
static void onUI_quit() {

}

/**
 * 串口数据回调接口
 */
static void onProtocolDataUpdate(const SProtocolData &data) {

}

/**
 * 定时器触发函数
 * 不建议在此函数中写耗时操作，否则将影响UI刷新
 * 参数： id
 *         当前所触发定时器的id，与注册时的id相同
 * 返回值: true
 *             继续运行当前定时器
 *         false
 *             停止运行当前定时器
 */
static bool onUI_Timer(int id){
	switch (id) {

		default:
			break;
	}
    return true;
}

/**
 * 有新的触摸事件时触发
 * 参数：ev
 *         新的触摸事件
 * 返回值：true
 *            表示该触摸事件在此被拦截，系统不再将此触摸事件传递到控件上
 *         false
 *            触摸事件将继续传递到控件上
 */
static bool onmainActivityTouchEvent(const MotionEvent &ev) {
    switch (ev.mActionStatus) {
		case MotionEvent::E_ACTION_DOWN://触摸按下
			//LOGD("时刻 = %ld 坐标  x = %d, y = %d", ev.mEventTime, ev.mX, ev.mY);
			break;
		case MotionEvent::E_ACTION_MOVE://触摸滑动
			break;
		case MotionEvent::E_ACTION_UP:  //触摸抬起
			break;
		default:
			break;
	}
	return false;
}
static bool onButtonClick_Button1(ZKButton *pButton) {
    RestClient::Response r = RestClient::get("http://www.baidu.com");
    mTextview1Ptr->setText(r.body);
    return false;
}
static bool onButtonClick_Button2(ZKButton *pButton) {

    return false;
}

static bool onButtonClick_Button3(ZKButton *pButton) {
    RestClient::Response r = RestClient::get("https://www.baidu.com");
    mTextview1Ptr->setText(r.body);
    return false;
}

#include "json/json.h"
static time_t get_timestamp_from_net(tm* out) {
    RestClient::Response r = RestClient::get(
            "http://api.m.taobao.com/rest/api3.do?api=mtop.common.getTimestamp");
    if (r.code != 200) {
        mTextview1Ptr->setText("请求失败");
        return -1;
    }

    Json::Value root;   // will contains the root value after parsing.
    Json::Reader reader;
    bool parsingSuccessful = reader.parse(r.body, root );
    if ( !parsingSuccessful )
    {
        mTextview1Ptr->setText(reader.getFormattedErrorMessages());
        return -1;
    }
    mTextview1Ptr->setText(r.body);
    if (root.isMember("data")) {
        string timestamp_str = root["data"]["t"].asString();
        time_t t = atoi(timestamp_str.substr(0, 10) .c_str()); //返回值为毫秒单位
        if (out != NULL) {
          *out = *gmtime(&t);
        }
        return t;
    }
    return -1;
}

static bool onButtonClick_ButtonHttp(ZKButton *pButton) {
    EASYUICONTEXT->openActivity("httpActivity");
    return false;
}

static bool onButtonClick_ButtonHttps(ZKButton *pButton) {
    EASYUICONTEXT->openActivity("httpsActivity");
    return false;
}

static bool onButtonClick_ButtonWifi(ZKButton *pButton) {
    EASYUICONTEXT->openActivity("WifiSettingActivity");
    return false;
}
