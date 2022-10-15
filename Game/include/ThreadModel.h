#pragma once

namespace ver
{
	class ThreadModel
	{
	public:
		ThreadModel()
		{
			static winrt::apartment_context ui;
			ui_tread = ui;
		}
	public:
		static winrt::apartment_context UIThread() {
			return ui_tread;
		}
	private:
		static winrt::apartment_context ui_tread;
	};

	winrt::apartment_context SwitchToUI()
	{
		return ThreadModel::UIThread();
	}
}