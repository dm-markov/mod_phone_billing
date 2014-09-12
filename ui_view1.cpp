#include "ui.hpp"

#include "../demay/format.hpp"
#include "../demay/scope_guard.hpp"

/*!	���������� ��������� '1' �� ����� View0
 *******************************************
 *	1) ������������ ���� "������"
 *	@param UI_Control_ ��������� �� �������
 */
void UI_View1::ev_1(std::string& html_output, HttpArgs const& http_args, DB_Handle&) {
	#ifdef _DEBUG
	function func("    "__FUNCTION__);
	#endif
	
	int next_view = 11;
	::format(html_output,
			#ifdef _DEBUG
			"\r\n\t<!-- " __FUNCTION__ " -->\r\n\r\n"
			#endif
			"\t<form method=\"post\" enctype=\"multipart/form-data\">\r\n"
			"\t\t<input type=\"hidden\" name=\"view\" value=\"%1\">\r\n" 
			"\t\t<input type=\"hidden\" name=\"auth\" value=\"%2\">\r\n"
			"\t\t<input type=\"hidden\" name=\"user\" value=\"%3\">\r\n"
			"\t\t<input type=\"submit\" name=\"btn\" value=\"<\" title=\"�����\">\r\n"
			"\t\t<b><u>������ ������</u></b><br/>\r\n"
			"\t\t<table cellspacing=\"0\" cellpadding=\"1\">\r\n"
			"\t\t<tr><td><input type=\"submit\" name=\"btn\" value=\"1) �������� ������\" class=\"cell_btn\" title=\"������ 1) �������� ������\"/></td></tr>\r\n"
			"\t\t<tr><td><input type=\"submit\" name=\"btn\" value=\"2) ������ � ������� �����������\" class=\"cell_btn\" title=\"������ 2) � ������� �����������\"/></td></tr>\r\n"
			"\t\t<tr><td><input type=\"submit\" name=\"btn\" value=\"3) ������ � E-mail\" class=\"cell_btn\" title=\"������ 3) � E-mail\"/></td></tr>\r\n"
			"\t\t<tr><td><input type=\"submit\" name=\"btn\" value=\"4) ������ � in.myskb.ru\" class=\"cell_btn\" title=\"������ 4) � in.myskb.ru\"/></td></tr>\r\n"
			"\t\t<tr><td><input type=\"submit\" name=\"btn\" value=\"5) ������ � �� ProView\" class=\"cell_btn\" title=\"������ 5) � �� ProView\"/></td></tr>\r\n"
			"\t\t<tr><td><input type=\"submit\" name=\"btn\" value=\"6) ������ � ��� ���������� ���\" class=\"cell_btn\" title=\"������ 6) � ��� ���������� ���\"/></td></tr>\r\n"
			"\t\t<tr><td><input type=\"submit\" name=\"btn\" value=\"7) ���� ���������� ����������\" class=\"cell_btn\" title=\"������ 7) ���� ���������� ����������\"/></td></tr>\r\n"
			"\t\t</table>\r\n"
			, next_view
			//, http_args("auth")
			//, http_args("user")
	);
}

/*!	���������� ��������� '9' �� ����� View0
 *******************************************
 *	1) ������������ ���� "���������"
 *	@param UI_Control_ ��������� �� �������
 */
void UI_View1::ev_9(std::string& html_output, HttpArgs const& http_args, DB_Handle&) {
	#ifdef _DEBUG
	function func("    "__FUNCTION__);
	#endif
	
	int next_view = 19;
	::format(html_output,
			#ifdef _DEBUG
			"\r\n\t<!-- " __FUNCTION__ " -->\r\n\r\n"
			#endif
			"\t<form method=\"post\" enctype=\"multipart/form-data\">\r\n"
			"\t\t<input type=\"hidden\" name=\"auth\" value=\"%1\">\r\n"
			"\t\t<input type=\"hidden\" name=\"view\" value=\"%2\">\r\n" 
			"\t\t<input type=\"hidden\" name=\"user\" value=\"%3\">\r\n"
			"\t\t<input type=\"submit\" name=\"btn\" value=\"<\" title=\"�����\">\r\n"
			"\t\t<b><u>������</u></b><br/>\r\n"
			"\t\t<table cellspacing=\"0\" cellpadding=\"1\">\r\n"
			"\t\t<tr><td><input type=\"submit\" name=\"btn\" value=\"1) �����\" class=\"cell_btn\" title=\"������ 1) �������������\"/></td></tr>\r\n"
			"\t\t<tr><td><input type=\"submit\" name=\"btn\" value=\"2) �������\" class=\"cell_btn\" title=\"������ 2) ��-�����������\"/></td></tr>\r\n"
			"\t\t<tr><td><input type=\"submit\" name=\"btn\" value=\"3) ��-�����������\" class=\"cell_btn\" title=\"������ 3) � E-mail\"/></td></tr>\r\n"
			"\t\t<tr><td><input type=\"submit\" name=\"btn\" value=\"4) ����������\" class=\"cell_btn\" title=\"������ 4) � in.myskb.ru\"/></td></tr>\r\n"
			"\t\t</table>\r\n"
			, http_args("auth")
			, next_view
			, http_args("user")
	);
}