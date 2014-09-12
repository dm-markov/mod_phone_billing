#pragma once
#ifndef _HTTP_FORM_ARGS_HPP_INCLUDED
#define _HTTP_FORM_ARGS_HPP_INCLUDED
#ifndef RC_INVOKED

#include <algorithm>
#include <exception>
#include <string>
#include <map>


#include "../demay/format.hpp"

class HttpArgs {
public:
	//! пары <имя:значение>
	//! имя храним в 'std::string' для O-n поиска в 'std::map.find(...)'
	typedef std::map<std::string, std::string> args_pool_type;
public:
	virtual ~HttpArgs() {}
	HttpArgs(char const* data_ptr, char const* data_end, char const* delimit_ptr, char const* delimit_end) {
		////////////////////
		// enctag_plain = "text/plain"
		// enctag_multipart = "multipart/form-data"
		// enctag_urlencoded = "application/x-www-form-urlencoded";
		///////////
		static const char enctag_multipart[] = "multipart/form-data";
		static const char enctag_urlencoded[] = "application/x-www-form-urlencoded";
		//
		// 1) получены данные формы кодированные в формате "multipart/form-data"
		//
		//char const* const delimit_end = delimit_ptr + ::strlen(delimit_ptr);
		if( delimit_end!=std::search(delimit_ptr, delimit_end, enctag_multipart, enctag_multipart + sizeof(enctag_multipart)-1) ) {
			//
			// 1.1) получаем последовательность символов, являющуюся разделителем http-переменных
			//
			static const char boundary_tag[] = " boundary=";
			delimit_ptr = std::search(delimit_ptr, delimit_end, boundary_tag, boundary_tag + sizeof(boundary_tag)-1);
			if( delimit_end==delimit_ptr ) throw std::runtime_error(__FUNCTION__": Not found boundary in recieved data");
			delimit_ptr += sizeof(boundary_tag)-1;

			//
			// 1.2) отделяем пары имя:значение от другой пары последовательностю [delimit_ptr..delimit_end] 
			//
			char const* next_pair_ptr = data_end;
			while( data_end!=(next_pair_ptr = std::search(data_ptr, data_end, delimit_ptr, delimit_end)) ) {
				//
				// 1.2.1) имя переменной указано в двойных кавычках после " name="
				//
				static const char name_tag[] = " name=\"";
				char const* name_ptr = std::search(data_ptr, next_pair_ptr, name_tag, name_tag+sizeof(name_tag)-1);
				if( name_ptr!=next_pair_ptr ) {
					name_ptr += sizeof(name_tag)-1;
					char const* const name_end = std::find(name_ptr, next_pair_ptr, '"');
					if( name_end!=next_pair_ptr && '"'==*(name_ptr-1) ) {
						//
						// 1.2.2) значение переменной указано после "\r\n\r\n"
						//
						static const char crnl_tag[] = "\r\n\r\n";
						char const* value_ptr = std::search(name_end, next_pair_ptr, crnl_tag, crnl_tag+sizeof(crnl_tag)-1);
						if( value_ptr!=next_pair_ptr ) {
							value_ptr += sizeof(crnl_tag)-1;
							char const* const value_end = std::find_end(value_ptr, next_pair_ptr, crnl_tag+(sizeof(crnl_tag)-1)/2, crnl_tag+sizeof(crnl_tag)-1);
							if( value_end!=next_pair_ptr ) {
								std::string name_str(name_ptr, name_end);
								std::string value_str(value_ptr, value_end);
								//- http_args_insert_pair(name_ptr, name_end, value_ptr, value_end); ----------
								args_pool_type::iterator args_iter(args_pool_.find(name_str));
								if( args_pool_.end()!=args_iter ) {
									std::string msg_str; 
									::format(msg_str, __FUNCTION__"-> name '%1' already exist, current value '%2', new value '%3'\r\n", name_str, args_iter->second, value_str);
									throw std::runtime_error(msg_str.c_str());
								}
								// #ifdef _DEBUG
								// { std::string out_str; ::format(out_str, "\t\t%1 == '%2'\r\n", name_str, value_str); ::OutputDebugString(out_str.c_str()); }
								// #endif
								args_pool_.insert(std::make_pair(name_str, value_str));
							}
						}
					}
				}
				//
				// 1.2.3) передвигаемся к следующей паре имя:значение
				//
				data_ptr = ++next_pair_ptr;
			}
		} else 
			//
			// 2) получены данные формы кодированные в формате "application/x-www-form-urlencoded"
			//
			if( delimit_end!=std::search(delimit_ptr, delimit_end, enctag_urlencoded, enctag_urlencoded + sizeof(enctag_urlencoded)-1) ) {
				throw std::runtime_error(__FUNCTION__": Wrong recieved data encoding, format 'application/x-www-form-urlencoded' not implemented");
		} else throw std::runtime_error(__FUNCTION__": Wrong recieved data encoding, 'multipart/form-data' or 'application/x-www-form-urlencoded' expected");
	}
	std::string const& operator() (char const* name_ptr) const {
		// поскольку 'HttpArgs::operator()' возвращает ссылки ...
		static std::string const empty; // создаем всегда существующий объект ...
		args_pool_type::const_iterator args_iter(args_pool_.find(name_ptr));
		if( args_pool_.end()==args_iter ) return empty; // исключаем 'std::bad_allocaton' например в 'std::string.append(...)'
		return args_iter->second;
	}
protected:
	args_pool_type	args_pool_;
};





#endif /* RC_INVOKED */
#endif /* _HTTP_FORM_ARGS_HPP_INCLUDED */
