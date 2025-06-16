#pragma once
#include<quill/Logger.h>

namespace ly {
	class Object {
	public:
		Object();
		bool IsPendingDestory() const {
			return mIsPendingDestory;
		}

		virtual ~Object();

		void Destory();
	private:
		bool mIsPendingDestory;
		quill::Logger* mlogger;
	};
}