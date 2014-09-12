
/**************************************************************************************
 *
 *	���������� ����������������� ����������
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


//	����������, ���������� �� �������� "UI_View" (GoF)
//	������ ���������� ��������� �������� ��������� �� ��� "���������"
//	������� ���������� � UI_View � �� ���������� (UI_View0, UI_View1, ...),
//	�������������� ����������, ��������� � STD. �������� (block A �activities�) � ������ ���������
//	��������� ������ �����������. �������� ����������� � ������ UI_Control, � ������ � � �������
//	����������� ������� ������ UI_View.

class UI_Control;

class UI_View {
	friend class UI_Control;
	//HttpFormArgs<HttpFormArgs_EcodingPolicy_Multipart, HttpFormArgs_ErrorPolicy_ThrowException<std::runtime_error> >  const& http_args

	//! ���������� ��������� '<'
	virtual void ev_prev(std::string& html_output, HttpArgs const& http_args, DB_Handle&)	{ handler_not_exist(html_output, http_args, '<'); }

	//! ���������� ��������� '>'
	virtual void ev_next(std::string& html_output, HttpArgs const& http_args, DB_Handle&)	{ handler_not_exist(html_output, http_args, '>'); }

	//! ���������� ��������� '+'
	virtual void ev_plus(std::string& html_output, HttpArgs const& http_args, DB_Handle&)	{ handler_not_exist(html_output, http_args, '+'); }

	//! ���������� ��������� '-'
	virtual void ev_minus(std::string& html_output, HttpArgs const& http_args, DB_Handle&)	{ handler_not_exist(html_output, http_args, '-'); }

	//! ���������� ��������� '^'
	virtual void ev_up(std::string& html_output, HttpArgs const& http_args, DB_Handle&) 	{ handler_not_exist(html_output, http_args, '^'); }

	//! ���������� ��������� 'v'
	virtual void ev_down(std::string& html_output, HttpArgs const& http_args, DB_Handle&)	{ handler_not_exist(html_output, http_args, 'v'); }

	//! ���������� ��������� 'a'
	virtual void ev_char_a(std::string& html_output, HttpArgs const& http_args, DB_Handle&)	{ handler_not_exist(html_output, http_args, 'a'); }
	
	// ...

	//! ���������� ��������� 'z'
	virtual void ev_char_z(std::string& html_output, HttpArgs const& http_args, DB_Handle&)	{ handler_not_exist(html_output, http_args, 'z'); }

	//! ���������� ��������� '0'
	virtual void ev_0(std::string& html_output, HttpArgs const& http_args, DB_Handle&)		{ handler_not_exist(html_output, http_args, '0'); }

	//! ���������� ��������� '1'
	virtual void ev_1(std::string& html_output, HttpArgs const& http_args, DB_Handle&)		{ handler_not_exist(html_output, http_args, '1'); }

	//! ���������� ��������� '2'
	virtual void ev_2(std::string& html_output, HttpArgs const& http_args, DB_Handle&)		{ handler_not_exist(html_output, http_args, '2'); }

	//! ���������� ��������� '3'
	virtual void ev_3(std::string& html_output, HttpArgs const& http_args, DB_Handle&)		{ handler_not_exist(html_output, http_args, '3'); }

	//! ���������� ��������� '4'
	virtual void ev_4(std::string& html_output, HttpArgs const& http_args, DB_Handle&)		{ handler_not_exist(html_output, http_args, '4'); }

	//! ���������� ��������� '5'
	virtual void ev_5(std::string& html_output, HttpArgs const& http_args, DB_Handle&)		{ handler_not_exist(html_output, http_args, '5'); }

	//! ���������� ��������� '6'
	virtual void ev_6(std::string& html_output, HttpArgs const& http_args, DB_Handle&)		{ handler_not_exist(html_output, http_args, '6'); }

	//! ���������� ��������� '7'
	virtual void ev_7(std::string& html_output, HttpArgs const& http_args, DB_Handle&)		{ handler_not_exist(html_output, http_args, '7'); }

	//! ���������� ��������� '8'
	virtual void ev_8(std::string& html_output, HttpArgs const& http_args, DB_Handle&)		{ handler_not_exist(html_output, http_args, '8'); }

	//! ���������� ��������� '9'
	virtual void ev_9(std::string& html_output, HttpArgs const& http_args, DB_Handle&)		{ handler_not_exist(html_output, http_args, '9'); }

	//! ���������� ��������� '9'
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
	� ������������ UI_Control ��������� � ���������������� ��������� ���� ���������
	� ������������ � GoF::UI_View ������� ��������� ������� ������������ ����������
	� ������������ � GoF ��� ��������� �� ��������� ������� ������������ UI_View
*/
class UI_Control : public HttpFormArgs<HttpFormArgs_ErrorPolicy_ThrowException<std::runtime_error>, HttpFormArgs_EcodingPolicy_Multipart, std::string> {
	typedef std::map<std::string, std::string> http_form_args_pool_type;
	std::map<std::string, std::string> args_pool_;


	//! � ������������ UI_Control ��������� � ���������������� ��������� ���� ���������
	std::map<int const, UI_View* const> view_pool_;
	//! � ������������ � GoF::UI_View ������� ��������� ������� ������������ ����������
	//UI_View*	view_ptr_;
	//! � ������������ � GoF ��� ��������� �� ��������� ������� ������������ UI_View
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
	//! ������� ������� view_id, ������������ ��� ����������� ������ �� ������:
	//  "�� ��������� �����������" � ������� ���������� � UI_View::event_handler
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
	//! <h2>���������� ������� �������</h2>
	void ui_handler(std::string&, HttpArgs const&, DB_Handle&);
	void ui_handler_0(std::string&, DB_Handle&);

	std::string const http_args(char const* const name_ptr) const;

	std::string	html_output_;

};


class UI_View0 : public UI_View {
	//! ��������� ��� ������������ � ������, ������������ ���� "�������"
    virtual void ev_next(std::string&, HttpArgs const&, DB_Handle&);
};


class UI_View1 : public UI_View {
	//! ������������ ���� "������"
	virtual void ev_1(std::string&, HttpArgs const&, DB_Handle&);
	//! ������������ ���� "���������"
	virtual void ev_9(std::string&, HttpArgs const&, DB_Handle&);
};


class UI_View11 : public UI_View {
	//! ������ ������ ���������� ���� �������
	virtual void ev_1(std::string&, HttpArgs const&, DB_Handle&);
	//! ���������� ��������� '>'
    //virtual void ev_next(std::string&, HttpArgs const&, DB_Handle&);
};

class UI_View111 : public UI_View {
	//! ������ ������������� ����� "������ �� ��", ��� �������������� ������������� ����������
	virtual void ev_1(std::string&, HttpArgs const&, DB_Handle&);
	virtual void ev_2(std::string&, HttpArgs const&, DB_Handle&);
	virtual void ev_3(std::string&, HttpArgs const&, DB_Handle&);
	virtual void ev_4(std::string&, HttpArgs const&, DB_Handle&);
	virtual void ev_5(std::string&, HttpArgs const&, DB_Handle&);
	virtual void ev_6(std::string&, HttpArgs const&, DB_Handle&);
	virtual void ev_7(std::string&, HttpArgs const&, DB_Handle&);
	virtual void ev_8(std::string&, HttpArgs const&, DB_Handle&);
	virtual void ev_9(std::string&, HttpArgs const&, DB_Handle&);
	//! ������ ������������� ����� "������ �� ��"
	virtual void ev_plus(std::string&, HttpArgs const&, DB_Handle&);
	//! ������ �������� ����� "������ �� ��"
	virtual void ev_next(std::string&, HttpArgs const&, DB_Handle&);
};

class UI_View12 : public UI_View {
	//! ���������� ��������� '>'
    //virtual void ev_next(std::string&, HttpArgs const&, DB_Handle&);
};

class UI_View123 : public UI_View {
	//! ���������� ��������� '>'
    //virtual void ev_next(std::string&, HttpArgs const&, DB_Handle&);
};


#endif /* RC_INVOKED */
#endif /* _MOD_PRO_UI_HPP_ */
