#ifndef SU_UTILS_RUBYUTILS_H_
#define SU_UTILS_RUBYUTILS_H_

#include "RubyLib.h"
#include <string>

/*
* Need to be very careful about how these macros are defined, especially
* when compiling C++ code or C code with an ANSI C compiler.
*
* VALUEFUNC(f) is a macro used to typecast a C function that implements
* a Ruby method so that it can be passed as an argument to API functions
* like rb_define_method() and rb_define_singleton_method().
*
* VOIDFUNC(f) is a macro used to typecast a C function that implements
* either the "mark" or "free" stuff for a Ruby Data object, so that it
* can be passed as an argument to API functions like Data_Wrap_Struct()
* and Data_Make_Struct().
*/

#define VALUEFUNC(f) ((VALUE (*)(ANYARGS)) f)
#define VOIDFUNC(f)  ((RUBY_DATA_FUNC) f)
//判断SUAPI调用是否失败 失败则直接return
#define SUAPIERROR(res,fun,handel) res = fun; if (res != SU_ERROR_NONE){char h_str[100];sprintf(h_str,"%s:%d",#fun,res);puts_gms(h_str); handel GetRubyInterface(res);}

// Ruby interfaces for strings.

VALUE GetRubyInterface(const char *s);

std::string GetRubyString(VALUE value);


// Ruby interfaces for booleans.

inline VALUE GetRubyInterface(bool bValue) {
	return bValue ? Qtrue : Qfalse;
}


// Ruby interfaces for numbers.

inline VALUE GetRubyInterface(double value) {
	return rb_float_new(value);
}

inline VALUE GetRubyInterface(float value) {
	return rb_float_new((double)value);
}

inline VALUE GetRubyInterface(long value) {
	return rb_long2num_inline(value);
}

inline VALUE GetRubyInterface(int value) {
	return rb_int2inum(value);
}

inline VALUE GetRubyInterface(short value) {
	return rb_int2inum(value);
}

inline VALUE GetRubyInterface(char value) {
	return rb_int2inum(value);
}

inline VALUE GetRubyInterface(long long value) {
	return rb_int2inum(value);
}

inline double GetRubyDouble(VALUE obj) {
	return NUM2DBL(obj);
}

inline long long GetRubyLongLong(VALUE obj) {
	return NUM2LL(obj);
}

inline long GetRubyLong(VALUE obj) {
	return NUM2LONG(obj);
}

inline int GetRubyInt(VALUE obj) {
	return NUM2INT(obj);
}

inline char GetRubyChar(VALUE obj) {
	return NUM2CHR(obj);
}


inline char * get_bytes(VALUE v, long *len) {
	char* res = NULL;
	if (TYPE(v) == T_ARRAY) {
		*len = RARRAY_LEN(v);
		res = (char*)malloc(((*len) + 1) * sizeof(char));
		for (long i = 0; i < (*len); i++) {
			res[i] = GetRubyChar(rb_ary_entry(v, i));
		}
		res[*len] = '\0';
		return res;
	}
	else {
		return res;
	}
}

inline void release_bytes(char * str) {
	if (str != NULL) free(str);
}


inline VALUE get_ruby_array(unsigned char *ary, long len) {
	VALUE array = rb_ary_new2(len);
	for (long i = 0; i < len; i++) {
		rb_ary_store(array, i, GetRubyInterface(ary[i]));
	}
	return array;
}

inline VALUE get_ruby_array(char *ary, long len) {
	VALUE array = rb_ary_new2(len);
	for (long i = 0; i < len; i++) {
		rb_ary_store(array, i, GetRubyInterface(ary[i]));
	}
	return array;
}

inline void debug_log(const char *str) {
	FILE *fp = NULL;
	fopen_s(&fp, "D:/GMS.log", "a");
	fprintf(fp, "%s\n", str);
	fclose(fp);
}


inline void debug_log(long str) {
	FILE *fp = NULL;
	fopen_s(&fp, "D:/GMS.log", "a");
	fprintf(fp, "%ld\n", str);
	fclose(fp);
}

inline void debug_log(unsigned char *str) {
	FILE *fp = NULL;
	fopen_s(&fp, "D:/GMS.log", "a");
	fprintf(fp, "%s\n", str);
	fclose(fp);
}

inline void debug_log(char *str, int len) {
	FILE *fp = NULL;
	fopen_s(&fp, "D:/GMS.log", "a");
	for (int i = 0; i < len; i++) {
		fprintf(fp, "%5d,", ((int)str[i]));
		if ((len - 1) == i)
			fprintf(fp, "\n");
	}
	fclose(fp);
}

inline void debug_log(unsigned char *str, int len) {
	FILE *fp = NULL;
	fopen_s(&fp, "D:/GMS.log", "a");
	for (int i = 0; i < len; i++) {
		fprintf(fp, "%5d,", ((int)str[i]));
		if ((len - 1) == i)
			fprintf(fp, "\n");
	}
	fclose(fp);
}

#endif // SU_UTILS_RUBYUTILS_H_

