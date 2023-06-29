#pragma once
#include <Controls/Keyboard.h>
#include <Controls/Mouse.h>

namespace UT
{
	class Window
	{
	private:
		class WindowClass
		{
		public:
			static const char* GetName()noexcept;
			static HINSTANCE GetInstance()noexcept;
		private:
			WindowClass() noexcept;
			~WindowClass();
			WindowClass(const WindowClass&) = delete;
			WindowClass& operator=(const WindowClass&) = delete;
			static constexpr const char* wndClassName = "Veritas Direct3D Window";
			static Window::WindowClass wndClass;
			HINSTANCE hInst;
		};
	public:
		Window(uint32_t width, uint32_t height, const char* name = "VTest");
		Window(const Window&) = delete;
		Window& operator=(const Window&) = delete;
	public:
		uint32_t GetWidth() const noexcept;
		uint32_t GetHeight() const noexcept;
		auto GetHandle()const noexcept { return hWnd.get(); }
		void EnableCursor() noexcept;
		void DisableCursor() noexcept;
		bool CursorEnabled() const noexcept;
		bool IsActive()const noexcept;
		void SetTitle(std::string_view title);

		std::optional<WPARAM> ProcessMessages()const noexcept;
	private:
		static LRESULT WINAPI HandleMsgSetup(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
		static LRESULT WINAPI HandleMsgThunk(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
		LRESULT HandleMsg(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

		void ConfineCursor() noexcept;
		void FreeCursor() noexcept;
		void ShowCursor() noexcept;
		void HideCursor() noexcept;
	public:
		ver::Keyboard kbd;
		ver::Mouse mouse;
	private:
		bool cursorEnabled = true;
		bool bLoadCallIssued = false;
		bool bGridEnabled = true;
		bool bResizeIssued = false;
		bool bRestyleIssued = false;
		bool bActive = true;
		uint32_t width;
		uint32_t height;
		wil::unique_hwnd hWnd;
		std::vector<BYTE> rawBuffer;
	};


}

