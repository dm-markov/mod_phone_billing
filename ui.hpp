
/**************************************************************************************
 *
 *	Контроллер пользовательского интерфейса
 *
 */
#pragma once
#ifndef _MOD_PRO_UI_HPP_
#define _MOD_PRO_UI_HPP_
#ifndef RC_INVOKED

#include <exception>
#include <string>
#include <map>

#include "http_form_args.hpp"
#include "../demay/http_form_args.hpp"
#include "db.hpp"
//#include "http.hpp"


//	реализация, основанная на паттерне "UI_View" (GoF)
//	Данная реализация упростила внесение изменений по оси "Состояние"
//	Введена абстракция – UI_View и ее реализации (UI_View0, UI_View1, ...),
//	сответствующие состояниям, описанным в STD. Действия (block A ‘activities’) и логика механизма
//	состояний строго разделяются. Действия реализуются в классе UI_Control, а логика – с помощью
//	производных модулей класса UI_View.

class UI_Control;

class UI_View {
	friend class UI_Control;
	//HttpFormArgs<HttpFormArgs_EcodingPolicy_Multipart, HttpFormArgs_ErrorPolicy_ThrowException<std::runtime_error> >  const& http_args

	//! обработчик сообщения '<'
	virtual void ev_prev(std::string& html_output, HttpArgs const& http_args, DB_Handle&)	{ handler_not_exist(html_output, http_args, '<'); }

	//! обработчик сообщения '>'
	virtual void ev_next(std::string& html_output, HttpArgs const& http_args, DB_Handle&)	{ handler_not_exist(html_output, http_args, '>'); }

	//! обработчик сообщения '+'
	virtual void ev_plus(std::string& html_output, HttpArgs const& http_args, DB_Handle&)	{ handler_not_exist(html_output, http_args, '+'); }

	//! обработчик сообщения '-'
	virtual void ev_minus(std::string& html_output, HttpArgs const& http_args, DB_Handle&)	{ handler_not_exist(html_output, http_args, '-'); }

	//! обработчик сообщения '^'
	virtual void ev_up(std::string& html_output, HttpArgs const& http_args, DB_Handle&) 	{ handler_not_exist(html_output, http_args, '^'); }

	//! обработчик сообщения 'v'
	virtual void ev_down(std::string& html_output, HttpArgs const& http_args, DB_Handle&)	{ handler_not_exist(html_output, http_args, 'v'); }

	//! обработчик сообщения 'a'
	virtual void ev_char_a(std::string& html_output, HttpArgs const& http_args, DB_Handle&)	{ handler_not_exist(html_output, http_args, 'a'); }
	
	// ...

	//! обработчик сообщения 'z'
	virtual void ev_char_z(std::string& html_output, HttpArgs const& http_args, DB_Handle&)	{ handler_not_exist(html_output, http_args, 'z'); }

	//! обработчик сообщения '0'
	virtual void ev_0(std::string& html_output, HttpArgs const& http_args, DB_Handle&)		{ handler_not_exist(html_output, http_args, '0'); }

	//! обработчик сообщения '1'
	virtual void ev_1(std::string& html_output, HttpArgs const& http_args, DB_Handle&)		{ handler_not_exist(html_output, http_args, '1'); }

	//! обработчик сообщения '2'
	virtual void ev_2(std::string& html_output, HttpArgs const& http_args, DB_Handle&)		{ handler_not_exist(html_output, http_args, '2'); }

	//! обработчик сообщения '3'
	virtual void ev_3(std::string& html_output, HttpArgs const& http_args, DB_Handle&)		{ handler_not_exist(html_output, http_args, '3'); }

	//! обработчик сообщения '4'
	virtual void ev_4(std::string& html_output, HttpArgs const& http_args, DB_Handle&)		{ handler_not_exist(html_output, http_args, '4'); }

	//! обработчик сообщения '5'
	virtual void ev_5(std::string& html_output, HttpArgs const& http_args, DB_Handle&)		{ handler_not_exist(html_output, http_args, '5'); }

	//! обработчик сообщения '6'
	virtual void ev_6(std::string& html_output, HttpArgs const& http_args, DB_Handle&)		{ handler_not_exist(html_output, http_args, '6'); }

	//! обработчик сообщения '7'
	virtual void ev_7(std::string& html_output, HttpArgs const& http_args, DB_Handle&)		{ handler_not_exist(html_output, http_args, '7'); }

	//! обработчик сообщения '8'
	virtual void ev_8(std::string& html_output, HttpArgs const& http_args, DB_Handle&)		{ handler_not_exist(html_output, http_args, '8'); }

	//! обработчик сообщения '9'
	virtual void ev_9(std::string& html_output, HttpArgs const& http_args, DB_Handle&)		{ handler_not_exist(html_output, http_args, '9'); }

	//! обработчик сообщения '9'
	void handler_not_exist(std::string&, HttpArgs const&, char);
public:
	virtual ~UI_View() {}
	//explicit UI_View(UI_Control const& http_form_args_ref):http_form_args_(http_form_args_ref), http_form_args_ptr_(0) {}
	//UI_View(UI_Control& http_form_args_ref):http_form_args_ref_(http_form_args_ref), http_form_args_ptr_(0) {}
	explicit UI_View(UI_Control* ui_control_ptr):/*http_form_args_ref_(http_form_args_ref),*/ ui_control_ptr_(ui_control_ptr) {}
	UI_View():ui_control_ptr_(0) {}
protected:
	//UI_Control&		http_form_args_ref_;
	UI_Control*		ui_control_ptr_;
};

/*!
	в конструкторе UI_Control создается и инициализируется множество всех состояний
	в соответствии с GoF::UI_View текущее состояние объекта определяется переменной
	в соответствии с GoF все зависимые от состояния запросы делегируются UI_View
*/
class UI_Control : public HttpFormArgs<HttpFormArgs_ErrorPolicy_ThrowException<std::runtime_error>, HttpFormArgs_EcodingPolicy_Multipart, std::string> {
	typedef std::map<std::string, std::string> http_form_args_pool_type;
	std::map<std::string, std::string> args_pool_;


	//! в конструкторе UI_Control создается и инициализируется множество всех состояний
	std::map<int const, UI_View* const> view_pool_;
	//! в соответствии с GoF::UI_View текущее состояние объекта определяется переменной
	//UI_View*	view_ptr_;
	//! в соответствии с GoF все зависимые от состояния запросы делегируются UI_View
	UI_View* view_str2ptr(std::string const& view_str) { 
		int view_id = ::atoi(view_str.c_str());
		std::map<int const, UI_View* const>::iterator view_pool_iter(view_pool_.find(view_id));
		if( view_pool_.end()==view_pool_iter ) {
			std::string err_str;
			::format(err_str, __FUNCTION__": view_str=%1 not exist in 'view_pool'", view_str);
			throw std::exception(err_str.c_str()); 
		}
		return view_pool_iter->second;
	}

	UI_View* view_arg2ptr() const { 
		http_form_args_pool_type::const_iterator http_args_iter(args_pool_.find("view"));
		if( args_pool_.end()!=http_args_iter ) {
			std::string view_str(http_args_iter->second);
			int view_id = ::atoi(view_str.c_str());
			std::map<int const, UI_View* const>::const_iterator view_pool_iter(view_pool_.find(view_id));
			if( view_pool_.end()==view_pool_iter ) {
				std::string err_str;
				::format(err_str, __FUNCTION__": view_str='%1' not exist in 'view_pool'", view_str);
				throw std::exception(err_str.c_str()); 
			}
			return view_pool_iter->second;
		}
		std::map<int const, UI_View* const>::const_iterator view_pool_iter(view_pool_.find(0));
		if( view_pool_.end()==view_pool_iter ) throw std::exception(__FUNCTION__": view_id='0' not exist in 'view_pool'"); 
		return view_pool_iter->second;
	}
protected:
	//typedef std::map<std::string, std::string> http_args_type;
	//char const* http_form_args_insert_pair_OLD(char const* name_ptr, char const* name_end, char const* value_ptr, char const* value_end);
	virtual char const* http_form_args_insert_pair(char const* name_ptr, char const* name_end, char const* value_ptr, char const* value_end);
public:
	virtual ~UI_Control();
	//void http_args_parse(char const* name_ptr, char const* name_end, char const* value_ptr, char const* value_end);
	//std::string const operator() (char const* const name_ptr) const;
	//std::string const operator() (std::string const& name_str) const;
	//std::string const input_hidden(char const* const name_ptr) const;
public:
/*
	//! вернуть текущий view_id, используется при формирвании текста об ошибке:
	//  "не найденном обработчике" и выбросе исключения в UI_View::event_handler
	int view_id(UI_View* view_ptr) { 
		std::map<int const, UI_View* const>::iterator std_map_iter(view_pool_.begin());
		while( view_pool_.end()!=std_map_iter ) {
			if( std_map_iter->second==view_ptr ) return std_map_iter->first;
			++std_map_iter;
		}
		return 3999999999;
	}

*/

	void sql_insert_prod_to_spec(std::string const& spec_str, std::string const& prod_str, std::string const& name_str, int amount);
	void sql_select_prods_for_slot(std::string const& rack_str);
	void sql_select_prods_for_spec(std::string const& spec_str);
	void sql_select_racks_for_prod(std::string const& prod_str);

	UI_Control();
	//! <h2>Обработчик событий сервера</h2>
	void ui_handler(std::string&, HttpArgs const&, DB_Handle&);
	void ui_handler_0(std::string&, DB_Handle&);

	std::string const http_args(char const* const name_ptr) const;

	std::string	html_output_;

};


class UI_View0 : public UI_View {
	//! проверить имя пользователя и пароль, сформировать меню "Главное"
    virtual void ev_next(std::string&, HttpArgs const&, DB_Handle&);
};


class UI_View1 : public UI_View {
	//! сформировать меню "Заявки"
	virtual void ev_1(std::string&, HttpArgs const&, DB_Handle&);
	//! сформировать меню "Настройка"
	virtual void ev_9(std::string&, HttpArgs const&, DB_Handle&);
};


class UI_View11 : public UI_View {
	//! выдать список настроеных прав доступа
	virtual void ev_1(std::string&, HttpArgs const&, DB_Handle&);
	//! обработчик сообщения '>'
    //virtual void ev_next(std::string&, HttpArgs const&, DB_Handle&);
};

class UI_View111 : public UI_View {
	//! выдать заполненяемую форму "Заявки на ФР", для редактирования существующего сотрудника
	virtual void ev_1(std::string&, HttpArgs const&, DB_Handle&);
	virtual void ev_2(std::string&, HttpArgs const&, DB_Handle&);
	virtual void ev_3(std::string&, HttpArgs const&, DB_Handle&);
	virtual void ev_4(std::string&, HttpArgs const&, DB_Handle&);
	virtual void ev_5(std::string&, HttpArgs const&, DB_Handle&);
	virtual void ev_6(std::string&, HttpArgs const&, DB_Handle&);
	virtual void ev_7(std::string&, HttpArgs const&, DB_Handle&);
	virtual void ev_8(std::string&, HttpArgs const&, DB_Handle&);
	virtual void ev_9(std::string&, HttpArgs const&, DB_Handle&);
	//! выдать заполненяемую форму "Заявки на ФР"
	virtual void ev_plus(std::string&, HttpArgs const&, DB_Handle&);
	//! выдать печатную форму "Заявки на ФР"
	virtual void ev_next(std::string&, HttpArgs const&, DB_Handle&);
};

class UI_View12 : public UI_View {
	//! обработчик сообщения '>'
    //virtual void ev_next(std::string&, HttpArgs const&, DB_Handle&);
};

class UI_View123 : public UI_View {
	//! обработчик сообщения '>'
    //virtual void ev_next(std::string&, HttpArgs const&, DB_Handle&);
};


#endif /* RC_INVOKED */
#endif /* _MOD_PRO_UI_HPP_ */
