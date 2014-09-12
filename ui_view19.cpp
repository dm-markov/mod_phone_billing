#include "ui.hpp"

#include "../demay/format.hpp"
#include "../demay/scope_guard.hpp"



//!	получает сообщение от View0
//!
void UI_View1::ev_1(std::string& html_output, HttpArgs const& http_args, DB_Handle&) {
	UI_Control* ui_cont_ptr = 0;
	#ifdef _DEBUG
	function func("    "__FUNCTION__);
	#endif
	
	int next_view = 19;
	/*
	::format(ui_cont_ptr->html_output(),
			#ifdef _DEBUG
			"\r\n\t<!-- " __FUNCTION__ " -->\r\n\r\n"
			#endif
			"\t<form method=\"post\" enctype=\"multipart/form-data\">\r\n"
			"\t\t<input type=\"hidden\" name=\"auth\" value=\"%1\">\r\n"
			"\t\t<input type=\"hidden\" name=\"view\" value=\"%2\">\r\n" 
			//"\t\t<input type=\"hidden\" name=\"spec\" value=\"%3\">\r\n"
			"\t\t<input type=\"submit\" name=\"btn\" value=\"<\" title=\"Назад\">\r\n"
			//"\t\t<input type=\"submit\" name=\"btn\" value=\">\" title=\"Выбрать\">\r\n"
			"\t\t<b><u>Заявки</u></b><br/>\r\n"
			"\t\t<table cellspacing=\"0\" cellpadding=\"1\">\r\n"
			"\t\t<tr><td><input type=\"submit\" name=\"btn\" value=\"1) Офисы\" class=\"cell_btn\" title=\"Заявка 1) Подразделения\"/></td></tr>\r\n"
			"\t\t<tr><td><input type=\"submit\" name=\"btn\" value=\"2) Секторы\" class=\"cell_btn\" title=\"Заявка 2) ИТ-специалисты\"/></td></tr>\r\n"
			"\t\t<tr><td><input type=\"submit\" name=\"btn\" value=\"3) ИТ-специалисты\" class=\"cell_btn\" title=\"Заявка 3) К E-mail\"/></td></tr>\r\n"
			"\t\t<tr><td><input type=\"submit\" name=\"btn\" value=\"4) Подчинения\" class=\"cell_btn\" title=\"Заявка 4) К in.myskb.ru\"/></td></tr>\r\n"
			"\t\t<tr><td><input type=\"submit\" name=\"btn\" value=\"5) Доступ к ПК ProView\" class=\"cell_btn\" title=\"Заявка 5) К ПК ProView\"/></td></tr>\r\n"
			"\t\t<tr><td><input type=\"submit\" name=\"btn\" value=\"6) Доступ к АРМ Мониторинг АТМ\" class=\"cell_btn\" title=\"Заявка 6) К АРМ Мониторинг АТМ\"/></td></tr>\r\n"
			"\t\t<tr><td><input type=\"submit\" name=\"btn\" value=\"7) План проведения стажировки\" class=\"cell_btn\" title=\"Заявка 7) План проведения стажировки\"/></td></tr>\r\n"
			"\t\t</table>\r\n"
			, ui_cont_ptr->get_auth_str(), next_view, ui_cont_ptr->get_spec_str()
	);
	ScopeGuard sg_html_form_end(MakeGuard(&::html_form_end, ui_cont_ptr));
	*/
/********************************************************************************************************************
	std::string prod_str(ui_cont_ptr->get_prod_str().empty()?"1)":ui_cont_ptr->get_prod_str());
	//! из БД извлекаем записи оборудования, в которых в слоте указана строка "1)" или PROD
	ui_cont_ptr->sql_select_racks_for_prod(prod_str);

	//! в правом столбце формируем ссылку на картинку
	std::string::size_type offset = ui_cont_ptr->get_prod_str().find_first_of(":");
	if( std::string::npos!=offset ) {
		std::string img_str(ui_cont_ptr->get_prod_str(), 0, offset);
		img_str.append("/");
		img_str.append(ui_cont_ptr->get_prod_str(), offset+1, ui_cont_ptr->get_prod_str().length());
		ui_cont_ptr->html_output().append("\t\t</td><td><img src=\"");
		ui_cont_ptr->html_output().append(img_str);
		ui_cont_ptr->html_output().append(".jpg\">");
	} else ui_cont_ptr->html_output().append("\t\t</td><td>&nbsp;");

	ui_cont_ptr->html_output().append("</td></tr></table>\r\n");
********************************************************************************************************************/
}

