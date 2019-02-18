1. 将ui目录下UserIme.ftu文件拷贝到自己工程ui目录下；
	将activity目录下UserImeActivity.h和UserImeActivity.cpp文件拷贝到自己工程activity目录下；
	将logic目录下UserImeLogic.cc文件拷贝到自己工程logic目录下；
	
2. 点击编辑控件会跳转到UserIme.ftu界面，UserImeLogic.cc 的 onUI_InitIME回调函数会收到编辑控件传递过来的信息；其他操作与普通界面编程一致；

3. 输入完毕后，点击回车按钮或隐藏按钮，界面会退出，回车后会将输入的内容信息传递回编辑控件，这两个按键的处理在 UserImeActivity.cpp的onClick函数中
	// 处理回车键和隐藏键
    switch (pBase->getID()) {
    case ID_USERIME_BUTTON_ENTER:
	case ID_USERIME_BUTTON_NUMBER_ENTER:
		doneIMETextUpdate(sContentStr);
		break;
	case ID_USERIME_BUTTON_HIDE:
	case ID_USERIME_BUTTON_NUMBER_HIDE:
		cancelIMETextUpdate();
		break;
    }