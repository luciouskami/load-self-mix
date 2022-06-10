#pragma once
#include <Windows.h>
#include <set>
#include <filesystem>


namespace fs = std::filesystem;



namespace model_pack
{
	class dll_module
	{
	public:
		dll_module();
		virtual ~dll_module();
		dll_module(dll_module&) = delete;
		dll_module& operator=(dll_module&) = delete;
		static dll_module* GetInstance();
		
		[[nodiscard]] bool IsInit() const;

		void Attach();
		void Detach();

	private:
		void Init();
		void LoadModelPacks();
		void UnLoadModelPacks();

	private:

		static dll_module* instance_;
		bool is_init_{false};
		std::vector<HANDLE> mpq_handles_;

		HMODULE storm_dll_instance_;
		uintptr_t storm_266_address_;
		uintptr_t storm_252_address_;

		fs::path war3_root_dir;
		fs::path mpq_root_dir_;
	};
}
