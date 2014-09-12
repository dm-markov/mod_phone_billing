#include "ui.hpp"

#include "../demay/format.hpp"
#include "../demay/scope_guard.hpp"

/*!	Обработчик сообщения '1' от формы View0
 *******************************************
 *	1) Сформировать меню "Заявки"
 *	@param UI_Control_ указатель на автомат
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
			"\t\t<input type=\"submit\" name=\"btn\" value=\"<\" title=\"Назад\">\r\n"
			"\t\t<b><u>Сверка счетов</u></b><br/>\r\n"
			"\t\t<table cellspacing=\"0\" cellpadding=\"1\">\r\n"
			"\t\t<tr><td><input type=\"submit\" name=\"btn\" value=\"1) Файловый доступ\" class=\"cell_btn\" title=\"Заявка 1) Файловый доступ\"/></td></tr>\r\n"
			"\t\t<tr><td><input type=\"submit\" name=\"btn\" value=\"2) Доступ к внешним устройствам\" class=\"cell_btn\" title=\"Заявка 2) К внешним устройствам\"/></td></tr>\r\n"
			"\t\t<tr><td><input type=\"submit\" name=\"btn\" value=\"3) Доступ к E-mail\" class=\"cell_btn\" title=\"Заявка 3) К E-mail\"/></td></tr>\r\n"
			"\t\t<tr><td><input type=\"submit\" name=\"btn\" value=\"4) Доступ к in.myskb.ru\" class=\"cell_btn\" title=\"Заявка 4) К in.myskb.ru\"/></td></tr>\r\n"
			"\t\t<tr><td><input type=\"submit\" name=\"btn\" value=\"5) Доступ к ПК ProView\" class=\"cell_btn\" title=\"Заявка 5) К ПК ProView\"/></td></tr>\r\n"
			"\t\t<tr><td><input type=\"submit\" name=\"btn\" value=\"6) Доступ к АРМ Мониторинг АТМ\" class=\"cell_btn\" title=\"Заявка 6) К АРМ Мониторинг АТМ\"/></td></tr>\r\n"
			"\t\t<tr><td><input type=\"submit\" name=\"btn\" value=\"7) План проведения стажировки\" class=\"cell_btn\" title=\"Заявка 7) План проведения стажировки\"/></td></tr>\r\n"
			"\t\t</table>\r\n"
			, next_view
			//, http_args("auth")
			//, http_args("user")
	);
}

/*!	Обработчик сообщения '9' от формы View0
 *******************************************
 *	1) Сформировать меню "Настройка"
 *	@param UI_Control_ указатель на автомат
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
			"\t\t<input type=\"submit\" name=\"btn\" value=\"<\" title=\"Назад\">\r\n"
			"\t\t<b><u>Заявки</u></b><br/>\r\n"
			"\t\t<table cellspacing=\"0\" cellpadding=\"1\">\r\n"
			"\t\t<tr><td><input type=\"submit\" name=\"btn\" value=\"1) Офисы\" class=\"cell_btn\" title=\"Заявка 1) Подразделения\"/></td></tr>\r\n"
			"\t\t<tr><td><input type=\"submit\" name=\"btn\" value=\"2) Секторы\" class=\"cell_btn\" title=\"Заявка 2) ИТ-специалисты\"/></td></tr>\r\n"
			"\t\t<tr><td><input type=\"submit\" name=\"btn\" value=\"3) ИТ-специалисты\" class=\"cell_btn\" title=\"Заявка 3) К E-mail\"/></td></tr>\r\n"
			"\t\t<tr><td><input type=\"submit\" name=\"btn\" value=\"4) Подчинения\" class=\"cell_btn\" title=\"Заявка 4) К in.myskb.ru\"/></td></tr>\r\n"
			"\t\t</table>\r\n"
			, http_args("auth")
			, next_view
			, http_args("user")
	);
}