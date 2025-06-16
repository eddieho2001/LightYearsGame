#include "framework/Object.h"
#include<quill/Frontend.h>
#include<quill/LogMacros.h>
#include<quill/sinks/ConsoleSink.h>

ly::Object::Object()
	: mIsPendingDestory{ false }
{
	mlogger = quill::Frontend::create_or_get_logger("Object", quill::Frontend::create_or_get_sink<quill::ConsoleSink>("sink_id_1"));
	mlogger->set_immediate_flush(true);
}

ly::Object::~Object()
{
	LOG_INFO(mlogger, "Object Destoryed");
}

void ly::Object::Destory()
{
	mIsPendingDestory = true;
}
