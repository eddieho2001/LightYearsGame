#pragma once
#include<quill/Logger.h>
#include<memory>
#include "framework/Core.h"
#include "framework/Delegate.h"

namespace ly {
	class Object:public std::enable_shared_from_this<Object> {
	public:
		Object();
		bool IsPendingDestory() const { return mIsPendingDestory; }
		virtual ~Object();
		virtual void Destory();
		weak<Object> GetWeakRef();
		weak<const Object> GetWeakRef() const;
		Delegate<Object*> onDestory;
	private:
		bool mIsPendingDestory;
		quill::Logger* mlogger;
	};
}