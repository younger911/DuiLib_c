#pragma once
#include "CefBrowser/CefBrowserDll.h"
#include <share.h>
#include <functional>
#include "DuiLib/UIlib.h"

#define CEF_API __declspec(dllexport)
/***********************************************************
使用说明：
	1.在DuiLib::Create函数前调用InitCef初始化cef
	2.在MessageLoop()之后Quit
	3.继承实现ISetHandleSolt回调,函数中实现指定浏览器的回调实例
	4.继承实现OnAfterCreate函数中ResizeBrowser浏览器
***********************************************************/
//类名称
const TCHAR CCefBrowserUIClassName[] = L"CefBrowserUI";		
//控件名称
const TCHAR CCefBrowserUIItemInterface[] = L"CefBrowser";	

class ISetHandleSolt {
public:
	//浏览器回调实例指针设置函数
	virtual DuiLib::ILoadHandleSlot* GetILoadHandleSlot(std::wstring browser_name) { return NULL; }
	virtual DuiLib::ILifeSpanHandleSlot* GetILifeSpanHandleSlot(std::wstring browser_name) { return NULL; }
	virtual DuiLib::IDisplayHandleSolt* GetIDisplayHandleSolt(std::wstring browser_name){ return NULL; }
	virtual DuiLib::ILifeSpanFileDialogSolt* GetILifeSpanFileDialogSolt(std::wstring browser_name){ return NULL; }
};

class CEF_API CCefBrowserUI : public DuiLib::CControlUI {
public:
	CCefBrowserUI(HWND parent, ISetHandleSolt* set_handle = NULL);
	~CCefBrowserUI(void);

//DuiLib回调函数
public:
	LPCTSTR GetClass() const;
	LPVOID GetInterface(LPCTSTR pstrName);
	void SetAttribute(LPCTSTR pstrName, LPCTSTR pstrValue);
	void DoInit();
	//设置位置
	virtual void SetPos(RECT rc);
	//父容器调用设置显示与否
	virtual void SetInternVisible(bool bVisible = true);
	//设置是否显示
	virtual void SetVisible(bool bVisible = true);

//静态功能接口
public:
	//初始化CEF
	static void InitCef(HINSTANCE hInstance, std::wstring cache_path = L"", std::wstring log_file = L"");
	//退出CEF
	static void Quit();
	//开启cef消息循环
	static void StartCefMessageLoop();

//控件cef功能
public:
	//加载url
	void LoadURL(std::wstring url);
	//是否可以向前导航
	bool CanGoForward();
	//向前导航
	void GoForward();
	//重新加载
	void Reload();
	//忽略缓存加载
	void ReloadIgnoreCache();
	//停止加载
	void StopLoad();
	//可以向后导航
	bool CanGoBack();
	//向后导航
	void GoBack();
	//获取浏览器句柄
	CefWindowHandle GetHwnd();
	//设置缩放比例
	void SetZoomLevel(double zoomLevel);
	//获取当前Url
	CefString GetURL();
	//执行JS 参数为 一段完整的js代码 或者已经存在的js函数名加参数
	void ExectueJS(const CefString &jscode);
	//创建Cef浏览器窗口
	bool CreateCefWindow(CefString url,
		DuiLib::ILifeSpanHandleSlot* life_handle = NULL, 
		DuiLib::ILoadHandleSlot* load_handle = NULL,
		DuiLib::ILifeSpanFileDialogSolt* filedialog_handle = NULL,
		DuiLib::IDisplayHandleSolt* display_handle = NULL);
	//关闭浏览器
	void CloseCefWindow();
	//添加注册函数
	void SetFunction(const CefString &name, DuiLib::CustomFunction function);

private:
	//默认地址
	std::wstring url_;
	//cef功能接口对象
	DuiLib::CefBrowserDll browser_dll_;
	//设置load life 回调函数回调指针
	ISetHandleSolt* set_handle_;
	//父窗体句柄
	HWND parent_hwnd_;
	//浏览器名称
	std::wstring browser_name_;
	//是否创建完成
	bool is_created_;
};

