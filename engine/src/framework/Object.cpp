#include "framework/Object.h"
#include<quill/Frontend.h>
#include<quill/LogMacros.h>
#include<quill/sinks/ConsoleSink.h>

namespace ly {
	Object::Object()
		: mIsPendingDestory{ false }
	{
		mlogger = quill::Frontend::create_or_get_logger("Object", quill::Frontend::create_or_get_sink<quill::ConsoleSink>("sink_id_1"));
		mlogger->set_immediate_flush(true);
	}

	Object::~Object()
	{
		LOG_INFO(mlogger, "Object Destoryed");
	}

	void Object::Destory()
	{
		mIsPendingDestory = true;
		onDestory.Broadcast(this);
	}

	weak<Object> Object::GetWeakRef()
	{
		return weak_from_this();
	}

	weak<const Object> Object::GetWeakRef() const
	{
		return weak_from_this();
	}

}
