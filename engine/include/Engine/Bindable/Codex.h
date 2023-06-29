#pragma once
#include <Engine/Bindable/Bindable.h>
#include <concepts>
#include <concurrent_unordered_map.h>
#include <pplawait.h>

namespace ver
{
	class Codex
	{
	public:
		template<class T, typename ...Params> requires std::derived_from<T, Bindable>
		static concurrency::task<std::shared_ptr<T>> ResolveAsync(Graphics& gfx, Params&& ...p)noexcept
		{
			co_return co_await Get()._ResolveAsync<T>(gfx, std::forward<Params>(p)...);
		}
		static void Trim()noexcept
		{
			Get()._Trim();
		}
	private:

		template<class T, typename ...Params>
		concurrency::task<std::shared_ptr<T>> _ResolveAsync(Graphics& gfx, Params&& ...p)noexcept
		{
			auto key = T::GenerateUID(std::forward<Params>(p)...);

			auto it = binds.find(key);

			if (it == binds.end()) 
			{
				co_await winrt::resume_background();
				auto pointer = std::make_shared<T>();
				co_await pointer->InitializeAsync(gfx, std::forward<Params>(p)...);
				binds.insert({ std::move(key), pointer });
				co_return pointer;
			}
			co_return std::static_pointer_cast<T>(it->second);
		}
		void _Trim()noexcept
		{
			std::vector<const std::wstring*> todelete;
			todelete.reserve(binds.size());

			for (auto& bind : binds)
			{
				if (bind.second.use_count() == 1)
					todelete.push_back(&bind.first);
			}
			for (auto& bind : todelete)
				binds.unsafe_erase(*bind);
		}
		static Codex& Get()
		{
			static Codex codex;
			return codex;
		}
	private:
		concurrency::concurrent_unordered_map<std::wstring, std::shared_ptr<Bindable>> binds;
	};
}
