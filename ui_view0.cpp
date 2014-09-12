#include "ui.hpp"
/// #include "db.hpp" //< ��� �������� ����� ������������ � ������

#include "../demay/format.hpp"
#include "../demay/scope_guard.hpp"

/*!	���������� ��������� '>' �� ����� Login
 *******************************************
 *	1) ��������� ��� ������������ � ������
 *	2) ������������ ������� ���� ->
 *	�������� ���:
 *	    prod_slot = '';
 *	    Automate::sql_select_prods_for_rack(slot) ->
 *	        select PROD_ART, PROD_NAME, PROD_NOTE from PRODUCTS where PROD_SLOT=''
 *	@param UI_Control_ ��������� �� �������
 */
void UI_View0::ev_next(std::string& html_output, HttpArgs const& http_args, DB_Handle&) {
	#ifdef _DEBUG
	function func("\t"__FUNCTION__);
	#endif

	//! �������� ����� ������������ � ������
	if( "admin"==http_args("user") && "qwerty"==http_args("pass") ) {
		int next_view = 1; //!< �� �������� �������� ��� ������ ���������� ����� ������ View1
		::format(html_output,
				#ifdef _DEBUG
				"\r\n\t<!-- " __FUNCTION__ " -->\r\n\r\n"
				#endif
				"\t<form method=\"post\" enctype=\"multipart/form-data\">\r\n"
				"\t\t<input type=\"hidden\" name=\"view\" value=\"%1\">\r\n" 
				//"\t\t<input type=\"hidden\" name=\"auth\" value=\"%2\">\r\n"
				//"\t\t<input type=\"hidden\" name=\"user\" value=\"%3\">\r\n"
				//"\t\t<input type=\"submit\" name=\"btn\" value=\"<\" title=\"�����\">\r\n"
				"\t\t<b><u>������� ����</u></b><br/>\r\n"
				"\t\t<input type=\"submit\" name=\"btn\" value=\"1) ������ ������\" class=\"cell_btn\" title=\"������� 1) ������\"/><br/>\r\n"
				//"\t\t<input type=\"submit\" name=\"btn\" value=\"2) ���-�� ���\" class=\"cell_btn\" title=\"������� 2) ���-�� ���\"/><br/>\r\n"
				//"\t\t<input type=\"submit\" name=\"btn\" value=\"3) ���-�� ������\" class=\"cell_btn\" title=\"������� 3) ���-�� ������\"/><br/>\r\n"
				"\t\t<input type=\"submit\" name=\"btn\" value=\"9) ���������\" class=\"cell_btn\" title=\"������� 9) �����������������\"/><br/>\r\n"
				"\t</form>\r\n"
				, next_view
				//, http_args("auth")
				//, http_args("user")
		);
	} else html_output.assign("�������� ��� ������������ ��� ������"); return;// throw std::runtime_error("�������� ��� ������������ ��� ������"); 
}

