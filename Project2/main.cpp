
#include <winsock2.h>
#include <windows.h>
#include "SketchUpAPI/sketchup.h"
#include <ruby.h>
#include <iostream>

#include "RubyUtils\RubyUtils.h"
VALUE plus(VALUE self, VALUE va, VALUE vb)
{
	int a = NUM2INT(va);
	int b = NUM2INT(vb);

	return INT2NUM(a + b);
}


VALUE save_skp_as(VALUE self, VALUE input_file, VALUE output_path, VALUE version_int) {
	SUModelVersion version_code = SUModelVersion_SU8;
	std::string i_f = GetRubyString(input_file);
	std::string o_f = GetRubyString(output_path);
	int version_n = GetRubyInt(version_int);
	switch (version_n)
	{
	case 15: version_code = SUModelVersion_SU2015; break;
	case 16: version_code = SUModelVersion_SU2016; break;

	case 17: version_code = SUModelVersion_SU2017; break;
	case 18: version_code = SUModelVersion_SU2018; break;
	/*default:
		version_code = SUModelVersion_SU8;*/
	}
	SUInitialize();
	SUModelRef model = SU_INVALID;
	auto result = SUModelCreateFromFile(&model, i_f.c_str());
	if (result != SU_ERROR_NONE)
	{
		return INT2NUM(result);
	}
	result = SUModelSaveToFileWithVersion(model, o_f.c_str(), version_code);
	if (result != SU_ERROR_NONE)
	{
		return INT2NUM(result);
	}
	SUModelRelease(&model);
	SUTerminate();
	return INT2FIX(version_n);
}

void Init_test() {
	VALUE p_lib = rb_define_module("Test");
	rb_define_module_function(p_lib, "plus", RUBY_METHOD_FUNC(plus), 2);
	rb_define_module_function(p_lib, "save_skp_as", RUBY_METHOD_FUNC(save_skp_as), 3);
}
